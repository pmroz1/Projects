#include "build.h"

struct ticket
{
	string from;
	string to;
	string date;
	string owner;
	lint seat_no = 0;
	string first_class; // yes/No
};

struct train
{
	string name;
	string from;
	string destination;
	string available_seats;
	lint day = 0;
	lint month = 0;
	lint year = 0;
	lint cost1c = 0;
	lint cost2c = 0;
};

struct User_data
{
	string fName;
	string lName;
	string username;
	string password;
};

lint manage::login_mode()
{
	cout << "\n..............................................................." << endl;
	cout << "         ................LOGIN MENU....................." << endl;
	cout << "..............................................................." << endl;
	cout << "Login as:\n1 Admin\n2 User\n3 Close application\nChoice: ";
	int choice;
	cin >> choice;
	while ((choice > 4) || (choice < 1))
	{
		cin >> choice;
	}
	if (choice == 1)
	{
		return 1;
	}
	if (choice == 3)
	{
		return 3;
	}
	return 2;
}

lint manage::login(const int16 login_m)
{
	const string authentication_pa = "cplusplus";
	string password;
	//Admin
	if (login_m == 1)
	{
		cout << "Password: ";
		cin >> password;
		while (password != authentication_pa)
		{
			cout << "Wrong Password\n Enter 'back' to go back to login menu" << endl;
			cout << "Password: ";
			cin >> password;
			if (password == "back")
			{
				return login(login_mode());
			}
		}
		return admin_mode();
	}
	if (login_m == 3)
	{
		cout << "\nClosing application." << endl;
		return r_success;
	}
	user_mode();
	return r_other;
}

int16 manage::admin_mode()
{
	int16 choice;
	string filename;
	string username;
	ofstream write_file;
	ifstream read_file;

	cout << "..............................................................." << endl;
	cout << "       ................ADMIN MENU...................." << endl;
	cout << "..............................................................." << endl;
	cout << "\nWhat you want to do:"
		"\n1) Create User account"
		"\n2) Manage account"
		"\n3) Delete User\n"
		"4) Add train connection\n"
		"5) Quit\n"
		"Your choice: ";
	cin >> choice;

	User_data profile;

	//show array of used id

	if (choice == 1)
	{
		//create user account

		cout << "\nName: ";
		cin >> profile.fName;
		cout << "\nLast name: ";
		cin >> profile.lName;
		profile.password = profile.fName + "123";
		cout << "\nPassword generated: " << profile.password;
		profile.username = profile.fName + profile.lName + "_RRS";

		filename = profile.username;

		write_file.open(filename.c_str());
		if (!write_file.good())
		{
			cout << "\nCannot open the file";
			return r_cant_open_file;
		}
		write_file << "Username: " << profile.username << endl;
		write_file << "First name: " << profile.fName << endl;
		write_file << "Last Name: " << profile.lName << endl;
		write_file << "Password: " << profile.password << endl;
		write_file.close();

		cout << "\nUser account created.\n";
		return admin_mode();
	}

	if (choice == 2)
	{
		//Manage User Account
		cout << "Enter username: ";
		cin >> username;
		cout << endl;
		filename = username + "_RRS";
		read_file.open(filename.c_str());

		if (read_file.is_open())
		{
			std::cout << read_file.rdbuf();
		}

		cout << endl;
		read_file.close();
		manage_user(username);
	}

	if (choice == 3)
	{
		//TODO
		//delete account
	}

	if (choice == 4)
	{
		add_train_connection();
		return r_success;
	}

	if (choice == 5)
	{
		return r_success;
	}
	return int16(r_success);
}

int16 manage::user_mode()
{
	string login_u;
	string password;
	string password_authentication;

	int16 i = 0;
	string helper;

	cout << "..............................................................." << endl;
	cout << "        ................USER MENU....................." << endl;
	cout << "..............................................................." << endl;
	cout << "Login: ";
	cin >> login_u;
	cout << "Password: ";
	cin >> password;

	const auto filename = login_u + "_RRS";

	ifstream basic_ifstream;
	basic_ifstream.open(filename.c_str());
	if (!basic_ifstream.is_open())
	{
		cout << "\nCannot find user" << endl;
		return (login(login_mode()));
	}

	while (!basic_ifstream.eof())
	{
		getline(basic_ifstream, helper);
		if (i == 3)
		{
			password_authentication = helper;
		}
		i++;
	}
	/*cout << passwordAuthentication;
	cout << password;*/

	basic_ifstream.close();

	const auto compare = password.compare(password_authentication);
	if (compare)
	{
		cout << "\nLogged in.\n"
			".............................................."
			"\nWhat you want to do: "
			"\n1 Check my ticket"
			"\n2 Buy ticket"
			"\n3 Cancel Ticket"
			"\n4 Log out\n"
			".............................................." << endl;
		int16 choice;
		cout << "Choice: ";
		cin >> choice;
		logged_user(choice, login_u);
	}
	return login(login_mode());
}

int16 manage::logged_user(const int16 choice, string username)
{
	if (choice == 1)
	{
		//view ticket
		/*ifstream filein;

		filein.close();*/
	}
	if (choice == 2)
	{
		//buy ticket
		view_connections();
		ticket newTicket;
	}
	if (choice == 3)
	{
		//cancel ticket
	}
	if (choice == 4)
	{
		//log out
		cout << "\nLogged out" << endl;
		return r_success;
	}
	return r_success;
}

