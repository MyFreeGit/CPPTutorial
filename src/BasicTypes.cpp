#include "BasicTypes.hpp"

#include <algorithm>

PDU::PDU(ProtocolType type, const Payload &payload) : data(payload.size() + 1)
{
    data[0] = static_cast<BYTE>(type);
    std::copy(payload.begin(), payload.end(), ++data.begin());
}

PDU::PDU(Payload payload) : data(payload.size())
{
    std::copy(payload.begin(), payload.end(), data.begin());
}

const Payload PDU::getPayload() const
{
    Payload result(data.size() - 1);
    copy(data.begin() + 1, data.end(), result.begin());
    return result;
}

const ProtocolType PDU::getType() const
{
    return static_cast<ProtocolType>(data[0]);
}
