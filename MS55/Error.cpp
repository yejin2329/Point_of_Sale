/* Citation and Sources...
Final Project Milestone 5
Module: Error
Filename: Error.cpp
Version 1.0
Author	Jenny Kim
Student ID: 139787220
Email: ykim314@myseneca.ca
Revision History
-----------------------------------------------------------
Date      2023/04/19
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my project milestones.
----------------------------------------------------------- */

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>
#include "Error.h"

using namespace std;
namespace sdds {

	Error::Error() {
		error_msg = nullptr;
	}

	Error::Error(const char errMsg[]) {

		error_msg = new char[strlen(errMsg) + 1];
		strcpy(error_msg, errMsg);
	}


	Error::Error(const Error& other) {

		if (&other != nullptr) {
			error_msg = nullptr;
			*this = other;
		}
	}
	Error& Error :: operator=(const Error& other) {

		if (&other.error_msg == nullptr) {
			this->error_msg = nullptr;
		}

		else {
			if (this->error_msg != other.error_msg && other.error_msg[0] != '\0') {

				delete[] error_msg;
				error_msg = new char[strlen(other.error_msg) + 1];
				strcpy(error_msg, other.error_msg);


			}
		}
		return *this;
	}

	Error::~Error() {

		if (error_msg != nullptr) {
			delete[] error_msg;
		}

	}

	Error::operator bool()const {

		return (error_msg != nullptr);
	}

	Error& Error::clear() {

		delete[]error_msg;
		error_msg = nullptr;
		return *this;
	}

	void Error::set(const char errMsg[]) {

		if (errMsg != nullptr) {
			if (error_msg != nullptr) {
				delete[]error_msg;
			}
			error_msg = new char[strlen(errMsg) + 1];
			strcpy(error_msg, errMsg);
		}
	}


	void Error::display(std::ostream& os) const {

		if (error_msg != nullptr) {
			os << error_msg;
		}
	}

	std::ostream& operator<<(std::ostream& os, const Error& error) {

		error.display(os);
		return os;
	}


}