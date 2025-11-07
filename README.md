# 🏦 Bank Management System (C++ OOP Project)

## 👨‍💻 Developed By
#### Manas Soni

#### Meenu Raghuwanshi


---

## 📘 Project Overview

This project is a **Bank Management System** developed in **C++**, designed to simulate real-world banking operations.  
It allows **Admins** to create, delete, and view customer accounts, while **Users (Customers)** can log in to manage their own bank accounts by depositing, withdrawing, and viewing transaction history.

The project demonstrates the use of **Object-Oriented Programming (OOP)** principles such as **Abstraction**, **Encapsulation**, **Inheritance**, and **Polymorphism** through a modular and extensible class hierarchy.

---

## ⚙️ Working of the Project

### 🔑 Main Features
- **Admin Login:**
  - Create new Savings or Current Accounts.
  - Delete existing accounts.
  - Display all account details.

- **User Login:**
  - Deposit and withdraw money.
  - View account information.
  - Check transaction history.

### 🧭 Flow of Execution
1. The program starts with the **loginSystem()** function.
2. User chooses between **Admin Login**, **User Login**, or **Exit**.
3. If **Admin** logs in:
   - Admin can create accounts with unique account numbers.
   - Admin can assign usernames/passwords for customers.
4. If **User** logs in:
   - User can perform operations like deposit, withdraw, and view transactions.
5. The system continues until the user chooses to exit.

---

## 🧩 OOP Concepts Used

### 1. Encapsulation
Each class bundles data and related operations together.  
Example:  
- The `Customer` class encapsulates personal details (name, address, phone).
- The `Account` class encapsulates account data and transaction behavior.

### 2. Abstraction
Abstract class `Account` hides common account details while providing a general interface.  
Functions like `deposit()`, `withdraw()`, and `displayAccountInfo()` are defined in base and specialized in derived classes.

### 3. Inheritance
`SavingsAccount` and `CurrentAccount` classes **inherit** from the base abstract class `Account`.  
They override the `withdraw()` and `deposit()` methods with their specific rules.

### 4. Polymorphism
Implemented through **virtual functions** and **dynamic binding**.  
- `Account* acc` can point to either a `SavingsAccount` or `CurrentAccount`.
- Calls like `acc->withdraw()` execute the correct version at runtime.

### 5. Composition (Has-a Relationship)
- `Account` **has-a** `Customer` (each account belongs to one customer).
- `Account` **has-a** list of `Transaction` objects.
- `Bank` **has-a** collection of `Account*` and `User` objects.

### 6. Constructor Overloading
Constructors are overloaded in several classes (`Customer`, `User`, `Account`, etc.) for flexible object creation.

### 7. Data Hiding
Private data members like `balance`, `password`, and `transactions` are protected from direct external access.

---

## 🧱 Class Relationships

| Class | Type | Relationship | Description |
|:------|:------|:-------------|:-------------|
| **Bank** | Controller | Has-a → `Account`, `User`, `Admin` | Central class that manages the system |
| **Admin** | Entity | Used-by → `Bank` | Handles account creation/deletion |
| **User** | Entity | Associated-with → `Account` | Represents login credentials for customers |
| **Customer** | Entity | Aggregated-by → `Account` | Represents customer’s personal data |
| **Account (Abstract)** | Base Class | Parent of → `SavingsAccount`, `CurrentAccount` | Common account structure |
| **SavingsAccount** | Derived Class | Inherits-from → `Account` | Adds interest rate handling |
| **CurrentAccount** | Derived Class | Inherits-from → `Account` | Adds overdraft limit |
| **Transaction** | Helper Class | Contained-in → `Account` | Records deposits and withdrawals |



## 🧪 Technologies Used
- **Language:** C++  
- **Paradigm:** Object-Oriented Programming  
- **Compiler:** g++  
- **Header Files:** `<iostream>`, `<vector>`, `<string>`  

---

## 🧠 Key Highlights
- Fully modular, scalable, and menu-driven system.
- Demonstrates real-world OOP implementation.
- Separates admin and user functionalities for clarity.
- Uses dynamic memory management (`new` and `delete`) for runtime account handling.

---

## 🚀 How to Run

1. Copy the code into a file named `BankManagement.cpp`.
2. Compile using:  
   ```bash
   g++ BankManagement.cpp -o bank
   ```
3. Run the executable:  
   ```bash
   ./bank
   ```
4. Use:
   - **Admin Login:**  
     Username: `___manas_soni`  
     Password: `12345678`  
   - **User Login:** Use credentials created by the admin.