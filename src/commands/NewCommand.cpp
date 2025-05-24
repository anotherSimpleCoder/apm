#include "commands/Commands.hh"
#include "cmake/CMake.hh"

#include <iostream>
#include <array>
#include <algorithm>
#include <filesystem>

using namespace Commands;

void create_folders(std::string& project_name) {
  bool done = false;
  std::array<std::string, 4> folders({project_name});
  std::array<std::string, 3> sub_folders({"src", "include", "test"});
  std::ranges::transform(sub_folders, folders.begin()+1, [project_name](const std::string& folder){
    return project_name + "/" + folder;
  });


  for(const std::string& folder_name : folders) {
    done = std::filesystem::create_directory(folder_name);
    if(!done) {
		  std::cerr << "Could not create directory " << project_name << std::endl;
		  return;
	  }
  }
}

void NewCommand::create_project(const std::vector<std::string>& args) {
  if(args.size() < 2) {
    std::cerr << "Insufficient amount of arguments!" << std::endl;
    return;
  }
  auto project_name = args[2];
  std::string mainExecName = "app";

  create_folders(project_name);
  CMake::write_c_make_project_file(project_name);
  CMake::write_c_make_test_file(project_name);
  CMake::write_c_make_executable_file(project_name, mainExecName);
  std::cout << "Project " << project_name << " created successfully!" << std::endl;
}

NewCommand::ModuleToken NewCommand::get_module_token(const std::string& string_module_token) {
  if(string_module_token == "library") return LIB;
  if(string_module_token == "shared") return SHARED_LIB;
  if(string_module_token == "executable") return EXEC;
  return INVALID_MODULE;
}

void NewCommand::create_module(const std::vector<std::string>& args) {
  if(args.size() < 3) {
    std::cerr << "Insufficient amount of arguments!" << std::endl;
    return;
  }

  const auto& project_name = args[1];
  auto module_name = args[2];

  switch(get_module_token(args[3])) {
    case LIB: {
      CMake::write_c_make_library_file(project_name, module_name);
      break;
    }

    case SHARED_LIB: {
      CMake::write_c_make_shared_library_file(project_name, module_name);
      break;
    }

    case EXEC: {
      CMake::write_c_make_executable_file(project_name, module_name);
      break;
    }

    case INVALID_MODULE: {
      std::cerr << "Invalid module type!" << std::endl;
      break;
    }
  }
}