#pragma once
#include <stdexcept>
#include "BasicTypes.hpp"

class Protocol
{
public:
    virtual PDU encode(const Payload &payload) const
    {
        PDU pdu{getType(), payload};
        return pdu;
    }

    virtual const Payload decode(const PDU &pdu) const
    {
        if (pdu.getType() != getType())
            throw std::invalid_argument("The header is miss match.");
        return pdu.getPayload();
    }
    virtual ProtocolType getType() const = 0;
    virtual ~Protocol() = default;
};

class PHY : public Protocol
{
public:
    virtual ProtocolType getType() const
    {
        return ProtocolType::PHY;
    }
};

class MAC : public Protocol
{
public:
    virtual ProtocolType getType() const
    {
        return ProtocolType::MAC;
    }
};

class RLC : public Protocol
{
public:
    virtual ProtocolType getType() const
    {
        return ProtocolType::RLC;
    }
};

class PDCP : public Protocol
{
public:
    virtual ProtocolType getType() const
    {
        return ProtocolType::PDCP;
    }
};
