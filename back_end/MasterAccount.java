import java.util.*;
import java.io.*;
import java.math.*;

/**
 * @author 100520095
 */

public class MasterAccount {
    /*
     * The class that handles reading and writing to the Master Bank Accounts file.
     */
    
    public void WriteAccountFiles(Vector<User> accounts_list){
        /*
         * Takes a vector of accounts. Then, overwrites the Master Accounts file with
         * all the information from the accounts vector.
         */
        
        //Set up the name to read
        String file_name = "master_accounts.txt";
        File file = new File(file_name);
        try {
            //Open a file writer with the file name specified
            FileWriter writer = new FileWriter(file.getAbsoluteFile(), false);
            BufferedWriter master_buffer = new BufferedWriter(writer);
            file = new File("accounts.txt");
            writer = new FileWriter(file.getAbsoluteFile(), false);
            BufferedWriter accounts_buffer = new BufferedWriter(writer);
            //For each account in the vector, write a line to both files with that accounts information
            for(int i = 0; i < accounts_list.size(); i++){
                User current_user = accounts_list.get(i);
                master_buffer.write(FormatNumber(current_user.GetNumber()) + " " 
                           + FormatName(current_user.GetName()) + " " 
                           + FormatStatus(current_user.GetStatus()) + " "
                           + FormatBalance(current_user.GetBalance()) + " "
                           + FormatTransactions(current_user.GetCount()) + " "
                           + FormatPlan(current_user.GetPlan()));
                master_buffer.newLine();
                accounts_buffer.write(FormatNumber(current_user.GetNumber()) + " " 
                           + FormatName(current_user.GetName()) + " "
                           + FormatStatus(current_user.GetStatus()) + " "
                           + FormatBalance(current_user.GetBalance()));
                accounts_buffer.newLine();
            }
            //Close the writers
            master_buffer.close();
            accounts_buffer.close();
        } catch (Exception ex){
            System.out.println("Error in WriteMasterFile");
        }
        
    }
    
    public Vector<User> ReadMasterFile(){
        /*
         * Reads all of the account information from the Master Accounts file. It stores
         * the information for each account in a vector, which it then returns.
         */
        
        //Set the file name
        String file_name = "master_accounts.txt";
        Vector<User> accounts = new Vector<User>();
        try {
            //Set up the file readers
            FileReader reader = new FileReader(file_name);
            BufferedReader buffer = new BufferedReader(reader);
            String line = "";
            //While there is another line in the master file, read in the account
            while((line = buffer.readLine()) != null){
            	if(!line.equals("")){
            		//Split the line into substrings with the information we need to make a user
	                String account = line.substring(0, 5);
	                int account_number = Integer.parseInt(account);
	                String name = line.substring(6, 25);
	                String account_name = "";
	                for(int i = 0; i < name.length()-1; i++){
	                	if(name.charAt(i) == ' ' && name.charAt(i+1) == ' '){
	                		
	                	} else {
	                		account_name += name.substring(i,i+1);
	                	}
	                }
	                String status = line.substring(27, 28);
	                char account_status = status.charAt(0);
	                String balance = line.substring(29, 37);
	                double account_balance = Double.parseDouble(balance);
	                String transactions = line.substring(38, 41);
	                int account_transactions = Integer.parseInt(transactions);
	                String account_plan = line.substring(43, 44);

	                //Make a user out of all the information we got from the line
	                User found_user = new User(account_name, account_number, account_status, account_plan, account_balance, account_transactions);
	                //Add that user to the accounts vector
	                accounts.addElement(found_user);
            	} 
            } 
        } catch(Exception ex) {
            System.out.println("Error occured in ReadMasterFile");
            System.out.println(ex);
        }
        //Return the completed accounts vector.
        return accounts;
    }
    
    private String FormatName(String name){
        /*
         * Formats a name to be the proper format for the accounts file.
         */
        int length = name.length();
        if(length < 20){
            for(int i = length; i < 20; i++){
                name = name + " ";
            }
        }
        return name;
    }
    
    private String FormatNumber(int number){
        /*
         * Formats an account number to be the proper format for the accounts file.
         */
        String formatted_number = String.valueOf(number);
        int length = formatted_number.length();
        if(length < 5){
            for(int i = length; i < 5; i++){
                formatted_number = "0" + formatted_number;
            }
        }
        return formatted_number;
    }
    
    private String FormatStatus(char status){
        /*
         * Formats the account status to be the proper format for the accounts file.
         */
        String account_status = String.valueOf(status);
        return account_status;
    }
    
    private String FormatBalance(double balance){
        /*
         * Formats the account balance to be the proper format for the accounts file.
         */
        double new_balance = new BigDecimal(balance).setScale(2,BigDecimal.ROUND_HALF_UP).doubleValue();
        String formatted_balance = String.valueOf(new_balance);
        char test = formatted_balance.charAt(formatted_balance.length()-2);
        if(test == '.'){
        	formatted_balance += "0";
        }
        int length = formatted_balance.length();
        if(length < 8){
            for(int i = length; i < 8; i++){
                formatted_balance = "0" + formatted_balance;
            }
        }
        return formatted_balance;
    }
    
    private String FormatTransactions(int transactions){
        /*
         * Formats the transaction count to be the proper format for the accounts file.
         */
        String formatted_transactions = String.valueOf(transactions);
        int length = formatted_transactions.length();
        if(length < 4){
            for(int i = length; i < 4; i++){
                formatted_transactions = "0" + formatted_transactions;
            }
        }
        return formatted_transactions;
    }
    
    private String FormatPlan(String plan){
        /*
         * Formats the account plan to be the proper format for the accounts file.
         */
        if(plan.equals("NP")){
            return "N";
        } else {
            return "S";
        }
    }
}
