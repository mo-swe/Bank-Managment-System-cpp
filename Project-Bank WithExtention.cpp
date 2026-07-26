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

struct stUserData;
void PrintMainMenu();
void ManageUsersMenuScreen();
 void PrintTransactionsMenu();
 void PrintManageUsersMenu();
 int ReadPermissions();
 vector <stUserData> LoadUserDataFromFileToStruct(string FileName);
 void LoginScreen();
const string Client = "Client.txt";
const string Users = "Users.txt";
enum enMainMenu {
	ShowClientDataList = 1, AddNewClient = 2, DeleteClient = 3
	, UpdateClientinfo = 4, FindClient = 5,TransActionMenu=6,ManageUsers=7 ,Logout = 8
};
enum enTransactionsMenu {Deposit= 1,WithDraw=2
	,TotalBalances=3,MainMenu=4};
enum enManageUsersMenu 
{ ListUser = 1, AddNewUser = 2, DeleteUser = 3, UpdateUser = 4,FindUser=5 ,BackToMainMenu = 6 };
enum enPermissions {FullAccess = -1,NoPermissions=0, PrShowClientDataList =1, PrAddNewClient =2, PrDeleteClient =4, PrUpdateClientinfo =8,
	PrFindClient =16, PrTransActionMenu =32,PrManageUsers=64};
