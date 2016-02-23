#include <fstream>
#include <sstream>
#include <iostream>

#include "TransactionsFile.h"
#include "User.h"

using namespace std;

void WriteTransaction(){

}

string FormatTransactionID(string transaction_id);
string FormatName(string name);
string FormatNumber(int account_number);
string FormatBalance(double balance);
string FormatMiscellaneous();