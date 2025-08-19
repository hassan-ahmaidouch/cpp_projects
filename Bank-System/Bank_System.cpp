#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

enum enMainMenueOptions{ eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
                         eUpdateClient = 4, eFindClient = 5, eTransactionsMenue = 6, eExit = 7 };

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowTotalBalance = 3, eShowMainMenue = 4 };


struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDlelete = false;
};

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease Account Number : ";
    cin >> AccountNumber;

    return AccountNumber;
}

vector <string> SplitString(string S1, string delim)
{
    vector <string> vString;
    short pos = 0;
    string sWord;

    while((pos = S1.find(delim)) != string::npos)
    {
        sWord = S1.substr(0,pos);
        
        if(sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + delim.length());
    }

    if(S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}

sClient ConvertLineToRecord(string S1, string separator = "#//#")
{
    sClient Client; 
    vector <string> vClientData = SplitString(S1, separator);
    
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to 
    
    return Client;
}

vector <sClient> LoadClientsDataFromFile(string FileName)
{
    fstream MyFile;
    vector <sClient> vClients;
    sClient Client;
    string Line;
    
    MyFile.open(FileName, ios::in);

    if(MyFile.is_open())
    {
        while(getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }

        MyFile.close();
       
    }

    return  vClients;
}

void PrintClientRecord(sClient Client) {
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector<sClient> vClients) {
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    for (sClient Client : vClients) {
        PrintClientRecord(Client);
        cout << endl;
    }

    cout << "_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

short ReadMainMenueOption()
{
    cout <<"Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;
    cin.ignore();
    return Choice;
}

void  ShowAllClientsScreen()
{
   vector <sClient> vClients = LoadClientsDataFromFile("clients.txt");
   PrintAllClientsData(vClients);
}

void GoBackToMainMenue();

sClient ReadNewClient() {
    sClient Client;

    cout << "Enter Account Number? ";
    getline(cin, Client.AccountNumber);

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

string ConvertRecordToLine(sClient Client, string Separator = "#//#")
{

    string stClientRecord = "";
    
    stClientRecord += Client.AccountNumber + Separator;
    stClientRecord += Client.PinCode + Separator;
    stClientRecord += Client.Name + Separator;
    stClientRecord += Client.Phone + Separator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}

void AddDataLineToFile(string FileName, string DataLine)
{
    fstream MyFile;
    
    MyFile.open(FileName, ios::out | ios::app);

    if(MyFile.is_open())
    {
        MyFile << DataLine <<endl;

        MyFile.close();
    }
}

void AddNewClient()
{
    sClient Client = ReadNewClient();
 
    AddDataLineToFile("clients.txt", ConvertRecordToLine(Client));
}

void AddClients()
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        cout << " Adding New client : \n\n";

        AddNewClient();

        cout << " \nClient Added Successfully, do you want to add more clients? Y/N?";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
    
}

void ShowAddNewClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddClients();
}

bool FindClientByAccountNumber(string AccountNumber,vector <sClient> vClients, sClient &Client)
{
   
    for(sClient &C : vClients)
    {
        if(C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }

    return false;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";

    cout << "\nAccount Number : " << Client.AccountNumber;
    cout << "\nPin Code       : " << Client.PinCode;
    cout << "\nName           : " << Client.Name;
    cout << "\nPhone          : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance << "\n";
}

void MarkForDeleteClientByAccountNumber(string AccountNumber, vector <sClient> &vClients)
{
    for(sClient &C : vClients)
    {
        if(C.AccountNumber == AccountNumber)
        {
            C.MarkForDlelete = true;
        }
    }
}

void SaveClientsDataToFile(string FileName, vector <sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out);

    string CLine;

    if(MyFile.is_open())
    {
        for(sClient &C : vClients)
        {
            if(C.MarkForDlelete == false)
            {
                CLine = ConvertRecordToLine(C);

                MyFile << CLine << endl;
            }
        }


        MyFile.close();
    }
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';

    if(FindClientByAccountNumber(AccountNumber,vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;

        if(Answer == 'y' || Answer == 'Y')
        {
            MarkForDeleteClientByAccountNumber(AccountNumber, vClients);

            SaveClientsDataToFile("clients.txt", vClients);

            // Refresh Clients
            vClients = LoadClientsDataFromFile("clients.txt");
            cout << "\n\nClient Deleted Successfully.";

           return true; 
        }
        else
        {
            cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!";
            return false;
        }
   

    }
    
    return false;
}

void ShowDeleteClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    vector<sClient> vClients = LoadClientsDataFromFile("clients.txt");

    DeleteClientByAccountNumber(AccountNumber, vClients);

}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
 
    Client.AccountNumber = AccountNumber;

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter Account Balance? ";
    cin >> Client.AccountBalance;

    return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';

    if(FindClientByAccountNumber(AccountNumber,vClients, Client))
    {
        PrintClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        cin.ignore();

        if(Answer == 'y' || Answer == 'Y')
        {
           for (sClient & C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            SaveClientsDataToFile("clients.txt", vClients);

            cout << "\n\nClient Updated Successfully."; 
           return true; 
        }
        else
        {
            cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!";
            return false;
        }
   

    }
    
    return false;
}

void ShowUpdateClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;
    string AccountNumber = ReadClientAccountNumber();
    vector<sClient> vClients = LoadClientsDataFromFile("clients.txt");

    UpdateClientByAccountNumber(AccountNumber, vClients);

}