enMainMenu ReadUserChoiseOFMainMenu()
{
	int Choice = 0;


	cin >> Choice;
	while (cin.fail() || Choice <= 0 || Choice>8)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << " is invalid Number , Enter a valid one :" << endl;

		cin >> Choice;
	}
	return (enMainMenu)Choice;
}
enTransactionsMenu ReadUserChoiseOfTransactionsMenu()
{
	int Choice = 0;
	cin >> Choice;
	while (cin.fail() || Choice <= 0 || Choice >4)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << " is invalid Number , Enter a valid one :" << endl;

		cin >> Choice;
	}
	return (enTransactionsMenu)Choice;
}
enManageUsersMenu ReadUserChoiseOfManageUsersMenu()
{
	int Choice = 0;
	cin >> Choice;
	while (cin.fail() || Choice <= 0 || Choice > 6)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << " is invalid Number , Enter a valid one :" << endl;

		cin >> Choice;
	}
	return (enManageUsersMenu)Choice;
}
vector <string> SplitString(string s1, string delim)
{

	int postion = 0;
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
char ReadCharYesOrNo()
{
	char GiveAccessOrTNot = ' ';
	cin >> GiveAccessOrTNot;
	cin.ignore(10000, '\n');
	GiveAccessOrTNot = tolower(GiveAccessOrTNot);
	while (GiveAccessOrTNot != 'y' && GiveAccessOrTNot != 'n')
	{
		cout << "Invalid Characater , Enter a Vaild one :";
		cin >> GiveAccessOrTNot;
		cin.ignore(10000, '\n');
		GiveAccessOrTNot = tolower(GiveAccessOrTNot);
		} 
		return GiveAccessOrTNot;
}
double ReadPositiveNumber()
{
	double Number = 0;

		cin >> Number;
	while (cin.fail()|| Number <= 0)
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << " is invalid Number , Enter a valid one :" << endl;

		cin >> Number;
	}

	return Number;
}
string ReadStringWithMessege(string Massege =" ")
{
	cout << Massege ;
	string Letter = " ";
	getline(cin >> ws, Letter);
	return Letter;
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
struct stUserData
{
	string UserName;
	string Password;
	int UserPermission=enPermissions::NoPermissions;
	bool MarkForDelete = false;
};
stUserData CurrentUser;
bool IsFindClientByAccountNumber(string AccountNumber, vector <stClientData> vClients)
{

	bool IsExeitAccountNumber = false;


	for (stClientData ClientData : vClients)
	{

		if (ClientData.AccountNumber == AccountNumber)
		{

			return   true;


		}

	}

	return false;
}
bool IsValidUserNameAndPassword(string UserName,string Passord,vector <stUserData> vUsers, stUserData& User)
{
	bool IsExeitAccountNumber = false;
	for (stUserData UserData : vUsers)
	{
		if (UserData.UserName == UserName && UserData.Password == Passord)
		{
			User = UserData;
			return true;
		}
	}
	return false;
}
bool IsUserExistsByUserName(string UserName,stUserData &User)
{
	vector <stUserData> vUsers = LoadUserDataFromFileToStruct(Users);
	bool IsExeitAccountNumber = false;
	for (stUserData UserData : vUsers)
	{
		if (UserData.UserName == UserName )
		{
			User = UserData;
			return true;
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
stClientData ChangeClientData(string AccountNumber)
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
stUserData ChangeUserData(string UserName)
{
	stUserData User;

	User.UserName = UserName;
	cout << "\nEnter Passord :";
	getline(cin >> ws, User.Password);
	cout << endl;
	User.UserPermission = ReadPermissions();
	return User;
}
string ConvertRecordToLine(stClientData Data, string Separator)
{

	string s = "";
	s += Data.AccountNumber + Separator;
	s += Data.Name + Separator;
	s += Data.PinCode + Separator;
	s += Data.phone + Separator;
	s += to_string(Data.AccountBalance) + Separator;

	return s;

}
string ConvertRecordToLine(stUserData User, string Separator)
{

	string s = "";
	s +=User.UserName + Separator;
	s += User.Password+ Separator;
	s += to_string(User.UserPermission);
	
	return s;

}
stClientData ConvertClientDataLineToRecord(string LineOfData, string Delim)
{
	stClientData stData;
	vector <string> ClientData;

	ClientData = SplitString(LineOfData, Delim);

	stData.AccountNumber = ClientData[0];
	stData.Name = ClientData[1];
	stData.PinCode = ClientData[2];
	stData.phone = ClientData[3];
	stData.AccountBalance = stod(ClientData[4]);

	return stData;
}
stUserData ConvertUserDataLineToRecord(string LineOfData, string Delim)
{
	stUserData stData;
	vector <string> UserData;

	UserData = SplitString(LineOfData, Delim);
	stData.UserName = UserData[0];
	stData.Password = UserData[1];
	stData.UserPermission = stoi(UserData[2]);

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
void PrintUserData(stUserData Data)
{

	cout << "\nThe Following are the User Details \n";
	cout << "___________________________________\n";
	cout  << setw(13) <<left<< "\nUser Name " << ":" << Data.UserName;
	cout  << setw(13) << left << "\nPassord " << ":" <<Data.Password;
	cout  << setw(13) << left << "\nPermissions " << ":" << Data.UserPermission;
	
	cout << "\n___________________________________\n";

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
void LoadDataFromRecordToFileUserData(string FileName, stUserData Data)
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
vector <stClientData> LoadClientDataFromFileToStruct(string FileName)
{
	vector <stClientData> stData;
	fstream File;
	File.open(FileName, ios::in);

	if (File.is_open())
	{
		string m;
		while (getline(File, m))
		{
			stData.push_back(ConvertClientDataLineToRecord(m, "#//#"));
		}
		File.close();
	}

	return stData;
}
vector <stUserData> LoadUserDataFromFileToStruct(string FileName)
{
	vector <string> vData;
	vector <stUserData> stData;
	fstream File;
	File.open(FileName, ios::in);

	if (File.is_open())
	{
		string m;
		while (getline(File, m))
		{
			vData.push_back(m);
			stData.push_back(ConvertUserDataLineToRecord(m, "#//#"));
		}
		File.close();
	}

	return stData;
}
bool IsFindClientByAccountNumber(string AccountNumber, stClientData& stData,const vector <stClientData> &vClients)
{

	bool IsExeitAccountNumber = false;


	for (stClientData ClientData : vClients)
	{

		if (ClientData.AccountNumber == AccountNumber)
		{
			stData = ClientData;
			return   true;


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
bool MarkUserForDeleteByUserName(vector <stUserData>& vUsers, string UserName)
{
	for (stUserData& User : vUsers)
	{
		if (UserName == User.UserName)
		{
			User.MarkForDelete = 1;
			return 1;
		}
	}
	return 0;
}
bool CheckAccessPermission(enPermissions Permission)
{
	if (CurrentUser.UserPermission == enPermissions::FullAccess)
		return true;
	if ((Permission & CurrentUser.UserPermission) == Permission)
		return true;
	else
		return false;
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
bool SaveUserDataToFile(string FileName, vector <stUserData>& vUsers)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string DataLine = "";
	if (MyFile.is_open())
	{
		for (stUserData C : vUsers)
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
void ShowAccessDeniedMessage()
{
	cout << "\n------------------------------------\n";
	cout << "Access Denied";
		cout<<"\nYou dont Have Permission To Do this",
		cout<<"\nPlease Conact Your Admin.";
		cout << "\n------------------------------------\n";
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
void PauseAndContiuneTransActionMenu()
{
	cout << "\n\nPress any key to go back to Transaction  Menue . . .";
	system("pause>0");
}
void PauseAndContiuneManageUsersMenu()
{
	cout << "\n\nPress any key to go back to Manage Users  Menue . . .";
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

	if (!CheckAccessPermission(enPermissions::PrShowClientDataList))
	{
		ShowAccessDeniedMessage();
		PauseAndContiune();
		return;
	}
	
		vector <stClientData> stData = LoadClientDataFromFileToStruct(Client);

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
		cout << "\n________________________________________________________________________________________________________________________" << endl;
	
	PauseAndContiune();
}
void PrintClientsDataWithTotalBalances()
{
	vector <stClientData>stData = LoadClientDataFromFileToStruct(Client);

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
	PauseAndContiuneTransActionMenu();
}
void DeleteClientByAccountNumber()
{
	vector <stClientData> vClients = LoadClientDataFromFileToStruct(Client);
	string AccountNumber = ReadAccountNumber();
	char DeleteClient;
	stClientData stClient;
	if (IsFindClientByAccountNumber(AccountNumber, stClient, vClients))
	{
		cout << "The Folowing are the client details :" << endl;
		PrintClientData(stClient);
		cout << "\n\n\nAre you sure want delete this client y/n ? ";
		DeleteClient = ReadCharYesOrNo();

		if (DeleteClient == ('y'))
		{
			MarkClientForDeleteByAccountNumber(vClients, AccountNumber);
			SaveClientDataToFile(Client, vClients);
			vClients = LoadClientDataFromFileToStruct(Client);
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
	vector <stClientData> vClients = LoadClientDataFromFileToStruct(Client);
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
	vector <stClientData> vClients = LoadClientDataFromFileToStruct(Client);
	string AccountNumber = ReadAccountNumber();
	char UpdateClient;
	stClientData stClient;
	if (IsFindClientByAccountNumber(AccountNumber, stClient, vClients))
	{
		cout << "The Folowing are the client details :" << endl;
		PrintClientData(stClient);
		cout << "\n\n\nAre you sure want update this client  y/n ? ";
		UpdateClient = ReadCharYesOrNo();

		if (UpdateClient == ('y'))
		{
			for (stClientData& C : vClients)
			{
				if (AccountNumber == C.AccountNumber)
				{
					C = ChangeClientData(AccountNumber);

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
	vector <stClientData> vClients = LoadClientDataFromFileToStruct(Client);

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

	
		for (stClientData &C : vClients)
		{
			if (AccountNumber==C.AccountNumber)
			{
				C.AccountBalance += Amount;
				sum = C.AccountBalance;
			}
		}
	return sum;
}
void DepositByAccountNumber()
{
	vector <stClientData> vClients = LoadClientDataFromFileToStruct(Client);
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
	cout << "\n\nPlease enter Deposit amount?  ";
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

	cout << "\n\nPlease enter Withdrow amount?  ";
	cin >> Amount;

	if (ClientData.AccountNumber == AccountNumber)
	{
		while (ClientData.AccountBalance < Amount&&Amount<=0)
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
	vector <stClientData> vClients = LoadClientDataFromFileToStruct(Client);
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
	 WithDrawOrNot = ReadCharYesOrNo();
	if (toupper(WithDrawOrNot) == 'Y')
	{
		Amount = DepositAndReturnAmount(vClients, AccountNumber, Amount);
		SaveClientDataToFile(Client, vClients);
		cout << "\n\nDone Successfuly , New Balance = " << Amount << " . ";

	}

}
void FindUserByUserNameAndPassword(stUserData& UserData)
{

   vector <stUserData> vUsers = LoadUserDataFromFileToStruct(Users);
   string UserName = ReadStringWithMessege("Please Enter UserName? ");
   string Passord = ReadStringWithMessege("Please Enter Passord? ");
   

   while (!IsValidUserNameAndPassword(UserName,Passord,vUsers, UserData))
   {
	   cout << "Invalid Username/Passord !\n";
	    UserName = ReadStringWithMessege("Please Enter UserName? ");
	    Passord = ReadStringWithMessege("Please Enter Passord? ");
   }
  
}
void AddClientsScreen()
{
	if (!CheckAccessPermission(enPermissions::PrAddNewClient))
	{
		ShowAccessDeniedMessage();
		PauseAndContiune();
		return;
	}
		cout << "\n---------------------------------------------------------------" << endl;
		cout << "\t Add New Client Screen :-)           " << endl;
		cout << "---------------------------------------------------------------" << endl;
		AddClients();
		


	PauseAndContiune();

}
void DeleteClientsScreen()
{
	if (!CheckAccessPermission(enPermissions::PrDeleteClient))
	{
		ShowAccessDeniedMessage();
		PauseAndContiune();
		return;
	}
		cout << "\n---------------------------------------------------------------" << endl;
		cout << "\t Delete Client Screen :-)           " << endl;
		cout << "---------------------------------------------------------------" << endl;
		DeleteClientByAccountNumber();
	
	PauseAndContiune();

}
void UpdateClientsScreen()
{
	if (!CheckAccessPermission(enPermissions::PrUpdateClientinfo))
	{
		ShowAccessDeniedMessage();
		PauseAndContiune();
		return;
	}
		cout << "\n---------------------------------------------------------------" << endl;
		cout << "\t Update Client Info Screen :-)           " << endl;
		cout << "---------------------------------------------------------------" << endl;
		UpdateClientDataByAccountNumber();
	
	PauseAndContiune();
}
void FindClientsScreen()
{
	if (!CheckAccessPermission(enPermissions::PrFindClient))
	{
		ShowAccessDeniedMessage();
		PauseAndContiune();
		return;
	}
		cout << "\n---------------------------------------------------------------" << endl;
		cout << "\t Find Client Screen :-)           " << endl;
		cout << "---------------------------------------------------------------" << endl;
		FindClientData();
	
	PauseAndContiune();
}
void LogoutScreen()
{
	LoginScreen();
}
void DepositScreen()
{
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\t\tDeposit Screen          " << endl;
	cout << "---------------------------------------------------------------" << endl;
	DepositByAccountNumber();
	PauseAndContiuneTransActionMenu();
}
void WithDrawScreen()
{
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\tWithDraw Screen          " << endl;
	cout << "---------------------------------------------------------------" << endl;
	WithdrawByAccountNumber();
	PauseAndContiuneTransActionMenu();
}
void TransactionsMenuScreen()
{

	if (!CheckAccessPermission(enPermissions::PrTransActionMenu))
	{
		ShowAccessDeniedMessage();
		PauseAndContiune();
		return;
	}
	enTransactionsMenu Menu;

	do
	{
		system("cls");
		PrintTransactionsMenu();
	cout << "Choose What do you want to do?  [1 to 4]? ";
	Menu = ReadUserChoiseOfTransactionsMenu();

	switch (Menu)
	{

	case 1:enTransactionsMenu::Deposit;
		system("cls");
		DepositScreen();
		break;
	case 2:enTransactionsMenu::WithDraw;
		system("cls");
		WithDrawScreen();
		break;
	case 3:enTransactionsMenu::TotalBalances;
		system("cls");
		PrintClientsDataWithTotalBalances();
		break;
	case 4:enTransactionsMenu::MainMenu;
		system("cls");
		break;
	}
	} while (Menu != enTransactionsMenu::MainMenu);
}
void MainMenuScreen()
{

	enMainMenu Menu;
	
	do
	{ 
		system("cls");
		PrintMainMenu();
	cout << "Choose What do you want to do [1 to 8]? ";
	Menu = ReadUserChoiseOFMainMenu();

	switch (Menu)
	{

	case 1:enMainMenu::ShowClientDataList;
		system("cls");
		PrintClientsData();
		break;
	case 2:enMainMenu::AddNewClient;
		system("cls");
		AddClientsScreen();
		break;
	case 3:enMainMenu::DeleteClient;
		system("cls");
		DeleteClientsScreen();
		break;
	case 4:enMainMenu::UpdateClientinfo;
		system("cls");
		UpdateClientsScreen();
		break;
	case 5:enMainMenu::FindClient;
		system("cls");
		FindClientsScreen();
		break;
	case 6:enMainMenu::TransActionMenu;
		system("cls");
		TransactionsMenuScreen();
		break;
	case 7:enMainMenu::ManageUsers;
		system("cls");
		ManageUsersMenuScreen();
		break;
	case 8: enMainMenu::Logout;
		system("cls");
		break;
	}
	} while (Menu != enMainMenu::Logout);
}
void PrintUsersInfo()
{
	vector <stUserData>stData = LoadUserDataFromFileToStruct(Users);

	cout << right << setw(50) << "Users List  (" << stData.size() << ") Client(s) " << setw(7);
	cout << "\n________________________________________________________________________________________________________________________" << endl;
	cout << "| User Name      | Passord       | Permissions" << endl;
	cout << "\n________________________________________________________________________________________________________________________" << endl << endl;

	for (stUserData& User : stData)
	{
		cout << "| " << left << setw(15) << User.UserName;
		cout << "| " << left << setw(14) << User.Password;
		cout << "| " << left << setw(1) << User.UserPermission;
		cout << endl;
	}
	cout << "\n________________________________________________________________________________________________________________________" << endl;
	PauseAndContiuneManageUsersMenu();
}
int ReadPermissions()
{
	
	char FullAccessOrNot = ' ';
	
	int Permissions = 0;
	cout << "Do You give full access y/n :";
	FullAccessOrNot = ReadCharYesOrNo();
	if ( FullAccessOrNot == 'y')
	{
		return -1;
	}
	cout << "\nDo you want to give access to:\n";

	cout << "\nShow Client List y/n: ";
	if (ReadCharYesOrNo() == 'y')
		Permissions |= enPermissions::PrShowClientDataList;

	cout << "\nAdd New Client y/n: ";
	if (ReadCharYesOrNo() == 'y')
		Permissions |= enPermissions::PrAddNewClient;

	cout << "\nDelete Client y/n: ";
	if (ReadCharYesOrNo() == 'y')
		Permissions |= enPermissions::PrDeleteClient;

	cout << "\nUpdate Client y/n: ";
	if (ReadCharYesOrNo() == 'y')
		Permissions |= enPermissions::PrUpdateClientinfo;

	cout << "\nFind Client y/n: ";
	if (ReadCharYesOrNo() == 'y')
		Permissions |= enPermissions::PrFindClient;

	cout << "\nTransactions y/n: ";
	if (ReadCharYesOrNo() == 'y')
		Permissions |= enPermissions::PrTransActionMenu;

	cout << "\nManage Users y/n: ";
	if (ReadCharYesOrNo() == 'y')
		Permissions |= enPermissions::PrManageUsers;

	return Permissions;

}
stUserData ReadNewUser()
{
	stUserData User;
	cout << "Enter UserName :";
	getline(cin >>ws, User.UserName);
	while (IsUserExistsByUserName(User.UserName,User))
	{
		cout << "User With [" << User.UserName << "] Aleardy Exists , Enter Another Username :";
		getline(cin >> ws, User.UserName);
	}
	cout << "\nEnter Passord :";
	getline(cin >> ws, User.Password);
	cout << endl;
	User.UserPermission = ReadPermissions();
	LoadDataFromRecordToFileUserData(Users, User);

	return User;
}
void AddUsers()
{
	char AddMoreUsers = ' ';
	vector <stUserData> vUsers = LoadUserDataFromFileToStruct(Users);

	do
	{

		ReadNewUser();
		cout << "\nUser Added Successfuly, do you want add more client :";
		cout << endl;
		cout << "\n\nDo you want add more Clients Y/N? ";
		AddMoreUsers = ReadCharYesOrNo();
	} while (toupper('y') == toupper(AddMoreUsers));
}
void DeleteUserByUserName()
{

	char DeleteUser;
	bool IsUserToDeleteAdmin = false;
	vector <stUserData> vUsers = LoadUserDataFromFileToStruct(Users);
	stUserData User;

	cout << "Enter UserName :";
	getline(cin >> ws, User.UserName);


	if (User.UserName == "Admin")
	{
		cout << "\nYou cannot Delete this User.\n";
		IsUserToDeleteAdmin = true;
	}

	if (IsUserExistsByUserName(User.UserName,User)&& !IsUserToDeleteAdmin)
	{
		
		PrintUserData(User);
		cout << "\n\n\nAre you sure want delete this User y/n ? ";
		DeleteUser = ReadCharYesOrNo();
		if (DeleteUser == 'y')
		{
			MarkUserForDeleteByUserName(vUsers, User.UserName);
			SaveUserDataToFile(Users, vUsers);
			vUsers = LoadUserDataFromFileToStruct(Users);
			cout << "\n\nUser Deleted successfuly. " << endl;
		}
	}
	else if(!IsUserToDeleteAdmin)
	{
		cout << "\n\nUser With User Name (" << User.UserName << ") Not found !" << endl;
	}
}
void FindUserByUserName()
{
	stUserData User;
	cout << "Enter UserName :";
	getline(cin >> ws, User.UserName);

	if (IsUserExistsByUserName(User.UserName, User))
	{

		PrintUserData(User);

	}
	else 
	{
		cout << "\n\nUser With User Name (" << User.UserName << ") Not found !" << endl;
	}
}
void UpdateUserByUserName()
{
	char UpdateUser = ' ';
	bool IsUserToUpdateAdmin = false;
	vector <stUserData> vUsers = LoadUserDataFromFileToStruct(Users);
	stUserData User;

	cout << "Enter UserName :";
	getline(cin >> ws, User.UserName);


	if (User.UserName == "Admin")
	{
		cout << "\nYou cannot Update this User.\n";
		IsUserToUpdateAdmin = true;
	}

	if (IsUserExistsByUserName(User.UserName, User) && !IsUserToUpdateAdmin)
	{

		PrintUserData(User);
		cout << "\n\n\nAre you sure want Update this User y/n ? ";
		UpdateUser = ReadCharYesOrNo();
		if (UpdateUser == 'y')
		{

			for (stUserData& U : vUsers)
			{
				if (User.UserName == U.UserName)
				{
					U = ChangeUserData(User.UserName);

				}
			}
				SaveUserDataToFile(Users, vUsers);
				cout << "\n\nUser Updated successfuly. " << endl;
			
		}
	}
	else if (!IsUserToUpdateAdmin)
	{
		cout << "\n\nUser With User Name (" << User.UserName << ") Not found !" << endl;
	}
}
void FindUserScreen()
{
	cout << "\n---------------------------------------" << endl;
	cout << "\t Find User Screen           " << endl;
	cout << "---------------------------------------" << endl;
	FindUserByUserName();
	PauseAndContiuneManageUsersMenu();
}
void AddUsersScreen()
{
	cout << "\n---------------------------------------------------------------" << endl;
	cout << "\t Add New Users Screen :-)           " << endl;
	cout << "---------------------------------------------------------------" << endl;
	AddUsers();
	PauseAndContiuneManageUsersMenu();

}
void DeleteUserScreen()
{
	cout << "\n---------------------------------------" << endl;
	cout << "\t Delete User Screen           " << endl;
	cout << "---------------------------------------" << endl;
	DeleteUserByUserName();
	PauseAndContiuneManageUsersMenu();
}
void UpdateUserScreen()
{
	cout << "\n---------------------------------------" << endl;
	cout << "\t Update User Screen           " << endl;
	cout << "---------------------------------------" << endl;
	UpdateUserByUserName();
	PauseAndContiuneManageUsersMenu();
}
void ManageUsersMenuScreen()
{
	if (!CheckAccessPermission(enPermissions::PrManageUsers))
	{
		ShowAccessDeniedMessage();
		PauseAndContiune();
		return;
	}
	enManageUsersMenu Menu;
	
	do
	{
		system("cls");
		PrintManageUsersMenu();

	cout << "Choose What do you want to do?  [1 to 6]? ";
	Menu = ReadUserChoiseOfManageUsersMenu();

	switch (Menu)
	{

	case 1:enManageUsersMenu::ListUser;
		system("cls");
		PrintUsersInfo();
		break;
	case 2:enManageUsersMenu::AddNewUser;
		system("cls");
		AddUsersScreen();
		break;
	case 3:enManageUsersMenu::DeleteUser;
		system("cls");
		DeleteUserScreen();
		break;
	case 4:enManageUsersMenu::UpdateUser;
		system("cls");
		UpdateUserScreen();
		break;
	case 5:enManageUsersMenu::FindUser;
		system("cls");
		FindUserScreen();
		break;
	case 6:enManageUsersMenu::BackToMainMenu;
		system("cls");
		break;
	}
	} while (Menu != enManageUsersMenu::BackToMainMenu);
}
void PrintMainMenu()
{
	system("cls");
	cout << "================================================" << endl;
	cout << "\t\t         Main Menue Screen " << endl;
	cout << "================================================" << endl;
	cout << "\t\t[1] Show Client List. " << endl;
	cout << "\t\t[2] Add New Client.  " << endl;
	cout << "\t\t[3] Delete Client.  " << endl;
	cout << "\t\t[4] Update Client Info.  " << endl;
	cout << "\t\t[5] Find Client.  " << endl;
	cout << "\t\t[6] Transaction.  " << endl;
	cout << "\t\t[7] Manage Users.  " << endl;
	cout << "\t\t[8] Logout.  " << endl;
	cout << "================================================" << endl;
	
}
void PrintManageUsersMenu()
{

		system("cls");
		cout << "================================================" << endl;
		cout << "\t\t     Manage Users Menue Screen " << endl;
		cout << "================================================" << endl;
		cout << "\t\t[1] List Users. " << endl;
		cout << "\t\t[2] Add New User.  " << endl;
		cout << "\t\t[3] Delete User.  " << endl;
		cout << "\t\t[4] Update User.  " << endl;
		cout << "\t\t[5] Find User.  " << endl;
		cout << "\t\t[6] MainMenue.  " << endl;

		cout << "================================================" << endl;

		
	
}
void PrintTransactionsMenu()
{
	
		system("cls");
		cout << "================================================" << endl;
		cout << "\t\t     Transactions Menue Screen " << endl;
		cout << "================================================" << endl;
		cout << "\t\t[1] Deposit. " << endl;
		cout << "\t\t[2] Withdraw.  " << endl;
		cout << "\t\t[3] TotalBalances.  " << endl;
		cout << "\t\t[4] Main Menue.  " << endl;

		cout << "================================================" << endl;

		
}
void LoginScreen()
{

	while (true)
	{
		system("cls");
	
	cout << "\n-------------------------------------------" << endl;
	cout << "\t Login Screen             " << endl;
	cout << "-------------------------------------------" << endl;
	FindUserByUserNameAndPassword(CurrentUser);
	MainMenuScreen();
	}
	
}
int main()
{

	LoginScreen();

}
