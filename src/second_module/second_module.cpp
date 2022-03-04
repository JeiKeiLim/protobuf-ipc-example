/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2021 J.Marple
/// @brief This module demonstrates how to construct C++ project.

#include "second_module/second_module.hpp"

#include <iostream>
#include <string>

namespace second_module {

std::string demo_generate_world(int n_repeat) {
  std::string result = "";

  for (int i = 0; i < n_repeat; i++) {
    result += "world";
  }

  return result;
}

}  // namespace second_module
