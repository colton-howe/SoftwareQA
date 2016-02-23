#include "Transactions.h"
#include "User.h"

#include <string>
#include <iostream>

using namespace std;

Transactions::Transactions(){
	transaction_id_ = "";
}

User Transactions::Login(string name){
	if(name == "admin"){
		User admin(00000, "ADMIN", 0);
		cout << "Login Successful" << endl;
		//TO DO: Write login to transaction file.
		return admin;
	} else {
		//TO DO: Handle standard login by checking if valid account or not
		User admin(00000, name, 0);
		cout << "Login Successful" << endl;
	}
}

void Transactions::Withdrawal(User user){
	string name_input;
	if(user.GetName() == "ADMIN"){
		cout << "Please enter the account name: ";
		cin >> name_input;
		//TO DO: Compare account name to account file and see if name is valid
	} else {
		name_input = user.GetName();
	}
	int account_input;
	cout << "Please enter the account number: ";
	cin >> account_input;
	User found_user = ReadAccount(name_input, account_input);
	if(found_user.GetName().compare("ERROR") == 0){
		cout << "Error: Account not found." << endl;
	} else {
		int withdraw_amount;
		cout << "Please enter the amount to withdraw: ";
		cin >> withdraw_amount;
		bool valid_balance = true;
		//TO DO: Check constraints on account balance for withdraw
		if(valid_balance){
			//TO DO: Write the transaction to the transaction file and then update to a "day" list of accounts that have been changed.
			cout << "Transaction Successful" << endl;
		} else {
			cout << "Error: Withdrawal would result in invalid account balance." << endl;
		}
	}
}

void Transactions::Deposit(User user){
	string name_input;
	if(user.GetName() == "ADMIN"){
		cout << "Please enter the account name: ";
		cin >> name_input;
	} else {
		name_input = user.GetName();
	}
	int account_input;
	cout << "Please enter the account number: ";
	cin >> account_input;
	User found_user = ReadAccount(name_input, account_input);
	double deposit_amount;
	cout << "Please enter the amount to deposit: ";
	cin >> deposit_amount;
	bool valid_balance = true;
	double fee;
	if(found_user.GetPlan() == "NP"){
		fee = 0.10;
	} else {
		fee = 0.05;
	}
	if(found_user.GetNewBalance() + deposit_amount - 0.05 > 99999.99 || found_user.GetNewBalance() + deposit_amount - 0.05 < 0){
		valid_balance = false;
	} 
	if(valid_balance){
		//TO DO: Write the transaction to the transaction file and then update to a "day" list of accounts that have been changed.
		cout << "Transaction Successful" << endl;
	} else {
		cout << "Error: Withdrawal would result in invalid account balance." << endl;
	}
}

void Transactions::Transfer(User user){
	//TO DO: Do this entire method
}

void Transactions::PayBill(User user){
	//TO DO: Do this entire method
}

void Transactions::Create(User user){
	//TO DO: Do this entire method
}

void Transactions::Delete(User user){
	//TO DO: Do this entire method
}

void Transactions::Enable(User user){
	//TO DO: Do this entire method
}

void Transactions::Disable(User user){
	//TO DO: Do this entire method
}

void Transactions::ChangePlan(User user){
	//TO DO: Do this entire method
}

User Transactions::ReadAccount(string name, int account){
	ifstream accounts("accounts.txt");
	ifstream touched_accounts("daily_changes.txt");
	string line;
	while(getline(touched_accounts, line)){
		token = strtok (line, " ");
		int account_to_check = stoi(token, nullptr, 10);
	  	if(account_to_check == account_number){
			string account_name = strtok(NULL, " ");
			string status = strtok(NULL, " ");
			string balance = strtok(NULL, " ");
			string::size_type sz;
			User found_account(account_to_check, account_name, stod(balance, &sz));
			if(status.compare("D") == 0){
				found_account.SetStatus();
			}
			return found_account;
		}
	}
	while(getline(accounts, line)){
		token = strtok (line, " ");
		int account_to_check = stoi(token, nullptr, 10);
	  	if(account_to_check == account_number){
			string account_name = strtok(NULL, " ");
			string status = strtok(NULL, " ");
			string balance = strtok(NULL, " ");
			string::size_type sz;
			User found_account(account_to_check, account_name, stod(balance, &sz));
			if(status.compare("D") == 0){
				found_account.SetStatus();
			}
			return found_account;
		}
	}
	User error(0,"ERROR",0);
	return error;
}

User Transactions::Logout(){
	User out(00000, "NULL", 0);
	return out;
}
