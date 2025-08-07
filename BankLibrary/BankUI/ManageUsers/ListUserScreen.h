#pragma once
#include <iostream>
#include <vector>
#include "../Screen.h"
#include "../../User.h"
#include "../../../../Libraries/InputValidate.h"

class ListUsersScreen : protected Screen
{
private:
    static void _UserRecordLine(User& UserRecord)
    {
        cout << "| " << left << setw(20) << UserRecord.FullName();
        cout << "| " << left << setw(12) << UserRecord.Get_Phone_Number();
        cout << "| " << left << setw(20) << UserRecord.Get_Email();
        cout << "| " << left << setw(12) << UserRecord.UserName();
        cout << "| " << left << setw(12) << UserRecord.Permissions();
    }

public:
    static void ShowListUsersScreen()
    {
        vector<User> vUsersList = User::GetUsersList();

        string SubTitle = "\t\t  Users List: (" + to_string(vUsersList.size()) + ")" ;

        ListUsersScreen::_ScreenHeader("\t\t  Users Screen", SubTitle);

        cout << "--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";

        cout << "| " << left << setw(20) << "Full Name";
        cout << "| " << left << setw(12) << "Phone Number";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(12) << "User Name";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "\n--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        if (vUsersList.empty())
        {
            cout << "\n\t\t\t\t\t\t\tEmpty Users List!" << endl;
        }
        else
        {
            for (User& C : vUsersList)
            {
                _UserRecordLine(C);
                cout << endl;
            }
        }
        cout << "\n--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
    }

};