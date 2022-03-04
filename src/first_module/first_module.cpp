/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2021 J.Marple
/// @brief This module demonstrates how to construct C++ project.

#include "first_module/first_module.hpp"

#include <iostream>

namespace first_module {

void demo_print_hello(int n_repeat) {
  for (int i = 0; i < n_repeat; i++) {
    std::cout << "Hello" << std::endl;
  }
}

}  // namespace first_module
