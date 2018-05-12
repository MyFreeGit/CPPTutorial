#pragma once
#include <vector>
#include <memory>
#include "Protocol.hpp"

/* Interface is */
class Interface
{
public:
    /* Return a PDU only for easy to write UT case. To simplify the code there
     * is no error checking */
    PDU sendData(const Payload &payload)
    {
        auto iter = protocolStack.cbegin();
        PDU pdu = (*iter)->encode(payload);
        while(++iter != protocolStack.cend())
        {
            pdu = (*iter)->encode(pdu.getFullPduData());
        }
        return pdu;
    }

    Payload receiveData(PDU pdu)
    {
        auto rit = protocolStack.crbegin();
        Payload payload = (*rit)->decode(pdu);
        while(++rit != protocolStack.crend())
        {
            payload = (*rit)->decode(PDU(payload));
        }
        return payload;
    }

protected:
    void addProtocolAtBottom(Protocol *prtcl)
    {
        protocolStack.push_back(SharedPtrType(prtcl));
    }

private:
    using SharedPtrType = std::shared_ptr<Protocol>;
    std::vector<SharedPtrType> protocolStack;
};

class UU_GNB_Interface : public Interface
{
public:
    UU_GNB_Interface()
    {
        addProtocolAtBottom(new PDCP());
        addProtocolAtBottom(new RLC());
        addProtocolAtBottom(new MAC());
        addProtocolAtBottom(new PHY());
    }
};
