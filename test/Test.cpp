//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"

#include "Crockford32.h"

std::string j = "dadad";

TEST_CASE("Testing the encode method") {
  CHECK(validate_checksum(j) == true);
}