lint manage::manage_user(string username)
{
	cout << "..............................................................." << endl;
	cout << ".................MANAGE USER ACCOUNT MENU......................" << endl;
	cout << "..............................................................." << endl;
	cout << "1 Change account details."
		"\n2 Manage Tickets."
		"\n3 Quit."
		<< endl;

	int16 choice;
	cin >> choice;
	if (cin.fail())
	{
		return manage_user(username);
	}

	string strtmp;

	if (choice == 1)
	{
		User_data profile;

		auto filename = username + "_RRS";
		ofstream basic_ofstream;
		basic_ofstream.open(filename.c_str());

		if (!basic_ofstream)
		{
			cout << "Error opening files!" << endl;
			return manage_user(username);
		}

		profile.username = username;
		cout << "\nName: ";
		cin >> profile.fName;
		cout << "\nLast name: ";
		cin >> profile.lName;
		cout << "\nPassword: ";
		cin >> profile.password;

		basic_ofstream << "Username: " << profile.username << endl;
		basic_ofstream << "First name: " << profile.fName << endl;
		basic_ofstream << "Last Name: " << profile.lName << endl;
		basic_ofstream << "Password: " << profile.password << endl;
		basic_ofstream.close();

		cout << "\nData changed successfully." << endl;
		return manage_user(username);
	}
	if (choice == 2)
	{
		//TODO
		//tickets
	}
	if (choice == 3)
	{
		return admin_mode();
	}

	return lint();
}

lint manage::add_train_connection()
{
	cout << "..............................................................." << endl;
	cout << "................ADD TRAIN CONNECTION MENU......................" << endl;
	cout << "..............................................................." << endl;

	train T1;
	string name;
	cout << "\nEnter Train name: ";
	cin >> T1.name;
	cout << "\nFrom: ";
	cin >> T1.from;
	cout << "\nDestination: ";
	cin >> T1.destination;
	cout << "\nNumber of seats: ";
	cin >> T1.available_seats;
	cout << "\nDay: ";
	cin >> T1.day;
	cout << "\nMonth: ";
	cin >> T1.month;
	cout << "\nYear: ";
	cin >> T1.year;
	cout << "\nCost first class ticket: ";
	cin >> T1.cost1c;
	cout << "\nCost second class ticket: ";
	cin >> T1.cost2c;

	ofstream fileout;
	string filename = T1.name + "_train";
	fileout.open(filename.c_str());
	if (!fileout)
	{
		cout << "Cannot open the file.";
		return r_cant_open_file;
	}
	fileout << "Train name: " << T1.name << endl;
	fileout << "From : " << T1.from << endl;
	fileout << "Destination: " << T1.destination << endl;
	fileout << "available seats: " << T1.available_seats << endl;
	fileout << "Date: " << T1.day << "." << T1.month << "." << T1.year << endl;
	fileout << "Cost of first class ticket: " << T1.cost1c << endl;
	fileout << "Cost of second class ticket: " << T1.cost2c << endl;

	fileout.close();

	cout << "\nConnection Created. Details below." << endl << endl;
	cout << "\t\t\t\tTrain name.........." << T1.name << ".........." << endl;
	cout << "\t\t\t\tFrom.." << T1.from << "...destination.." << T1.destination << ".." << endl;
	cout << "\t\t\t\tDate...." << T1.day << "." << T1.month << "." << T1.year << "......." << endl;
	cout << "\t\t\t\tTicket cost..first class.." << T1.cost1c << "..second class.." << T1.cost2c << ".." << endl <<
		endl;

	ofstream trainConn;
	trainConn.open("Connections", ios_base::app);
	if (!trainConn)
	{
		cout << "\nCant open file." << endl;
		return r_cant_open_file;
	}
	string write_filename = T1.name + "_train";
	trainConn << write_filename << "\n";
	trainConn.close();

	return admin_mode();
}

int manage::view_connections() //buy
{
	ifstream view_conn;
	string str;
	vector<string> trains_connections;
	view_conn.open("Connections");

	if (!view_conn.is_open())
	{
		cout << "\nCannot open file." << endl;
		return r_cant_open_file;
	}
	cout << "\n................................................" << endl;
	cout << "..........Showing Available Connections.........." << endl;
	cout << "................................................\n" << endl;
	while (!view_conn.eof())
	{
		getline(view_conn, str);
		if (!str.empty())
		{
			auto compare = str.compare("\0");
			if (compare)
				trains_connections.push_back(str);
		}
		ifstream trains;
		trains.open(str.c_str());
		if (trains.is_open())
		{
			std::cout << trains.rdbuf();
			cout << "\n.......................................\n" << endl;
		}
		trains.close();
	}

	cout << "..............................."
		"\n\tChoose connection\n"
		"................................\n" << endl;
	int16 i = 0;

	cond_ = i < trains_connections.size();
	for (i = 0; cond_; i++)
	{
		//if(!trains_connections.empty())
		cout << i << " " << trains_connections[i] << "\n";
	}
	int choice_oftrain;
	string username;
	string passenger_name;
	int16 seat;

	cout << "\nChoose connection";
	cin >> choice_oftrain;
	cout << "\nUsername: ";
	cin >> username;
	cout << "\nPassenger name: ";
	cin >> passenger_name;
	cout << "\n(odd numbers are seats next to corridor)\nChoose seat: ";
	cin >> seat;


	cout << "\nCreating reservation\n" << endl
		<< "\t\t\t..................Reservation...................." << endl;

	ifstream trains;
	trains.open(trains_connections[choice_oftrain].c_str());
	if (trains.is_open())
	{
		std::cout << trains.rdbuf();
	}
	trains.close();
	cout << "\n\t\t\t         Passenger...." << passenger_name << ".....Seat....." << seat << endl
		<< "\n\t\t\t\t\t   ATTENTION \n\t\t    Reservations can be canceled only,till the day of departure!\n" << endl;
	cout << "\n\t\t\t...................................................\n" << endl;

	return r_success;
}
