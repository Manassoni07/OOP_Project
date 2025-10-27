#include <iostream>
#include <vector>
#include <string>
using namespace std;

//--------------------- Transaction Class ------------------------
class Transaction {
private:
    string type;
    double amount;
public:
    Transaction(string t, double a) : type(t), amount(a) {}
    void display() const {
        cout << type << " of " << amount << " units\n";
    }
};

//--------------------- Customer Class ------------------------
class Customer {
private:
    int customerID;
    string name;
    string address;
    string phone;

public:
    Customer(int id = 0, string n = "", string a = "", string p = "")
        : customerID(id), name(n), address(a), phone(p) {}

    void displayCustomer() const {
        cout << "Customer ID: " << customerID << "\nName: " << name
             << "\nAddress: " << address << "\nPhone: " << phone << endl;
    }

    string getName() const { return name; }
    int getID() const { return customerID; }
};

//--------------------- Abstract Account Class ------------------------
class Account {
protected:
    int accountNumber;
    double balance;
    Customer owner;
    vector<Transaction> transactions;

public:
    Account(int accNo, const Customer &cust, double bal = 0.0)
        : accountNumber(accNo), owner(cust), balance(bal) {}

    virtual void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "Deposited: " << amount << " | New Balance: " << balance << endl;
    }

    virtual void withdraw(double amount) = 0;

    virtual void displayAccountInfo() const {
        cout << "\nAccount No: " << accountNumber << "\nBalance: " << balance << endl;
        owner.displayCustomer();
    }

    void showTransactions() const {
        cout << "\n--- Transaction History for Account " << accountNumber << " ---\n";
        for (const auto &t : transactions)
            t.display();
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    string getOwnerName() const { return owner.getName(); }

    virtual string getAccountType() const = 0;
    virtual ~Account() {}
};

//--------------------- SavingsAccount Class ------------------------
class SavingsAccount : public Account {
private:
    double interestRate;
public:
    SavingsAccount(int accNo, const Customer &cust, double rate, double bal = 0.0)
        : Account(accNo, cust, bal), interestRate(rate) {}

    void deposit(double amount) override {
        double interest = amount * interestRate / 100;
        balance += amount + interest;
        transactions.emplace_back("Deposit (with interest)", amount);
        cout << "Deposited: " << amount << " + Interest: " << interest
             << " | New Balance: " << balance << endl;
    }

    void withdraw(double amount) override {
        if (amount <= balance) {
            balance -= amount;
            transactions.emplace_back("Withdraw", amount);
            cout << "Withdrawn: " << amount << " | New Balance: " << balance << endl;
        } else {
            cout << "Insufficient balance!\n";
        }
    }

    void displayAccountInfo() const override {
        cout << "\n[Saving Account]\n";
        Account::displayAccountInfo();
        cout << "Interest Rate: " << interestRate << "%\n";
    }

    string getAccountType() const override { return "Savings"; }
};

//--------------------- CurrentAccount Class ------------------------
class CurrentAccount : public Account {
private:
    double overdraftLimit;

public:
    CurrentAccount(int accNo, const Customer &cust, double limit, double bal = 0.0)
        : Account(accNo, cust, bal), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (amount <= balance + overdraftLimit) {
            balance -= amount;
            transactions.emplace_back("Withdraw", amount);
            cout << "Withdrawn: " << amount << " | New Balance: " << balance << endl;
        } else {
            cout << "Overdraft limit exceeded!\n";
        }
    }

    void displayAccountInfo() const override {
        cout << "\n[Current Account]\n";
        Account::displayAccountInfo();
        cout << "Overdraft Limit: " << overdraftLimit << endl;
    }

    string getAccountType() const override { return "Current"; }
};

//--------------------- User Class ------------------------
class User {
private:
    string username;
    string password;
    int accountNumber;

public:
    User(string u = "", string p = "", int accNo = 0)
        : username(u), password(p), accountNumber(accNo) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    int getAccountNumber() const { return accountNumber; }
};

//--------------------- Admin Class ------------------------
class Admin {
private:
    string username;
    string password;
public:
    Admin(string u = "___manas_soni", string p = "12345678") : username(u), password(p) {}

    bool login(string u, string p) {
        return (u == username && p == password);
    }
};

//--------------------- Bank Class ------------------------
class Bank {
private:
    vector<Account*> accounts;
    vector<User> users;
    Admin admin;
    int nextAccountNumber = 1001;
    int nextCustomerID = 1;

public:
    ~Bank() {
        for (auto acc : accounts)
            delete acc;
    }

