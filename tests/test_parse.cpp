//
// Created by fbdtemme on 25/01/2020.
//

#include <catch2/catch_test_macros.hpp>
#include <termcontrol/termcontrol.hpp>

TEST_CASE("test parse")
{
    auto s = termcontrol::total_control_sequences_length("Test\033[2m]BlahBlah\033[1AEnd");
    CHECK(s == 8);
}

TEST_CASE("test strip")
{
    auto s = termcontrol::strip_control_sequences("Test\033[2m]BlahBlah\033[1AEnd");
    CHECK(s == "Test]BlahBlahEnd");
}