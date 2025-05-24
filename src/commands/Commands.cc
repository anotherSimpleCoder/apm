#include "commands/Commands.hh"

#include <filesystem>



Commands::CommandToken Commands::get_command_token(const std::string& string_command) {
	if(string_command == "new") return Commands::CommandToken::NEW;
	return Commands::CommandToken::INVALID;
}