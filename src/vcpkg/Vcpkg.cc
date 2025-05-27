//
// Created by abav on 26.05.2025.
//
#include "vcpkg/Vcpkg.hh"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

void clone_vcpkg(const std::string& project_name) {
    std::cout << "Downloading VCPKG..." << std::endl;
    std::string command = "git clone https://github.com/microsoft/vcpkg " + project_name + "/vcpkg";
    int err = std::system(command.c_str());
    if (err != 0) {
        throw Vcpkg::VcpkgException();
    }
}

void setup_vcpkg(const std::string& project_name) {
    std::cout << "Bootstrapping VCPKG..." << std::endl;
    std::string command;

#ifdef _WIN32
    command = "cd " + project_name + "/vcpkg && bootstrap-vcpkg.bat";
#else
    command = "cd " + project_name + "/vcpkg && bootstrap-vcpkg.sh";
#endif

    int err = std::system(command.c_str());
    if (err != 0) {
        throw Vcpkg::VcpkgException();
    }

    command = "cd " + project_name + "/vcpkg && vcpkg new --version 1.0.0 --name " + project_name;
    err = std::system(command.c_str());
    if (err != 0) {
        throw Vcpkg::VcpkgException();
    }
}

void connect_to_cmake(const std::string& project_name) {
    std::cout << "Connecting VCPKG to CMake..." << std::endl;
    std::string command = "cd " + project_name + " && cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake";
    int err = std::system(command.c_str());
    if (err != 0) {
        throw Vcpkg::VcpkgException();
    }
}

void Vcpkg::initialize_vcpkg(const std::string& project_name) {
    clone_vcpkg(project_name);
    setup_vcpkg(project_name);
    connect_to_cmake(project_name);
}