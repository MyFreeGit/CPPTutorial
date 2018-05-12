#include <gtest/gtest.h>
#include <vector>
#include "Protocol.hpp"

namespace
{
class ProtocolTest: public ::testing::Test
{
protected:
    Payload payload = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

    void testSingleProtocol(const Protocol &prtcl, ProtocolType type)
    {
        using namespace std;
        PDU pdu = prtcl.encode(payload);
        EXPECT_EQ(type, pdu.getType());
        EXPECT_EQ(payload, pdu.getPayload());
        Payload target = {static_cast<Payload::value_type>(type)};
        target.insert(target.end(), payload.begin(), payload.end());
        EXPECT_EQ(target, pdu.getFullPduData());

        const Payload result = prtcl.decode(pdu);
        EXPECT_EQ(payload, result);

    }
};

TEST_F(ProtocolTest, testAllProtocol)
{
    testSingleProtocol(PHY(), ProtocolType::PHY);
    testSingleProtocol(MAC(), ProtocolType::MAC);
    testSingleProtocol(RLC(), ProtocolType::RLC);
    testSingleProtocol(PDCP(), ProtocolType::PDCP);
}
}
