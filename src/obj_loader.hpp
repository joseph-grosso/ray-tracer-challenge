#pragma once

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <string>
#include <tuple.hpp>
#include <unordered_map>
#include <vector>

#include "group.hpp"
#include "triangle.hpp"

class OBJParser {
 public:
  OBJParser() {
    ignored_lines = 0;
    default_group = Group();
    _current_group_name = "";
    _groups = {};
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
  void parse_line(std::string curline);
  void update_group(std::string curline);
  unsigned int get_ignored_lines() { return ignored_lines; };
  std::string firstToken(const std::string in);
  std::string tail(const std::string in);
  std::vector<std::string> split(const std::string in,
                                 std::string split_token = " ");
  Tuple *create_point(const std::string tail);
  void initialize_triangles(std::string tail);
  void fan_triangulation(std::string tail, Group *g);
  Group *get_named_group(std::string key);
  Group *obj_to_group();

 private:
  std::vector<Tuple *> vertices_;
  unsigned int ignored_lines;
  std::string _current_group_name;
  std::unordered_map<std::string, Group *> _groups;
};
