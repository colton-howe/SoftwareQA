#include "User.h"
#include "Transactions.h"

#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

main(){
	User active_user(00000, "NULL", 0);
	while(true){
		string input;
		Transactions trans;
		cout << "Please enter a command: ";
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		if(active_user.GetName() == "NULL"){
			if(input == "login"){
				cout << "Please enter the session type: ";
				cin >> input;
				transform(input.begin(), input.end(), input.begin(), ::tolower);
				if(input == "admin"){
					active_user = trans.Login("admin");
				} else if(input == "standard") {
					cout << "Please enter the account name: ";
					cin.ignore(1, '\n');
					getline(cin, input);
					transform(input.begin(), input.end(), input.begin(), ::toupper);
					active_user = trans.Login(input);
				} else {
					cout << "Error: Please enter 'standard' or 'admin' as your session type." << endl;
				}
			} else {
				cout << "Please login first before issuing commands" << endl;
			}
		} else {
			if(input == "login"){
				cout << "Error: Already logged into account" << endl;
			} else if (input == "withdrawal"){
				trans.Withdrawal(active_user);
			} else if (input == "transfer"){
				trans.Transfer(active_user);
			} else if (input == "paybill"){
				trans.PayBill(active_user);
			} else if (input == "deposit"){
				trans.Deposit(active_user);
			} else if (input == "create"){
				trans.Create(active_user);
			} else if (input == "delete"){
				trans.Delete(active_user);
			} else if (input == "disable"){
				trans.Disable(active_user);
			} else if (input == "enable"){
				trans.Enable(active_user);
			} else if (input == "changeplan"){
				trans.ChangePlan(active_user);
			} else if (input == "logout"){
				active_user = trans.Logout();
			} else {
				cout << "Error: Not a valid command." << endl;
			}
		}
	}
}