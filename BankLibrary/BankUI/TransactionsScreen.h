#pragma once
#include <iostream>
#include <vector>
#include "Screen.h"
#include "../BankClient.h"
#include "../../../Libraries/InputValidate.h"

#include "./Transactions/DepositScreen.h"
#include "./Transactions/WithdrawScreen.h"
#include "./Transactions/TotalBalancesScreen.h"
#include "./Transactions/TransferScreen.h"
#include "./Transactions/TransferLogs.h"


class TransactionsScreen : protected Screen
{
private:
    enum _eTransactionsOptions 
    {
        eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eTransfer = 4, eTransferLogs = 5, eMainMenu = 6 
    };

    static void _ShowDepositScreen()
    {
        DepositScreen::ShowDepositScreen();
    }

    static void _ShowWithdrawScreen()
    {
        WithdrawScreen::ShowWithdrawScreen();
    }
    
    static void _ShowTotalBalancesScreen()
    {
        TotalBalancesScreen::ShowTotalBalancesScreen();
    }

    static void _ShowTransferScreen()
    {
        TransferScreen::ShowTransferScreen();
    }

    static void _ShowTransferLogsScreen()
    {
        TransferLogsScreen::ShowTransferLogsScreen();
    }
    
    static void _GoBackToTransactionsScreen()
    {
        char input;
        cout << "\nEnter any Key to go back to Transactions menu: " << endl;
        cin >> input;
        TransactionsScreen::ShowTransactionsScreen();
    }

    static void _PerformMainMenuScreen(_eTransactionsOptions option)
    {
        switch (option)
        {
            case _eTransactionsOptions::eDeposit:
                TransactionsScreen::_ClearScreen();
                _ShowDepositScreen();
                _GoBackToTransactionsScreen();
                break;
            case _eTransactionsOptions::eWithdraw:
                TransactionsScreen::_ClearScreen();
                _ShowWithdrawScreen();
                _GoBackToTransactionsScreen();
                break;
            case _eTransactionsOptions::eTotalBalances:
                TransactionsScreen::_ClearScreen();
                _ShowTotalBalancesScreen();
                _GoBackToTransactionsScreen();
                break;
            case _eTransactionsOptions::eTransfer:
                TransactionsScreen::_ClearScreen();
                _ShowTransferScreen();
                _GoBackToTransactionsScreen();
                break;
            case _eTransactionsOptions::eTransferLogs:
                TransactionsScreen::_ClearScreen();
                _ShowTransferLogsScreen();
                _GoBackToTransactionsScreen();
                break;
            case _eTransactionsOptions::eMainMenu:
                break;
        }
    }

public:
    static void ShowTransactionsScreen()
    {
        if (!_CheckAccessRights(User::enPermissions::pTransactions))
        {
            return;
        }
        
        TransactionsScreen::_ClearScreen();
        TransactionsScreen::_ScreenHeader("\t\t\tTransactions Screen");
        cout << setw(48) << "" << "======================================================\n";
        cout << setw(48) << "" << "\t\t\tTransactions Menu" << endl;
        cout << setw(48) << "" << "======================================================\n";
        cout << setw(48) << "" << left << "[1] Deposit.           " << endl;
        cout << setw(48) << "" << left << "[2] Withdraw.          " << endl;
        cout << setw(48) << "" << left << "[3] Total Balances.    " << endl;
        cout << setw(48) << "" << left << "[4] Transfer.          " << endl;
        cout << setw(48) << "" << left << "[5] Transfer Logs.     " << endl;
        cout << setw(48) << "" << left << "[6] Main Menue.        " << endl;
        cout << setw(48) << "" << "======================================================\n";
        _PerformMainMenuScreen((_eTransactionsOptions) InputValidate::readShortNumBetween(1, 6, "\t\t\t\t\t\tWhat do you want to choose [1-6]?: ", "\n\t\t\t\t\t\t** Invalid Input Enter a number between 1 - 6! try again **\n"));
    }
};

