#pragma once

#include <exception>
#include <string>

class Exception : public std::exception {
private:
    const char* message;
public:
    Exception(const char* message) {
        this->message = message;
    }

    Exception(std::string message) {
        this->message = message.c_str();
    }

    virtual const char* what() const throw() {
        return message;
    }


};