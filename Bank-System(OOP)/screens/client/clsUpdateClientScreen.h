#pragma once
#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"


class clsUpdateClientScreen : protected clsScreen
{
private :

    static void _ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.setFirstName(clsInputValidate::ReadString());
    
        cout << "\nEnter LastName: ";
        Client.setLastName(clsInputValidate::ReadString());
    
        cout << "\nEnter Email: ";
        Client.setEmail(clsInputValidate::ReadString());
    
        cout << "\nEnter Phone: ";
        Client.setPhone(clsInputValidate::ReadString());
    
        cout << "\nEnter PinCode: ";
        Client.SetPinCode(clsInputValidate::ReadString());
    
        cout << "\nEnter Account Balance: ";
        Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());
    }
    
    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.GetFirstName();
        cout << "\nLastName    : " << Client.GetLastName();
        cout << "\nFull Name   : " << Client.GetFullName();
        cout << "\nEmail       : " << Client.GetEmail();
        cout << "\nPhone       : " << Client.GetPhone();
        cout << "\nAcc. Number : " << Client.GetAccountNumber();
        cout << "\nPassword    : " << Client.GetPinCode();
        cout << "\nBalance     : " << Client.GetAccountBalance();
        cout << "\n___________________\n";

    }

public : 

    static void ShowUpdateClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;// this will exit the function and it will not continue
        }

        _DrawScreenHeader("\tUpdate Client Screen");

        string AccountNumber = "";
    
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount number is not found, choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
    
        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);
    
        cout << "\n\nUpdate Client Info:";
        cout << "\n____________________\n";
    
      
        _ReadClientInfo(Client1);
    
        clsBankClient::enSaveResults SaveResult;
    
        SaveResult = Client1.Save();
    
        switch (SaveResult)
        {

        case  clsBankClient::enSaveResults::svSucceeded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintClient(Client1);
            break;
        }

        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;
    
        }
    
        }
    }



};