#define CATCH_CONFIG_MAIN

#include <iostream>
#include <vector>

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

TEST_CASE("Vector pop_back works", "[Vector]") {
  Custom::Vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  CHECK(vec.back() == 2);

  vec.pop_back();
  REQUIRE(vec.size() == 1);
  REQUIRE(vec.pop_back() == 2);
}

TEST_CASE("Empty vector disallows pop_back", "[Vector]") {
  Custom::Vector<double> vec;
  REQUIRE_THROWS(vec.pop_back());
}

TEST_CASE("Vector initializer list constructor works", "[Vector]") {
  std::initializer_list<double> ilist{1., 2., 3.};
  Custom::Vector<double> vec{ ilist };
  REQUIRE(vec.size() == 3);
}

TEST_CASE("Vector rvalue initializer list constructor works", "[Vector]") {
  Custom::Vector<int> vec{ {1, 2, 3} };
  REQUIRE(vec.size() == 3);
}