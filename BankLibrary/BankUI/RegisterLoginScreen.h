#pragma once
#include <iostream>
#include <vector>
#include "Screen.h"
#include "../User.h"

#include "../../../Libraries/InputValidate.h"

class RegisterLoginScreen : protected Screen
{
private:
    static void _PrintRegisterLoginList(User::stLoginRegister&RegisterLoginObj)
    {
        cout << "| " << left << setw(25) << RegisterLoginObj.DateTime;
        cout << "| " << left << setw(20) << RegisterLoginObj.UserName;
        cout << "| " << left << setw(15) << RegisterLoginObj.Password;
        cout << "| " << left << setw(25) << RegisterLoginObj.Permissions;
    }
public:
    static void ShowRegisterLoginScreen()
    {
        if (!_CheckAccessRights(User::enPermissions::pRegisterLogin))
        {
            return;
        }
        vector <User::stLoginRegister> vRegisterLogin = User::GetRegisterLoginList();
        _ClearScreen();
        _ScreenHeader("\t\tRegister Login Screen");

        cout << "--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\tLogin Register List: (" << vRegisterLogin.size() << ")" << endl;

        cout << "--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        cout << "| " << left << setw(25) << "Date Time";
        cout << "| " << left << setw(20) << "User Name";
        cout << "| " << left << setw(15) << "Password";
        cout << "| " << left << setw(25) << "Permissions";
        cout << "\n--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        if (vRegisterLogin.empty())
        {
            cout << "\n\t\t\t\t\t\t\tEmpty Register Login List!" << endl;
        }
        else
        {
            for (User::stLoginRegister& C : vRegisterLogin)
            {
                _PrintRegisterLoginList(C);
                cout << endl;
            }
        }
        cout << "\n--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";

    }

};