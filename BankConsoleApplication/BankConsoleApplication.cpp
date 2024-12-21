#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#pragma region Variables Const
const string ClientsFileName = "Clients.txt";
#pragma endregion

#pragma region Defined Function
void ShowMainMenue();

void ShowTransactionsMenue();
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

#pragma region struct Client Data
struct stClientData
{
	string accountNumber = "", name = "", pinCode = "", phone = "";
	float accountBalance = 0.00;
	bool markForDelete = false;
};
#pragma endregion

#pragma region Enum Main Menue Options
enum enMainMenueOption
{
	eShowAllClient = 1, eAddClient, eDelete, eUpdate, eFindClient, eTransactions, eExit
};
#pragma endregion

#pragma region Enum Main Menue Options
enum enTransactionMenueOption
{
	eDeposit = 1, eWithdraw, eTotalBalancces, eMainMenue
};
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
		system("cls");
		PrintMessageOnScreen("Adding New Clien:\n");

		AddNewClient();

		cout << "\nClient Added Successfully, ";
		addMore = ReadCharacter("do you want to add more clients? Y/N?");

	} while (addMore == 'y' || addMore == 'Y');
}

void ShowAddNewClientScreen()
{
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
	PrintMessageOnScreen("-------------------------------------------------");
	PrintMessageOnScreen("\t\tUpdate Client Screen");
	PrintMessageOnScreen("-------------------------------------------------");

	vector<stClientData> Vclients = LoadClientsDataFromFile();
	string accountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(accountNumber, Vclients);
}
#pragma endregion


void GoBackToTransactionsMenue()
{
	PrintMessageOnScreen("\nPress any key to go back to Transaction Menue...");
	system("pause>0");
	ShowTransactionsMenue();
}

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

#pragma region Exist Program
void ShowEndScreen()
{
	PrintMessageOnScreen("-------------------------------------------------");
	PrintMessageOnScreen("\t\tProgram End :-)");
	PrintMessageOnScreen("-------------------------------------------------");
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
		break;
	case enMainMenueOption::eExit:
		system("cls");
		ShowEndScreen();
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
	PrintMessageOnScreen("\t[7] Exit.");
	PrintMessageOnScreen("===========================================");
	MainMenue(ReadChoiseMainMenue(7));

}
#pragma endregion


int main()
{
	ShowMainMenue();
}
