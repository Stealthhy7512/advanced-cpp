#define CATCH_CONFIG_MAIN

#include <iostream>
#include <vector>
#include <initializer_list>

#include <catch2/catch_all.hpp>
#include "vector.hpp"

TEST_CASE("Constructors work", "[Vector]") {
  SECTION("Default initialization works") {
    Custom::Vector<int> vec; // default constructor
    REQUIRE(vec.size() == 0);

    Custom::Vector<int> vec2{}; // falls back to default constructor
    REQUIRE(vec2.size() == 0);
  }

  SECTION("Copy constructor works") {
    Custom::Vector<int> vec{};
    Custom::Vector<int> copied_vec(vec);
    REQUIRE(copied_vec.size() == vec.size());

    std::initializer_list<int> ilist{ 1, 2, 3, 4 };
    Custom::Vector<int> list_copied_vec{ ilist };
    REQUIRE(list_copied_vec.size() == 4);
  }

  SECTION("Move constructor works") {
    Custom::Vector<int> vec{};
    Custom::Vector<int> moved_vec(std::move(vec)); // or use a literal init list here
    REQUIRE(moved_vec.size() == vec.size());

    std::initializer_list<int> ilist{1, 2, 3, 4};
    Custom::Vector<int> list_moved_vec{ std::move(ilist) };
    REQUIRE(list_moved_vec.size() == ilist.size());
  }
}

TEST_CASE("Vectors can be assigned", "[Vector]") {
  Custom::Vector<int> vec{ {1, 2, 3} };

  SECTION("Copying works") {
    Custom::Vector<int> vec_copy{ vec };
    REQUIRE(vec_copy.size() == vec.size());
  }

  SECTION("Moving works") {

  }
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

  REQUIRE(vec.pop_back() == 2);
  REQUIRE(vec.size() == 1);
}

TEST_CASE("Empty vector disallows pop_back", "[Vector]") {
  Custom::Vector<double> vec;
  REQUIRE_THROWS(vec.pop_back());
}
