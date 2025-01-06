# Banking System Application

## Overview
This project is a C++ application designed to manage client and user data efficiently. It provides various functionalities including the ability to add, delete, update, and find clients and users. The application also supports different transaction types such as deposits and withdrawals, while maintaining robust access control through user permissions.

---

## Features

- Manage clients and users
- Conduct transactions
- Access control with permissions
- User-friendly interface

## Usage

### Main Menu Options

- **Show All Clients**
- **Add Client**
- **Delete Client**
- **Update Client**
- **Find Client**
- **Transactions**
- **Manage Users**
- **Logout**

### Transactions Menu Options

- **Show All Clients**
- **Deposit**
- **Withdraw**
- **Total Balancces**
- **Main Menue**

### Manage Users Menu Options

- **List Users**
- **Add New User**
- **Delete User**
- **Update User**
- **Find User**
- **Main Menue**

### Permissions

Define different permission levels for users to control access to various functionalities.

### Helper Functions

- **PrintMessageOnScreen**: Displays a message on the screen.
- **ReadCharacter**: Reads a single character input from the user.
- **ReadWords**: Reads multiple words input from the user.
- **ReadWord**: Reads a single word input from the user.
- **ReadNumberInteger**: Reads an integer input from the user.
- **ReadNumberFloat**: Reads a floating-point number input from the user.
- **ReadFullName**: Prompts the user for their full name.
- **ReadPositiveNumber**: Reads a positive integer input from the user.
- **ReadNumberWithValidate**: Reads and validates integer input from the user.
- **ReadPositiveFloatNumber**: Reads a positive floating-point number input from the user.
- **SplitEachWordInVector**: Splits a string into words based on a delimiter.

### Client Management

- **convertFromLineToRecord**: Converts a line of text to a client record.
- **LoadClientsDataFromFile**: Loads client data from a file.
- **ReadClientAccountNumber**: Prompts the user to enter an account number.
- **isFindClient**: Checks if a client exists by account number.
- **PrintClientRecordDetails**: Displays details of a client record.
- **ShowFindClientScreen**: Interface to find a client.
- **PrintClientRecord**: Displays a single client record.
- **ShowAllClientScreen**: Displays all client records.
- **convertFromRecordToString**: Converts a client record to a string.
- **saveRecordLineToFile**: Saves a record line to a file.
- **saveClientsDataToFile**: Saves client data to a file.
- **ReadNewClient**: Prompts the user to enter new client details.
- **AddNewClient**: Adds a new client to the file.
- **AddNewClients**: Interface to add multiple new clients.
- **ShowAddNewClientScreen**: Interface to add a new client.
- **markClientForDeleteByAccountNumber**: Marks a client for deletion by account number.
- **DeleteClientByAccountNumber**: Deletes a client by account number.
- **ShowDeleteClientScreen**: Interface to delete a client.
- **changeClientRecord**: Changes the client record.
- **UpdateClientByAccountNumber**: Updates a client by account number.
- **ShowUpdateClientScreen**: Interface to update a client.
- **GoBackToTransactionsMenue**: Returns to the transactions menu.
- **getClientByAccountNumber**: Retrieves a client by account number.

### Transactions

- **Deposit**: Adds funds to a client's account.
- **ShowDepositScreen**: Interface to deposit funds.
- **Withdraw**: Withdraws funds from a client's account.
- **ShowWithdrawScreen**: Interface to withdraw funds.
- **GetTotalBalances**: Calculates the total balance of all clients.
- **ShowAllClientsTotalBalances**: Displays the total balance of all clients.
- **TransactionsMenue**: Interface for transactions menu.
- **ShowTransactionsMenue**: Displays the transactions menu.

### User Management

- **isFindUser**: Checks if a user exists by username.
- **convertUserFromLineToRecord**: Converts a line of text to a user record.
- **LoadUsersDataFromFile**: Loads user data from a file.
- **checkLogin**: Validates username and password.
- **ShowLoginScreen**: Interface for user login.
- **PrintUserRecord**: Displays a single user record.
- **ShowAllUserScreen**: Displays all user records.
- **ReadUserUsername**: Prompts the user to enter a username.
- **ReadPermissionsToSet**: Prompts the user to set permissions.
- **convertFromRecordUserToString**: Converts a user record to a string.
- **saveUsersDataToFile**: Saves user data to a file.
- **ShowFindUserScreen**: Interface to find a user.
- **ReadNewUser**: Prompts the user to enter new user details.
- **AddNewUser**: Adds a new user to the file.
- **AddNewUsers**: Interface to add multiple new users.
- **ShowAddNewUserScreen**: Interface to add a new user.
- **markUserForDeleteByAccountNumber**: Marks a user for deletion by username.
- **DeleteUserByUsername**: Deletes a user by username.
- **ShowDeleteUserScreen**: Interface to delete a user.
- **changeUserRecord**: Changes the user record.
- **UpdateUserByUsername**: Updates a user by username.
- **ShowUpdateUserScreen**: Interface to update a user.
- **GoBackToManageUsersMenue**: Returns to the manage users menu.
- **ManageUsersMenue**: Interface for managing users menu.
- **ShowManageUsersMenue**: Displays the manage users menu.

### Main Menu and Logout

- **ShowLogoutScreen**: Interface to log out the user.
- **GoBackToMainMenue**: Returns to the main menu.
- **MainMenue**: Interface for main menu options.
- **ShowMainMenue**: Displays the main menu.


## File Format
Client data is stored in a structured format:
```
<AccountNumber>#//#<PinCode>#//#<Name>#//#<Phone>#//#<AccountBalance>#//#
```
Example:
```
12345#//#1234#//#John Doe#//#555-1234#//#1000.50#//#
```

User data is stored in a structured format:
```
<Username>#//#<Password>#//#<Permission>#//#
```
Example:
```
John Doe#//#1234#//#-1#//#
```

## Future Improvements
- Add support for transferring funds between accounts.
- Implement a GUI interface for better usability.
- Encrypt sensitive data like pin codes for security.

---

## Contributing

Contributions are welcome! Feel free to fork the repository, improve the code, and submit a pull request.
