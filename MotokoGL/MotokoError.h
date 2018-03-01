#pragma once
// By Oleksiy Grechnyev

#include <stdexcept>

namespace MotokoGL {
struct MotokoError : public std::runtime_error{
    MotokoError(const std::string & msg) :
        runtime_error(msg) {}
};
}
