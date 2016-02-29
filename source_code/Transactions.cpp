#include "Transactions.h"
#include "User.h"
#include "TransactionsFile.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <algorithm>
#include <iomanip>

using namespace std;

Transactions::Transactions(){
	transaction_id_ = "";
}

User Transactions::Login(string name){
	//If the user logins in as admin, log them in automatically. Else, prompt for account name
	if(name == "admin"){
		User admin(00000, "ADMIN", 0);
		cout << "Login Successful" << endl;
		//TO DO: Write login to transaction file.
		return admin;
	} else {
		//Go through the accounts folder, and check if that name is attached to at least 1 account. If so, login. Else, error.
		ifstream accounts("accounts.txt");
		string line;
		while(getline(accounts, line)){
			size_t found = line.find(name);
			if(found != string::npos){
				cout << "Login Successful" << endl;
				//TO DO: Write login to transaction file.
				User found_user(0, name, 0);
				return found_user;	
			} 
		}
		cout << "Error: Account not found under that name." << endl;
		User null(00000, "NULL", 0);
		return null;
	}
}

void Transactions::Withdrawal(User user){
	cout << "------------------" << endl;
	cout << "|   Withdrawal   |" << endl;
	cout << "------------------" << endl;
	string name_input;
	//If the user is an admin, ask for a name, otherwise, auto fill in name.
	if(user.GetName() == "ADMIN"){
		cout << "Please enter the account name: ";
		cin.ignore(1, '\n');
		getline(cin, name_input);
		transform(name_input.begin(), name_input.end(), name_input.begin(), ::toupper);
	} else {
		name_input = user.GetName();
	}
	//Ask for the user to enter an account number
	int account_input;
	cout << "Please enter the account number: ";
	cin >> account_input;
	//Call ReadAccount to check if an account with that name and number exist
	User found_user = ReadAccount(name_input, account_input);
	//If ReadAccount returns an account with name "ERROR", then the account doesn't exist. otherwise, continue with withdrawal
	if(found_user.GetName().compare("ERROR") == 0){
		cout << "Error: Account not found." << endl;
	} else {
		//Ask for withdraw amount
		int withdraw_amount;
		cout << "Please enter the amount to withdraw: ";
		cin >> withdraw_amount;
		//Before checking withdraw amount, check which fee we need to charge. 0.10 if not a student, 0.05 if a student
		double fee;
		if(found_user.GetPlan() == "NP"){
			fee = 0.10;
		} else {
			fee = 0.05;
		}
		//Check for error conditions withdrawal > balance, withdrawal > 500 when not admin, withdrawal not divisible by 5.
		if(fee + withdraw_amount > found_user.GetNewBalance()){
			cout << "Error: Withdrawal amount + fee is greater then balance" << endl;
		} else if (user.GetName() != "ADMIN" && withdraw_amount > 500){
			cout << "Error: Only admin may withdraw more then $500.00" << endl;
		} else if (withdraw_amount < 0 || (withdraw_amount % 5) != 0){
			cout << "Error: Invalid Withdrawal amount" << endl;
		} else {
			//Write transaction log
			TransactionsFile trans("01", found_user.GetName(), found_user.GetNumber(), withdraw_amount);
			trans.WriteTransaction();
			//Update the users account balance.
			found_user.UpdateNewBalance(0-withdraw_amount);
			found_user.UpdateBalance();
			//Update daily account file
			UpdateDay(found_user);
			cout << "Transaction Successful" << endl;
		}
	}
}

