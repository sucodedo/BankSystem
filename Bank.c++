#include <iostream>
#include <iomanip>
#include "BankLibrary/BankClient.h"
#include "../Libraries/InputValidate.h"
#include "../Libraries/Utils.h"

using namespace std;

void ClearScreen()
{
    system("clear");
}

void ReadClientInfo(BankClient& Client)
{
    Client.First_Name(InputValidate::ReadStr("Enter The First Name: "));
    Client.Last_Name(InputValidate::ReadStr("Enter The Last Name: "));
    Client.Phone_Number(InputValidate::ReadStr("Enter The Phone Number: "));
    Client.Email(InputValidate::ReadStr("Enter The Email: "));
    Client.Set_PinCode(InputValidate::ReadStr("Enter The Pin Code: "));
    Client.Set_Account_Balance(InputValidate::input_Db_Number("Enter Account Balance: ", "Invalid Input! try Again"));
}

void UpdateClient()
{
    string AccountNumber = "";
    AccountNumber = InputValidate::ReadStr("Enter Account Number: ");
    while (!BankClient::IsClientExists(AccountNumber))
    {
        cout << "Client is not exists! try again" << endl;
        AccountNumber = InputValidate::ReadStr("Enter Account Number: "); 
    }
    BankClient Client = BankClient::Find(AccountNumber);

    Client.is_Empty() ? cout << "True\n" : cout << "False\n"; 

    Client.Print();

    cout << "\n\nUpdate Client Info:";
    cout << "\n____________________\n";
    ReadClientInfo(Client);

    BankClient::enSaveResults SaveResults;

    SaveResults = Client.Save();
    switch (SaveResults)
    {
        case BankClient::enSaveResults::svSucceeded:
            cout << "\nClient updated succeessfully.\n" << endl;
            Client.Print();
            break;
        case BankClient::enSaveResults::svFailedEmptyObj:
            cout << "Client update Failed" << endl;
            break;
    }
}

void AddNewClient()
{
    string AccountNumber = InputValidate::ReadStr("Enter Account Number: ");
    while(BankClient::IsClientExists(AccountNumber))
    {
        cout << "Client Exists! Try Again" << endl;
        AccountNumber = InputValidate::ReadStr("Enter Account Number: ");
    }

    BankClient NewClient = BankClient::GetAddNewClient(AccountNumber);

    ReadClientInfo(NewClient);

    BankClient::enSaveResults SaveResults;
    SaveResults = NewClient.Save();

    switch (SaveResults)
    {
        case BankClient::enSaveResults::svSucceeded:
            cout << "\nClient added succeessfully.\n" << endl;
            NewClient.Print();
            break;
        case BankClient::enSaveResults::svFailedEmptyObj:
            cout << "Client added Failed" << endl;
            break;
        case BankClient::enSaveResults::svFailedAccountNumberExists:
            cout << "Client already exists!" << endl;
            break;
    }
}

void DeleteClient()
{
    string AccountNumber = InputValidate::ReadStr("Enter Account Number: ");

    while(!BankClient::IsClientExists(AccountNumber))
    {
        cout << "There is no Account Exists! try again" << endl;
        AccountNumber = InputValidate::ReadStr("Enter Account Number: ");
    }

    BankClient DelClient = BankClient::Find(AccountNumber);

    DelClient.Print();

    cout << "Delete Client: " << endl;
    char AskForDelete = 'n';
    cout << "Are you sure you want to delete that Client y/n: ";
    cin >> AskForDelete;
    if (AskForDelete == 'Y' || AskForDelete == 'y')
    {
        if (DelClient.Delete())
        {
            cout << "\nClient Deleted Successfully\n" << endl;
            DelClient.Print();
        }
        else 
        {
            cout << "Something went wrong!?" << endl;
        }
    } 
}

void PrintClientsList(BankClient&Client)
{
    cout << "| " << left << setw(20) << Client.Get_First_Name();
    cout << "| " << left << setw(20) << Client.Get_Last_Name();
    cout << "| " << left << setw(15) << Client.Get_Phone_Number();
    cout << "| " << left << setw(25) << Client.Get_Email();
    cout << "| " << left << setw(12) << Client.Get_Account_Number();
    cout << "| " << left << setw(12) << Client.Get_PinCode();
    cout << "| " << left << setw(12) << Client.Get_Account_Balance();
}

void ClientsList()
{
    vector<BankClient> vClsList = BankClient::GetClientsList();
    cout << "--------------------------------------------------------------------";
    cout << "--------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\tClients Lists: (" << vClsList.size() << ")" << endl;

    cout << "--------------------------------------------------------------------";
    cout << "--------------------------------------------------------------------\n";
    cout << "| " << left << setw(20) << "First Name";
    cout << "| " << left << setw(20) << "Last Name";
    cout << "| " << left << setw(15) << "Phone";
    cout << "| " << left << setw(25) << "Email";
    cout << "| " << left << setw(12) << "Acc.. Number";
    cout << "| " << left << setw(12) << "Pin Code";
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
            PrintClientsList(C);
            cout << endl;
        }
    }
    cout << "\n--------------------------------------------------------------------";
    cout << "--------------------------------------------------------------------\n";
}

void ClientRecordBalanceLine(BankClient& Client)
{
    cout << "| " << left << setw(20) << Client.FullName();
    cout << "| " << left << setw(12) << Client.Get_Account_Number();
    cout << "| " << left << setw(12) << Client.Get_Account_Balance();
}

void ShowTotalBalances()
{
    vector<BankClient> vClsList = BankClient::GetClientsList();
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
            ClientRecordBalanceLine(C);
            cout << endl;
        }
    }
    cout << "\n--------------------------------------------------------------------";
    cout << "--------------------------------------------------------------------\n";
    cout << "\t\t\t\t\t\t\t\t\tTotal Balances: " << BankClient::GetTotalBalances() << endl;
    cout << "Print Balances to text" << endl;
}

int main()
{
    ClearScreen();
    // UpdateClient();
    // AddNewClient();
    // DeleteClient();
    // ClientsList();
    // ShowTotalBalances();
    cout << Utils::Decryption("0123456*/") << endl;


    return 0;
}