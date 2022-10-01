#include <catch2/catch_all.hpp>

#include <termcontrol/detail/windows.hpp>

namespace tc = termcontrol;

TEST_CASE("test console setup")
{
    auto console = tc::win32_terminal();
}