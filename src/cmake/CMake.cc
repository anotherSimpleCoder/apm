#include "cmake/CMake.hh"

#include <filesystem>
#include <sstream>
#include <fstream>
#include <iostream>

void CMake::write_c_make_project_file(std::string& project_name) {
  std::ostringstream fileBuffer;
  std::ofstream fileStream(project_name + "/CMakeLists.txt");

  if(!fileStream) {
    std::cerr << "Error writing root CMakeLists.txt file!" << std::endl;
    return; 
  }

  fileBuffer << "cmake_minimum_required(VERSION 3.30)" << std::endl;
  fileBuffer << "project(" << project_name << ")" << std::endl;
  fileBuffer << "\n";
  fileBuffer << "set(CMAKE_CXX_STANDARD 20)" << std::endl;
  fileBuffer << "list(APPEND CMAKE_MODULE_PATH \"${CMAKE_SOURCE_DIR}/cmake\")" << std::endl;
  fileBuffer << "\n";
  fileBuffer << "include_directories(" << std::endl;
  fileBuffer << "\t${CMAKE_SOURCE_DIR}/include" << std::endl;
  fileBuffer << ")" << std::endl;
  fileBuffer << "\n";
  fileBuffer << "add_subdirectory(src)" << std::endl;
  fileBuffer << "\n";
  fileBuffer << "enable_testing()" << std::endl;
  fileBuffer << "add_subdirectory(test)" << std::endl;

  fileStream << fileBuffer.str();
}

void CMake::write_c_make_test_file(const std::string& project_name) {
  std::ofstream test_c_make_file(project_name + "/test/CMakeLists.txt");
  test_c_make_file << "find_package(GTest CONFIG REQUIRED)" << std::endl;
}

std::string create_module_folders(const std::string& project_name, const std::string& module_name) {
  //Create directories
  std::ofstream src_cmake_file(project_name + "/src/CMakeLists.txt", std::ios::app);
  std::ostringstream src_cmake_file_buffer;

  std::string module_folder_path = project_name + "/" + "src/" + module_name;
  if(std::filesystem::exists(module_folder_path)) {
    std::cerr << "Folder " << module_folder_path << "already exists!" << std::endl;
  }

  auto done = std::filesystem::create_directory(module_folder_path);
  if(!done) {
    std::cerr << "Error creating directory " << module_folder_path << std::endl;
    return "";
  }

  src_cmake_file_buffer << "add_subdirectory(" << module_name << ")" << std::endl;
  src_cmake_file << src_cmake_file_buffer.str();

  return module_folder_path;
}

void CMake::write_c_make_library_file(const std::string& project_name, std::string& library_name) {
  auto module_folder = create_module_folders(project_name, library_name);

  //Create files
  std::ofstream empty_source_file(module_folder + library_name + ".cc");
  std::ofstream module_cmake_file(module_folder + "CMakeLists.txt");
  std::ostringstream module_cmake_file_buffer;

  module_cmake_file_buffer << "add_library(" << library_name << std::endl;
  module_cmake_file_buffer << "\t" << library_name << ".cc" << std::endl;
  module_cmake_file_buffer << ")" << std::endl;
  module_cmake_file << module_cmake_file_buffer.str();
}

void CMake::write_c_make_shared_library_file(const std::string& project_name, std::string &library_name) {
  auto module_folder = create_module_folders(project_name, library_name);

  //Create files
  std::ofstream empty_source_file(module_folder + library_name + ".cc");
  std::ofstream module_cmake_file(module_folder + "CMakeLists.txt");
  std::ostringstream module_cmake_file_buffer;

  module_cmake_file_buffer << "add_library(" << library_name << " SHARED" << std::endl;
  module_cmake_file_buffer << "\t" << library_name << ".cc" << std::endl;
  module_cmake_file_buffer << ")" << std::endl;
  module_cmake_file << module_cmake_file_buffer.str();
}

void CMake::write_c_make_executable_file(const std::string& project_name, std::string& executable_name) {
  auto module_folder = create_module_folders(project_name, executable_name);

  //Create files
  std::ofstream empty_source_file(module_folder + "/" + executable_name + ".cc");
  std::ofstream module_cmake_file(module_folder + "/" + "CMakeLists.txt");
  std::ostringstream module_cmake_file_buffer;

  module_cmake_file_buffer << "add_executable(" << executable_name << std::endl;
  module_cmake_file_buffer << "\t" << executable_name << ".cc" << std::endl;
  module_cmake_file_buffer << ")" << std::endl;
  module_cmake_file << module_cmake_file_buffer.str();
}