#include "Protocol.hpp"

#include <boost/functional/hash.hpp>
#include <string>

void Protocol::checkType(ProtocolType pduType) const
{
    if (pduType!= getType())
    {
        auto expect = ProtocolNameChecker::getChecker()->find(pduType);
        auto get = ProtocolNameChecker::getChecker()->find(getType());
        throw std::invalid_argument("The header shall be " + expect + ", but get " + get + "!");
     }
}

PDU Protocol::encode(const Payload &payload) const
{
    PDU pdu{getType(), payload};
    return pdu;
}

const Payload Protocol::decode(const PDU &pdu) const
{
    // Remove the const from pdu to call the >> operator
    PDU *pPDU = const_cast<PDU*>(&pdu);
    ProtocolType pduType;
    Payload userData;
    (*pPDU) >> pduType >> userData;
    pPDU->rewind(); // Call the rewind function to restore the PDU state.
    checkType(pduType);
    return userData;
}

PDU PHY::encode(const Payload &payload) const
{
    PDU pdu{getType()};
    pdu << static_cast<BYTE>(payload.size()) << payload;
    return pdu;
}

const Payload PHY::decode(const PDU &pdu) const
{
    // Remove the const from pdu to call the >> operator
    PDU *pPDU = const_cast<PDU*>(&pdu);
    ProtocolType pduType;
    BYTE length;
    Payload userData;
    (*pPDU) >> pduType >> length >> userData;
    pPDU->rewind(); // Call the rewind function to restore the PDU state.
    checkType(pduType);
    if(length != userData.size())
        throw std::invalid_argument("The payload size isn't correct!");
    return userData;
}

PDU PHYWithHash::encode(const Payload &payload) const
{
    std::size_t hash = boost::hash_value(payload);
    Payload temp(payload.size() + HASH_KEY_SIZE);
    PDU pdu(getType());
    pdu << hash << payload;
    return pdu;
}

const Payload PHYWithHash::decode(const PDU &pdu) const
{
    PDU *pPDU = const_cast<PDU*>(&pdu);

    ProtocolType pduType;
    Payload userData;
    std::size_t targetHash;
    (*pPDU) >> pduType >> targetHash >> userData;
    pPDU->rewind();

    if (pduType!= getType())
        throw std::invalid_argument("The header shall be PHY.");

    std::size_t hash = boost::hash_value(userData);

    if(hash != targetHash)
        throw std::invalid_argument("Hash verification failed!");

    return userData;
}


