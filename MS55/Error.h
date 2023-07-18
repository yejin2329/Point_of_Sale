#ifndef SDDS_ERROR_H_
/* Citation and Sources...
Final Project Milestone 5
Module: Error
Filename: Error.h
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

#define SDDS_ERROR_H_
#include<iostream>

namespace sdds {
	class Error {
	private:
		char* error_msg = nullptr;
	public:
		//contrsuctor
		Error();
		Error(const char errMsg[]);

		//copy constructor
		Error(const Error& other);
		Error& operator=(const Error& other);

		//destructor
		~Error();

		operator bool()const;
		Error& clear();
		void set(const char errMsg[]);
		void display(std::ostream& os) const;

	};

	std::ostream& operator << (std::ostream& os, const Error& error);


}
#endif