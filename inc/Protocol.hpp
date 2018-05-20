#pragma once
#include <stdexcept>
#include "BasicTypes.hpp"

class Protocol
{
public:
    virtual PDU encode(const Payload &payload) const;

    virtual const Payload decode(PDU &pdu) const;

    virtual ProtocolType getType() const = 0;
    virtual ~Protocol() = default;
};

class PHY : public Protocol
{
public:
    virtual PDU encode(const Payload &payload) const;

    virtual const Payload decode(PDU &pdu) const;

    virtual ProtocolType getType() const
    {
        return ProtocolType::PHY;
    }
private:
    static const int HASH_KEY_SIZE = sizeof(std::size_t) / sizeof(BYTE);
};

class MAC : public Protocol
{
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
