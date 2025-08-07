#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "../Screen.h"
#include "../../BankClient.h"
#include "../../../../Libraries/InputValidate.h"

class TransferLogsScreen : protected Screen
{
private:

    static void _TransferLogLine(BankClient::stTransferLogs& TransferLog)
    {
        cout << "| " << left << setw(23) << TransferLog.Date_Time;
        cout << "| " << left << setw(15) << TransferLog.Sender_Account_Number;
        cout << "| " << left << setw(15) << TransferLog.Receiver_Account_Number;
        cout << "| " << left << setw(15) << TransferLog.Amount;
        cout << "| " << left << setw(15) << TransferLog.Account_Balance_After_Transfer;
        cout << "| " << left << setw(15) << TransferLog.Receiver_New_Account_Balance;
        cout << "| " << left << setw(15) << TransferLog.UserName;
    }

public:
    static void ShowTransferLogsScreen()
    {
        _ClearScreen();

        vector<BankClient::stTransferLogs> vGetTransferLogs = BankClient::GetTransferLogs();

        string subTitle = "\t\tTransfer Logs: " + to_string(vGetTransferLogs.size()); 

        _ScreenHeader("\t\tTransfer Logs Screen", subTitle);

        cout << "--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        cout << "| " << left << setw(23) << "Date Time";
        cout << "| " << left << setw(15) << "S.Acc.. Number";
        cout << "| " << left << setw(15) << "R.Acc.. Number";
        cout << "| " << left << setw(15) << "Amount";
        cout << "| " << left << setw(15) << "S.Acc.. Balance";
        cout << "| " << left << setw(15) << "R.Acc.. Balance";
        cout << "| " << left << setw(15) << "User Name";

        cout << "\n--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";
        if (vGetTransferLogs.empty())
        {
            cout << "\n\t\t\t\t\t\t\tEmpty Transfer Logs!" << endl;
        }
        else
        {
            for (BankClient::stTransferLogs& TransferLog : vGetTransferLogs)
            {
                _TransferLogLine(TransferLog);
                cout << endl;
            }
        }
        cout << "\n--------------------------------------------------------------------";
        cout << "--------------------------------------------------------------------\n";    }
    
};