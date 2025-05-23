#include <string>

namespace CMake {
  void write_c_make_project_file(std::string& project_name);
  //void write_c_make_library_file(std::string& project_name, std::string& library_name);
  //void write_c_make_shared_library_file(std::string& project_name, std::string& library_name);
  void write_c_make_executable_file(std::string& executable_name);
};