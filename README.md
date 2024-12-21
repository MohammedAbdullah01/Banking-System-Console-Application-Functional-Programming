# Banking System Application

## Overview
This project is a C++ banking system application that allows managing client data, including adding, updating, deleting, and finding clients. It also supports basic transactions such as deposits and withdrawals. The application is structured using various helper functions, enums, and organized code regions for clarity and maintainability.

---

## Features

### Core Functionalities
1. **Show All Clients**
   - Displays a detailed list of all clients in the system.

2. **Add New Clients**
   - Allows users to add new clients with attributes such as account number, name, pin code, phone, and balance.

3. **Delete Clients**
   - Enables deletion of clients based on their account number.

4. **Update Client Details**
   - Updates existing client records with new details.

5. **Find Clients**
   - Searches for clients using their account number and displays their details.

6. **Transactions**
   - Deposit and withdraw functionalities for client accounts.

---

## Code Organization

### Variables
```cpp
const string ClientsFileName = "Clients.txt";
```
All client data is stored in a text file named `Clients.txt`.

### Defined Functions
- **ShowMainMenue**
- **ShowTransactionsMenue**

These functions manage the primary and transaction menus.

### Helper Functions
- **PrintMessageOnScreen**: Displays messages on the screen.
- **ReadCharacter**: Reads a single character input from the user.
- **ReadWords**: Reads multiple words from user input.
- **ReadNumberInteger / ReadNumberFloat**: Reads numeric input with type-specific validation.
- **ReadPositiveNumber**: Ensures the user enters a positive number.
- **SplitEachWordInVector**: Splits a string into individual words based on a delimiter.

### Struct: `stClientData`
Represents the structure for storing client data:
```cpp
struct stClientData {
    string accountNumber;
    string name;
    string pinCode;
    string phone;
    float accountBalance;
    bool markForDelete;
};
```

### Enums
- **enMainMenueOption**: Options for the main menu.
- **enTransactionMenueOption**: Options for the transaction menu.

### File Operations
- **LoadClientsDataFromFile**: Loads client data from `Clients.txt` into a vector.
- **SaveClientsDataToFile**: Writes updated client data back to the file.

### Client Management
- **AddNewClient**: Prompts the user to input new client details and saves them.
- **DeleteClientByAccountNumber**: Marks a client for deletion and updates the data file.
- **UpdateClientByAccountNumber**: Updates client details based on their account number.
- **FindClientByAccountNumber**: Searches for a client using their account number.

### Transactions
- **Deposit**: Adds a specified amount to the client’s balance.
- **Withdraw**: Deducts a specified amount from the client’s balance (if sufficient funds exist).

---

## How to Use
1. **Compile and Run**: Use any C++ compiler to compile the project files. Execute the resulting binary.
2. **Navigate Menus**: Follow on-screen instructions to navigate through menus.
3. **Client Management**: Perform operations like adding, updating, or deleting clients.
4. **Transactions**: Use transaction features for deposits and withdrawals.

---

## File Format
Client data is stored in a structured format:
```
<AccountNumber>#//#<PinCode>#//#<Name>#//#<Phone>#//#<AccountBalance>#//#
```
Example:
```
12345#//#1234#//#John Doe#//#555-1234#//#1000.50#//#
```

---

## Future Improvements
- Add support for transferring funds between accounts.
- Implement a GUI interface for better usability.
- Encrypt sensitive data like pin codes for security.
