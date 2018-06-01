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
        ProtocolType pduType;
        Payload userData;
        pdu >> pduType >> userData;
        pdu.rewind(); // Call the rewind function to restore the PDU state.
        checkType(pduType);
        return userData;
    }

    virtual ProtocolType getType() const = 0;

    virtual ~Protocol() = default;
protected:
    void checkType(ProtocolType pduType) const
    {
        if (pduType!= getType())
        {
            auto expect = ProtocolNameChecker::getChecker()->find(pduType);
            auto get = ProtocolNameChecker::getChecker()->find(getType());
            throw std::invalid_argument("The header shall be " + expect + ", but get " + get + "!");
         }
    }
};

/* Using the ProtocolType value as template parameter. */
template <ProtocolType type>
class ConcreteProtocol : public Protocol
{
public:
    virtual ProtocolType getType() const final
    {
        return type;
    }

};
template <>
class ConcreteProtocol <ProtocolType::PHY> : public Protocol
{
public:
    virtual PDU encode(const Payload &payload) const
    {
        PDU pdu{getType()};
        pdu << static_cast<BYTE>(payload.size()) << payload;
        return pdu;
    }

    virtual const Payload decode(const PDU &pdu) const
    {
        ProtocolType pduType;
        BYTE length;
        Payload userData;
        pdu >> pduType >> length >> userData;
        pdu.rewind(); // Call the rewind function to restore the PDU state.
        checkType(pduType);
        if(length != userData.size())
            throw std::invalid_argument("The payload size isn't correct!");
        return userData;
    }

    virtual ProtocolType getType() const
    {
        return ProtocolType::PHY;
    }
};

