/// @file
/// @author Jongkuk Lim <limjk@jmarple.ai>
/// @copyright 2021 J.Marple
/// @brief This module demonstrates how to construct C++ project.

#ifndef INCLUDE_SECOND_MODULE_SECOND_MODULE_HPP_
#define INCLUDE_SECOND_MODULE_SECOND_MODULE_HPP_

#include <string>

/// Second module description here
namespace second_module {

/// Generate string that 'world' string concatenated n_repeat times.
///
/// @param n_repeat: Number of repeatition.
///
/// @return: n_repeat time concatenated 'world'
std::string demo_generate_world(int n_repeat);
}  // namespace second_module

#endif  // INCLUDE_SECOND_MODULE_SECOND_MODULE_HPP_
