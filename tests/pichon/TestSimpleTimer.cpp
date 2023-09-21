#include "Interfaces.h"
#include "SimpleTicker.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(ASimpleTicker, IsCreatedWithATickRateInMilliseconds)
{
    SimpleTicker ticker{std::chrono::milliseconds{10}};
}
