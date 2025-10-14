# 🏦 Simple Bank Management System (C++)

## 📘 Overview
This project is a **console-based Bank Management System** developed in **C++** using **Object-Oriented Programming (OOP)** concepts.  
It allows users (both Admin and Customers) to perform essential banking operations such as account creation, deposit, withdrawal, and account management.

---

## ⚙️ Features

### 👨‍💼 Admin Functions
- Create a new bank account  
- Delete an existing account  
- View all customer accounts  
- Search for an account by account number  

### 👤 User Functions
- Log in using an account number  
- View account details and balance  
- Deposit money  
- Withdraw money  

---

## 🧱 Class Structure (UML Diagram)
![UML Diagram](A_UML_(Unified_Modeling_Language)Project.svg)

### **Classes**
1. **Account**
   - Represents a single customer's account.  
   - Handles deposits, withdrawals, and displays account details.  

2. **Bank**
   - Manages a collection of accounts.  
   - Handles account creation, deletion, searching, and viewing all accounts.  

3. **Global Functions**
   - `clearScreen()` – Clears the console screen.  
   - `showAdminDash()` – Displays the admin interface.  
   - `showUserDash()` – Displays the user interface.  

---

## 🧩 Object-Oriented Concepts Used
- **Encapsulation:**  
  Account data (like `balance`, `ownerName`, etc.) is private and accessed through public methods.  

- **Abstraction:**  
  Complex operations (like managing multiple accounts) are abstracted behind class methods.  

- **Composition:**  
  `Bank` class contains a collection (`vector`) of `Account` objects.  

---

