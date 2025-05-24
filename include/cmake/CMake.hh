#pragma once
#include <string>

namespace CMake {
  void write_c_make_project_file(std::string& project_name);
  void write_c_make_test_file(const std::string& project_name);
  void write_c_make_library_file(const std::string& project_name, std::string& library_name);
  void write_c_make_shared_library_file(const std::string& project_name, std::string& library_name);
  void write_c_make_executable_file(const std::string& project_name, std::string& executable_name);
};