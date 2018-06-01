#include <gtest/gtest.h>
#include <vector>
#include "Protocol.hpp"

namespace
{
class ProtocolTest: public ::testing::Test
{
protected:
    Payload payload = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    Payload empty{};
    Payload hashPart = {0xFE, 0x4C, 0x61, 0xC5, 0xF2, 0x17, 0x3D, 0xCE,};

    void testCommonProtocol(const Protocol &prtcl, ProtocolType type, const Payload &payload)
    {
        using namespace std;
        PDU pdu = prtcl.encode(payload);
        EXPECT_EQ(type, pdu.getType());

        Payload target = {static_cast<Payload::value_type>(type)};
        target.insert(target.end(), payload.begin(), payload.end());
        EXPECT_EQ(target, pdu.getFullData());

        const Payload result = prtcl.decode(pdu);
        EXPECT_EQ(payload, result);

    }
};

TEST_F(ProtocolTest, Protocol_PDCP)
{
    testCommonProtocol(ConcreteProtocol<ProtocolType::PDCP>(), ProtocolType::PDCP, payload);
    testCommonProtocol(ConcreteProtocol<ProtocolType::PDCP>(), ProtocolType::PDCP, empty);
}

TEST_F(ProtocolTest, Protocol_RLC)
{
    testCommonProtocol(ConcreteProtocol<ProtocolType::RLC>(), ProtocolType::RLC, payload);
    testCommonProtocol(ConcreteProtocol<ProtocolType::RLC>(), ProtocolType::RLC, empty);
}

TEST_F(ProtocolTest, Protocol_MAC)
{
    testCommonProtocol(ConcreteProtocol<ProtocolType::MAC>(), ProtocolType::MAC, payload);
    testCommonProtocol(ConcreteProtocol<ProtocolType::MAC>(), ProtocolType::MAC, empty);
}

TEST_F(ProtocolTest, Protocol_PHY)
{
    ConcreteProtocol<ProtocolType::PHY> phy;
    PDU pdu = phy.encode(payload);
    EXPECT_EQ(ProtocolType::PHY, pdu.getType());

    Payload target = {static_cast<Payload::value_type>(ProtocolType::PHY), static_cast<BYTE>(payload.size())};
    target.insert(target.end(), payload.begin(), payload.end());
    EXPECT_EQ(target, pdu.getFullData());

    const Payload result = phy.decode(pdu);
    EXPECT_EQ(payload, result);
}
}
