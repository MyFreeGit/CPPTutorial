#pragma once
#include <stdexcept>
#include <functional>
#include "BasicTypes.hpp"

class Protocol
{
public:
    virtual PDU encode(const Payload &payload) const = 0;

    virtual const Payload decode(const PDU &pdu) const = 0;

    virtual ~Protocol() = default;
};

struct NormalEncoder
{
    static PDU encode(ProtocolType type, const Payload &payload)
    {
        PDU pdu { type, payload };
        return pdu;
    }
};

struct NormalDecoder
{
    static const Payload decode(ProtocolType type, const PDU &pdu)
    {
        ProtocolType pduType;
        Payload userData;
        pdu >> pduType >> userData;
        pdu.rewind(); // Call the rewind function to restore the PDU state.
        return userData;
    }
};

template < ProtocolType type,
          typename Encoder = NormalEncoder,
          typename Decoder = NormalDecoder>
class ConcreteProtocol : public Protocol
{
public:
    PDU encode(const Payload &payload) const final
    {
        return Encoder::encode(type, payload);
    }

    const Payload decode(const PDU &pdu) const final
    {
        return Decoder::decode(type, pdu);
    }
};

struct DataCountingEncoder
{
    static PDU encode(ProtocolType type, const Payload &payload)
    {
        PDU pdu{type};
        pdu << static_cast<BYTE>(payload.size()) << payload;
        return pdu;
    }
};

struct DataCountingDecoder
{
    static const Payload decode(ProtocolType type, const PDU &pdu)
    {
        ProtocolType pduType;
        BYTE length;
        Payload userData;
        pdu >> pduType >> length >> userData;
        pdu.rewind(); // Call the rewind function to restore the PDU state.
        if(length != userData.size())
            throw std::invalid_argument("The payload size isn't correct!");
        return userData;
    }
};

template <>
class ConcreteProtocol<ProtocolType::PHY>: public Protocol
{
public:
    PDU encode(const Payload &payload) const final
    {
        return DataCountingEncoder::encode(ProtocolType::PHY, payload);
    }

    const Payload decode(const PDU &pdu) const final
    {
        return DataCountingDecoder::decode(ProtocolType::PHY, pdu);
    }

};
