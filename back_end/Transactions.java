import java.util.*;
import java.io.*;

/**
 * @author 100520095
 */

public class Transactions {
    /*
     * The class that handles all transaction reading and parsing. This class is called by the main 
     * method in BackEnd.java. 
     *
     * It takes a single string as its parameter, which is the name of the file that the transactions 
     * are stored in.
     *
     * It will loop through the transactions file, parsing each line of the file to figure out which 
     * command was run. It will then run the specific method for that function to handle it. It will 
     * do this until the entire transactions file has been parsed.
     */
    private Vector<User> accounts_;
    public Transactions(String transactions_file){
        //Set up our list of accounts. 
        MasterAccount accounts_file = new MasterAccount();
        accounts_ = accounts_file.ReadMasterFile();
        //Set up the file reader based on the string passed to the class
        File file = new File(transactions_file);
        try {
        	String line = "";
            //Open a file writer with the file name specified
            FileReader reader = new FileReader(file.getAbsoluteFile());
            BufferedReader buffer = new BufferedReader(reader);
            while((line = buffer.readLine()) != null){
            	if(!line.equals("")){
            		//Parse each transaction
	                String transaction = line.substring(0, 2);
	                int transaction_number = Integer.parseInt(transaction);
	                String name = line.substring(3, 23);
	                String account_name = "";
	                for(int i = 0; i < name.length()-1; i++){
	                	if(name.charAt(i) == ' ' && name.charAt(i+1) == ' '){
	                		
	                	} else {
	                		account_name += name.substring(i,i+1);
	                	}
	                }
	                String account = line.substring(24, 29);
	                int account_number = Integer.parseInt(account);
	                String balance = line.substring(30, 38);
	                double account_balance = Double.parseDouble(balance);
	                int index = 0;
	                int index2 = 0;
	                //Find the correct account in our accounts_ array that matches the account
	                //for the transaction. Only exception is create.
	                if(transaction_number != 5){
	                    for(int i = 0; i < accounts_.size(); i++){
	                        if(account_number == accounts_.get(i).GetNumber()){
	                            index = i+1;
	                        } 
	                    } 
	                }
	                //If the transaction is a transfer, get the second account to transfer funds to
	                if (transaction_number == 2){
	                    line = buffer.readLine();
	                    account = line.substring(24, 28);
	                    account_number = Integer.parseInt(account);
	                    for(int i = 0; i < accounts_.size(); i++){
	                        if(account_number == accounts_.get(i).GetNumber()){
	                            index2 = i;
	                        } 
	                    } 	
	                    
	                }
	                //Run the correct command for that transction number
	                if(index != 0 || transaction_number == 5){
	                    switch(transaction_number){
	                        case 0:
	                            Login(index);
	                            break;
	                        case 1:
	                            Withdrawal(index, account_balance);
	                            break;
	                        case 2:
	                            Transfer(index, index2, account_balance);
	                            break;
	                        case 3:
	                            PayBill(index, account_balance);
	                            break;
	                        case 4:
	                            Deposit(index, account_balance);
	                            break;
	                        case 5:
	                            Create(name, account_balance);
	                            break;
	                        case 6:
	                            Delete(index);
	                            break;
	                        case 7:
	                            EnableOrDisable(index);
	                            break;
	                        case 8:
	                            ChangePlan(index);
	                            break;
	                        case 9:
	                            EnableOrDisable(index);
	                            break;
	                        case 10:
	                            Logout(index);
	                            break;
	                    }
	                }
            	}
            }
        } catch (Exception ex){
            System.out.println("Error in Transactions Constructor");
            System.out.println(ex);
        }
        System.out.println("Transactions proccessed. Updating Master Accounts file.");
        //Update the master accounts file and the accounts file used by te front end
        accounts_file.WriteAccountFiles(accounts_);
        System.out.println("Master Accounts file written. New Accounts file generated.");
    }
    
    private void Login(int index){
        accounts_.get(index).IncrementCount();
    }
    
    private void Logout(int index){
        accounts_.get(index).IncrementCount();
    }
    
    private void Withdrawal(int index, double balance){
        //Calculate the right fee, and then subtract the difference and fee from the accounts balance.
        double fee = 0.10;
        if(accounts_.get(index).GetPlan().equals("SP")){
            fee = 0.05;
        }
        accounts_.get(index).UpdateBalance(accounts_.get(index).GetBalance() - balance - fee);
        accounts_.get(index).IncrementCount();
    }
    
    private void Deposit(int index, double balance){
        //Calculate the fee, then add the difference to the accounts balance minus the fee.
        double fee = 0.10;
        if(accounts_.get(index).GetPlan().equals("SP")){
            fee = 0.05;
        }
        accounts_.get(index).UpdateBalance(accounts_.get(index).GetBalance() + balance - fee);
        accounts_.get(index).IncrementCount();
    }
    
    private void Transfer(int index, int index2, double balance){
        //Calculate the fee, then take one the balance from one account to the other.
        double fee = 0.10;
        if(accounts_.get(index).GetPlan().equals("SP")){
            fee = 0.05;
        }
        accounts_.get(index).UpdateBalance(accounts_.get(index).GetBalance() - balance - fee);
        accounts_.get(index2).UpdateBalance(accounts_.get(index2).GetBalance() + balance);
        accounts_.get(index).IncrementCount();
    }
    
    private void PayBill(int index, double balance){
        //Subtract the balance and fee from the account balance
        double fee = 0.10;
        if(accounts_.get(index).GetPlan().equals("SP")){
            fee = 0.05;
        }
        accounts_.get(index).UpdateBalance(accounts_.get(index).GetBalance() - balance - fee);
        accounts_.get(index).IncrementCount();
    }
    
    private void Create(String name, double balance){
        /*
         * Create a new account by finding the first available account number and creating a new user
         * In the accounts vector for it. Insert the account at the correct index position in the
         * vector to keep the list sorted.
         */
        boolean found = false;
        int i = 0;
        while(!found){
            if(accounts_.get(i).GetNumber() != i+1){
                User created_user = new User(name, i+1, 'A', "NP", balance, 0);
                accounts_.add(i, created_user);
                found = true;
            } else {
                i++;
            }
        }
    }
    
    private void Delete(int index){
        //Remove the account from the vector, deleting it when the master accounts file is written
        accounts_.remove(index);
    }
    
    private void EnableOrDisable(int index){
        //Swaps the account from active/disabled or vice versa
        accounts_.get(index).SetStatus();
        accounts_.get(index).IncrementCount();
    }
    
    private void ChangePlan(int index){
        //Swaps the account from student/non-student or vice versa
        accounts_.get(index).SetPlan();
        accounts_.get(index).IncrementCount();
    }
}
