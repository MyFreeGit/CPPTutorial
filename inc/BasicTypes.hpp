#pragma once

#include <vector>
#include <iterator>
#include <iostream>

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
    PDU(ProtocolType type, const Payload &payload);

    PDU(Payload payload);

    PDU(ProtocolType type);

    PDU() = delete;

    const ProtocolType getType() const;

    const Payload getFullData() const
    {
        return data;
    }

    void rewind()
    {
        readPos = 0;
    }

    PDU& operator << (ProtocolType type)
    {
        data.push_back(static_cast<BYTE>(type));
        return *this;
    }

    PDU& operator << (std::size_t value)
    {
        BYTE *p = (BYTE*)&value;
        data.insert(data.end(), (BYTE*)&value, (BYTE*)&value + SIZE_T_SIZE);
        return *this;
    }

    PDU& operator << (const Payload &userData)
    {
        data.insert(data.end(), userData.begin(), userData.end());
        return *this;
    }

    void operator >> (ProtocolType &target)
    {
        target = static_cast<ProtocolType>(data[readPos++]);
    }

    void operator >> (std::size_t &target)
    {
        if(data.size() - readPos < SIZE_T_SIZE)
            throw std::invalid_argument("No enough data left for std::size_t value.");
        target = 0;
        for(int i = 0; i < SIZE_T_SIZE; i++)
        {
            target |= (static_cast<std::size_t>(data[readPos++]) << (i * 8));
        }
    }

    void operator >> (Payload &target)
    {
        target.insert(target.end(), data.begin() + readPos, data.end());
        readPos = data.size();
    }

    const std::size_t getSize() const
    {
        return this->data.size();
    }

private:
    /* How many BYTEs the std::size_t will takes*/
    static const int SIZE_T_SIZE = sizeof(std::size_t) / sizeof(BYTE);

    /* Couldn't use iterator type to records the read position, due to the data maybe re-allocated,
     * when the vector's size is growing*/
    int readPos;

    Payload data;
};

