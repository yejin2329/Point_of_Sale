/* Citation and Sources...
Final Project Milestone 5
Module: Date
Filename: Date.cpp
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
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <typeinfo>
#include <string>
#include "POS.h"
#include "Error.h"
#include "Date.h"

using namespace std;
namespace sdds {


	Date::Date() {
		int year_, month_, day_, hour_, minute_;
		Date::getSystemDate(year_, month_, day_, hour_, minute_, false);
		year = year_;
		month = month_;
		day = day_;
		hour = hour_;
		minute = minute_;
		error_.clear();

	}
	Date::Date(int yr, int mon, int day_) {
		error_.clear();
		this->year = yr;
		this->month = mon;
		this->day = day_;
		hour = 0;
		minute = 0;

		date_Only = true;
		validate();
	}
	Date::Date(int yr, int mon, int day_, int hr) {
		error_.clear();
		this->year = yr;
		this->month = mon;
		this->day = day_;
		this->hour = hr;
		this->minute = 0;
		date_Only = false;
		validate();
	}
	Date::Date(int yr, int mon, int day_, int hr, int min) {
		error_.clear();
		this->year = yr;
		this->month = mon;
		this->day = day_;
		this->hour = hr;
		this->minute = min;

		date_Only = false;
		validate();
	}

	void Date::setEmpty() {
		error_.clear();
		year = 0;
		month = 0;
		day = 0;
		hour = 0;
		minute = 0;
		date_Only = false;
	}

	Date::~Date() {
		setEmpty();

	}

	//Copy constructor
	Date::Date(const Date& other) {
		if (&other != nullptr) {
			*this = other;
		}
	}
	Date& Date:: operator = (const Date& other) {
		if (this != &other && &other != nullptr) {
			this->year = other.year;
			this->month = other.month;
			this->day = other.day;
			this->date_Only = other.date_Only;
			this->hour = other.hour;
			this->minute = other.minute;
			this->error_ = other.error_;
		}
		return *this;
	}


	void Date::getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly) {
		time_t t = time(NULL);
		tm lt = *localtime(&t);
		day = lt.tm_mday;
		mon = lt.tm_mon + 1;
		year = lt.tm_year + 1900;
		if (dateOnly) {
			hour = min = 0;
		}
		else {
			hour = lt.tm_hour;
			min = lt.tm_min;
		}
	}

	bool Date::validate() {
		error_.clear();
		int maxDay = daysOfMonth(year, month);
		int success = 0;
		if (year < MIN_YEAR || year > MAX_YEAR) {
			error_.set("Invalid Year");

		}
		else {
			success++;
		}

		if (month < 1 || month > 12) {
			error_.set("Invalid Month");


		}
		else {
			success++;
			if (day < 1 || day > maxDay) {
				error_.set("Invalid Day");
				return false;
			}
			else {
				success++;
			}

		}




		if (hour < 0 || hour > 23) {
			error_.set("Invalid Hour");
		}

		else {
			success++;
		}

		if (minute < 0 || minute > 59) {
			error_.set("Invlid Minute");

		}
		else {
			success++;
		}


		if (success == 5) {
			return true;
		}
		else {
			return false;
		}

	}

	int Date::uniqueDateValue(int year, int mon, int day, int hour, int min) const {
		return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
	}

	int Date::daysOfMonth(int year, int month) {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = month >= 1 && month <= 12 ? month : 13;
		mon--;
		return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	//operator overloading
	bool operator==(const Date& lhs, const Date& rhs) {
		return lhs.uniqueDateValue(lhs.year, lhs.month, lhs.day, lhs.hour, lhs.minute) ==
			rhs.uniqueDateValue(rhs.year, rhs.month, rhs.day, rhs.hour, rhs.minute);
	}
	bool operator!=(const Date& lhs, const Date& rhs) {
		return lhs.uniqueDateValue(lhs.year, lhs.month, lhs.day, lhs.hour, lhs.minute) !=
			rhs.uniqueDateValue(rhs.year, rhs.month, rhs.day, rhs.hour, rhs.minute);
	}
	bool operator<(const Date& lhs, const Date& rhs) {
		return lhs.uniqueDateValue(lhs.year, lhs.month, lhs.day, lhs.hour, lhs.minute) <
			rhs.uniqueDateValue(rhs.year, rhs.month, rhs.day, rhs.hour, rhs.minute);
	}
	bool operator>(const Date& lhs, const Date& rhs) {
		return lhs.uniqueDateValue(lhs.year, lhs.month, lhs.day, lhs.hour, lhs.minute) >
			rhs.uniqueDateValue(rhs.year, rhs.month, rhs.day, rhs.hour, rhs.minute);
	}
	bool operator<=(const Date& lhs, const Date& rhs) {
		return lhs.uniqueDateValue(lhs.year, lhs.month, lhs.day, lhs.hour, lhs.minute) <=
			rhs.uniqueDateValue(rhs.year, rhs.month, rhs.day, rhs.hour, rhs.minute);
	}
	bool operator>=(const Date& lhs, const Date& rhs) {
		return lhs.uniqueDateValue(lhs.year, lhs.month, lhs.day, lhs.hour, lhs.minute) >=
			rhs.uniqueDateValue(rhs.year, rhs.month, rhs.day, rhs.hour, rhs.minute);
	}


	//Date Only Modifier Method
	Date& Date::dateOnly(bool value) {
		date_Only = value;
		if (date_Only) {
			hour = 0;
			minute = 0;
		}
		return *this;
	}

	//overloading bool operator
	Date::operator bool() const {
		return (!error_);
	}

	//the error query
	const Error& Date::error() const {
		return this->error_;
	}

	void Date::display(std::ostream& os) {
		if (error()) {


			if (date_Only) {
				os << error_ << '(' << year << '/' << std::setfill('0') << std::setw(2) << month << '/' << std::setw(2) << day << ')';
			}
			else {

				os << error_ << '(' << year << '/' << std::setfill('0') << std::setw(2) << month << '/' << std::setw(2) << day;
				os << std::setfill(' ') << std::setw(2) << ", ";
				os << std::setfill('0') << std::setw(2) << hour << ':' << std::setw(2) << minute << ')';

			}


		}
		else {
			if (date_Only) {
				os << std::setw(4) << year << '/' << std::right << std::setfill('0') << std::setw(2) << month << '/' << std::setw(2) << day;
			}
			else {

				os << std::setw(4) << year << '/' << std::right << std::setfill('0') << std::setw(2) << month << '/' << std::setw(2) << day << ", " << std::setw(2) << hour << ':' << std::setw(2) << minute;

			}
		}
	}

	std::ostream& operator <<(std::ostream& os, Date& right) {
		right.display(os);
		return os;
	}

	std::istream& operator >>(std::istream& is, Date& right) {
		right.read(is);
		return is;
	}

	void Date::read(std::istream& is) {

		char delimiter;
		int success = 0;
		int yr = 0, mon = 0, dy = 0, hr = 0, min = 0;
		year = 0; month = 0; day = 0; hour = 0; minute = 0;
		error_.clear();


		std::string input;
		if (is.peek() == '\n') {
			is.ignore();
		}
		std::getline(is, input);
		std::stringstream ss(input);
		if (is.eof()) {
			is.clear();

		}
		is.putback('\n');




		//year


		if (ss >> yr) {
			success += 1;
		}
		else {
			error_.set("Cannot read year entry");
			yr = 0;
		}
		if (success == 1) {
			ss >> delimiter;

			// month
			if (ss >> mon) {
				success += 1;
			}
			else
			{
				error_.set("Cannot read month entry");
				mon = 0;

			}
		}
		if (success == 2) {
			ss >> delimiter;
			// Read day
			if (ss >> dy) {
				success += 1;
			}
			else {
				error_.set("Cannot read day entry");
				dy = 0;
			}
		}
		if (success == 3) {
			ss >> delimiter;

			if (!ss.eof()) {
				// Read hour
				if (ss >> hr) {
					success += 1;
				}
				else {
					error_.set("Cannot read hour entry");
					hr = 0;
				}
				// Read minute
				if (success == 4) {
					ss >> delimiter;
					if (ss >> min) {
						success += 1;
					}
					else {
						error_.set("Cannot read minute entry");
						min = 0;

					}
				}

			}




		}
		if (error_) {
			this->year = yr;
			this->month = mon;
			this->day = dy;
			this->hour = hr;
			this->minute = min;
		}


		// Set the date
		if (!(error_)) {
			this->year = yr;
			this->month = mon;
			this->day = dy;

			if (success == 3) {
				this->date_Only = true;
				this->hour = 0;
				this->minute = 0;
				validate();
			}
			if (success == 5) {
				this->date_Only = false;
				this->hour = hr;
				this->minute = min;
				validate();
			}

		}



	}


	//newly added
	int Date::getyear() const {
		return year;
	}
	int Date::getmon() const {
		return month;
	}
	int Date::getday() const {
		return day;
	}

}