bool FindClientByAccountNumber(string AccountNumber, sClient &Client)
{
    vector <sClient> vClients = LoadClientsDataFromFile("clients.txt");

    for(sClient &C : vClients)
    {
        if(C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }

    return false;
}

void ShowFindClientScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;
    
    string AccountNumber = ReadClientAccountNumber();

    if(FindClientByAccountNumber(AccountNumber, Client))
    {
        PrintClientCard(Client);
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
    
    
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

short ReadTransactionsMenueOption()
{
    cout << "Choose what do you want to do? [1 to 4]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void GoBackToTransactionsMenue();

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount,vector <sClient> vClients)
{
    char Answer = 'n';

    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {

        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientsDataToFile("clients.txt", vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;

                return true;
            }

        }

    }
    
    return false;
}   

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients = LoadClientsDataFromFile("clients.txt");
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    double Amount = 0;
    
    cout << " enter The Amount : ";
    cin >> Amount;

    PrintClientCard(Client);
    
    DepositBalanceToClientByAccountNumber(AccountNumber, Amount, vClients);

}

void ShowWithDrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithDraw Screen";
    cout << "\n-----------------------------------\n";


    sClient Client;

    vector <sClient> vClients = LoadClientsDataFromFile("clients.txt");
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, Client))
    {
        cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;
    
    cout << " enter The Amount : ";
    cin >> Amount;

    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Amount;
    }

    
    
    DepositBalanceToClientByAccountNumber(AccountNumber, -1 * Amount , vClients);

}

void PrintClientRecordBalanceLine(sClient Client)
{

    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.AccountBalance;

}

void ShowTotalBalances()
{

    vector <sClient> vClients = LoadClientsDataFromFile("clients.txt");

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            PrintClientRecordBalanceLine(Client);
            TotalBalances += Client.AccountBalance;

            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t   Total Balances = " << TotalBalances;

}

void ShowTotalBalancesScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tTotal Balances Screen";
    cout << "\n-----------------------------------\n";

    ShowTotalBalances();


}

void PerfromTranactionsMenueOption(enTransactionsMenueOptions TransactionMenueOption)
{
    switch (TransactionMenueOption)
    {
    case enTransactionsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransactionsMenue();
        break;
    }

    case enTransactionsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithDrawScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowTotalBalance:
    {
        system("cls");
        ShowTotalBalancesScreen();
        GoBackToTransactionsMenue();
        break;
    }


    case enTransactionsMenueOptions::eShowMainMenue:
    {

        GoBackToMainMenue();

    }
    }

}

void ShowTransactionsMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";
    PerfromTranactionsMenueOption((enTransactionsMenueOptions)ReadTransactionsMenueOption());
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
        case eListClients:
        {
            system("cls");
            ShowAllClientsScreen();
            GoBackToMainMenue();
            break;
        }

        case eAddNewClient:
        {
            system("cls");
            ShowAddNewClientScreen();
            GoBackToMainMenue();
            break;
        }

        case eDeleteClient:
        {
            system("cls");
            ShowDeleteClientScreen();
            GoBackToMainMenue();
            break;
        }

        case eUpdateClient:
        {
            system("cls");
            ShowUpdateClientScreen();
            GoBackToMainMenue();
            break;
        }

        case eFindClient:
        {
            system("cls");
            ShowFindClientScreen();
            GoBackToMainMenue();
            break;
        }

        case eTransactionsMenue:
        {
            system("cls");
            ShowTransactionsMenue();
        }

        case eExit:
        {
            system("cls");
            ShowEndScreen();
            break;
        }
        
    }
}

void ShowMainMenue()
{
    system("cls");
    cout <<"===========================================\n";
    cout <<"\t\tMain Menue Screen\n";
    cout <<"===========================================\n";
    cout <<"\t[1] Show Client List.\n";
    cout <<"\t[2] Add New Client.\n";
    cout <<"\t[3] Delete Client.\n";
    cout <<"\t[4] Update Client Info.\n";
    cout <<"\t[5] Find Client.\n";
    cout <<"\t[6] Transactions.\n";
    cout <<"\t[7] Exit.\n";
    cout <<"===========================================\n";

    PerfromMainMenueOption(enMainMenueOptions(ReadMainMenueOption()));

}

int main()
{
    
    ShowMainMenue();

}

void GoBackToMainMenue()
{
    cout <<"\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}


void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    ShowTransactionsMenue();
}