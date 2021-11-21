

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Crockford32.h"

std::string one = "a";
std::string two = "aB";
std::string three = "Patrick";
std::string four = "0";

std::string five = "C4";
std::string six = "C510";
std::string seven = "85146";
std::string eight = "d1jg";

TEST_CASE("Testing the encode method") {
  CHECK(encode(one) == "C4");
  CHECK(encode(two) == "C510");
  CHECK(encode(three) == "A1GQ8WK9CDNG");
  CHECK(encode(four) == "60");
}


TEST_CASE("Testing the decode method") {
  CHECK(decode(five) == "a"); 
  CHECK(decode(six) == "aB");
  CHECK(decode(seven) == "ABC");
  CHECK(decode(eight) == "he");
}


TEST_CASE("Testing to checksum validation method") {
  CHECK(validate_checksum(one) == true);
}
