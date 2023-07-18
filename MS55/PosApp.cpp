/* Citation and Sources...
Final Project Milestone 5
Module: PosApp
Filename: PosApp.cpp
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
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>
#include <fstream>
#include "PosApp.h"

using namespace std;
namespace sdds {
	void PosApp::run() {
		bool exit = false;

		do {
			int selection = menu();

			switch (selection) {
			case 1:
				this->listItems(true);
				break;

			case 2:
				this->addItem();
				break;

			case 3:
				this->removeItem();
				break;

			case 4:
				this->stockItem();
				break;

			case 5:
				this->POS();
				break;

			case 0:
				this->saveRecs();
				exit = true;
				break;
			}
		} while (exit == false);

	}


	int PosApp::menu() {
		int user_value;
		cout << "The Sene-Store" << endl;
		cout << "1- List items" << endl;
		cout << "2- Add item" << endl;
		cout << "3- Remove item" << endl;
		cout << "4- Stock item" << endl;
		cout << "5- POS" << endl;
		cout << "0- exit program" << endl;
		user_value = input();

		return user_value;


	}

	void PosApp::addItem() {

		Item* newItem = nullptr;
		actionTitle(ADD);
		char choice;
		if (nptr >= MAX_NO_ITEMS) {
			cout << "Inventory Full!";

		}
		else {

			do {

				cout << "Is the Item perishable? (Y)es/(N)o: ";
				cin >> choice;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					std::cout << "Invalid input, try again..." << std::endl;
				}
			} while (choice != 'Y' && choice != 'N' && choice != 'y' && choice != 'n');


			if (choice == 'Y' || choice == 'y') {
				newItem = new Perishable;
			}
			else if (choice == 'N' || choice == 'n') {
				newItem = new NonPerishable;
			}

			do {
				newItem->read(cin);
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << newItem << ", try again..." << endl;

				}
			} while (cin.fail());



			Iptr[nptr] = newItem;
			nptr++;



			cout << ">>>> DONE!..................................................................." << endl;







		}


	}

	void PosApp::removeItem() {

		cout << ">>>> Remove Item............................................................." << endl;
		int rowDelete = selectItem();
		cout << "Removing...." << endl;
		Iptr[rowDelete - 1]->displayType(POS_FORM);
		Iptr[rowDelete - 1]->write(cout);

		Iptr[rowDelete - 1]->setEmpty();
		delete Iptr[rowDelete - 1];
		Iptr[rowDelete - 1] = nullptr;


		for (int i = rowDelete - 1; i < nptr; i++) {
			Iptr[i] = Iptr[i + 1];
		}

		Iptr[nptr - 1] = nullptr;
		nptr--;

		cout << ">>>> DONE!..................................................................." << endl;
	}

	void PosApp::stockItem() {

		int row_stock;
		int enter;
		bool check = false;
		actionTitle(STOCK);
		row_stock = selectItem();
		cout << "Selected Item:" << endl;
		Iptr[row_stock - 1]->displayType(POS_FORM);
		Iptr[row_stock - 1]->write(cout);
		cout << "Enter quantity to add: ";

		do
		{
			std::cin.clear();
			std::cin >> enter;

			if (std::cin.fail()) {
				cout << "Invalid Integer, try again: ";
				std::cin.clear();
				std::cin.ignore(1000, '\n');

				if (std::cin.peek() == '\n') {
					std::cin.ignore();
				}
			}

			else {
				if (enter <= 0 || enter > (MAX_STOCK_NUMBER - Iptr[row_stock - 1]->quantity())) {
					cout << "[1<=value<=" << (MAX_STOCK_NUMBER - Iptr[row_stock - 1]->quantity()) << "], retry: Enter quantity to add: ";
					std::cin.ignore(1000, '\n');
				}
				else {
					check = true;
				}
			}


		} while (std::cin.fail() || check == false);

		Iptr[row_stock - 1]->addquantity(enter);

		cout << ">>>> DONE!..................................................................." << endl;



	}

	void PosApp::listItems(bool assest) {
		actionTitle(LIST);

		double total_asset = 0.0;

		sortItems(Iptr, nptr);
		std::cout << " Row | SKU    | Item Name          | Price |TX |Qty |   Total | Expiry Date |" << std::endl;
		std::cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << std::endl;



		// Loop through items up to nptr and display them in POS_LIST format
		for (int i = 0; i < nptr; i++) {
			Item* item = Iptr[i];
			int row = i + 1;
			std::cout << std::setw(4) << row << " | ";
			item->write(std::cout);
			std::cout << std::endl;

			total_asset += item->cost() * item->quantity();
		}


		// Print
		std::cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << std::endl;
		if (assest == true) {
			std::cout << std::setw(48) << "Total Asset: $  |" << std::setw(14) << std::fixed << std::setprecision(2) << total_asset << "|" << std::endl;
			std::cout << "-----------------------------------------------^--------------^" << std::endl << std::endl;
		}



	}

	void PosApp::POS() {

		actionTitle(PO);
		string input;
		char inputSku[50] = { '\0' };
		int index;
		bool check = false;
		bool exit = false;
		bool addBill = false;
		Bill bill{};
		bill.clear();

		do {
			while (!check || !exit) {
				cout << "Enter SKU or <ENTER> only to end sale..." << endl;
				cout << "> ";
				std::cin.ignore(1000, '\n');
				std::getline(cin, input);
				std::strcpy(inputSku, input.c_str());
				if (inputSku[0] == '\0') {
					exit = true;
					check = true;
				}
				else if (strlen(inputSku) > MAX_SKU_LEN || std::cin.fail()) {
					cout << "SKU too long";
					std::cin.clear();
					std::cin.putback('\n');

				}
				else if (inputSku[0] != '\0' && !std::cin.fail()) {

					index = searchsku(inputSku);

					if (index == -1) {

						cout << "!!!!! Item Not Found !!!!!" << endl;
						std::cin.clear();

						std::cin.putback('\n');
					}

					else {
						check = true;
						if (Iptr[index]->quantity() > 0) {
							Iptr[index]->deductquantity(1);
							addBill = bill.add(Iptr[index]);

							if (addBill) {
								Iptr[index]->displayType(POS_FORM);
								Iptr[index]->write(cout);
							}
							std::cout << endl;
							std::cout << ">>>>> Added to bill" << endl;
							std::cout << ">>>>> Total: " << std::fixed << std::setprecision(2) << bill.total() << endl;
							std::cout << std::resetiosflags(std::ios_base::floatfield);

						}
						else {
							cout << "Item out of stock" << endl;

							check = false;
						}

						std::cin.clear();


						std::cin.putback('\n');





					}

				}
				else {
					;
				}
			}

		} while (!exit);


		bill.print(cout);
		cout << std::left;


	}

	void PosApp::saveRecs() {

		actionTitle(SAVE);
		std::ofstream file(file_name);
		if (file) {

			for (int i = 0; i < nptr; i++) {

				Iptr[i]->save(file);
			}

		}



		file.close();

		deallocateItems();

		cout << "Goodbye!" << endl;
	}

	void PosApp::loadRecs() {

		cout << ">>>> Loading Items..........................................................." << endl;
		char item_type;

		deallocateItems();


		std::ifstream input(file_name);

		if (!input) {

			std::ofstream file(file_name);
			file.close();
			setEmpty();
			return;
		}
		else {


			nptr = 0;
			while (input.good() && nptr < MAX_NO_ITEMS) {
				try {
					item_type = '\0';
					input >> item_type;




					if (item_type == 'N') {
						Iptr[nptr] = new NonPerishable;
						Iptr[nptr]->load(input);
						nptr++;
					}
					else if (item_type == 'P') {

						Iptr[nptr] = new Perishable;
						Iptr[nptr]->load(input);
						nptr++;
					}
					else {
						;
					}





				}
				catch (std::bad_alloc& ex) {

					deallocateItems();
					input.close();
					throw;
				}
			}
			input.close();
		}

	}


	PosApp::PosApp() {
		this->setEmpty();
	}


	PosApp::PosApp(const char fname[]) {

		this->setEmpty();
		if (fname != nullptr && fname[0] != '\0' && strlen(fname) <= MAX_LEN_FILENAME) {
			strncpy(file_name, fname, strlen(fname));
			loadRecs();
		}
	}



	void PosApp::setEmpty() {
		file_name[0] = '\0';
	}


	//get user input
	int input()
	{

		int value = 0;
		bool success = false;

		do {
			cout << "> ";

			while (!(cin >> value))
			{
				cin.clear();
				cin.ignore(10000, '\n');

				cout << "Invalid Integer, try again: ";



			}

			if (value < 0 || value > 5) {

				cout << "[0<=value<=5], retry: ";
			}
			else {
				success = true;
			}




		} while (success == false);

		return value;


	}



	void PosApp::actionTitle(int menuNo) {

		char title[50];
		int selection = menuNo;
		std::cout << ">>>> ";
		std::cout.width(72);

		std::cout.fill('.');
		std::cout.setf(ios::left);

		switch (selection) {
		case 1:
			strcpy(title, "Listing Items");
			break;

		case 2:
			strcpy(title, "Adding Item to the store");
			break;

		case 3:
			strcpy(title, "Remove Items");
			break;

		case 4:
			strcpy(title, "Select an item to stock");

			break;

		case 5:
			strcpy(title, "Starting Point of Sale");
			break;

		case 6:
			strcpy(title, "Loading Items");
			break;

		case 7:
			strcpy(title, "DONE!");
			break;

		case 8:
			strcpy(title, "Item Selection by row number");
			break;

		case 0:
			strcpy(title, "Saving Data");
			break;
		}

		std::cout << title << endl;
		std::cout.fill(' ');
		std::cout.unsetf(ios::left);


	}

	void PosApp::deallocateItems() {

		for (int i = 0; i < nptr; i++) {
			if (Iptr[i] != nullptr) {
				Iptr[i]->m_error.clear();
				Iptr[i]->setEmpty();
				delete Iptr[i];

				Iptr[i] = nullptr;
			}
		}

		nptr = 0;
	}

	void PosApp::sortItems(Item* Iptr[], int nptr) {

		for (int i = 0; i < nptr; i++) {
			for (int j = 0; j < nptr - 1 - i; j++) {
				const char* name1 = Iptr[j]->getName();
				const char* name2 = Iptr[j + 1]->getName();
				int k = 0;
				while (true) {
					if (name1[k] < name2[k]) {
						break;
					}
					else if (name1[k] > name2[k]) {
						Item* temp = Iptr[j];
						Iptr[j] = Iptr[j + 1];
						Iptr[j + 1] = temp;
						break;
					}
					else {
						k++;
						if (name1[k] == '\0' && name2[k] == '\0') {
							break;
						}
					}
				}
			}
		}
	}

	PosApp::~PosApp() {
		deallocateItems();

	}



	//Additional Method for MS53
	int PosApp::selectItem() {

		int enter;
		bool check = false;
		actionTitle(SELECT);

		cout << "Press <ENTER> to start....";
		cin.ignore(100, '\n');
		std::string line;
		std::getline(std::cin, line);


		PosApp::listItems(false);

		cout << "Enter the row number: ";

		do
		{
			cin.clear();
			cin >> enter;

			if (cin.fail()) {
				cout << "Invalid Integer, try again: ";
				cin.clear();
				cin.ignore(1000, '\n');

				if (cin.peek() == '\n') {
					cin.ignore();
				}
			}

			else {
				if (enter < 0 || enter > nptr) {
					cout << "[1<=value<=" << nptr << "], retry: Enter the row number: ";
					cin.ignore(1000, '\n');
				}
				else {
					check = true;
				}
			}


		} while (cin.fail() || check == false);


		return enter;

	}



	int PosApp::searchsku(char sku[]) {
		int index = -1;
		for (int i = 0; i < nptr; i++) {
			if (!strcmp(Iptr[i]->getsku(), sku)) {
				index = i;
			}
			else {
				;
			}

		}
		return index;
	}

}
