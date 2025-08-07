#pragma once
#include <iostream>
#include <vector>
#include "../Screen.h"
#include "../../BankClient.h"
#include "../../../../Libraries/InputValidate.h"

using namespace std;

class WithdrawScreen : protected Screen
{
private:
    static string _ReadAccountNumber()
    {
        return InputValidate::ReadStr("Enter The Account Number: ");
    }

    static void _PrintClientInfo(BankClient Client)
    {
        cout << "Client Card" << endl;
        cout << "--------------------";
        cout << "\nFirst Name  : " << Client.Get_First_Name();
        cout << "\nLast Name   : " << Client.Get_Last_Name();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Get_Email();
        cout << "\nPhone       : " << Client.Get_Phone_Number();
        cout << "\nAcc.. Number: " << Client.Get_Account_Number();
        cout << "\nPassword    : " << Client.Get_PinCode();
        cout << "\nBalance     : " << Client.Get_Account_Balance();
        cout << "\n-----------------------" << endl;
    }
public:
    static void ShowWithdrawScreen()
    {
        WithdrawScreen::_ScreenHeader("\t\tWithdraw Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!BankClient::IsClientExists(AccountNumber))
        {
            cout << "Client with [" << AccountNumber <<  "] does not exists! try again" << endl;
            AccountNumber = _ReadAccountNumber(); 
        }

        BankClient Client = BankClient::Find(AccountNumber);

        _PrintClientInfo(Client);

        double Amount = InputValidate::input_Db_Number("Enter The Amount That You Want To Withdraw: ", "Try Again!");
        
        if (Amount > 0)
        {
            char AskForWithdraw = InputValidate::ReadChar("Are you sure you want tp perform this transaction y/n?: ");

            if (AskForWithdraw == 'y' || AskForWithdraw == 'Y')
            {
                if (Client.Withdraw(Amount))
                {
                    cout << "\nAmount Withdraw Successfull\n" << endl; 
                    cout << "New Balance is: " << Client.Get_Account_Balance() << endl;
                }
                else    
                {
                    cout << "\nCannot withdraw, Insuffecient Balance!" << endl;
                    cout << "\nAmount to Withdraw is: " << Amount << endl;
                    cout << "\nYour Balance is: " << Client.Get_Account_Balance() << endl;
                }
            } 
            else 
                cout << "Withdraw was cancelled" << endl;
        }
    }
};