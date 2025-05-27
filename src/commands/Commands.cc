#include "commands/Commands.hh"

#include <filesystem>

#include "vcpkg/Vcpkg.hh"

Commands::CommandToken Commands::get_command_token(const std::string& string_command) {
	if (string_command == "new") return NEW;
	return INVALID;
}
