#pragma once
#include <iostream>
#include <vector>
#include "../Screen.h"
#include "../../BankClient.h"
#include "../../../../Libraries/InputValidate.h"

using namespace std;

class TotalBalancesScreen : protected Screen
{
private:
    static void _ClientRecordBalanceLine(BankClient& Client)
    {
        cout << "| " << left << setw(20) << Client.FullName();
        cout << "| " << left << setw(12) << Client.Get_Account_Number();
        cout << "| " << left << setw(12) << Client.Get_Account_Balance();
    }

public:
    static void ShowTotalBalancesScreen()
    {
        vector<BankClient> vClsList = BankClient::GetClientsList();

        string SubTitle = "\t\t  Clients Lists: (" + to_string(vClsList.size()) + ")" ;

        TotalBalancesScreen::_ScreenHeader("\t\tTotal Balances Screen", SubTitle);

        cout << "--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\tClients Lists: (" << vClsList.size() << ")" << endl;

        cout << "--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        cout << "| " << left << setw(20) << "Acc.. Name";
        cout << "| " << left << setw(12) << "Acc.. Number";
        cout << "| " << left << setw(12) << "Acc.. Balance";
        cout << "\n--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        if (vClsList.empty())
        {
            cout << "\n\t\t\t\t\t\t\tEmpty Client List!" << endl;
        }
        else
        {
            for (BankClient& C : vClsList)
            {
                _ClientRecordBalanceLine(C);
                cout << endl;
            }
        }
        cout << "\n--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        cout << "\t\t\t\t\t\t\t\t\tTotal Balances: " << BankClient::GetTotalBalances() << endl;
        cout << "Print Balances to text" << endl;
    }
};