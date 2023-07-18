/* Citation and Sources...
Final Project Milestone 5
Module: PosApp
Filename: PosApp.h
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

#ifndef SDDS_POSAPP_H_
#define SDDS_POSAPP_H_
//#define MAX_LEN_FILENAME 255
#define LIST 1
#define ADD 2
#define REMOVE 3
#define STOCK 4
#define PO 5
#define LOAD 6
#define SAVE 0
#define DONE 7
#define SELECT 8


#include <iostream>
#include "POS.h"
#include "Item.h"
#include "Perishable.h"
#include "NonPerishable.h"
#include "Utils.h"
#include "Bill.h"

namespace sdds {
	class PosApp {

	private:
		char file_name[MAX_LEN_FILENAME + 1] = { '\0' };
		void addItem();
		void removeItem();
		void stockItem();
		void listItems(bool assest);
		void POS();
		void saveRecs();
		void loadRecs();
		void setEmpty();



		Item* Iptr[MAX_NO_ITEMS];
		int nptr = 0;



		void actionTitle(int menuNo);




	public:
		int menu();
		void run();


		//Constructor
		PosApp();
		PosApp(const char fname[]);
		PosApp(const PosApp& posapp) = delete;
		PosApp& operator=(const PosApp& posapp) = delete;
		~PosApp();


		void deallocateItems();
		void sortItems(Item* Iptr[], int nptr);

		//Additional Method for MS53
		int selectItem();

		//Additional Method for MS55
		int searchsku(char sku[]);

	};


	//Helper function
	std::istream& operator>>(std::istream& istr, PosApp& right);
	std::ostream& operator<<(std::ostream& ostr, const PosApp& right);

	//UserInterface
	int input();




}



#endif // !POSAPP_
