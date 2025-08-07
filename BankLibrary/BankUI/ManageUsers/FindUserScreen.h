#pragma once
#include <iostream>
#include <vector>
#include "../Screen.h"
#include "../../User.h"
#include "../../../../Libraries/InputValidate.h"

class FindUserScreen : protected Screen 
{
private:
    static string _ReadUserName()
    {
        return InputValidate::ReadStr("Enter User Name: ");
    }

    static void _PrintUserInfo(User UserObj)
    {
        cout << "User Card" << endl;
        cout << "--------------------";
        cout << "\nFirst Name  : " << UserObj.Get_First_Name();
        cout << "\nLast Name   : " << UserObj.Get_Last_Name();
        cout << "\nFull Name   : " << UserObj.FullName();
        cout << "\nEmail       : " << UserObj.Get_Email();
        cout << "\nPhone       : " << UserObj.Get_Phone_Number();
        cout << "\nPassword    : " << UserObj.Password();
        cout << "\nPermissions : " << UserObj.Permissions();
        cout << "\n-----------------------" << endl;
    }

public:
    static void ShowFindUserScreen()
    {
        FindUserScreen::_ClearScreen();
        FindUserScreen::_ScreenHeader("\t\tFind User Screen");

        string UserName = _ReadUserName();

        while(!User::IsUserExists(UserName))
        {
            cout << "User Does Not Exists! Try Again" << endl;
            UserName = _ReadUserName();
        }

        User UserObj = User::Find(UserName);

        if (UserObj.is_Empty())
        {
            cout << "User Does Not Exists!" << endl;
        }
        else
        {
            _PrintUserInfo(UserObj);
        }
    }
};