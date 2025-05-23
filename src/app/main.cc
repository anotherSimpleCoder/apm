#include <iostream>
#include "cli/CLI.hh"

int main(int argc, char** argv) {
	CLI cli;
	cli.run(argc, argv);
	return 0;
}
