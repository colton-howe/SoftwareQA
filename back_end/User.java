/**
 * @author 100520095
 */

public class User {
    /*
     * File to store the information for an account/user.
     *
     * The constructor takes a name, account number, account_status, plan_type_, balance, 
     * and transaction count as parameters for its constructor.
     */
    private String account_name_;
    private int account_number_;
    private char account_status_;
    private String plan_type_;
    private double balance_;
    private int transaction_count_;
    
    public User(String name, int number, char status, String plan, double balance, int count){
        //Constructor to set all the initial variables for the user.
        account_name_ = name;
        account_number_ = number;
        account_status_ = status;
        plan_type_ = plan;
        balance_ = balance;
        transaction_count_ = count; 
    }
    
    //Getters for each variable.
    public String GetName(){
        return account_name_;
    }
    
    public int GetNumber(){
        return account_number_;
    }
    
    public char GetStatus(){
        return account_status_;
    }
    
    public String GetPlan(){
        return plan_type_;
    }
    
    public double GetBalance(){
        return balance_;
    }
    
     public int GetCount(){
        return transaction_count_;
    }
    
    //Setters for those varables that can be changed.
    public void SetStatus(){
        if(account_status_ == 'A'){
            account_status_ = 'D';
        } else {
            account_status_ = 'A';
        }
    }
    
    public void SetPlan(){
        if(plan_type_.equals("NP")){
            plan_type_ = "SP";
        } else {
            plan_type_ = "NP";
        }
    }
    
    public void UpdateBalance(double new_balance){
        //Updates the balance on the account to the new amount.
        balance_ = new_balance;
    }
    
    public void IncrementCount(){
        //Increments the transaction count after every transaction
        transaction_count_++;
    }
    
}
