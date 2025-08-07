#pragma once
#include <iostream>
#include <vector>
#include "../Screen.h"
#include "../../User.h"
#include "../../../../Libraries/InputValidate.h"

class DeleteUserScreen : protected Screen
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
    static void ShowDeleteUserScreen()
    {
        DeleteUserScreen::_ClearScreen();
        DeleteUserScreen::_ScreenHeader("\t\tDelete User Screen");

        string UserName = _ReadUserName();

        while(!User::IsUserExists(UserName))
        {
            cout << "User Name Does not exists! try again" << endl;
            UserName = _ReadUserName();
        }

        User UserObj = User::Find(UserName);
        _PrintUserInfo(UserObj);

        char AskforDelete = InputValidate::ReadChar("\nAre you sure you want to delete that User y/n? : ");

        if (AskforDelete == 'y' || AskforDelete == 'Y')
        {
            if (UserObj.Delete())
            {
                cout << "\nUser Deleted Successfully" << endl;
                _PrintUserInfo(UserObj);
            }
            else 
                cout << "\nSomething went wrong!?" << endl;
        }
        else 
            cout << "\nYou Canceled Delete That User" << endl;
        
    }

};