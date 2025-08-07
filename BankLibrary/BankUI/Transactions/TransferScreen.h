#pragma once
#include <iostream>
#include <vector>
#include "../Screen.h"
#include "../../BankClient.h"
#include "../../../../Libraries/InputValidate.h"
#include "../../Global.h"

class TransferScreen : protected Screen
{
private: 
    static string _ReadAccountNumber(const string Message)
    {
        return InputValidate::ReadStr(Message);
    }

    static string _ReadAccountNumber()
    {
        return InputValidate::ReadStr("Enter a Valid Account Number: ");
    }

    static bool _CheckIsClientExists(string& AccountNumber)
    {
        while (!BankClient::IsClientExists(AccountNumber))
        {
            cout << "Account Number Does't Exists! Try Again" << endl;
            AccountNumber = _ReadAccountNumber();
        }
        return true;
    }

    static void _PrintClientInfo(BankClient Client)
    {
        cout << "Client Card" << endl;
        cout << "--------------------";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc.. Number: " << Client.Get_Account_Number();
        cout << "\nBalance     : " << Client.Get_Account_Balance();
        cout << "\n-----------------------" << endl;
    }

public:
    static void ShowTransferScreen()
    {
        _ScreenHeader("\t\tTransfer Screen");

        string AccountNumber = _ReadAccountNumber("Enter Account Number To Transfer From: ");

        _CheckIsClientExists(AccountNumber);
        
        BankClient Sender_Client = BankClient::Find(AccountNumber);
        _PrintClientInfo(Sender_Client);
        
        AccountNumber = _ReadAccountNumber("Enter Account Number To Transfer To: ");

        while (AccountNumber == Sender_Client.Get_Account_Number())
        {
            cout << "\nYou Can't Transfer To Your Self, Enter Another Account Number!" << endl;
            AccountNumber = _ReadAccountNumber("\nEnter Account Number To Transfer To: ");
        }
        
        _CheckIsClientExists(AccountNumber);
        
        BankClient Receiver_Client = BankClient::Find(AccountNumber);
        _PrintClientInfo(Receiver_Client);

        double Amount = InputValidate::input_Db_Number("\nEnter Transfer Amount: ", "Try Again!");
        while(Sender_Client.Get_Account_Balance() < Amount)
        {
            Amount = InputValidate::input_Db_Number("\nAmount Exeeds The Available Balance, Enter Another Amount: ", "Try Again!");
        }
        char AskForPerform = InputValidate::ReadChar("\nAre You Sure you want to perform this tranfer operation y/n: ");

        if (AskForPerform == 'y' || AskForPerform == 'Y')
        {
            if(Sender_Client.Transfer(Receiver_Client, Amount, CurrentLogin.UserName()))
            {
                cout << "Successfully transfered money" << endl;
                _PrintClientInfo(Sender_Client);
                cout << "\n";
                _PrintClientInfo(Receiver_Client);
                // Sender_Client.RegisterTransferLogs(Receiver_Client, Amount, CurrentLogin.UserName());
            }
            else
                cout << "\nYou Can't Do This Operation!" << endl;
        }
        else
            cout << "\nYou Canceled This Operation" << endl;
    }

};