#define CATCH_CONFIG_MAIN

#include <iostream>

#include <catch2/catch_all.hpp>
#include "vector.hpp"

TEST_CASE("Vectors are zero initialized", "[Vector]") {
  Custom::Vector<int> vec;
  REQUIRE(vec.size() == 0);
  REQUIRE(vec.capacity() == 0);
}

TEST_CASE("Vector push_back works", "[Vector]") {
  Custom::Vector<int> vec;
  vec.push_back(42);
  REQUIRE(vec.size() == 1);
  REQUIRE(vec[0] == 42);
}

TEST_CASE("Vector can be resized properly", "[Vector]") {
  Custom::Vector<char> vec;
  vec.push_back('a');
  CHECK(vec.size() == 1);
  REQUIRE(vec.capacity() == 1);

  vec.push_back('b');
  vec.push_back('c');
  CHECK(vec.size() == 3);
  REQUIRE(vec.capacity() == 4);
}