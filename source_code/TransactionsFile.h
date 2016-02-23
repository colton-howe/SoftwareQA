#ifndef TRANSACTIONSFILE_H
#define TRANSACTIONSFILE_H

#include "User.h"
#include <string>

using namespace std;

class TransactionsFile{
private:
	string transaction_id_;
	string account_name_;
	int account_number_;
	double new_balance_;

public:
	void WriteTransaction();
	string FormatTransactionID(string transaction_id);
	string FormatName(string name);
	string FormatNumber(int account_number);
	string FormatBalance(double balance);
	string FormatMiscellaneous();
};

#endif