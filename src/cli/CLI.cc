#include "cli/CLI.hh"
#include "cli/Commands.hh"

#include <iostream>
#include <vector>
#include <string>


void usage() {
	std::cout << "apm - a package manager" << std::endl;
	std::cout << "\n";
	std::cout << "new \t " << "Creates a new apm project" << std::endl;
}


void CLI::run(int argc, char** argv) {
	std::vector<std::string> args(argv, argv + argc);

	if(args.size() < 2) {
		usage();
		return;
	}

	auto command = Commands::get_command_token(args[1]);

	switch(command) {
		case Commands::CommandToken::NEW: {
			Commands::create_project(args);
			break;			
		}

		case Commands::CommandToken::INVALID: {
			std::cerr << "Invalid command!" << std::endl;
			usage();
			break;			
		}
	}
}
