#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#pragma region Variables Const
const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
#pragma endregion




#pragma region Defined Function
void ShowMainMenue();

void ShowTransactionsMenue();

void ShowManageUsersMenue();
#pragma endregion

#pragma region Helper Function

void PrintMessageOnScreen(string msg)
{
	cout << msg << endl;
}

char ReadCharacter(string msg)
{
	char charcter;
	cout << msg;
	cin >> charcter;
	return charcter;
}

string ReadWords(string msg)
{
	string name;
	cout << msg;
	getline(cin >> ws, name);
	return name;
}

string ReadWord(string msg)
{
	string name;
	cout << msg;
	cin >> name;
	return name;
}

int ReadNumberInteger(string msg)
{
	int number;
	cout << msg;
	cin >> number;
	return number;
}

float ReadNumberFloat(string msg)
{
	float number;
	cout << msg;
	cin >> number;
	return number;
}

string ReadFullName()
{
	string fullName;

	fullName = ReadWord("Please Enter First Name ?");

	fullName += " " + ReadWord("Please Enter Last Name ?");

	return fullName;
}

int ReadPositiveNumber()
{
	int number;
	do
	{
		number = ReadNumberInteger("Pleas Enter Positive Number ? ");
	} while (number <= 0);

	return number;
}

int ReadNumberWithValidate(string msg)
{
	int number;
	cout << msg << endl;
	cin >> number;

	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Invalid Number, Enter valid Number:";
		cin >> number;
	}
	return number;
}

float ReadPositiveNumber(string msg)
{
	float number;
	do
	{
		number = ReadNumberFloat(msg);
	} while (number <= 0);

	return number;
}

float ReadPositiveFloatNumber(string msg)
{
	float number;
	do
	{
		number = ReadNumberFloat(msg);
	} while (number <= 0);

	return number;
}

vector<string> SplitEachWordInVector(string str , string delimter = " ")
{
	vector<string> VWords;
	size_t position = 0;
	string word = "";

	while ((position = str.find(delimter) ) != string::npos)
	{
		word = str.substr(0 , position);
		if (!word.empty())
		{
			VWords.push_back(word);
		}
			str.erase(0 , position + delimter.length());
	}

	if (!str.empty())
	{
		VWords.push_back(str);
	}

	return VWords;
}

#pragma endregion

#pragma region structs 
struct stClientData
{
	string accountNumber = "", name = "", pinCode = "", phone = "";
	float accountBalance = 0.00;
	bool markForDelete = false;
};

struct stUserData
{
	string userName = "", password = "";
	short permission = -1;
	bool markForDelete = false;
};
#pragma endregion

#pragma region Enums
enum enMainMenueOption
{
	eShowAllClient = 1, eAddClient, eDelete, eUpdate, 
	eFindClient, eTransactions, eManageUsers, eLogout
};

enum enManageUsersMenue
{
	eListUser = 1,
	eAddNewUser = 2,
	eDeleteUser = 3,
	eUpdateUser = 4,
	eFindUser = 5,
	eUMainMenue = 6
};

enum enTransactionMenueOption
{
	eDeposit = 1, eWithdraw, eTotalBalancces, eMainMenue
};

enum enMainMenuePermissions
{
	pAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8,
	pFindClient = 16, pTransactions = 32, pManageUser = 64
};
#pragma endregion

#pragma region Gloabal Variables
stUserData GlobalUserData;
#pragma endregion

#pragma region Check Access Permissions
bool CheckAccessPermissions(enMainMenuePermissions permission)
{
	if (GlobalUserData.permission == enMainMenuePermissions::pAll)
		return true;

	if ((permission & GlobalUserData.permission) == permission)
		return true;
	else
		return false;
}
#pragma endregion

#pragma region Show Access Denied
void ShowAccessDenied()
{
	system("cls");
	PrintMessageOnScreen("===========================================");
	PrintMessageOnScreen("\tAccess Denied Screen");
	PrintMessageOnScreen("===========================================");
	PrintMessageOnScreen("You Dont Have Permission To Do this,");
	PrintMessageOnScreen("Please Contact Your Admin.");
	PrintMessageOnScreen("===========================================");
}
#pragma endregion


#pragma region Read Choise Main Menue
short ReadChoiseMainMenue(short to)
{
	short num = 0;

	do
	{
		num = ReadNumberWithValidate("choose what do you want to do ? [ 1 to " + to_string(to) + " ] ? ");

	} while (num < 1 || num > to);

	return num;
}
#pragma endregion

