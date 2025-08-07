#pragma once
#include <iostream>
#include <iomanip>
#include "../../../Libraries/DateLib.h"
#include "../User.h"
#include "../Global.h"

using namespace std;

class Screen
{
protected:
    static void _ClearScreen()
    {
        system("clear");
    }

    static void _ScreenHeader(string Title, string SubTitle = "")
    {
        cout << endl;
        cout << setw(48) << "" << "------------------------------------------------------\n";
        cout << setw(48) << "" << Title << endl;
        if (SubTitle != "")
            cout << setw(48) << "" << SubTitle << endl;
        cout << setw(48) << "" << "------------------------------------------------------\n";
        cout << "\n";
        if (CurrentLogin.is_Empty())
        {
            cout << setw(48) << "" << "Date        : " << _CurrentDate() << endl;
        }
        else 
        {
            cout << setw(48) << "" << "Current User: " << CurrentLogin.Get_First_Name() << endl;
            cout << setw(48) << "" << "Date        : " << _CurrentDate() << endl;
        }
        cout << endl;
    }

    static bool _CheckAccessRights(User::enPermissions Permission)
    {
        if (!CurrentLogin.CheckAccessPermission(Permission))
        {
            cout << endl;
            cout << setw(48) << "" << "------------------------------------------------------\n";
            cout << setw(48) << "" << "Access Denied! Contact Your Admin!" << endl;
            cout << setw(48) << "" << "------------------------------------------------------\n";
            return false;
        }
        else
        {
            return true;
        }
    }

    static string _CurrentDate()
    {
        return DateLib::DateFormat(DateLib(), "mm/dd/yyyy");
    }
};