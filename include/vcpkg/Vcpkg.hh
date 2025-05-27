//
// Created by abav on 26.05.2025.
//

#ifndef VCPKG_HH
#define VCPKG_HH

#include <exception>
#include <string>

namespace Vcpkg {
    void initialize_vcpkg(const std::string& project_name);

    class VcpkgException final : public std::exception {
        [[nodiscard]] const char* what() const noexcept {
            return "VCPKG exception";
        }
    };
};
#endif //VCPKG_HH
