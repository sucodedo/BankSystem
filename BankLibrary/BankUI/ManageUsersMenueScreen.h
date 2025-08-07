#pragma once
#include <iostream>
#include <vector>
#include "Screen.h"
#include "../BankClient.h"
#include "../../../Libraries/InputValidate.h"

#include "ManageUsers/ListUserScreen.h"
#include "ManageUsers/AddNewUserScreen.h"
#include "ManageUsers/DeleteUserScreen.h"
#include "ManageUsers/UpdateUserScreen.h"
#include "ManageUsers/FindUserScreen.h"

class ManageUsersMenueScreen : protected Screen
{
private:
    enum eManageUsersMenueOption
    {
        eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
        eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
    };  

    static short _ReadManageUsersOption()
    {
        return InputValidate::readShortNumBetween(1, 6, "\t\t\t\t\t\tWhat do you want to choose [1-6]?: ", "\n\t\t\t\t\t\t** Invalid Input Enter a number between 1 - 6! try again **\n");
    }

    static void _ShowListUsersScreen()
    {
        ListUsersScreen::ShowListUsersScreen();
    }

    static void _ShowAddNewUserScreen()
    {
        AddNewUserScree::ShowAddNewUserScreen();
    }
    
    static void _ShowDeleteUserScreen()
    {
        DeleteUserScreen::ShowDeleteUserScreen();
    }
    
    static void _ShowUpdateUserScreen()
    {
        UpdateUserScreen::ShowUpdateUserScreen();
    }
    
    static void _ShowFindUserScreen()
    {
        FindUserScreen::ShowFindUserScreen();
    }

    static void _GoBackToShowManageUsersMenueScreen()
    {
        char input;
        cout << "\nEnter any Key to go back to Manage Users menue: " << endl;
        cin >> input;
        ManageUsersMenueScreen::ShowManageUsersMenueScreen();
    }

    static void _PerformManageUsersMenueOption(eManageUsersMenueOption Option) 
    {
        switch (Option)
        {
            case eManageUsersMenueOption::eListUsers:
                ManageUsersMenueScreen::_ClearScreen();
                _ShowListUsersScreen();
                _GoBackToShowManageUsersMenueScreen();
                break;
            case eManageUsersMenueOption::eAddNewUser:
                ManageUsersMenueScreen::_ClearScreen();
                _ShowAddNewUserScreen();
                _GoBackToShowManageUsersMenueScreen();
                break;
            case eManageUsersMenueOption::eDeleteUser:
                ManageUsersMenueScreen::_ClearScreen();
                _ShowDeleteUserScreen();
                _GoBackToShowManageUsersMenueScreen();
                break;
            case eManageUsersMenueOption::eFindUser:
                ManageUsersMenueScreen::_ClearScreen();
                _ShowFindUserScreen();
                _GoBackToShowManageUsersMenueScreen();
                break;
            case eManageUsersMenueOption::eUpdateUser:
                ManageUsersMenueScreen::_ClearScreen();
                _ShowUpdateUserScreen();
                _GoBackToShowManageUsersMenueScreen();
                break;
            case eManageUsersMenueOption::eMainMenue:
                break;
        }
    }

public:
    static void ShowManageUsersMenueScreen()
    {
        if (!_CheckAccessRights(User::enPermissions::pManageUsers))
        {
            return;
        }
    
        ManageUsersMenueScreen::_ClearScreen();
        ManageUsersMenueScreen::_ScreenHeader("\t\tManage Users Screen");
        cout << setw(48) << "" << "======================================================\n";
        cout << setw(48) << "" << "\t\t\tManage Users Menue" << endl;
        cout << setw(48) << "" << "======================================================\n";
        cout << setw(48) << "" << left << "[1] List Users.  " << endl;
        cout << setw(48) << "" << left << "[2] Add New User." << endl;
        cout << setw(48) << "" << left << "[3] Delete User. " << endl;
        cout << setw(48) << "" << left << "[4] Update User. " << endl;
        cout << setw(48) << "" << left << "[5] Find User.   " << endl;
        cout << setw(48) << "" << left << "[6] Main Menue.  " << endl;
        cout << setw(48) << "" << "======================================================\n";
        _PerformManageUsersMenueOption((eManageUsersMenueOption) _ReadManageUsersOption());
    }
};