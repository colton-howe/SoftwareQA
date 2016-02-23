#include "User.h"

#include <string>

using namespace std;

User::User(int account_number, string account_name, double balance){
	account_number_ = account_number;
	account_name_ = account_name;
	balance_ = balance;
	account_status_ = 'A';
	plan_type_ = "NP";
	new_balance_ = balance;
}

void User::SetStatus(){
	if(account_status_ == 'A'){
		account_status_ = 'D';
	} else {
		account_status_ = 'A';
	}
}

void User::SetPlan(){
	if(plan_type_ == "NP"){
		plan_type_ = "SP";
	} else {
		plan_type_ = "NP";
	}
}

void User::UpdateBalance(){
	balance_ = new_balance_;
}

void User::UpdateNewBalance(double change){
	new_balance_ = new_balance_ + change;
}