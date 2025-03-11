#include <gmock/gmock.h>
#include <math.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "gtest/gtest.h"
#include "ray_tracer.hpp"

// Scenario: Ignore unrecognized lines
// p213
TEST(TestOBJ, ReadGibberish) {
  OBJParser o;
  o.parse_obj_file("tests/obj_files/ch15.gibberish.obj");
  EXPECT_EQ(o.get_ignored_lines(), 5);
}

// Scenario: Vertex records
// p214
TEST(TestOBJ, ReadVertexRecords) {
  OBJParser o;
  o.parse_obj_file("tests/obj_files/ch15.vertex_record.obj");
  EXPECT_EQ(o.get_ignored_lines(), 0);
  EXPECT_EQ(o.get_vertex(1), point(-1, 1, 0));
  EXPECT_EQ(o.get_vertex(2), point(-1, 0.5, 0));
  EXPECT_EQ(o.get_vertex(3), point(1, 0, 0));
  EXPECT_EQ(o.get_vertex(4), point(1, 1, 0));
}

// Scenario: Parser errors when values are read outside of int
// p214
TEST(TestOBJ, ParserError) {
  OBJParser o;
  o.parse_obj_file("tests/obj_files/ch15.vertex_record.obj");

  // Parsers are indexed at 1
  EXPECT_THROW(o.get_vertex(0), std::invalid_argument);
  // Parsers expressively error when out if index
  EXPECT_THROW(o.get_vertex(100), std::invalid_argument);
}
