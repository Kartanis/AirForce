#pragma once

#include <exceptions/Exception.h>

class IOException : public Exception {
public:
    IOException(const char* message) : Exception(message) {


    }
};