#include <iostream>
#include<random>
#include <iomanip> // this Library stored the std ::setw
#include <vector> //too use vectors
#include <cctype>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <string>


using namespace std;

void PrintMainMenue();
void PrintTransactionsMenue();
const string Client = "Client.txt";
enum enMainMenue {
	ShowClientDataList = 1, AddNewClient = 2, DeleteClient = 3
	, UpdateClientinfo = 4, FindClient = 5,TransActionMenue=6, Exit = 7
};
enum enTransactionsMenue {Deposit= 1,WithDraw=2
	,TotalBalances=3,MainMenue=4};
enMainMenue ReadUserChoiseOFMainMenue()
{
	int Choice;
	do
	{

		cin >> Choice;
	} while (Choice > 7 || Choice < 0);
	return (enMainMenue)Choice;
}
enTransactionsMenue ReadUserChoiseOfTransactionsMenue()
{
	int Choice;
	do
	{

		cin >> Choice;
	} while (Choice >4 || Choice < 0);
	return (enTransactionsMenue)Choice;
}
vector <string> SplitString(string s1, string delim)
{

	short postion = 0;
	string word;
	vector <string> Split;


	while ((postion = s1.find(delim)) != std::string::npos)
	{

		word = s1.substr(0, postion);

		if (word != "")
		{
			Split.push_back(word);
		}
		s1.erase(0, postion + delim.length());
	}
	if (s1 != "")
	{
		Split.push_back(s1);
	}

	return Split;
}
string ReadAccountNumber()
{
	cout << "Please Enter Account Number?  ";
	string Letter = " ";
	getline(cin >> ws, Letter);
	return Letter;
}
string ReadString()
{
	string Letter = " ";
	getline(cin >> ws, Letter);
	return Letter;
}
int ReadPositiveNumber()
{
	int Number = 0;

	do
	{
		cin >> Number;
	} while (Number <= 0);
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << " is invalid Number , Enter a valid one :" << endl;

		cin >> Number;
	}

	return Number;
}
struct stClientData
{
	string AccountNumber;
	string PinCode;
	string Name;
	string phone;
	double AccountBalance;
	bool MarkForDelete = 0;
};
bool IsFindClientByAccountNumber(string AccountNumber, vector <stClientData> vClients)
{

	bool IsExeitAccountNumber = false;


	for (stClientData ClientData : vClients)
	{

		if (ClientData.AccountNumber == AccountNumber)
		{

			return IsExeitAccountNumber = true;


		}

	}

	return false;
}
stClientData ReadClientData(string AccountNumber, vector <stClientData> vClients)
{
	cout << endl << endl;
	stClientData Data;

	cout << endl << endl;
	while (IsFindClientByAccountNumber(AccountNumber, vClients) == true)
	{
		cout << "Client With [" << AccountNumber << "] already exists, ";
		cout << "Enter Another Account Number? ";
		cin >> AccountNumber;
	}
	Data.AccountNumber = AccountNumber;
	cout << "Enter " << setw(2) << "Pin Code ? ";
	Data.PinCode = ReadString();
	cout << endl;
	cout << "Enter " << setw(2) << "Name ? ";
	Data.Name = ReadString();
	cout << endl;
	cout << "Enter " << setw(2) << "Phone ? ";
	Data.phone = ReadString();
	cout << endl;
	cout << "Enter " << setw(2) << "Account Balance ? ";
	Data.AccountBalance = ReadPositiveNumber();
	cout << endl;

	return Data;
}
stClientData ChangeClientData(string AccountNumber, vector <stClientData> vClients)
{
	stClientData Data;
	Data.AccountNumber = AccountNumber;
	cout << endl << endl;


	cout << "Enter " << setw(2) << "Pin Code ? ";
	Data.PinCode = ReadString();
	cout << endl;
	cout << "Enter " << setw(2) << "Name ? ";
	Data.Name = ReadString();
	cout << endl;
	cout << "Enter " << setw(2) << "Phone ? ";
	Data.phone = ReadString();
	cout << endl;
	cout << "Enter " << setw(2) << "Account Balance ? ";
	Data.AccountBalance = ReadPositiveNumber();
	cout << endl;

	return Data;
}
string ConvertRecordToLine(stClientData Data, string Siprator)
{
	string s = "";
	s += Data.AccountNumber + Siprator;
	s += Data.Name + Siprator;
	s += Data.PinCode + Siprator;
	s += Data.phone + Siprator;
	s += to_string(Data.AccountBalance) + Siprator;

	return s;

}
stClientData ConvertLineToRecord(string LineOfData, string Delim)
{
	stClientData stData;
	vector <string> ClientData;

	ClientData = SplitString(LineOfData, Delim);

	stData.AccountNumber = ClientData[0];
	stData.Name = ClientData[1];
	stData.PinCode = ClientData[2];
	stData.phone = ClientData[3];
	stData.AccountBalance = stoi(ClientData[4]);

	return stData;
}
void PrintClientData(stClientData Data)
{

	cout << "\nThe Following are the Client Details \n";
	cout << left << setw(20) << "\nAccount Number " << ":" << Data.AccountNumber;
	cout << left << setw(20) << "\nName " << ":" << Data.Name;
	cout << left << setw(20) << "\nPin Code " << ":" << Data.PinCode;
	cout << left << setw(20) << "\nphone " << ":" << Data.phone;
	cout << left << setw(20) << "\nAccount Balance " << ":" << Data.AccountBalance;
}
void LoadDataFromRecordToFile(string FileName, stClientData Data)
{
	fstream ClientDataFiles;
	vector <string> vData;
	ClientDataFiles.open(FileName, ios::out | ios::app);
	while (ClientDataFiles.is_open())
	{
		ClientDataFiles << ConvertRecordToLine(Data, "#//#") << endl;
		ClientDataFiles.close();
	}

}
void LoadDataFromFileToVector(string FileName, vector <string>& vData)
{
	fstream MyFirstFile;
	MyFirstFile.open(FileName, ios::in);

	if (MyFirstFile.is_open())
	{

		string m;
		while (getline(MyFirstFile, m))
		{
			vData.push_back(m);
		}
		MyFirstFile.close();

	}

}
vector <stClientData> LoadDataFromFileToStruct(string FileName)
{
	vector <string> vData;
	vector <stClientData> stData;
	fstream File;
	File.open(FileName, ios::in);

	if (File.is_open())
	{
		string m;
		while (getline(File, m))
		{
			vData.push_back(m);
			stData.push_back(ConvertLineToRecord(m, "#//#"));
		}
		File.close();
	}

	return stData;
}
bool IsFindClientByAccountNumber(string AccountNumber, stClientData& stData, vector <stClientData> vClients)
{

	bool IsExeitAccountNumber = false;


	for (stClientData ClientData : vClients)
	{

		if (ClientData.AccountNumber == AccountNumber)
		{
			stData = ClientData;
			return IsExeitAccountNumber = true;


		}

	}

	return false;
}
bool MarkClientForDeleteByAccountNumber(vector <stClientData>& vClients, string AccountNumber)
{
	for (stClientData& vClient : vClients)
	{
		if (AccountNumber == vClient.AccountNumber)
		{
			vClient.MarkForDelete = 1;
			return 1;
		}
	}
	return 0;
}
bool SaveClientDataToFile(string FileName, vector <stClientData>& vClients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine = "";
	if (MyFile.is_open())
	{
		for (stClientData C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C, "#//#");
				MyFile << DataLine << endl;

			}
		}
		return true;
	}
	return false;
}
void SaveUdatedClientDataToFile(string FileName, vector <stClientData> vClients)
{
	fstream MySecondFiless;
	MySecondFiless.open(FileName, ios::out);
	string DatalLine;

	if (MySecondFiless.is_open())
	{

		for (stClientData& C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DatalLine = ConvertRecordToLine(C, "#//#");
				MySecondFiless << DatalLine << endl;
			}

		}
		MySecondFiless.close();

	}

}
void PauseAndContiune()
{
	cout << "\n\nPress any key to go back to Main Menue . . .";
	system("pause>0");
}
void PauseAndContiuneTransActionMenue()
{
	cout << "\n\nPress any key to go back to Transaction  Menue . . .";
	system("pause>0");
}
double CalculatTotalBalances(vector <stClientData> stData)
{
	double sum = 0;
	for (stClientData D : stData)
	{
		sum += D.AccountBalance;
	}
	return sum;
}
void PrintClientsData()
{
	vector <stClientData>stData = LoadDataFromFileToStruct(Client);

	cout << right << setw(50) << "Client List  (" << stData.size() << ") Client(s) " << setw(7);
	cout << "\n________________________________________________________________________________________________________________________" << endl;
	cout << "| Account Number  | Pin Code | Client Name                             | phone                      | balance" << endl;
	cout << "\n________________________________________________________________________________________________________________________" << endl << endl;

	for (stClientData& Client : stData)
	{
		cout << "| " << left << setw(15) << Client.AccountNumber;
		cout << "| " << left << setw(10) << Client.PinCode;
		cout << "| " << left << setw(40) << Client.Name;
		cout << "| " << left << setw(27) << Client.phone;
		cout << "| " << left << setw(15) << Client.AccountBalance;
		cout << endl;
	}
	cout << "\n______________________________________________________________________________________________________________" << endl;
	PauseAndContiune();
}
void PrintClientsDataWithTotalBalances()
{
	vector <stClientData>stData = LoadDataFromFileToStruct(Client);

	cout << right << setw(50) << "Client List  (" << stData.size() << ") Client(s) " << setw(7);
	cout << "\n________________________________________________________________________________________________________________________" << endl;
	cout << "| Account Number   | Client Name                             | balance" << endl;
	cout << "\n________________________________________________________________________________________________________________________" << endl << endl;

	for (stClientData& Client : stData)
	{
		cout << "| " << left << setw(15) << Client.AccountNumber;
		cout << "| " << left << setw(40) << Client.Name;
		cout << "| " << left << setw(15) << Client.AccountBalance;
		cout << endl;
	}
	cout << "\n______________________________________________________________________________________________________________" << endl;
	cout << "\n\t\t\t\t\t\tTotal Balance = " << CalculatTotalBalances(stData);
	PauseAndContiuneTransActionMenue();
}
void DeleteClientByAccountNumber()
{
	vector <stClientData> vClients = LoadDataFromFileToStruct(Client);
	string AccountNumber = ReadAccountNumber();
	char DeleteClient;
	stClientData stClient;
	if (IsFindClientByAccountNumber(AccountNumber, stClient, vClients))
	{
		cout << "The Folowing are the client details :" << endl;
		PrintClientData(stClient);
		cout << "\n\n\nAre you sure want delete this client y/n ? ";
		cin >> DeleteClient;

		if (toupper(DeleteClient) == ('Y'))
		{
			MarkClientForDeleteByAccountNumber(vClients, AccountNumber);
			SaveClientDataToFile(Client, vClients);
			vClients = LoadDataFromFileToStruct(Client);
			cout << "\n\nClient Deleted successfuly. " << endl;

		}

	}
	else
	{
		cout << "\n\nClient With Account Number (" << AccountNumber << ") Not found !" << endl;

	}
}
void FindClientData()
{
	vector <stClientData> vClients = LoadDataFromFileToStruct(Client);
	string AccountNumber = ReadAccountNumber();
	stClientData stClient;
	if (IsFindClientByAccountNumber(AccountNumber, stClient, vClients))
	{
		cout << "The Folowing are the client details :" << endl;
		PrintClientData(stClient);

	}
	else
	{
		cout << "\n\nClient With Account Number (" << AccountNumber << ") Not found !" << endl;

	}
}
void UpdateClientDataByAccountNumber()
{
	vector <stClientData> vClients = LoadDataFromFileToStruct(Client);
	string AccountNumber = ReadAccountNumber();
	char DeleteClient;
	stClientData stClient;
	if (IsFindClientByAccountNumber(AccountNumber, stClient, vClients))
	{
		cout << "The Folowing are the client details :" << endl;
		PrintClientData(stClient);
		cout << "\n\n\nAre you sure want update this client  y/n ? ";
		cin >> DeleteClient;

		if (toupper(DeleteClient) == ('Y'))
		{
			for (stClientData& C : vClients)
			{
				if (AccountNumber == C.AccountNumber)
				{
					C = ChangeClientData(AccountNumber, vClients);

				}
			}
			SaveUdatedClientDataToFile(Client, vClients);

			cout << "\n\nClient Updated successfuly. " << endl;

		}
	}
	else
	{
		cout << "\n\nClient With Account Number (" << AccountNumber << ") Not found !" << endl;
	}
}
void AddClient(vector <stClientData>& vClients)
{

	stClientData Data;
	string AccountNumber = ReadAccountNumber();


	Data = ReadClientData(AccountNumber, vClients);
	LoadDataFromRecordToFile(Client, Data);


}
void AddClients()
{
	char AddMoreClient = ' ';
	vector <stClientData> vClients = LoadDataFromFileToStruct(Client);

	do
	{

		AddClient(vClients);
		cout << "\nClient Added Successfuly, do you want add more client :";
		cout << endl;
		cout << "\n\nDo you want add more Clients Y/N? ";
		cin >> AddMoreClient;
	} while (toupper('y') == toupper(AddMoreClient));

}
double DepositAndReturnAmount(vector <stClientData> &vClients,string AccountNumber,double Amount)
{
	vector <stClientData> stData;
	string FileName = Client;
	fstream File;
	double sum;
	File.open(FileName, ios::in);

	if (File.is_open())
	{
		for (stClientData &C : vClients)
		{
			if (AccountNumber==C.AccountNumber)
			{
				C.AccountBalance += Amount;
				sum = C.AccountBalance;
			}
		}
		File.close();
	}
	return sum;
}
void DepositByAccountNumber()
{
	vector <stClientData> vClients = LoadDataFromFileToStruct(Client);
	string AccountNumber = ReadAccountNumber();
	stClientData ClientData;
	double Amount;
	char DepositOrNot = 'N';
	while (!IsFindClientByAccountNumber(AccountNumber,ClientData,vClients))
	{
		cout << "Client With [" << AccountNumber << "] does not exist. " << endl;
		AccountNumber = ReadAccountNumber();
	}


	cout << endl;
	PrintClientData(ClientData);
	cout << "\n\n\Please enter Deposit amount?  ";
	cin >> Amount;

	cout << "\n\n\nAre You sure you want perform this transaction y/n ? ";
	cin >> DepositOrNot;
	if (toupper(DepositOrNot) == 'Y')
	{
		Amount=DepositAndReturnAmount(vClients, AccountNumber, Amount);
		SaveClientDataToFile(Client, vClients);
		cout << "Done Successfuly , New Balance = " << Amount<<". ";

		
	}

}
double isWithdrawAmountValid(stClientData& ClientData, string AccountNumber)
{
	double Amount;

	cout << "\n\n\Please enter Withdrow amount?  ";
	cin >> Amount;

	if (ClientData.AccountNumber == AccountNumber)
	{
		while (ClientData.AccountBalance < Amount)
		{
			cout << "Amount Exceeds the Balance , you can withdraw up to  :" << ClientData.AccountBalance << endl;
			cout << "Please enter another amount ? ";
			cin >> Amount;
		}
	
	}
	return Amount * -1;
}
void WithdrawByAccountNumber()
{
	vector <stClientData> vClients = LoadDataFromFileToStruct(Client);
	string AccountNumber = ReadAccountNumber();
	stClientData ClientData;
	double Amount;
	char WithDrawOrNot = 'N';
	while (!IsFindClientByAccountNumber(AccountNumber, ClientData, vClients))
	{
		cout << "Client With [" << AccountNumber << "] does not exist. " << endl;
		AccountNumber = ReadAccountNumber();
	}


	cout << endl;
	PrintClientData(ClientData);
	Amount = isWithdrawAmountValid(ClientData, AccountNumber);
	cout << "\n\n\nAre You sure you want perform this transaction y/n ? ";
	cin >> WithDrawOrNot;
	if (toupper(WithDrawOrNot) == 'Y')
	{
		Amount = DepositAndReturnAmount(vClients, AccountNumber, Amount);
		SaveClientDataToFile(Client, vClients);
		cout << "\n\nDone Successfuly , New Balance = " << Amount << " . ";

	}

}
void AddClientsScreen()
{
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\t Add New Client Screen :-)           " << endl;
	cout << "---------------------------------------------------------------" << endl;
	AddClients();
	PauseAndContiune();

}
void DeleteClientsScreen()
{
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\t Delete Client Screen :-)           " << endl;
	cout << "---------------------------------------------------------------" << endl;
	DeleteClientByAccountNumber();
	PauseAndContiune();

}
void UpdateClientsScreen()
{
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\t Update Client Info Screen :-)           " << endl;
	cout << "---------------------------------------------------------------" << endl;
	UpdateClientDataByAccountNumber();
	PauseAndContiune();
}
void FindClientsScreen()
{
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\t Find Client Screen :-)           " << endl;
	cout << "---------------------------------------------------------------" << endl;
	FindClientData();
	PauseAndContiune();
}
void ExitScreen()
{
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\t Program End :-)           " << endl;
	cout << "---------------------------------------------------------------" << endl;
	cout << "\n\nPress any key to Finish . . .";
	system("pause>0");

}
void DepositScreen()
{
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\t\tDeposit Screen          " << endl;
	cout << "---------------------------------------------------------------" << endl;
	DepositByAccountNumber();
	PauseAndContiuneTransActionMenue();
}
void WithDrawScreen()
{
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\tWithDraw Screen          " << endl;
	cout << "---------------------------------------------------------------" << endl;
	WithdrawByAccountNumber();
	PauseAndContiuneTransActionMenue();
}
void GoBackToTransactionsMenue()
{
	PrintTransactionsMenue();
}
void GoBackToMainMenue()
{
	PrintMainMenue();
}
void TransactionsMenueScreen()
{
	enTransactionsMenue Menue;

	cout << "Choose What do you want to do?  [1 to 4]? ";
	Menue = ReadUserChoiseOfTransactionsMenue();

	switch (Menue)
	{

	case 1:enTransactionsMenue::Deposit;
		system("cls");
		DepositScreen();
		GoBackToTransactionsMenue();

		break;
	case 2:enTransactionsMenue::WithDraw;
		system("cls");
		WithDrawScreen();
		GoBackToTransactionsMenue();
		break;
	case 3:enTransactionsMenue::TotalBalances;
		system("cls");
		PrintClientsDataWithTotalBalances();
		GoBackToTransactionsMenue();
		break;
	case 4:enTransactionsMenue::MainMenue;
		system("cls");
		GoBackToMainMenue();
		break;

	}
}
void MainMenueScreen()
{
	enMainMenue Menue;

	cout << "Choose What do you want to do [1 to 7]? ";
	Menue = ReadUserChoiseOFMainMenue();

	switch (Menue)
	{

	case 1:enMainMenue::ShowClientDataList;
		system("cls");
		PrintClientsData();
		GoBackToMainMenue();

		break;
	case 2:enMainMenue::AddNewClient;
		system("cls");
		AddClientsScreen();
		GoBackToMainMenue();
		break;
	case 3:enMainMenue::DeleteClient;
		system("cls");
		DeleteClientsScreen();
		GoBackToMainMenue();

		break;
	case 4:enMainMenue::UpdateClientinfo;
		system("cls");
		UpdateClientsScreen();
		GoBackToMainMenue();
		break;
	case 5:enMainMenue::FindClient;
		system("cls");
		FindClientsScreen();
		GoBackToMainMenue();
	case 6:enMainMenue::TransActionMenue;
		system("cls");
		PrintTransactionsMenue();
	case 7: enMainMenue::Exit;
		system("cls");
		ExitScreen();
	}
}
void PrintMainMenue()
{
	system("cls");
	cout << "================================================" << endl;
	cout << "\t\t\         Main Menue Screen " << endl;
	cout << "================================================" << endl;
	cout << "\t\t[1] Show Client List. " << endl;
	cout << "\t\t[2] Add New Client.  " << endl;
	cout << "\t\t[3] Delete Client.  " << endl;
	cout << "\t\t[4] Update Client Info.  " << endl;
	cout << "\t\t[5] Find Client.  " << endl;
	cout << "\t\t[6] Transactions.  " << endl;
	cout << "\t\t[7] Exit.  " << endl;
	cout << "================================================" << endl;

	MainMenueScreen();
}
void PrintTransactionsMenue()
{
	system("cls");
	cout << "================================================" << endl;
	cout << "\t\t\        Transactions Menue Screen " << endl;
	cout << "================================================" << endl;
	cout << "\t\t[1] Deposit. " << endl;
	cout << "\t\t[2] Withdraw.  " << endl;
	cout << "\t\t[3] TotalBalances.  " << endl;
	cout << "\t\t[4] Main Menue.  " << endl;

	cout << "================================================" << endl;

	TransactionsMenueScreen();
}


int main()
{
	
	PrintMainMenue();
	system("pause>0");
}
