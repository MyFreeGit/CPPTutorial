#pragma once

#include <vector>
#include <algorithm>


using BYTE = unsigned char;
/* To simplify the coding, the payload is holds in vector. This will increase unnecessary temporary objects */
using Payload = std::vector<BYTE>;

/* To make the excise easy, each protocol header is only one byte, the value is indicate which protocol is*/
enum class ProtocolType : BYTE
{
    PHY = 1, MAC = 2, RLC = 3, PDCP = 4
};

/* Interface type is named base <Interface name>_<NE name> */
enum class InterfaceType
{
    UU_GNB, UU_UE, S1U_GNB
};

/* */
class PDU
{
public:
    PDU(ProtocolType type, const Payload &payload) : data(payload.size() + 1)
    {
        data[0] = static_cast<BYTE>(type);
        std::copy(payload.begin(), payload.end(), ++data.begin());
    }

    PDU(Payload payload) : data(payload.size())
    {
        std::copy(payload.begin(), payload.end(), data.begin());
    }

    /* Create a temporary Payload object return the payload without the header.*/
    const Payload getPayload() const
    {
        Payload result(data.size() - 1);
        copy(data.begin() + 1, data.end(), result.begin());
        return result;
    }

    const ProtocolType getType() const
    {
    	return static_cast<ProtocolType>(data[0]);
    }

    const Payload getFullPduData() const
    {
        return data;
    }

    const size_t getSize() const
    {
        return this->data.size();
    }
private:
    Payload data;
};
