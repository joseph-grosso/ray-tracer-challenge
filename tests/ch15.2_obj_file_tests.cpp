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

// Scenario: Parser errors when values are read outside of valid range
// pMe
TEST(TestOBJ, ParserError) {
  OBJParser o;
  o.parse_obj_file("tests/obj_files/ch15.vertex_record.obj");

  // Parsers are indexed at 1
  EXPECT_THROW(o.get_vertex(0), std::invalid_argument);
  // Parsers expressively error when out if index
  EXPECT_THROW(o.get_vertex(100), std::invalid_argument);
}

// Scenario: Parsing triangle faces
// p214
TEST(TestOBJ, ParsingTriangleFaces) {
  OBJParser o;
  o.parse_obj_file("tests/obj_files/ch15.triangle_faces.obj");

  Group g = o.default_group;
  Triangle t1 = *(Triangle *)g.get_child(0);
  Triangle t2 = *(Triangle *)g.get_child(1);

  EXPECT_EQ(o.get_ignored_lines(), 1);
  EXPECT_EQ(t1.p1, o.get_vertex(1));
  EXPECT_EQ(t1.p2, o.get_vertex(2));
  EXPECT_EQ(t1.p3, o.get_vertex(3));
  EXPECT_EQ(t2.p1, o.get_vertex(1));
  EXPECT_EQ(t2.p2, o.get_vertex(3));
  EXPECT_EQ(t2.p3, o.get_vertex(4));
}

// Scenario: Parsing triangle faces on a polygon
// p215
TEST(TestOBJ, ParsingPolygoneFaces) {
  OBJParser o;
  o.parse_obj_file("tests/obj_files/ch15.polygon_faces.obj");

  Group g = o.default_group;
  Triangle t1 = *(Triangle *)g.get_child(0);
  Triangle t2 = *(Triangle *)g.get_child(1);
  Triangle t3 = *(Triangle *)g.get_child(2);

  EXPECT_EQ(o.get_ignored_lines(), 1);
  EXPECT_EQ(t1.p1, o.get_vertex(1));
  EXPECT_EQ(t1.p2, o.get_vertex(2));
  EXPECT_EQ(t1.p3, o.get_vertex(3));
  EXPECT_EQ(t2.p1, o.get_vertex(1));
  EXPECT_EQ(t2.p2, o.get_vertex(3));
  EXPECT_EQ(t2.p3, o.get_vertex(4));
  EXPECT_EQ(t3.p1, o.get_vertex(1));
  EXPECT_EQ(t3.p2, o.get_vertex(4));
  EXPECT_EQ(t3.p3, o.get_vertex(5));
}

// Scenario: Triangles in groups
// p217
TEST(TestOBJ, TrianglesInGroups) {
  OBJParser o;
  o.parse_obj_file("tests/obj_files/ch15.triangle_groups.obj");

  Group g1 = *o.get_named_group("FirstGroup");
  Group g2 = *o.get_named_group("SecondGroup");
  Triangle t1 = *(Triangle *)g1.get_child(0);
  Triangle t2 = *(Triangle *)g2.get_child(0);

  EXPECT_EQ(t1.p1, o.get_vertex(1));
  EXPECT_EQ(t1.p2, o.get_vertex(2));
  EXPECT_EQ(t1.p3, o.get_vertex(3));
  EXPECT_EQ(t2.p1, o.get_vertex(1));
  EXPECT_EQ(t2.p2, o.get_vertex(3));
  EXPECT_EQ(t2.p3, o.get_vertex(4));
}

// Scenario: Converting an OBJ file to a group
// p218
TEST(TestOBJ, OBJFileToGroup) {
  OBJParser o;
  o.parse_obj_file("tests/obj_files/ch15.triangle_groups.obj");

  Group file_group = *o.obj_to_group();
  Group *g1 = o.get_named_group("FirstGroup");
  Group *g2 = o.get_named_group("SecondGroup");

  // TODO: test that pointer is in list of children,
  //       not that it's at a specific index.
  EXPECT_EQ(file_group.get_child(0), g1);
  EXPECT_EQ(file_group.get_child(1), g2);
}
