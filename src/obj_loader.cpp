#include "obj_loader.hpp"

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide :
// - Binary files. Reading a model should be just a few memcpy's away, not
// parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

void OBJParser::parse_obj_file(std::string file_path) {
  std::cout << "Loading OBJ file " << file_path << "...\n";
  std::ifstream file(file_path);

  if (!file.is_open()) {
    throw std::invalid_argument(
        "Impossible to open the file! Are you in the right path?");
  };

  std::string curline;

  while (std::getline(file, curline)) {
    parse_line(curline);
  };

  std::cout << "OBJ file " << file_path << " successfully loaded.\n";
};

void OBJParser::parse_line(std::string curline) {
  std::string first_token = firstToken(curline);
  if (first_token == "v") {
    vertices_.push_back(create_point(tail(curline)));
  } else if (first_token == "f") {
    initialize_triangles(tail(curline));
  } else if (first_token == "g") {
    update_group(tail(curline));
  } else if (first_token == "vn") {
    parse_normals(tail(curline));
  } else {
    ignored_lines++;
  };
}

void OBJParser::update_group(std::string tail) {
  _current_group_name = tail;
  if (!_groups.contains(tail)) {
    Group* g = new Group;
    default_group.add_child(g);
    _groups.insert({tail, g});
  };
};

void OBJParser::parse_normals(std::string tail) {
  normal_vectors_.push_back(create_vector(tail));
}

// Get first token of string
std::string OBJParser::firstToken(const std::string in) {
  if (!in.empty()) {
    size_t token_start = in.find_first_not_of(" \t");
    size_t token_end = in.find_first_of(" \t", token_start);
    if (token_start != std::string::npos && token_end != std::string::npos) {
      return in.substr(token_start, token_end - token_start);
    } else if (token_start != std::string::npos) {
      return in.substr(token_start);
    }
  }
  return "";
}

std::string OBJParser::tail(const std::string in) {
  size_t token_start = in.find_first_not_of(" \t");
  size_t space_start = in.find_first_of(" \t", token_start);
  size_t tail_start = in.find_first_not_of(" \t", space_start);
  size_t tail_end = in.find_last_not_of(" \t");
  if (tail_start != std::string::npos && tail_end != std::string::npos) {
    return in.substr(tail_start, tail_end - tail_start + 1);
  } else if (tail_start != std::string::npos) {
    return in.substr(tail_start);
  }
  return "";
}

std::vector<std::string> OBJParser::split(const std::string in,
                                          std::string split_token) {
  // Split a String into a string array at a given token
  std::vector<std::string> out;
  std::string temp;

  for (int i = 0; i < int(in.size()); i++) {
    std::string test = in.substr(i, split_token.size());

    if (test == split_token) {
      if (!temp.empty()) {
        out.push_back(temp);
        temp.clear();
        i += (int)split_token.size() - 1;
      } else {
        out.push_back("");
      }
    } else if (i + split_token.size() >= in.size()) {
      temp += in.substr(i, split_token.size());
      out.push_back(temp);
      break;
    } else {
      temp += in[i];
    }
  }
  return out;
}

Tuple* OBJParser::create_point(const std::string tail) {
  std::vector<std::string> vals = split(tail);
  return new Tuple(std::stof(vals[0]), std::stof(vals[1]), std::stof(vals[2]),
                   1);
};

Tuple* OBJParser::create_vector(const std::string tail) {
  std::vector<std::string> vals = split(tail);
  return new Tuple(std::stof(vals[0]), std::stof(vals[1]), std::stof(vals[2]),
                   0);
};

void OBJParser::initialize_triangles(std::string tail) {
  if (_current_group_name == "") {
    fan_triangulation(tail, &default_group);
  } else {
    fan_triangulation(tail, _groups.at(_current_group_name));
  };
};

void OBJParser::fan_triangulation(std::string tail, Group* g) {
  // Lots of TODOs in this parsing logic!
  std::vector<std::string> vals = split(tail);
  std::vector<std::vector<std::string>> all_split;
  int vertex_type;
  for (auto i : vals) {
    all_split.push_back(split(i, "/"));
  };
  // TODO: fix ref to all_split[0] to something more complete -
  //       don't simply check the first value
  if (all_split[0].size() == 1) {
    vertex_type = 1;
  } else if (all_split[0].size() == 2) {
    vertex_type = 2;
  } else if (all_split[0].size() == 3) {
    // TODO: add handling logic for Texture type
    vertex_type = 3;
  };

  for (int i = 1; i < vals.size() - 1; i++) {
    switch (vertex_type) {
      case 1:  // Position only
      {
        g->add_child(new Triangle(get_vertex(std::stoi(vals[0])),
                                  get_vertex(std::stoi(vals[i])),
                                  get_vertex(std::stoi(vals[i + 1]))));
        break;
      }
      case 2:  // Position and texture
      {
        // TODO: add texture handling logic
        g->add_child(new Triangle(get_vertex(std::stoi(vals[0])),
                          get_vertex(std::stoi(vals[i])),
                          get_vertex(std::stoi(vals[i + 1]))));
        break;
      }
      case 3:  // Position, texture, and normal
      {
        g->add_child(new SmoothTriangle(
          get_vertex(std::stoi(all_split[0][0])),
          get_vertex(std::stoi(all_split[i][0])),
          get_vertex(std::stoi(all_split[i + 1][0])),
          get_normal_vector(std::stoi(all_split[0][2])),
          get_normal_vector(std::stoi(all_split[i][2])),
          get_normal_vector(std::stoi(all_split[i + 1][2]))
        ));
        break;
      }
      default: 
      {
        break;
      };
    }
  };
};

Group* OBJParser::get_named_group(std::string key) { return _groups.at(key); };
Group* OBJParser::obj_to_group() { return &default_group; };
