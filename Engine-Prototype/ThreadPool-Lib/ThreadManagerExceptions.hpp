#pragma once

#include <iostream>
#include <string>
#include <exception>

struct ThreadManagerExceptions : public std::exception {
    ThreadManagerExceptions(int thrId) {
        err_msg = "";
        err_msg += std::to_string(th_id);
        th_id = thrId;
    }

    virtual const char* what() const throw() {
        return err_msg.c_str();
    }

    
    std::string err_msg;
    int th_id;
};