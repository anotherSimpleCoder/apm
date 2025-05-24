#include "cli/Commands.hh"
#include "cmake/CMake.hh"

#include <iostream>
#include <filesystem>
#include <array>
#include <algorithm>


Commands::CommandToken Commands::get_command_token(const std::string& string_command) {
	if(string_command == "new") return Commands::CommandToken::NEW;
	return Commands::CommandToken::INVALID;
}

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

void Commands::create_project(const std::vector<std::string>& args) {
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

Commands::ModuleToken Commands::get_module_token(const std::string& string_module_token) {
  if(string_module_token == "library") return Commands::ModuleToken::LIB;
  if(string_module_token == "shared") return Commands::ModuleToken::SHARED_LIB;
  if(string_module_token == "executable") return Commands::ModuleToken::EXEC;
  return Commands::ModuleToken::INVALID_MODULE;
}

void Commands::create_module(const std::vector<std::string>& args) {
  if(args.size() < 3) {
    std::cerr << "Insufficient amount of arguments!" << std::endl;
    return;
  }

  const auto& project_name = args[1];
  auto module_name = args[2];

  switch(get_module_token(args[3])) {
    case Commands::ModuleToken::LIB: {
      break;
    }

    case Commands::ModuleToken::SHARED_LIB: {
      break;
    }

    case Commands::ModuleToken::EXEC: {
      CMake::write_c_make_executable_file(project_name, module_name);
      break;
    }

    case Commands::ModuleToken::INVALID_MODULE: {
      break;
    }
  }
}