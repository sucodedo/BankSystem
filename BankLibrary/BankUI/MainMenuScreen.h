#pragma once
#include <iostream>
#include <iomanip>

#include "../../../Libraries/InputValidate.h"

#include "Screen.h"
#include "../Global.h"

#include "ClientListScreen.h"
#include "AddNewClientScreen.h"
#include "DeleteClientScreen.h"
#include "UpdateClientInfoScreen.h"
#include "FindClientScreen.h"
#include "TransactionsScreen.h"
#include "ManageUsersMenueScreen.h"
#include "RegisterLoginScreen.h"
#include "CurrencyExchangeMenueScreen.h"

using namespace std;

class MainMenuScreen : protected Screen
{
private:
    enum eMainMenuOptions 
    {
        eShowClientsList = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenu = 6,
        eManageUsers = 7, eRegisterLogin = 8, eCurrencyExchange = 9, eExit = 10,
    };

    // Go Back To Main Menu
    static void _GoBackToMainMenu()
    {
        char input;
        cout << "\nEnter any Key to go back to main menu: " << endl;
        cin >> input;
        MainMenuScreen::ShowMainMenuScreen();
    }

    // _showClientList()
    static void _ShowClientsListScreen()
    {
        ClientListScreen::ClientsList();
    }

    static void _ShowAddNewClientScreen()
    {
        AddNewClientScreen::ShowAddNewClient();
    }

    static void _ShowDeletClientScreen()
    {
        DeleteClientScreen::ShowDeleteClientScreen();
    }

    static void _ShowUpdateClientInfoScreen()
    {
        UpdateClientInfoScreen::ShowUpdateClientInfoScreen();
    }

    static void _ShowFindClientScreen()
    {
        FindClientScreen::ShowFindClientScreen();
    }

    static void _ShowTransactionsScreen()
    {
        TransactionsScreen::ShowTransactionsScreen();
    }

    static void _ShowManageUsersScreen()
    {
        ManageUsersMenueScreen::ShowManageUsersMenueScreen();
    }

    // add register login
    static void _ShowRegisterLoginScreen()
    {
        RegisterLoginScreen::ShowRegisterLoginScreen();
    }

    // Add Currency Exchange
    static void _ShowCurrencyExchangeScreen()
    {
        CurrencyExchangeMenueScreen::ShowCurrencyExchangeMenueScreen();
    }

    static void _Logout()
    {
        CurrentLogin = CurrentLogin.Find("", "");
    }

    static void _PerformMainMenuScreen(eMainMenuOptions option)
    {
        switch (option)
        {
        case eMainMenuOptions::eShowClientsList:
            MainMenuScreen::_ClearScreen();
            _ShowClientsListScreen();
            _GoBackToMainMenu();  
            break;
        case eMainMenuOptions::eAddNewClient:
            MainMenuScreen::_ClearScreen();
            _ShowAddNewClientScreen();
            _GoBackToMainMenu();
            break;
        case eMainMenuOptions::eDeleteClient:
            MainMenuScreen::_ClearScreen();
            _ShowDeletClientScreen();
            _GoBackToMainMenu();
            break;
        case eMainMenuOptions::eUpdateClient:
            MainMenuScreen::_ClearScreen();
            _ShowUpdateClientInfoScreen();
            _GoBackToMainMenu();
            break;
        case eMainMenuOptions::eFindClient:
            MainMenuScreen::_ClearScreen();
            _ShowFindClientScreen();
            _GoBackToMainMenu();
            break;
        case eMainMenuOptions::eShowTransactionsMenu:
            MainMenuScreen::_ClearScreen();
            _ShowTransactionsScreen();
            _GoBackToMainMenu();
            break;
        case eMainMenuOptions::eManageUsers:
            MainMenuScreen::_ClearScreen();
            _ShowManageUsersScreen();
            _GoBackToMainMenu();
            break;
        case eMainMenuOptions::eRegisterLogin:
            MainMenuScreen::_ClearScreen();
            _ShowRegisterLoginScreen();
            _GoBackToMainMenu();
            break;
        case eMainMenuOptions::eCurrencyExchange:
            MainMenuScreen::_ClearScreen();
            _ShowCurrencyExchangeScreen();
            _GoBackToMainMenu();
            break;
        case eMainMenuOptions::eExit:
            MainMenuScreen::_ClearScreen();
            _Logout();
            break;
        default:
            break;
        }
    }

public:
    static void ShowMainMenuScreen()
    {
        MainMenuScreen::_ClearScreen();
        MainMenuScreen::_ScreenHeader("\t\t\tMain Screen");
        cout << setw(48) << "" << "======================================================\n";
        cout << setw(48) << "" << "\t\t\tMain Menu" << endl;
        cout << setw(48) << "" << "======================================================\n";
        cout << setw(48) << "" << left << "[01] Show Clients List   " << endl;
        cout << setw(48) << "" << left << "[02] Add New Client      " << endl;
        cout << setw(48) << "" << left << "[03] Delete Client       " << endl;
        cout << setw(48) << "" << left << "[04] Update Client Info. " << endl;
        cout << setw(48) << "" << left << "[05] Find Client.        " << endl;
        cout << setw(48) << "" << left << "[06] Transactions.       " << endl;
        cout << setw(48) << "" << left << "[07] Manage Users.       " << endl;
        cout << setw(48) << "" << left << "[08] Show Register Login." << endl;
        cout << setw(48) << "" << left << "[09] Currency Exchange.  " << endl;
        cout << setw(48) << "" << left << "[10] Logout.            " << endl;
        cout << setw(48) << "" << "======================================================\n";
        _PerformMainMenuScreen((eMainMenuOptions) InputValidate::readShortNumBetween(1, 10, "\t\t\t\t\t\tWhat do you want to choose [1-10]?: ", "\n\t\t\t\t\t\t** Invalid Input Enter a number between 1 - 10! try again **\n"));
    }

};