//
// Created by kartanis on 26.07.15.
//
#pragma once
#include <exceptions/Exception.h>

class OutOfMemoryException : public Exception {
public:
    OutOfMemoryException(const char* message) : Exception(message) {


    }
};