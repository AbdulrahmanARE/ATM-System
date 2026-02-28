# ATM System (C++)

Console-based **ATM System** written in C++ with **user authentication, deposit, withdraw, and balance checking**, using file-based storage.

This project simulates the real behavior of an ATM machine, allowing clients to securely access their accounts and perform banking transactions.

---

## Features

* **Secure Login System**

  * Login using Account Number and Pin Code
  * Validates user credentials from file

* **Withdraw Operations**

  * Quick Withdraw (predefined amounts)
  * Normal Withdraw (custom amount, multiple of 5)
  * Prevents withdrawing more than available balance

* **Deposit Operation**

  * Deposit money into account
  * Automatically updates account balance

* **Balance Checking**

  * View current account balance instantly

* **File-Based Storage**

  * All client data stored in `Clients.txt`
  * Automatic loading and saving of data

---

## Purpose

This project is designed to practice:

* C++ programming fundamentals
* File handling
* Structs and data management
* Console-based application design
* Simulation of real-world ATM systems

---

## How to Run

1. Download or clone the repository
2. Make sure `Clients.txt` exists in the same folder
3. Compile using a C++ compiler (Visual Studio or g++)
4. Run the program
5. Login using Account Number and Pin Code

---

## Main Menu

[1] Quick Withdraw
[2] Normal Withdraw
[3] Deposit
[4] Check Balance
[5] Logout

---

## File Format (Clients.txt)

Each client is stored in the following format:

AccountNumber#//#PinCode#//#Name#//#Phone#//#AccountBalance

Example:

A150#//#1234#//#Abdulrahman Ramadan#//#01128663647#//#5000.000000

---

## Author

Abdulrahman Ramadan – ATM System project in C++ demonstrating authentication, transactions, and file handling.
