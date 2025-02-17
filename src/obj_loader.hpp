// taken from www.opengl-tutorial.org and modified for my own purposes
#pragma once

#include <stdio.h>

#include <fstream>
#include <iostream>
#include <string>
#include <tuple.hpp>
#include <vector>

class OBJParser {
 public:
  OBJParser() { ignored_lines = 0; };
  std::string file_path;
  Tuple get_vertices(int i) {
    if (i == 0) {
      throw std::invalid_argument("Parsers are indexed at 1, not 0.");
    };
    return vertices_[i];
  };
  void parse_obj_file(std::string file_path);
  unsigned int get_ignored_lines() { return ignored_lines; };
  // Split a String into a string array at a given token
  // inline void split(const std::string &in, std::vector<std::string> &out,
  // std::string token) { 	out.clear();

  // 	std::string temp;

  // 	for (int i = 0; i < int(in.size()); i++)
  // 	{
  // 		std::string test = in.substr(i, token.size());

  // 		if (test == token)
  // 		{
  // 			if (!temp.empty())
  // 			{
  // 				out.push_back(temp);
  // 				temp.clear();
  // 				i += (int)token.size() - 1;
  // 			}
  // 			else
  // 			{
  // 				out.push_back("");
  // 			}
  // 		}
  // 		else if (i + token.size() >= in.size())
  // 		{
  // 			temp += in.substr(i, token.size());
  // 			out.push_back(temp);
  // 			break;
  // 		}
  // 		else
  // 		{
  // 			temp += in[i];
  // 		}
  // 	}
  // }
 private:
  std::vector<Tuple> vertices_;
  unsigned int ignored_lines;
};

// bool operator==(Material lhs, Material rhs);