void Transactions::Deposit(User user){
	//Need to redo,
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
	if(found_user.GetNewBalance() + deposit_amount - 0.05 > 99999.99 || found_user.GetNewBalance() + deposit_amount - fee < 0){
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
	//Look through the daily account changes and see if the account is there. if it is, pull information from that.
	while(getline(touched_accounts, line)){
		string account_name;
		string account_status;
		string account_balance;
		string account_to_check;
		//Go through each line and process the information in it.
		for(int i = 0; i < 36; i++){
			if(i >= 0 && i < 5){
				account_to_check = account_to_check + line[i];
			} else if (i > 5 && i < 25) {
				if(line[i] == ' ' && line[i+1] == ' '){
					//Don't do anything, its a filler space
				} else {
					account_name = account_name + line[i];
				}
			} else if (i > 25 && i < 27){
				account_status = account_status + line[i];
			} else if (i > 27){
				account_balance = account_balance + line[i];
			}
		}
		istringstream balance_buf(account_balance);
		double balance;
		balance_buf >> balance;
		istringstream number_buf(account_to_check);
		int account_num;
		number_buf >> account_num;
		//If the account is the account we are looking for, put its information into a user and return it.
	  	if(account_num == account && account_name.compare(name) == 0){
			User found_account(account_num, account_name, balance);
			if(account_status.compare("D") == 0){
				found_account.SetStatus();
			}
			return found_account;
		}
	}
	//If not in the daily accounts, look through the accounts file and see if the account is there.
	while(getline(accounts, line)){
		string account_name;
		string account_status;
		string account_balance;
		string account_to_check;
		//Process the information pulled from the account line
		for(int i = 0; i < 36; i++){
			if(i >= 0 && i < 5){
				account_to_check = account_to_check + line[i];
			} else if (i > 5 && i < 25) {
				if(line[i] == ' ' && line[i+1] == ' '){
					//Don't do anything, its a filler space
				} else {
					account_name = account_name + line[i];
				}
			} else if (i > 25 && i < 27){
				account_status = account_status + line[i];
			} else if (i > 27){
				account_balance = account_balance + line[i];
			}
		}
		istringstream balance_buf(account_balance);
		double balance;
		balance_buf >> balance;
		istringstream number_buf(account_to_check);
		int account_num;
		number_buf >> account_num;
		//If account is found, return a user that contains its information.
	  	if(account_num == account && account_name.compare(name) == 0){
			User found_account(account_num, account_name, balance);
			if(account_status.compare("D") == 0){
				found_account.SetStatus();
			}
			return found_account;
		}
	}
	//If no account with that name/number is found, return an error user.
	User error(0,"ERROR",0);
	return error;
}

void Transactions::UpdateDay(User changed_user){
	//Load the daily changes text file that stores all changed accounts for the day
	ifstream touched_accounts("daily_changes.txt");
	ofstream daily_changes;
	string line;
	string entire_file = "";
	string found_line = "NULL";
	//Parse through the file and search for a line matching the change user
	while(getline(touched_accounts, line)){
		//Store each line in an entire file line. Important for later
		entire_file = entire_file + line + "\n";
		string account_name;
		string account_status;
		string account_balance;
		string account_to_check;
		//Go through each line and process the information in it.
		for(int i = 0; i < 36; i++){
			if(i >= 0 && i < 5){
				account_to_check = account_to_check + line[i];
			} else if (i > 5 && i < 25) {
				if(line[i] == ' ' && line[i+1] == ' '){
					//Don't do anything, its a filler space
				} else {
					account_name = account_name + line[i];
				}
			} else if (i > 25 && i < 27){
				account_status = account_status + line[i];
			} else if (i > 27){
				account_balance = account_balance + line[i];
			}
		}
		istringstream balance_buf(account_balance);
		double balance;
		balance_buf >> balance;
		istringstream number_buf(account_to_check);
		int account_num;
		number_buf >> account_num;
		//If we find a matching user, store the found user for later.
		if(changed_user.GetNumber() == account_num && account_name.compare(changed_user.GetName()) == 0){
			found_line = line;
		}
	}
	//Remove the last newline from the file.
	entire_file.replace(entire_file.end()-1,entire_file.end(),"");
	//If we didn't find the account, format a string correctly containing the users information and put it int their with their new balance.
	//If we did find the account, update the balance of the account in the file.
	if(found_line != "NULL"){
		daily_changes.open("daily_changes.txt", ios::app);
		string found_name = changed_user.GetName();
		if(changed_user.GetName().length() < 20){
			for(int i = changed_user.GetName().length(); i < 20; i++){
				found_name.insert(0," ");
			}
		}
		stringstream status_buf;
		status_buf << changed_user.GetStatus();
		string found_status = status_buf.str();
		stringstream balance_buf;
		balance_buf << setprecision(2) << fixed << changed_user.GetBalance();
		string str_balance = balance_buf.str();
		if(str_balance.length() < 8){
			for(int i = 0; i < 9-str_balance.length(); i++){
				str_balance.insert(0,"0");
			}
		}
		int account_length;
		int num_length = changed_user.GetNumber();
		//For each time the number is succesfully divided by 10, increase the integer length.
		if(changed_user.GetNumber() > 0){
			for(account_length = 0; num_length > 0; account_length++){
				num_length = num_length / 10;
			}
		}
		//Make a string stream to type cast the integer to a string
		stringstream account_buf;
		account_buf << changed_user.GetNumber();
		string str_number = account_buf.str();
		//If the length of account number < 5, pad 0's until length is 5.
		if(account_length < 5){
			for(int i = 0; i < 5-account_length; i++){
				str_number.insert(0,"0");
			}
		}
		string new_line = str_number + " " + found_name + " " + found_status + " " + str_balance + "\n";
		daily_changes << new_line;
		daily_changes.close();
	} else {
		//Format the new balance correctly
		stringstream balance_buf;
		balance_buf << setprecision(2) << fixed << changed_user.GetBalance();
		string str_balance = balance_buf.str();
		if(str_balance.length() < 8){
			for(int i = 0; i < 9-str_balance.length(); i++){
				str_balance.insert(0,"0");
			}
		}
		//Change the balance of the account to the new account
		string editted_line = found_line.replace(28,8,str_balance);
		//Go through the string containg the entire file and replace the line we had with the new editted line.
		entire_file.replace(entire_file.find(found_line),37, editted_line);
		//Replace the old daily changes file with the new, editted daily changes file using the editted entire file string.
		daily_changes.open("daily_changes.txt");
		daily_changes << entire_file;
		daily_changes.close();
	}
}

User Transactions::Logout(){
	User out(00000, "NULL", 0);
	cout << "Logout Successful" << endl;
	return out;
}