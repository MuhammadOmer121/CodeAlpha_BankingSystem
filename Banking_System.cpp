#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

//customer will have account and transaction //use map
class Customer {
    string name;
    unsigned long accountNo;
public:
    Customer() {
        name = "";
        accountNo = 0;
    }
    Customer(string n, unsigned long acc) {
        name = n;
        accountNo = acc;
    }
    string getName() {
        return name;
    }
};
class Account : public Customer {
    string username;
    string password;

public:
    Account() {

    }
    Account(string un, string p) {
        username = un;
        password = p;
    }
    string getUsername() {
        return username;
    }
    string getPassword() {
        return password;
    }


};
class Transaction {
    string date;
    double amount;
    string reciever;
    string sender;
    double balance = 10000;
public:
    Transaction() {
        amount = 0.0;
    }
    Transaction(string d, double am, string s, string r) {
        date = d;
        amount = am;
        reciever = r;
        sender = s;
    }
    void deposit(double amount) {
        balance += amount;
    }
    void sendMoney(double amount) {
        balance -= amount;
    }
    void withdraw(double amount) {
        balance -= amount;
    }
    string display() {
        return ("Transaction:[ Date: " + date + ", Amount: " + to_string(amount) + " , From: " + sender + ", To: " + reciever + " ]");
    }
};

class Management {
    vector<string> transactions;
    map<const unsigned long,Account> users;
    map<const unsigned long, vector<string> > AccTransaction;

public:
    void registerUser(string& nam, unsigned long& accNo,string& uname,string& pass) {
        Customer* c = new Customer(nam, accNo);
        users.insert({ accNo,Account(uname,pass) });
        cout << "Account Created Successfully! " << endl;
        cout << "Welcome " << nam << "..." << endl;
    }
    void LoginUser(unsigned long accNo) {
        string uname;
        string pass;
        if (users.size() > 0) {
            if (users.find(accNo) == users.end()) {
                cerr << "Wrong Account Number! " << endl;
            }
            else {
                cout << "Enter Username: " << endl;
                getline(cin, uname);
                if (users[accNo].getUsername() == uname) {
                    cout << "Enter Password: " << endl;
                    getline(cin, pass);
                    if (users[accNo].getPassword() == pass) {
                        cout << "Login Successfull." << endl;
                        UserFunc(users[accNo].getName(),accNo);
                    }
                    else {
                        cerr << "Wrong Password!" << endl;
                    }
                }
                else {
                    cerr << "Wrong Username!" << endl;
                }
            }
        }
        else {
            cerr << "First Register Account! " << endl;
        }
        
    }

    void UserFunc(string name,unsigned long accno) {
        int choice = -1;
        do {
            cout << "1: View transactions " << endl;
            cout << "2: Send Money" << endl;
            cout << "3: Deposit Money" << endl;
            cout << "4: Withdraw Money" << endl;
            cout << "0: Log out" << endl;
            cin >> choice;
            switch (choice) {
            case 1:
            {
                AccTransaction.insert({ accno,transactions });
                for (int i = 0; i < AccTransaction[accno].size(); i++) {
                    cout << AccTransaction[accno].at(i) << endl;
                }
            }
            break;
            case 2:
            {
                double amount;
                string reciever;
                cout << "Enter amount to Send: ";
                cin >> amount;
                cin.ignore();
                cout << "Enter Reciever: ";
                getline(cin, reciever);
                Transaction t("12-3-2025", amount, "omer", reciever);
                t.sendMoney(amount);
                transactions.push_back(t.display());
            }
            break;
            case 3:
            {
                double amount;
                cout << "Enter amount to Deposit: ";
                cin >> amount;
                Transaction t("12-3-2025", amount, "omer", name);
                t.deposit(amount);
                transactions.push_back(t.display());
            }
            break;
            case 4:
            {
                double amount;
                cout << "Enter amount to Withdraw: ";
                cin >> amount;
                Transaction t("12-3-2025", amount, "omer", name);
                t.withdraw(amount);
                transactions.push_back(t.display());
            }
            break;
            case 0:
                break;
            default:
                cerr << "Invalid choice" << endl;
                break;
            }
        } while (choice != 0);
        
    }

};
int main()
{
    cout << "====== Banking System ======" << endl;
    int choice = -1;
    Management m;
    do {
        cout << "1: Sign Up" << endl;
        cout << "2: Sign In" << endl;
        cout << "0: Exit" << endl;
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            string name, username, pass;
            unsigned long accNo;
            cout << "Enter your full name: ";
            getline(cin, name);
            cout << "Enter your Account No: ";
            cin >> accNo;
            cin.ignore();
            cout << "Enter your username: ";
            getline(cin, username);
            cout << "Enter your password: ";
            getline(cin, pass);
            m.registerUser(name, accNo, username, pass);
        }
        else if (choice == 2) {
            unsigned long accNo;
            cout << "Enter your Account No: ";
            cin >> accNo;
            cin.ignore();
            m.LoginUser(accNo);
        }
        else if (choice == 0) {

        }
        else {
            cout << "Invalid" << endl;
        }
    } while (choice != 0);
}


