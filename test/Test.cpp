

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Crockford32.h"

std::string one = "a";
std::string two = "aB";
std::string three = "Patrick";
std::string four = "0";

TEST_CASE("Testing the encode method") {
  CHECK(encode(one) == "C4");
  CHECK(encode(two) == "C510");
  CHECK(encode(three) == "A1GQ8WK9CDNG");
  CHECK(encode(four) == "60");
}
