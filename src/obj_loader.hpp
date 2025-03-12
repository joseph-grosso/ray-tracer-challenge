// taken from www.opengl-tutorial.org and modified for my own purposes
#pragma once

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <string>
#include <tuple.hpp>
#include <vector>

#include "group.hpp"
#include "triangle.hpp"

class OBJParser {
 public:
  OBJParser() {
    ignored_lines = 0;
    default_group = Group();
  };
  std::string file_path;
  Group default_group;
  Tuple get_vertex(unsigned int i) {
    if (i > vertices_.size()) {
      throw std::invalid_argument(
          "Requested index greater than number of vertices.");
    } else if (i == 0) {
      throw std::invalid_argument("Parsers are indexed at 1, not 0.");
    };
    return *vertices_[i - 1];
  };
  void parse_obj_file(std::string file_path);
  unsigned int get_ignored_lines() { return ignored_lines; };
  std::string firstToken(const std::string in);
  std::string tail(const std::string in);
  std::vector<std::string> split(const std::string in,
                                 std::string split_token = " ");
  Tuple *create_point(const std::string tail);
  Triangle *create_triangle(std::string tail);

 private:
  std::vector<Tuple *> vertices_;
  unsigned int ignored_lines;
};
