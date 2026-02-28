
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};
enum enATMMainMenueOptions
{
	eQuickWithdraw = 1,
	eNormalWithdraw = 2,
	eDeposit = 3,
	eChackBalances = 4,
	Logout = 5
};
sClient CurrentClient;
using namespace std;
const string ClientsFileName = "Clients.txt";
void Login();
void ShowATMMainMenue();
void ShowNormalWithdrawScreen();
void ShowQuickWithdrawScreen();
vector<string> SplitString(string S1, string delim) {
	vector<string> vString;
	short pos = 0;
	string sWord;
	while ((pos = S1.find(delim)) != string::npos)
	{
		sWord = S1.substr(0, pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}
sClient convertLineToRecord(string line, string Seperator = "#//#") {
	vector<string>ClientData = SplitString(line, Seperator);
	sClient Client;
	Client.AccountNumber = ClientData[0];
	Client.PinCode = ClientData[1];
	Client.Name = ClientData[2];
	Client.Phone = ClientData[3];
	Client.AccountBalance = stod(ClientData[4]);
	return Client;
}
vector<sClient>LoadCleintsDataFromFile(string FileName) {
	vector <sClient> vClients;
	fstream ClientFile;
	ClientFile.open(FileName, ios::in);
	string line;
	sClient Client;
	if (ClientFile.is_open()) {
		while (getline(ClientFile, line)) {
			Client = convertLineToRecord(line);
			vClients.push_back(Client);

		}
		ClientFile.close();
	}
	return vClients;
}
bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client)
{
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	for (sClient C : vClients)
	{
		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
		{
			Client = C;
			return true;
		}
	}

	return false;
}
bool LoadClientInfo(string AccountNumber, string PinCode)
{

	return (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient));

}
void GoBackToATMMianMenue() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	ShowATMMainMenue();
}
string ConvertRecordToLine(sClient Client, string Seperator = "#//#") {
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient>& vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine;
	if (MyFile.is_open())
	{
		for (sClient& C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClients;
}
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <sClient>& vClients)
{
	char Answer = 'n';
	cout << "\n\nAre you sure you want perfrom this transaction? y / n ? ";
	cin >> Answer;
	if (Answer == 'y' || Answer == 'Y')
	{
		for (sClient& C : vClients)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveCleintsDataToFile(ClientsFileName, vClients);
				cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

				return true;
			}
		}
		return false;
	}
	return false;
}
double ReadDepositAmount()
{
	double Amount;
	cout << "\nEnter a positive Deposit Amount? ";

	cin >> Amount;
	while (Amount <= 0)
	{
		cout << "\nEnter a positive Deposit Amount? ";
		cin >> Amount;
	}
	return Amount;
}
int ReadWithDrawAmont()
{
	int Amount;
	do {
		cout << "\nEnter an amount multiple of 5's ? ";
		cin >> Amount;
	} while (Amount % 5 != 0);
	return Amount;
}
short ReadQuickWithdrawOption()
{
	short Choice = 0;
	while (Choice < 1 || Choice>9)
	{
		cout << "\nChoose what to do from [1] to [9] ? ";
		cin >> Choice;
	}

	return Choice;
}
short getQuickWithDrawAmount(short QuickWithDrawOption)
{
	switch (QuickWithDrawOption)
	{
	case 1:
		return  20;
	case 2:
		return 50;
	case 3:
		return 100;
	case 4:
		return 200;
	case 5:
		return 400;
	case 6:
		return 600;
	case 7:
		return 800;
	case 8:
		return 1000;
	default:
		return 0;

	}

}

void PerfromQuickWithdrawOption(short QuickWithDrawOption)
{
	if (QuickWithDrawOption == 9)//exit 
		return;

	short WithDrawBalance = getQuickWithDrawAmount(QuickWithDrawOption);

	if (WithDrawBalance > CurrentClient.AccountBalance)
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "Press Anykey to continue...";
		system("pause>0");
		ShowQuickWithdrawScreen();
		return;
	}

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	if (DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawBalance * -1, vClients))
	{
		CurrentClient.AccountBalance -= WithDrawBalance; 
	}


}

