/* Citation and Sources...
Final Project Milestone 5
Module: Date
Filename: Date.h
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

#ifndef SDDS_DATE_H_
#define SDDS_DATE_H_
#include <iostream>
#include "Error.h"

namespace sdds {
	class Date {
	private:
		int year = 0;
		int month = 0;
		int day = 0;
		int hour = 0;
		int minute = 0;
		bool date_Only = false;
		class Error error_;
	public:
		Date();
		Date(int yr, int mon, int day_);
		Date(int yr, int mon, int day_, int hr);
		Date(int yr, int mon, int day_, int hr, int min);
		Date(const Date& other);
		Date& operator = (const Date& other);
		bool validate();
		~Date(); // added

		void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);
		int uniqueDateValue(int year, int mon, int day, int hour, int min) const;
		int daysOfMonth(int year, int month);
		Date& dateOnly(bool value);
		const Error& error() const;
		void display(std::ostream& os);
		void read(std::istream& is);
		void setEmpty();  //added

		operator bool() const;
		friend bool operator==(const Date& lhs, const Date& rhs);
		friend bool operator!=(const Date& lhs, const Date& rhs);
		friend bool operator<(const Date& lhs, const Date& rhs);
		friend bool operator>(const Date& lhs, const Date& rhs);
		friend bool operator<=(const Date& lhs, const Date& rhs);
		friend bool operator>=(const Date& lhs, const Date& rhs);

		//newly added
		int getyear() const;
		int getmon() const;
		int getday() const;

	};

	std::ostream& operator <<(std::ostream& os, Date& right);
	std::istream& operator >>(std::istream& is, Date& right);


}
#endif