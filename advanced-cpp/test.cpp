#define CATCH_CONFIG_MAIN

#include <iostream>

#include <catch2/catch_all.hpp>
#include "vector.hpp"

TEST_CASE("Vector push_back works", "[Vector]") {
  Custom::Vector<int> vec;
  vec.push_back(42);
  REQUIRE(vec.size() == 1);
  REQUIRE(vec[0] == 42);
}