#pragma region Client
#pragma region convert From Line To Record
stClientData convertFromLineToRecord(string line, string separetor = "#//#")
{
	stClientData client;

	vector<string> VClient = SplitEachWordInVector(line, separetor);

	client.accountNumber = VClient[0];
	client.pinCode = VClient[1];
	client.name = VClient[2];
	client.phone = VClient[3];
	client.accountBalance = stof(VClient[4]);

	return client;
}
#pragma endregion

#pragma region Load Clients Data From File 
vector<stClientData> LoadClientsDataFromFile()
{
	fstream myFile;
	vector<stClientData> VClients;

	myFile.open(ClientsFileName, ios::in);

	if (myFile.is_open())
	{
		string line = "";
		stClientData client;

		while (getline(myFile, line))
		{
			client = convertFromLineToRecord(line);
			VClients.push_back(client);
		}

		myFile.close();
	}
	return VClients;
}
#pragma endregion

#pragma region Read Client Account Number
string ReadClientAccountNumber()
{
	string accountNumber;
	accountNumber = ReadWord("\nPlease Enter Account Number ? ");
	return accountNumber;
}
#pragma endregion

#pragma region Find Client By Account Number
bool isFindClient(string accountNumber, vector<stClientData> VClients, stClientData& client)
{
	for (stClientData& C : VClients)
	{
		if (C.accountNumber == accountNumber)
		{
			client = C;
			return true;
		}
	}
	return false;
}

void PrintClientRecordDetails(stClientData client)
{
	cout << "The following is the extracted client Details :\n\n"
		<< "- Account Number :" << client.accountNumber << "\n"
		<< "- PinCode :" << client.pinCode << "\n"
		<< "- Name :" << client.name << "\n"
		<< "- Phone :" << client.phone << "\n"
		<< "- Account Balance :" << client.accountBalance << "\n\n";
}

void ShowFindClientScreen()
{
	if (!CheckAccessPermissions(enMainMenuePermissions::pFindClient))
	{
		ShowAccessDenied();
		return;
	}

	PrintMessageOnScreen("------------------------------------------------");
	PrintMessageOnScreen("\t\tFind Client Screen");
	PrintMessageOnScreen("------------------------------------------------");

	vector <stClientData> VClients = LoadClientsDataFromFile();
	stClientData client;
	string accountNumber = ReadClientAccountNumber();

	if (isFindClient(accountNumber, VClients, client))
	{
		PrintClientRecordDetails(client);
		return;
	}
	cout << "\nClient With Account Number [" << accountNumber << "] Is Not Found\n";
}
#pragma endregion

#pragma region Display All Clients
void PrintClientRecord(stClientData client)
{
	cout << "| " << setw(15) << left << client.accountNumber;
	cout << "| " << setw(10) << left << client.pinCode;
	cout << "| " << setw(40) << left << client.name;
	cout << "| " << setw(12) << left << client.phone;
	cout << "| " << setw(12) << left << client.accountBalance;
}

void ShowAllClientScreen(vector<stClientData>& vClients)
{
	if (!CheckAccessPermissions(enMainMenuePermissions::pListClients))
	{
		ShowAccessDenied();
		return;
	}
	cout << "\t\t\t\t\tClinet List (" << vClients.size() << ") Client(s)";
	cout << "\n-------------------------------------------------";
	cout << "-------------------------------------------------\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n-------------------------------------------------";
	cout << "-------------------------------------------------\n" << endl;

	for (stClientData& client : vClients)
	{
		PrintClientRecord(client);
		cout << endl;
	}
	cout << "\n-------------------------------------------------";
	cout << "-------------------------------------------------\n" << endl;
}
#pragma endregion

#pragma region convert From Record To String
string convertFromRecordToString(stClientData clientRecord, string separetor = "#//#")
{
	string result = "";
	result += clientRecord.accountNumber + separetor;
	result += clientRecord.pinCode + separetor;
	result += clientRecord.name + separetor;
	result += clientRecord.phone + separetor;
	result += to_string(clientRecord.accountBalance) + separetor;
	return result;
}
#pragma endregion

#pragma region save Record Line To File
void saveRecordLineToFile(string fileName, string line)
{
	fstream Myfile;

	Myfile.open(fileName, ios::out | ios::app);

	if (Myfile.is_open())
	{
		Myfile << line << endl;
	}

	Myfile.close();
}
#pragma endregion

