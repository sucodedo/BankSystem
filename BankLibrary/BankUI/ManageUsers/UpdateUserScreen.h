#pragma once
#include <iostream>
#include <vector>
#include "../Screen.h"
#include "../../User.h"
#include "../../../../Libraries/InputValidate.h"

class UpdateUserScreen : protected Screen
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

    static void _ReadUserInfo(User& UserObj)
    {
        UserObj.First_Name(InputValidate::ReadStr("Enter FirstName: "));
        UserObj.Last_Name(InputValidate::ReadStr("Enter LastName: "));
        UserObj.Email(InputValidate::ReadStr("Enter Email: "));
        UserObj.Phone_Number(InputValidate::ReadStr("Enter Phone: "));
        UserObj.Password(InputValidate::ReadStr("Enter Password: "));
        UserObj.Permissions(UpdateUserScreen::_ReadPermissions());
    }

    static int _ReadPermissions()
    {
        int Permissions = 0;
        char AskForPer;
        AskForPer = InputValidate::ReadChar("Do you want to give full access y/n? : ");
        if (AskForPer == 'Y' || AskForPer == 'y')
        {
            return -1;
        }

        AskForPer = InputValidate::ReadChar("\nShow Client List    y/n: ");
        if (AskForPer == 'y' || AskForPer == 'Y')
            Permissions += User::enPermissions::pListClient;

        AskForPer = InputValidate::ReadChar("\nAdd New Client      y/n: ");
        if (AskForPer == 'y' || AskForPer == 'Y')
            Permissions += User::enPermissions::pAddNewClient;
        
        AskForPer = InputValidate::ReadChar("\nDelete Client       y/n: ");
        if (AskForPer == 'y' || AskForPer == 'Y')
            Permissions += User::enPermissions::pDeleteClient;
        
        AskForPer = InputValidate::ReadChar("\nUpdate Client Info  y/n: ");
        if (AskForPer == 'y' || AskForPer == 'Y')
            Permissions += User::enPermissions::pUpdateClients;
        
        AskForPer = InputValidate::ReadChar("\nFind Client         y/n: ");
        if (AskForPer == 'y' || AskForPer == 'Y')
            Permissions += User::enPermissions::pFindClient;
        
        AskForPer = InputValidate::ReadChar("\nTransaction         y/n: ");
        if (AskForPer == 'y' || AskForPer == 'Y')
            Permissions += User::enPermissions::pTransactions;
        
        AskForPer = InputValidate::ReadChar("\nManage Users        y/n: ");
        if (AskForPer == 'y' || AskForPer == 'Y')
            Permissions += User::enPermissions::pManageUsers;

        AskForPer = InputValidate::ReadChar("\nShow Login Register y/n: ");
        if (AskForPer == 'y' || AskForPer == 'Y')
            Permissions += User::enPermissions::pManageUsers;
        
        AskForPer = InputValidate::ReadChar("\nShow Currency Exchange y/n: ");
        if (AskForPer == 'y' || AskForPer == 'Y')
            Permissions += User::enPermissions::pCurrencyexchange;

        return Permissions;
    }

public:
    static void ShowUpdateUserScreen()
    {
        UpdateUserScreen::_ClearScreen();
        UpdateUserScreen::_ScreenHeader("\t\tUpdate User Screen");

        string UserName = _ReadUserName();

        while(!User::IsUserExists(UserName))
        {
            cout << "User Name Does not exists! try again" << endl;
            UserName = _ReadUserName();
        }

        User UserObj = User::Find(UserName);
        _PrintUserInfo(UserObj);

        char AskForUpdate = InputValidate::ReadChar("Are you sure you want to update that user y/n? : ");

        if (AskForUpdate == 'y' || AskForUpdate == 'Y')
        {
            _ReadUserInfo(UserObj);
            User::enSaveResults Result; 
            Result = UserObj.Save();
            switch (Result)
            {
                case User::enSaveResults::svSucceeded:
                    cout << "\nUser Updated succeessfully.\n" << endl;
                    _PrintUserInfo(UserObj);
                    break;
                case User::enSaveResults::svFailedEmptyObj:
                    cout << "User Updated Failed" << endl;
                    break;
            }
        }
        else 
            cout << "User Updated Canceled" << endl;
        
    }

};