#include "cmake/CMake.hh"

#include <array>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <iostream>
#include <format>

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

std::array<std::string, 2> create_module_folders(std::string& module_name) {
  //Create directories
  std::array<std::string, 2> folders({
    "include/" + module_name,
    "src/" + module_name
  });
  std::for_each(folders.begin(), folders.end(), [](std::string folderName){
    if(std::filesystem::exists(folderName)) {
      std::cerr << "Folder " << folderName << "already exists!" << std::endl;
      return;
    }
  });
  for(std::string folder : folders) {
    auto done = std::filesystem::create_directory(folder);
    if(!done) {
      std::cerr << "Error creating directory " << folder << std::endl;
      return folders;
    }
  }

  return folders;
}

void CMake::write_c_make_executable_file(std::string& executable_name) {
  auto folders = create_module_folders(executable_name);

  //Create files
  std::ofstream empty_header_file(folders[0] + executable_name + ".hh");
  std::ofstream empty_source_file(folders[1] + executable_name + ".cc");
  std::ofstream module_cmake_file(folders[1] + "CMakeLists.txt");
  std::ostringstream module_cmake_file_buffer;

  module_cmake_file_buffer << "add_executable(" << executable_name << std::endl;
  module_cmake_file_buffer << "\t" << executable_name << ".cc" << std::endl;
  module_cmake_file_buffer << ")" << std::endl;
  module_cmake_file << module_cmake_file_buffer.str();
}