#pragma region save Clients Data To File
vector<stClientData> saveClientsDataToFile(string FileName, vector<stClientData> vClients)
{
	fstream myFile;
	string dataLine;

	myFile.open(ClientsFileName, ios::out);

	if (myFile.is_open())
	{
		for (stClientData& c : vClients)
		{
			if (c.markForDelete == false)
			{
				dataLine = convertFromRecordToString(c);

				myFile << dataLine << endl;
			}
		}
		myFile.close();
	}
	return vClients;
}
#pragma endregion

#pragma region Add New Client
stClientData ReadNewClient()
{
	vector<stClientData> VClients = LoadClientsDataFromFile();
	stClientData client;
	client.accountNumber = ReadWord("Enter Account Number ? ");

	while (isFindClient(client.accountNumber, VClients, client))
	{
		cout << "\nClient With [" << client.accountNumber << "] already exists, ";
		client.accountNumber = ReadWord("Enter another Account Number ? ");
	}
	client.pinCode = ReadWord("Enter PinCode ? ");
	client.name = ReadWords("Enter Name ? ");
	client.phone = ReadWord("Enter Phone ? ");
	client.accountBalance = ReadPositiveFloatNumber("Enter AccountBalance? ");

	return client;
}

void AddNewClient()
{
	stClientData client;
	string line = "";

	client = ReadNewClient();
	line = convertFromRecordToString(client);
	saveRecordLineToFile(ClientsFileName, line);
}

void AddNewClients()
{
	char addMore = 'y';

	do
	{
		PrintMessageOnScreen("Adding New Clien:\n");

		AddNewClient();

		cout << "\nClient Added Successfully, ";
		addMore = ReadCharacter("do you want to add more clients? Y/N?");

	} while (addMore == 'y' || addMore == 'Y');
}

void ShowAddNewClientScreen()
{
	if (!CheckAccessPermissions(enMainMenuePermissions::pAddNewClient))
	{
		ShowAccessDenied();
		return;
	}
	PrintMessageOnScreen("-------------------------------------------------");
	PrintMessageOnScreen("\t\tAdd New Clients Screen");
	PrintMessageOnScreen("-------------------------------------------------");

	AddNewClients();
}
#pragma endregion

