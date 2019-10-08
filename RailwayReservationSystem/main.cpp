#include"build.h"

#ifndef DEBUG
#define DEBUG 1

int main() {
	manage run;
	lint result = 0;
	try {
		result=run.login(run.login_mode());
	}
	catch (const std::exception& e) {
		std::cout << " a standard exception was caught, with message '"
			<< e.what() << "'\n";
	}
	return result;
}
#endif

//TO DO

//user menu

//manage tickets
//file of trains

//std::string wiersz;
//while (std::getline(plik, wiersz))
//std::cout << wiersz << std::endl;

//struct ticket {
//	string from;
//	string to;
//	string date;
//	string owner;
//	float cost;
//};

//struct User_data {
//	string fName;
//	string lName;
//	string username;
//	string password;
//};

//struct train {
//	string name;
//	string from;
//	string destination;
//	string avaiableseats;
//	lint day;
//	lint month;
//	lint year;
//};

//cout << "\nConnection Created. Details below." << endl << endl;
//cout << "\t\t\t\tTrain name.........." << T1.name << ".........." << endl;
//cout << "\t\t\t\tFrom.." << T1.from << "...destination.." << T1.destination << ".." << endl;
//cout << "\t\t\t\tDate...." << T1.day << "." << T1.month << "." << T1.year << "......." << endl;
//cout << "\t\t\t\tTicket cost..first class.." << T1.cost1c << "..second class.." << T1.cost2c << ".." << endl << endl;