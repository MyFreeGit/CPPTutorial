#include "Protocol.hpp"

#include <boost/functional/hash.hpp>

PDU Protocol::encode(const Payload &payload) const
{
    PDU pdu{getType(), payload};
    return pdu;
}

const Payload Protocol::decode(PDU &pdu) const
{
    ProtocolType pduType;
    pdu >> pduType;
    if (pduType!= getType())
        throw std::invalid_argument("The header shall be PHY.");

    Payload userData{};
    pdu >> userData;
    pdu.rewind();
    return userData;
}



PDU PHY::encode(const Payload &payload) const
{
    std::size_t hash = boost::hash_value(payload);
    Payload temp(payload.size() + HASH_KEY_SIZE);
    PDU pdu(getType());
    pdu << hash << payload;
    return pdu;
}

const Payload PHY::decode(PDU &pdu) const
{
    ProtocolType pduType;
    pdu >> pduType;
    if (pduType!= getType())
        throw std::invalid_argument("The header shall be PHY.");

    std::size_t targetHash;
    pdu >> targetHash;
    Payload userData;
    pdu >> userData;
    std::size_t hash = boost::hash_value(userData);
    pdu.rewind();

    if(hash != targetHash)
        throw std::invalid_argument("Hash verification failed!");

    return userData;
}


