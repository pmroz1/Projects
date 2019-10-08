#pragma once
#include"build.h"

using namespace std;

class manage
{
private:
	lint manage_user(string username);
	lint add_train_connection();
	static bool cond_;
public:
	int view_connections();
	static lint login_mode();
	lint login(int16 login_m);
	int16 admin_mode();
	int16 user_mode();
	int16 logged_user(int16 choice, string username);
};