    // Admin Functions
    void createAccount() {
        string name, address, phone, username, password;
        int type;
        cout << "\nEnter Customer Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter Phone: ";
        getline(cin, phone);
        Customer cust(nextCustomerID++, name, address, phone);

        cout << "Set Username for this Customer: ";
        cin >> username;
        cout << "Set Password: ";
        cin >> password;

        cout << "Select Account Type (1. Savings | 2. Current): ";
        cin >> type;

        if (type == 1) {
            double rate;
            cout << "Enter Interest Rate (%): ";
            cin >> rate;
            accounts.push_back(new SavingsAccount(nextAccountNumber, cust, rate));
        } else {
            double limit;
            cout << "Enter Overdraft Limit: ";
            cin >> limit;
            accounts.push_back(new CurrentAccount(nextAccountNumber, cust, limit));
        }

        users.emplace_back(username, password, nextAccountNumber);
        cout << "Account Created Successfully! Account Number: " << nextAccountNumber << endl;
        nextAccountNumber++;
    }

    void deleteAccount(int accNo) {
        for (size_t i = 0; i < accounts.size(); ++i) {
            if (accounts[i]->getAccountNumber() == accNo) {
                delete accounts[i];
                accounts.erase(accounts.begin() + i);
                cout << "Account deleted successfully.\n";
                return;
            }
        }
        cout << "Account not found.\n";
    }

    void displayAllAccounts() const {
        if (accounts.empty()) {
            cout << "No accounts in bank.\n";
            return;
        }
        for (auto acc : accounts)
            acc->displayAccountInfo();
    }

    // User Functions
    Account* findAccount(int accNo) {
        for (auto acc : accounts)
            if (acc->getAccountNumber() == accNo)
                return acc;
        return nullptr;
    }

    User* findUser(string username, string password) {
        for (auto &u : users)
            if (u.getUsername() == username && u.getPassword() == password)
                return &u;
        return nullptr;
    }

    // Login & Menus
    void adminMenu() {
        int choice, accNo;
        do {
            cout << "\n====== ADMIN MENU ======\n";
            cout << "1. Create Account\n2. Delete Account\n3. View All Accounts\n4. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2:
                    cout << "Enter Account Number to delete: ";
                    cin >> accNo;
                    deleteAccount(accNo);
                    break;
                case 3:
                    displayAllAccounts();
                    break;
                case 4:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } while (choice != 4);
    }

    void userMenu(Account *acc) {
        int choice;
        double amount;
        do {
            cout << "\n====== USER MENU ======\n";
            cout << "1. Deposit\n2. Withdraw\n3. View Account Details\n4. View Transactions\n5. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    acc->deposit(amount);
                    break;
                case 2:
                    cout << "Enter amount to withdraw: ";
                    cin >> amount;
                    acc->withdraw(amount);
                    break;
                case 3:
                    acc->displayAccountInfo();
                    break;
                case 4:
                    acc->showTransactions();
                    break;
                case 5:
                    cout << "Logging out...\n";
                    break;
                default:
                    cout << "Invalid choice!\n";
            }
        } while (choice != 5);
    }

    void loginSystem() {
        int choice;
        do {
            cout << "\n====== BANK LOGIN ======\n";
            cout << "1. Admin Login\n2. User Login\n3. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1) {
                string u, p;
                cout << "Enter Admin Username: ";
                cin >> u;
                cout << "Enter Password: ";
                cin >> p;
                if (admin.login(u, p))
                    adminMenu();
                else
                    cout << "Invalid admin credentials!\n";
            } else if (choice == 2) {
                string u, p;
                cout << "Enter Username: ";
                cin >> u;
                cout << "Enter Password: ";
                cin >> p;
                User *usr = findUser(u, p);
                if (usr) {
                    Account *acc = findAccount(usr->getAccountNumber());
                    if (acc)
                        userMenu(acc);
                    else
                        cout << "Account not found!\n";
                } else {
                    cout << "Invalid username or password!\n";
                }
            } else if (choice == 3) {
                cout << "Exiting system...\n";
            } else {
                cout << "Invalid choice!\n";
            }

        } while (choice != 3);
    }
};

//--------------------- Main Function ------------------------
int main() {
    Bank bank;
    bank.loginSystem();
    return 0;
}
