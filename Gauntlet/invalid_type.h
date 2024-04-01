#pragma once

#include <exception>
#include <string>


// Used for invalid enum entries; NULL_TYPE
class invalid_type : public std::exception {
private:
    std::string message;

public:
    invalid_type(const std::string& msg) : message(msg) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }
};
