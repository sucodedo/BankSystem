#pragma once 
#include <iostream>
#include "vector"
#include "fstream"

// my Lib
#include "Person.h"
#include "../../Libraries/StrLib.h"
#include "../../Libraries/DateLib.h"


using namespace std;

class BankClient : public Person
{
private:
    enum enMode {EmtyMode = 0, UpdateMode = 1, AddNewClient = 2};

    enMode _Mode;
    string _Account_Number = "";
    string _PinCode = "";
    double _Account_Balance = 0;
    bool _MarkClientForDelete = false;

    // Convert Line To Object Method
    static BankClient _ConvertLineToClientObj(string Line, string Separetor = "#//#")
    {
        vector<string> vClient;
        vClient = Str::split(Line, Separetor);
        return BankClient(enMode::UpdateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4], vClient[5], stod(vClient[6]));
    }

    // ConvertClientObjToLine
    static string _ConvertClientObjToLine(BankClient ClientObj, string Separetor = "#//#")
    {
        string Line = "";
        Line += ClientObj.Get_First_Name() + Separetor;
        Line += ClientObj.Get_Last_Name() + Separetor;
        Line += ClientObj.Get_Phone_Number() + Separetor;
        Line += ClientObj.Get_Email() + Separetor;
        Line += ClientObj.Get_Account_Number() + Separetor;
        Line += ClientObj.Get_PinCode() + Separetor;
        Line += to_string(ClientObj.Get_Account_Balance());
        
        return Line;
    }

    // is_Empty Object Method
    static BankClient _GetEmtyClientObj()
    {
        return BankClient(enMode::EmtyMode, "", "", "", "", "", "", 0);
    } 

    // LoadClientDataFromFile
    static vector<BankClient>_LoadClientDataFromFile()
    {
        vector<BankClient>vClients;
        fstream File;
        File.open("BankClients.txt", ios::in); // Read mode
        if (File.is_open())
        {
            string Line = "";
            while (getline(File, Line))
            {
                BankClient ClientObj = _ConvertLineToClientObj(Line);
                vClients.push_back(ClientObj);
            }
            File.close();
        }
        return vClients;
    }

    static void _SaveClientDataToFile(vector<BankClient>vClient)
    {
        fstream File;
        File.open("BankClients.txt", ios::out); // write mode
        if (File.is_open())
        {
                for (BankClient C : vClient)
                {
                    if (!C._MarkClientForDelete)
                    {
                        File << _ConvertClientObjToLine(C) << "\n";
                    }
                }
            }
            File.close(); 
    }

    // Update
    void _Update()
    {
        vector<BankClient>_vClient = _LoadClientDataFromFile();
        for (BankClient&C : _vClient)
        {
            if (C.Get_Account_Number() == Get_Account_Number())
            {
                C = *this;
                break;
            }
        }
        _SaveClientDataToFile(_vClient);
    }

    void AddDataLineToFile(string Line)
    {
        fstream File;
        File.open("BankClients.txt", ios::app | ios::out); // Append mode
        if (File.is_open())
        {
            File << Line << '\n';
        }
        File.close();
    }

    void _AddNewRecord()
    {
        AddDataLineToFile(_ConvertClientObjToLine(*this));
    }

    string _ConvertRegisterTransferLogsToLine(BankClient Receiver_Client, double Amount, string UserName, string Separetor = "#//#")
    {
        string Line = "";
        Line += DateLib::CurrentDateTime() + Separetor;
        Line += this->_Account_Number + Separetor;
        Line += Receiver_Client.Get_Account_Number() + Separetor;
        Line += to_string(Amount) + Separetor;
        Line += to_string(this->_Account_Balance) + Separetor;
        Line += to_string(Receiver_Client.Get_Account_Balance()) + Separetor;
        Line += UserName;
        return Line;
    }

    // Register Transfer logs 
    void _RegisterTransferLogs(BankClient Receiver_Client, double Amount, string UserName)
    {
        // Date/Time + Sender Account Num + Receiver Account Num + Amount to transfer + Account balance after transfer + Receiver new account balance + The user that make that transfer 
        string Line = _ConvertRegisterTransferLogsToLine(Receiver_Client, Amount, UserName, "#//#");
        fstream File;
        File.open("TransferLogs.txt", ios::app | ios::out); 
        if (File.is_open())
        {
            File << Line << '\n';
            File.close();
        }
    }

