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
    testCommonProtocol(PDCP(), ProtocolType::PDCP, payload);
    testCommonProtocol(PDCP(), ProtocolType::PDCP, empty);
}

TEST_F(ProtocolTest, Protocol_RLC)
{
    testCommonProtocol(RLC(), ProtocolType::RLC, payload);
    testCommonProtocol(RLC(), ProtocolType::RLC, empty);
}

TEST_F(ProtocolTest, Protocol_MAC)
{
    testCommonProtocol(MAC(), ProtocolType::MAC, payload);
    testCommonProtocol(MAC(), ProtocolType::MAC, empty);
}

TEST_F(ProtocolTest, Protocol_PHY)
{
    Payload target = {static_cast<Payload::value_type>(ProtocolType::PHY)};
    target.insert(target.end(), hashPart.begin(), hashPart.end());
    target.insert(target.end(), payload.begin(), payload.end());
    PHY phy{};
    PDU pdu = phy.encode(payload);

    EXPECT_EQ(target, pdu.getFullData());
    const Payload result = phy.decode(pdu);
    EXPECT_EQ(payload, result);
}

TEST_F(ProtocolTest, Protocol_PHY_Empty_Userdata)
{
    //ce3d17f2c5614cfe
    Payload target = {static_cast<Payload::value_type>(ProtocolType::PHY)};
    target.insert(target.end(), 8, 0x0);
    Payload empty{};
    target.insert(target.end(), empty.begin(), empty.end());

    PHY phy{};
    PDU pdu = phy.encode(empty);

    EXPECT_EQ(target, pdu.getFullData());
    const Payload result = phy.decode(pdu);
    EXPECT_EQ(payload, result);
}
}