void ShowQuickWithdrawScreen() {
	cout << "\n------------------------------------\n";
	cout << "\tQuick Withdraw  \n";
	cout << "------------------------------------\n";
	cout << "\t[1] 20\t\t[2] 50\n";
	cout << "\t[3] 100\t\t[4] 200\n";
	cout << "\t[5] 400\t\t[6] 600\n";
	cout << "\t[7] 800\t\t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "------------------------------------\n\n";
	cout << "Your Balance is " << CurrentClient.AccountBalance;
	PerfromQuickWithdrawOption(ReadQuickWithdrawOption());
}


void PerfromNormalWithdrawOption()
{

	int WithDrawBalance = ReadWithDrawAmont();

	if (WithDrawBalance > CurrentClient.AccountBalance)
	{
		cout << "\nThe amount exceeds your balance, make another choice.\n";
		cout << "Press Anykey to continue...";
		system("pause>0");
		ShowNormalWithdrawScreen();
		return;
	}

	vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
	if (DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithDrawBalance * -1, vClients))
	{
		CurrentClient.AccountBalance -= WithDrawBalance;
	}
}
void ShowNormalWithdrawScreen() {
	cout << "\n------------------------------------\n";
	cout << "\tNormal Withdraw Screen  \n";
	cout << "------------------------------------\n\n";
	PerfromNormalWithdrawOption();
}
void PerfromDepositOption()
{
	double DepositAmount = ReadDepositAmount();
	vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

	
	if (DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClients))
	{
		CurrentClient.AccountBalance += DepositAmount; 
	}
}


void ShowDepositScreen() {
	cout << "\n------------------------------------\n";
	cout << "\tDeposit Screen  \n";
	cout << "------------------------------------\n\n";
	PerfromDepositOption();
}
void ShowChackBalancesScreen() {
	cout << "\n------------------------------------\n";
	cout << "\tChack Balances Screen  \n";
	cout << "------------------------------------\n\n";
	cout << "New balance is: " << CurrentClient.AccountBalance;
}

void PerformATMMainMenueOption(enATMMainMenueOptions ATMMainMenueOption) {
	switch (ATMMainMenueOption)
	{
	case enATMMainMenueOptions::eQuickWithdraw:
		system("cls");
		ShowQuickWithdrawScreen();
		GoBackToATMMianMenue();
		break;
	case  enATMMainMenueOptions::eNormalWithdraw:
		system("cls");
		ShowNormalWithdrawScreen();
		GoBackToATMMianMenue();
		break;
	case  enATMMainMenueOptions::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToATMMianMenue();
		break;
	case  enATMMainMenueOptions::eChackBalances:
		system("cls");
		ShowChackBalancesScreen();
		GoBackToATMMianMenue();
		break;
	case  enATMMainMenueOptions::Logout:
		system("cls");;
		Login();
		break;
	}
}
short ReadATMMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 5]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}

void ShowATMMainMenue() {
	system("cls");
	cout << "===============================================\n";
	cout << "\t\tATM Main Menue Screen \n";
	cout << "===============================================\n";
	cout << "\t[1] Quick Withdraw.   \n ";
	cout << "\t[2] Normal Withdraw.     \n ";
	cout << "\t[3] Deposit.       \n ";
	cout << "\t[4] Chack Balances. \n ";
	cout << "\t[5] Logout.\n ";
	cout << "===============================================\n";
	PerformATMMainMenueOption(enATMMainMenueOptions(ReadATMMainMenueOption()));
}
void Login()
{
	bool LoginFaild = false;

	string AccountNumber, PinCode;
	do
	{
		system("cls");
		cout << "\n---------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n---------------------------------\n";

		if (LoginFaild)
		{
			cout << "Invlaid AccountNumber/PinCode!\n";
		}

		cout << "Enter Account Number? ";
		cin >> AccountNumber;
		cout << "Enter Pin Code? ";
		cin >> PinCode;
		LoginFaild = !LoadClientInfo(AccountNumber, PinCode);
	} while (LoginFaild);

	ShowATMMainMenue();

}
int main() {
	Login();
	system("pause>0");
	return 0;
}