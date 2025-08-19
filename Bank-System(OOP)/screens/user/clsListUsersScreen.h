#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsUser.h"


class clsListUsersScreen : protected clsScreen
{
private : 

    static void _PrintUserRecordLine(clsUser User)
    {
    
        cout << "| " << setw(15) << left << User.GetUserName();
        cout << "| " << setw(10) << left << User.GetPassword();
        cout << "| " << setw(40) << left << User.GetPermissions();
    }


public : 

    static void ShowAllUsersScreen()
    {
        
       clsScreen::_DrawScreenHeader("Show All Users Screen : ");
    
        vector <clsUser> vUsers = clsUser::GetUsersList();
    
        cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    
        cout << "| " << left << setw(15) << "User Name";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(40) << "Permissions";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    
        if (vUsers.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else
    
            for (clsUser User : vUsers)
            {
    
                _PrintUserRecordLine(User);
                cout << endl;
            }
    
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    
    }

};