#pragma once
#include <vector>
#include <string>

namespace Commands {
	enum CommandToken {
		NEW,
		INVALID
	};

  enum ModuleToken {
    LIB,
    SHARED_LIB,
    EXEC,
    INVALID_MODULE
  };

	CommandToken get_command_token(const std::string& string_command);
  ModuleToken get_module_token(const std::string& string_module_token);
	void create_project(const std::vector<std::string>& args);
  void create_module(const std::vector<std::string>& args);
};