#pragma region Delete Client By Account Number
bool markClientForDeleteByAccountNumber(string accountNumber, vector<stClientData>& vClients)
{
	for (stClientData& client : vClients)
	{
		if (accountNumber == client.accountNumber)
		{
			client.markForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteClientByAccountNumber(string accountNumber, vector<stClientData>& VClients)
{
	stClientData client;
	char answer = 'n';

	if (isFindClient(accountNumber, VClients, client))
	{
		PrintClientRecordDetails(client);

		cout << "\n\nAre You Sure You Want Delete This Client ? y/n ?";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			markClientForDeleteByAccountNumber(accountNumber, VClients);
			saveClientsDataToFile(ClientsFileName, VClients);
			VClients = LoadClientsDataFromFile();
			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	cout << "\nClient With Account Number (" << accountNumber << ") Is Not Found\n";
	return false;
}

void ShowDeleteClientScreen()
{
	if (!CheckAccessPermissions(enMainMenuePermissions::pDeleteClient))
	{
		ShowAccessDenied();
		return;
	}

	PrintMessageOnScreen("-------------------------------------------------");
	PrintMessageOnScreen("\t\tDelete Client Screen");
	PrintMessageOnScreen("-------------------------------------------------");

	vector<stClientData> Vclients = LoadClientsDataFromFile();
	string accountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(accountNumber, Vclients);

}
#pragma endregion

#pragma region Update Client By Account Number
stClientData changeClientRecord(string accountNumber)
{
	stClientData client;
	client.accountNumber = accountNumber;

	client.pinCode = ReadWord("Enter Pin Code ?");
	client.name = ReadWords("Enter Your Name ?");
	client.phone = ReadWord("Enter Phone Number ?");
	client.accountBalance = ReadPositiveFloatNumber("Enter Account Balance ?");

	return client;
}

bool UpdateClientByAccountNumber(string accountNumber, vector<stClientData>& VClients)
{
	stClientData client;
	char answer = 'n';

	if (isFindClient(accountNumber, VClients, client))
	{
		PrintClientRecordDetails(client);

		cout << "\n\nAre You Sure You Want Update This Client ? y/n ?";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			for (stClientData& C : VClients)
			{
				if (C.accountNumber == accountNumber)
				{
					C = changeClientRecord(accountNumber);
					break;
				}
			}

			saveClientsDataToFile(ClientsFileName, VClients);
			cout << "\n\nClient Updated Successfully\n";
			return true;
		}
	}
	cout << "\nClient With Account Number (" << accountNumber << ") Not Found\n";
	return false;
}

void ShowUpdateClientScreen()
{
	if (!CheckAccessPermissions(enMainMenuePermissions::pUpdateClient))
	{
		ShowAccessDenied();
		return;
	}

	PrintMessageOnScreen("-------------------------------------------------");
	PrintMessageOnScreen("\t\tUpdate Client Screen");
	PrintMessageOnScreen("-------------------------------------------------");

	vector<stClientData> Vclients = LoadClientsDataFromFile();
	string accountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(accountNumber, Vclients);
}
#pragma endregion

#pragma region Go Back To Transactions Menue
void GoBackToTransactionsMenue()
{
	PrintMessageOnScreen("\nPress any key to go back to Transaction Menue...");
	system("pause>0");
	ShowTransactionsMenue();
}
#pragma endregion

#pragma region get Client By Account Number
stClientData getClientByAccountNumber(vector<stClientData> VClients)
{
	stClientData client;
	bool findClient;
	string accountNumber;

	do
	{
		accountNumber = ReadClientAccountNumber();
		findClient = isFindClient(accountNumber, VClients, client);

		if (!findClient)
		{
			cout << "Client With [ " << accountNumber << " ] does not exist.\n\n";
		}

	} while (!findClient);

	return client;
}
#pragma endregion  
#pragma endregion


#pragma region Deposit
void Deposit(vector<stClientData>& VClients)
{
	stClientData client;
	float amount = 0.00;
	char answerYOrN = 'y';

	client = getClientByAccountNumber(VClients);

	PrintClientRecordDetails(client);

	amount = ReadPositiveFloatNumber("\nPlease Enter Deposit Amount ? ");

	answerYOrN = ReadCharacter("\nAre You Sure You Want Perfrom This Transaction ? y/n ? ");

	if (answerYOrN == 'y' || answerYOrN == 'Y')
	{
		for (stClientData& C : VClients)
		{
			if (C.accountNumber == client.accountNumber)
			{
				C.accountBalance += amount;
				client.accountBalance = C.accountBalance;
				break;
			}
		}

		PrintMessageOnScreen("\nThe amount has been deposited successfully.");
		printf("\nDeposited Amount : %.2f", amount);
		printf("\nCurrent Balance : %.2f\n\n", client.accountBalance);

		saveClientsDataToFile(ClientsFileName, VClients);
		GoBackToTransactionsMenue();
	}
	else
	{
		ShowTransactionsMenue();
	}
}

void ShowDepositScreen()
{
	PrintMessageOnScreen("-------------------------------------------------");
	PrintMessageOnScreen("\t\tDeposit Screen");
	PrintMessageOnScreen("-------------------------------------------------");

	vector<stClientData> VClients;
	VClients = LoadClientsDataFromFile();

	Deposit(VClients);
}
#pragma endregion

#pragma region Withdraw
void Withdraw(vector<stClientData>& VClients)
{
	stClientData client;
	float amount = 0.00;
	char answerYOrN = 'y';

	client = getClientByAccountNumber(VClients);

	PrintClientRecordDetails(client);

	amount = ReadPositiveFloatNumber("\nPlease Enter Withdrawn Amount ? ");

	answerYOrN = ReadCharacter("\nAre You Sure You Want Perfrom This Transaction ? y/n ? ");

	if (answerYOrN == 'y' || answerYOrN == 'Y')
	{
		for (stClientData& C : VClients)
		{
			if (C.accountNumber == client.accountNumber)
			{
				if (amount <= C.accountBalance)
				{
					C.accountBalance -= amount;
					client.accountBalance = C.accountBalance;
					break;
				}
				else
				{
					printf("\nThe Amount To Be Withdrawn Is [ %.2f ] Not Available In Your Account\n\n", amount);
					GoBackToTransactionsMenue();
				}
			}
		}

		PrintMessageOnScreen("\nThe Amount Has Been Withdrawn Successfully.");
		printf("\nWithdrawn Amount : %.2f", amount);
		printf("\nCurrent Balance : %.2f\n\n", client.accountBalance);

		saveClientsDataToFile(ClientsFileName, VClients);
		GoBackToTransactionsMenue();
	}
	else
	{
		ShowTransactionsMenue();
	}
}

void ShowWithdrawScreen()
{
	PrintMessageOnScreen("-------------------------------------------------");
	PrintMessageOnScreen("\t\tWithdraw Screen");
	PrintMessageOnScreen("-------------------------------------------------");

	vector<stClientData> VClients;
	VClients = LoadClientsDataFromFile();

	Withdraw(VClients);
}
#pragma endregion

#pragma region Show All Clients Total Balances
float GetTotalBalances(vector<stClientData>& vClients)
{
	float sumBalaces = 0.00;
	for (stClientData& client : vClients)
	{
		sumBalaces += client.accountBalance;
	}
	return sumBalaces;
}

void PrintClientRecordTotalBalance(stClientData client)
{
	cout << "| " << setw(15) << left << client.accountNumber;
	cout << "| " << setw(40) << left << client.name;
	cout << "| " << setw(12) << left << client.accountBalance;
}

void ShowAllClientsTotalBalances(vector<stClientData>& vClients)
{
	cout << "\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s)";
	cout << "\n-------------------------------------------------";
	cout << "-------------------------------------------------\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n-------------------------------------------------";
	cout << "-------------------------------------------------\n" << endl;

	for (stClientData& client : vClients)
	{
		PrintClientRecordTotalBalance(client);
		cout << endl;
	}
	cout << "\n-------------------------------------------------";
	cout << "-------------------------------------------------\n" << endl;

	printf("\t\t\t\t\tTotal Balances = %.2f\n\n", GetTotalBalances(vClients));
}
#pragma endregion

#pragma region  Transactions Menue
void TransactionsMenue(int chooseNumber)
{

	vector<stClientData> VClients;
	VClients = LoadClientsDataFromFile();
	switch (chooseNumber)
	{
	case enTransactionMenueOption::eDeposit:
		system("cls");
		ShowDepositScreen();
		break;
	case enTransactionMenueOption::eWithdraw:
		system("cls");
		ShowWithdrawScreen();
		break;

	case enTransactionMenueOption::eTotalBalancces:
		system("cls");
		ShowAllClientsTotalBalances(VClients);
		GoBackToTransactionsMenue();
		break;

	case enTransactionMenueOption::eMainMenue:
		system("cls");
		ShowMainMenue();
		break;
	}
}
#pragma endregion

#pragma region Show Transactions Menue
void ShowTransactionsMenue()
{
	if (!CheckAccessPermissions(enMainMenuePermissions::pTransactions))
	{
		ShowAccessDenied();
		return;
	}

	system("cls");
	PrintMessageOnScreen("===========================================");
	PrintMessageOnScreen("\tTransactions Menue Screen");
	PrintMessageOnScreen("===========================================");
	PrintMessageOnScreen("\t[1] Deposit.");
	PrintMessageOnScreen("\t[2] Withdraw.");
	PrintMessageOnScreen("\t[3] Total Balancces.");
	PrintMessageOnScreen("\t[4] Main Menue.");
	PrintMessageOnScreen("===========================================");
	TransactionsMenue(ReadChoiseMainMenue(4));
}
#pragma endregion

#pragma region Find User By UserName
bool isFindUser(string userName, vector<stUserData>& users, stUserData& user)
{
	for (stUserData& U : users)
	{
		if (userName == U.userName)
		{
			user = U;
			return true;
		}
	}
	return false;
}
#pragma endregion

#pragma region convert User From Line To Record
stUserData convertUserFromLineToRecord(string line, string separetor = "#//#")
{
	stUserData user;

	vector<string> VUsers = SplitEachWordInVector(line, separetor);

	user.userName = VUsers[0];
	user.password = VUsers[1];
	user.permission = stoi(VUsers[2]);

	return user;
}
#pragma endregion

#pragma region Load Users Data From File 
vector<stUserData> LoadUsersDataFromFile()
{
	fstream myFile;
	vector<stUserData> VUsers;

	myFile.open(UsersFileName, ios::in);

	if (myFile.is_open())
	{
		string line = "";
		stUserData user;

		while (getline(myFile, line))
		{
			user = convertUserFromLineToRecord(line);
			VUsers.push_back(user);
		}

		myFile.close();
	}
	return VUsers;
}
#pragma endregion

#pragma region Check userName and password valid or not valid
void checkLogin()
{
	stUserData user;
	string username = "", password;
	vector<stUserData> users = LoadUsersDataFromFile();
	bool isInvalid = false;

	do
	{
		if (isInvalid)
		{
			cout << "\nInvalid Username OR Password\n";
		}

		username = ReadWord("Enter Username ? ");

		password = ReadWord("Enter Password ? ");

		if (isFindUser(username, users, user))
		{
			if (user.password == password)
			{
				GlobalUserData = user;
				return;
			}
		}
		isInvalid = true;
	} while (true);
}
#pragma endregion

#pragma region Login Screen

void ShowLoginScreen()
{
	PrintMessageOnScreen("-------------------------------------------------");
	PrintMessageOnScreen("\t\tLogin Screen");
	PrintMessageOnScreen("-------------------------------------------------");

	checkLogin();
	ShowMainMenue();
}
#pragma endregion

#pragma region Display All Users
void PrintUserRecord(stUserData user)
{
	cout << "| " << setw(15) << left << user.userName;
	cout << "| " << setw(10) << left << user.password;
	cout << "| " << setw(40) << left << user.permission;
}

void ShowAllUserScreen(vector<stUserData>& vUsers)
{
	cout << "\t\t\t\t\tUser List (" << vUsers.size() << ") User(s)";
	cout << "\n-------------------------------------------------";
	cout << "-------------------------------------------------\n" << endl;

	cout << "| " << left << setw(15) << "UserName";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permission";
	cout << "\n-------------------------------------------------";
	cout << "-------------------------------------------------\n" << endl;

	for (stUserData& user : vUsers)
	{
		PrintUserRecord(user);
		cout << endl;
	}
	cout << "\n-------------------------------------------------";
	cout << "-------------------------------------------------\n" << endl;
}
#pragma endregion

#pragma region Read User Username
string ReadUserUsername()
{
	string username = ReadWord("\nPlease Enter Username ? ");
	return username;
}
#pragma endregion

#pragma region Add User Permissions 
int ReadPermissionsToSet()
{
	int permissions = 0;

	char answer = ReadCharacter("\nDo You Want To Give Full Access? y/n?");

	if (answer == 'Y' || answer == 'y')
	{
		return enMainMenuePermissions::pAll;
	}
	PrintMessageOnScreen("\nDo You Want To Give Access To :\n");
	answer = ReadCharacter("\nShow Client List ? y/n? ");

	if (answer == 'Y' || answer == 'y')
	{
		permissions += enMainMenuePermissions::pListClients;
	}

	answer = ReadCharacter("\nAdd New Client ? y/n? ");

	if (answer == 'Y' || answer == 'y')
	{
		permissions += enMainMenuePermissions::pAddNewClient;
	}

	answer = ReadCharacter("\nDelete Client ? y/n? ");

	if (answer == 'Y' || answer == 'y')
	{
		permissions += enMainMenuePermissions::pDeleteClient;
	}

	answer = ReadCharacter("\nUpdate Client ? y/n? ");

	if (answer == 'Y' || answer == 'y')
	{
		permissions += enMainMenuePermissions::pUpdateClient;
	}

	answer = ReadCharacter("\nFins Client ? y/n? ");

	if (answer == 'Y' || answer == 'y')
	{
		permissions += enMainMenuePermissions::pFindClient;
	}

	answer = ReadCharacter("\nTransactions ? y/n? ");

	if (answer == 'Y' || answer == 'y')
	{
		permissions += enMainMenuePermissions::pTransactions;
	}

	answer = ReadCharacter("\nManage Users ? y/n? ");

	if (answer == 'Y' || answer == 'y')
	{
		permissions += enMainMenuePermissions::pManageUser;
	}

	return permissions;

}
#pragma endregion

#pragma region convert From Record To String
string convertFromRecordUserToString(stUserData userRecord, string separetor = "#//#")
{
	string result = "";
	result += userRecord.userName + separetor;
	result += userRecord.password + separetor;
	result += to_string(userRecord.permission) + separetor;
	return result;
}
#pragma endregion

#pragma region save Clients Data To File
vector<stUserData> saveUsersDataToFile(string FileName, vector<stUserData> vUsers)
{
	fstream myFile;
	string dataLine;

	myFile.open(UsersFileName, ios::out);

	if (myFile.is_open())
	{
		for (stUserData& u : vUsers)
		{
			if (u.markForDelete == false)
			{
				dataLine = convertFromRecordUserToString(u);

				myFile << dataLine << endl;
			}
		}
		myFile.close();
	}
	return vUsers;
}
#pragma endregion

#pragma region Show Find User Screen
void PrintUserRecordDetails(stUserData user)
{
	cout << "The following is the extracted client Details :\n\n"
		<< "- Username   : " << user.userName << "\n"
		<< "- Password   : " << user.password << "\n"
		<< "- Permission : " << user.permission << "\n\n";
}

void ShowFindUserScreen()
{
	PrintMessageOnScreen("------------------------------------------------");
	PrintMessageOnScreen("\t\tFind User Screen");
	PrintMessageOnScreen("------------------------------------------------");

	vector <stUserData> VUsers = LoadUsersDataFromFile();
	stUserData user;
	string username = ReadUserUsername();

	if (isFindUser(username, VUsers, user))
	{
		PrintUserRecordDetails(user);
		return;
	}
	cout << "\nUser With Username [" << username << "] Is Not Found\n";
}
#pragma endregion

#pragma region Add New User
stUserData ReadNewUser()
{
	vector<stUserData> VUsers = LoadUsersDataFromFile();
	stUserData user;
	user.userName = ReadUserUsername();

	while (isFindUser(user.userName, VUsers, user))
	{
		cout << "\nClient With [" << user.userName << "] already exists, ";
		user.userName = ReadWord("Enter another Username ? ");
	}
	user.password = ReadWord("\nEnter Password ? ");
	user.permission = ReadPermissionsToSet();

	return user;
}

void AddNewUser()
{
	stUserData user;
	string line = "";

	user = ReadNewUser();
	line = convertFromRecordUserToString(user);
	saveRecordLineToFile(UsersFileName, line);
}

void AddNewUsers()
{
	char addMore = 'y';

	do
	{
		PrintMessageOnScreen("Adding New User:\n");

		AddNewUser();

		cout << "\nUser Added Successfully, ";
		addMore = ReadCharacter("do you want to add more users? Y/N?");

	} while (addMore == 'y' || addMore == 'Y');
}

void ShowAddNewUserScreen()
{
	PrintMessageOnScreen("-------------------------------------------------");
	PrintMessageOnScreen("\t\tAdd New User Screen");
	PrintMessageOnScreen("-------------------------------------------------");

	AddNewUsers();
}
#pragma endregion

#pragma region Delete User By Username
bool markUserForDeleteByAccountNumber(string username, vector<stUserData>& vUsers)
{
	for (stUserData& user : vUsers)
	{
		if (username == user.userName)
		{
			user.markForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteUserByUsername(string username, vector<stUserData>& VUsers)
{
	if (username == "Admin")
	{
		cout << "\n\nYou cannot Delete This User.";
		return false;
	}

	stUserData user;
	char answer = 'n';

	if (isFindUser(username, VUsers, user))
	{
		PrintUserRecordDetails(user);

		cout << "\n\nAre You Sure You Want Delete This User ? y/n ?";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			markUserForDeleteByAccountNumber(username, VUsers);
			saveUsersDataToFile(UsersFileName, VUsers);
			VUsers = LoadUsersDataFromFile();
			cout << "\n\nUser Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nUser With Username (" << username << ") Is Not Found\n";
	}
	return false;
}

void ShowDeleteUserScreen()
{
	PrintMessageOnScreen("-------------------------------------------------");
	PrintMessageOnScreen("\t\tDelete User Screen");
	PrintMessageOnScreen("-------------------------------------------------");

	vector<stUserData> Vusers = LoadUsersDataFromFile();
	string username = ReadClientAccountNumber();
	DeleteUserByUsername(username, Vusers);

}
#pragma endregion

#pragma region Update User By Username
stUserData changeUserRecord(string username)
{
	stUserData user;
	user.userName = username;
	user.password = ReadWord("\nEnter Password ? ");
	user.permission = ReadPermissionsToSet();

	return user;
}

bool UpdateUserByUsername(string username, vector<stUserData>& VUsers)
{
	stUserData user;
	char answer = 'n';

	if (isFindUser(username, VUsers, user))
	{
		PrintUserRecordDetails(user);

		cout << "\n\nAre You Sure You Want Update This User ? y/n ?";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			for (stUserData& U : VUsers)
			{
				if (U.userName == username)
				{
					U = changeUserRecord(username);
					break;
				}
			}

			saveUsersDataToFile(UsersFileName, VUsers);
			cout << "\n\nUser Updated Successfully\n";
			return true;
		}
	}
	cout << "\nUser With Username (" << username << ") Not Found\n";
	return false;
}

void ShowUpdateUserScreen()
{
	PrintMessageOnScreen("-------------------------------------------------");
	PrintMessageOnScreen("\t\tUpdate User Screen");
	PrintMessageOnScreen("-------------------------------------------------");

	vector<stUserData> Vusers = LoadUsersDataFromFile();
	string username = ReadUserUsername();
	UpdateUserByUsername(username, Vusers);
}
#pragma endregion

#pragma region Go Back To Manage Users Menue
void GoBackToManageUsersMenue()
{
	PrintMessageOnScreen("\nPress any key to go back to Manage Users Menue...");
	system("pause>0");
	ShowManageUsersMenue();
}
#pragma endregion

#pragma region Manage Users Menu
void ManageUsersMenue(enManageUsersMenue chooseNumber)
{
	vector<stUserData> VUsers;
	stUserData user;
	VUsers = LoadUsersDataFromFile();

	switch (chooseNumber)
	{
	case eListUser:
		system("cls");
		ShowAllUserScreen(VUsers);
		GoBackToManageUsersMenue();
		break;
	case eAddNewUser:
		system("cls");
		ShowAddNewUserScreen();
		GoBackToManageUsersMenue();
		break;
	case eDeleteUser:
		system("cls");
		ShowDeleteUserScreen();
		GoBackToManageUsersMenue();
		break;
	case eUpdateUser:
		system("cls");
		ShowUpdateUserScreen();
		GoBackToManageUsersMenue();
		break;
	case eFindUser:
		system("cls");
		ShowFindUserScreen();
		GoBackToManageUsersMenue();
		break;
	case eUMainMenue:
		system("cls");
		ShowMainMenue();
		break;
	default:
		cout << "Invalid menu option!\n";
		break;
	}
}
#pragma endregion

#pragma region Show Manage Users Menue
void ShowManageUsersMenue()
{
	if (!CheckAccessPermissions(enMainMenuePermissions::pManageUser))
	{
		ShowAccessDenied();
		return;
	}

	system("cls");
	PrintMessageOnScreen("===========================================");
	PrintMessageOnScreen("\tManage Users Menue Screen");
	PrintMessageOnScreen("===========================================");
	PrintMessageOnScreen("\t[1] List Users.");
	PrintMessageOnScreen("\t[2] Add New User.");
	PrintMessageOnScreen("\t[3] Delete User.");
	PrintMessageOnScreen("\t[4] Update User.");
	PrintMessageOnScreen("\t[5] Find User.");
	PrintMessageOnScreen("\t[6] Main Menue.");
	PrintMessageOnScreen("===========================================");
	ManageUsersMenue((enManageUsersMenue)ReadChoiseMainMenue(6));
}
#pragma endregion

#pragma region Logout
void ShowLogoutScreen()
{
	ShowLoginScreen();
}
#pragma endregion

#pragma region Go Back To Main Menue
void GoBackToMainMenue()
{
	PrintMessageOnScreen("\nPress any key to go back to Main Menue...");
	system("pause>0");
	ShowMainMenue();
}
#pragma endregion

#pragma region Main Menue
void  MainMenue(int chooseNumber)
{
	vector<stClientData> VClients;
	stClientData client;
	VClients = LoadClientsDataFromFile();

	switch (chooseNumber)
	{
	case enMainMenueOption::eShowAllClient:
		system("cls");
		ShowAllClientScreen(VClients);
		GoBackToMainMenue();
		break;
	case enMainMenueOption::eAddClient:
		system("cls");
		ShowAddNewClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::eDelete:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;

	case enMainMenueOption::eUpdate:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOption::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenue();
		break;
	case enMainMenueOption::eTransactions:
		system("cls");
		ShowTransactionsMenue();
		GoBackToMainMenue();
		break;
	case enMainMenueOption::eManageUsers:
		system("cls");
		ShowManageUsersMenue();
		break;
	case enMainMenueOption::eLogout:
		system("cls");
		ShowLogoutScreen();
		break;
	}
}
#pragma endregion

#pragma region Show Main Menue
void ShowMainMenue()
{
	system("cls");
	PrintMessageOnScreen("===========================================");
	PrintMessageOnScreen("\tMain Menue Screen");
	PrintMessageOnScreen("===========================================");
	PrintMessageOnScreen("\t[1] Show Clients List.");
	PrintMessageOnScreen("\t[2] Add New Client.");
	PrintMessageOnScreen("\t[3] Delete Client.");
	PrintMessageOnScreen("\t[4] Update Client Info.");
	PrintMessageOnScreen("\t[5] Find Client.");
	PrintMessageOnScreen("\t[6] Transactions.");
	PrintMessageOnScreen("\t[7] Manage Users.");
	PrintMessageOnScreen("\t[8] Logout.");
	PrintMessageOnScreen("===========================================");
	MainMenue(ReadChoiseMainMenue(8));

}
#pragma endregion


int main()
{
	ShowLoginScreen();
}
