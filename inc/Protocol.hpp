#pragma once
#include <stdexcept>
#include "BasicTypes.hpp"

class Protocol
{
public:
    virtual PDU encode(const Payload &payload) const;

    virtual const Payload decode(const PDU &pdu) const;

    virtual ProtocolType getType() const = 0;
    virtual ~Protocol() = default;
protected:
    void checkType(ProtocolType pduType) const;
};

class PHY : public Protocol
{
    virtual PDU encode(const Payload &payload) const override;

    virtual const Payload decode(const PDU &pdu) const override;

    virtual ProtocolType getType() const override
    {
        return ProtocolType::PHY;
    }
};

class MAC : public Protocol
{
    virtual ProtocolType getType() const override
    {
        return ProtocolType::MAC;
    }
};

class RLC : public Protocol
{
public:
    virtual ProtocolType getType() const override
    {
        return ProtocolType::RLC;
    }
};

class PDCP : public Protocol
{
public:
    virtual ProtocolType getType() const override
    {
        return ProtocolType::PDCP;
    }
};

class PHYWithHash : public Protocol
{
public:
    virtual PDU encode(const Payload &payload) const override;

    virtual const Payload decode(const PDU &pdu) const override;

    virtual ProtocolType getType() const override
    {
        return ProtocolType::PHY;
    }
private:
    static const int HASH_KEY_SIZE = sizeof(std::size_t) / sizeof(BYTE);
};