public:
    BankClient(enMode Mode, string First_Name, string Last_Name, string Phone_Number, string Email, string Account_Number, string PinCode, double Account_Balance)
    : Person(First_Name, Last_Name, Phone_Number, Email)
    {
        _Mode = Mode;
        _Account_Number = Account_Number;
        _PinCode = PinCode;
        _Account_Balance = Account_Balance;
    }

    // is Empty Obj
    bool is_Empty()
    {
        return (_Mode == enMode::EmtyMode);
    }

    // Setters and Getters Properties
    string Get_Account_Number()
    {
        return _Account_Number;
    }

    void Set_PinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string Get_PinCode()
    {
        return _PinCode;
    }
    
    void Set_Account_Balance(double Account_Balance)
    {
        _Account_Balance = Account_Balance;
    }

    double Get_Account_Balance()
    {
        return _Account_Balance;
    }

    bool MarkForDelete()
    {
        return _MarkClientForDelete;
    }

    // Find Bank Client By Account Number 
    static BankClient Find(string Account_Number)
    {   
        vector<BankClient> vClient;
        fstream File;
        File.open("BankClients.txt", ios::in);
        if (File.is_open())
        {
            string Line = "";
            while(getline(File, Line))
            {
                BankClient Client = _ConvertLineToClientObj(Line, "#//#");
                if (Client._Account_Number == Account_Number)
                {
                    File.close();
                    return Client;
                }
            }
            File.close();
        }
        return _GetEmtyClientObj();
    }

    // Find Bank Client By Account Number && PinCode
    static BankClient Find(string Account_Number, string PinCode)
    {   
        vector<BankClient> vClient;
        fstream File;
        File.open("BankClients.txt", ios::in);
        if (File.is_open())
        {
            string Line = "";
            while(getline(File, Line))
            {
                BankClient Client = _ConvertLineToClientObj(Line, "#//#");
                if (Client._Account_Number == Account_Number && Client._PinCode == PinCode)
                {
                    File.close();
                    return Client;
                }
            }
            File.close();
        }
        return _GetEmtyClientObj();
    }

    static bool IsClientExists(string Account_Number)
    {
        BankClient Client = BankClient::Find(Account_Number);
        return (!Client.is_Empty());
    }

    // There is Ui
    // // Print Bank Client Info
    void Print()
    {
        cout << "Client Card" << endl;
        cout << "--------------------";
        cout << "\nFirst Name  : " << Get_First_Name();
        cout << "\nLast Name   : " << Get_Last_Name();
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Get_Email();
        cout << "\nPhone       : " << Get_Phone_Number();
        cout << "\nAcc.. Number: " << _Account_Number;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _Account_Balance;
        cout << "\n-----------------------" << endl;
    }

    // save method 
    enum enSaveResults {svDefault = -1, svFailedEmptyObj = 0, svSucceeded = 1, svFailedAccountNumberExists = 2};

    enSaveResults Save()
    {
        switch (this->_Mode)
        {
            case enMode::EmtyMode:
                if (is_Empty())
                {
                    return enSaveResults::svFailedEmptyObj;
                }
            case enMode::UpdateMode:
                // Update
                _Update();
                return enSaveResults::svSucceeded;
            case enMode::AddNewClient:
                if (BankClient::IsClientExists(this->_Account_Number))
                {
                    return enSaveResults::svFailedAccountNumberExists;
                }
                else
                {
                    _AddNewRecord();
                    _Mode = enMode::UpdateMode;
                    return enSaveResults::svSucceeded;
                }
            default:
                return enSaveResults::svDefault;
        }
    }

    // Add A New Client
    static BankClient GetAddNewClient(string AccountNumber)
    {
        return BankClient(enMode::AddNewClient, "", "", "", "", AccountNumber, "", 0);
    }

    // Delete Client
    bool Delete()
    {
        vector<BankClient>vClients;
        vClients = _LoadClientDataFromFile();
        for (BankClient&C : vClients)
        {
            if (C.Get_Account_Number() == this->_Account_Number)
            {  
                C._MarkClientForDelete = true;
            }
        }
        _SaveClientDataToFile(vClients);
        *this = _GetEmtyClientObj();
        return true;
    }

    // Get Clients List
    static vector<BankClient> GetClientsList()
    {
        return _LoadClientDataFromFile();
    }

    // Get Total Balances 
    static double GetTotalBalances()
    {
        vector<BankClient> vClientsList = _LoadClientDataFromFile();
        double totalBalance = 0;
        for (BankClient& C : vClientsList)
        {
            totalBalance += C.Get_Account_Balance();
        }
        return totalBalance;
    }

    // Deposit 
    void Deposit(double Amount)
    {
        this->_Account_Balance += Amount;
        Save(); 
    }

    // Withdraw
    bool Withdraw(double Amount)
    {
        if (Amount > this->_Account_Balance)
        {
            return false;
        }
        else 
        {
            this->_Account_Balance -= Amount;
            Save();
            return true;
        }
    }

    // Transfer 
    bool Transfer(BankClient& Receiver_Client, double Amount, string UserName)
    {
        if (this->_Account_Balance < Amount || Amount <= 0)
        {
            return false;
        }
        Withdraw(Amount);
        Receiver_Client.Deposit(Amount);
        _RegisterTransferLogs(Receiver_Client, Amount, UserName);
        return true;
    }

    struct stTransferLogs 
    {
        string Date_Time = "", Sender_Account_Number = "", Receiver_Account_Number = "";
        double Amount = 0, Account_Balance_After_Transfer = 0, Receiver_New_Account_Balance = 0;
        string UserName = "";
    };
    
    static stTransferLogs _ConvertTransferLogsLineToObj(string Line, string Seperator = "#//#")
    {
        stTransferLogs TransferLogObj;
        vector<string> _vLineData = Str::split(Line, Seperator);
        TransferLogObj.Date_Time = _vLineData[0];
        TransferLogObj.Sender_Account_Number = _vLineData[1];
        TransferLogObj.Receiver_Account_Number = _vLineData[2];
        TransferLogObj.Amount = stod(_vLineData[3]);
        TransferLogObj.Account_Balance_After_Transfer = stod(_vLineData[4]);
        TransferLogObj.Receiver_New_Account_Balance = stod(_vLineData[5]);
        TransferLogObj.UserName = _vLineData[6];
        return TransferLogObj;
    }

    static vector<stTransferLogs> GetTransferLogs()
    {
        vector<stTransferLogs> vTransferLogs;
        fstream File;
        File.open("TransferLogs.txt", ios::in); // Read Mode
        if (File.is_open())
        {
            string Line = "";
            stTransferLogs TransferLogsObj;
            while(getline(File, Line))
            {
                TransferLogsObj = _ConvertTransferLogsLineToObj(Line, "#//#");
                vTransferLogs.push_back(TransferLogsObj);
            }
            File.close();
        }
        return vTransferLogs;
    }

};
