#pragma once

#include <string>
#include <exception>

struct ThreadManagerExceptions : std::exception {
	explicit ThreadManagerExceptions(int thrId) {
        err_msg = "";
        err_msg += std::to_string(th_id);
        th_id = thrId;
    }

	const char* what() const throw() override;


	std::string err_msg;
    int th_id;
};

inline const char* ThreadManagerExceptions::what() const {
	return err_msg.c_str();
}
