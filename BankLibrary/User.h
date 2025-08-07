#pragma once 
#include <iostream>
#include "vector"
#include "fstream"
#include "Person.h"
#include "../../Libraries/StrLib.h"
#include "../../Libraries/DateLib.h"
#include "../../Libraries/Utils.h"


using namespace std;

class User : public Person
{
private:
    enum enMode {EmtyMode = 0, UpdateMode = 1, AddNewClient = 2};
    enMode _Mode;
    string _UserName = "", _Password = "";
    int _Permissions = 0;

    bool _MarkedForDelete = false;

    static User _ConvertLineToUserObj(string Line, string Separator = "#//#")
    {
        vector<string>vUser = Str::split(Line, Separator);
        return User(enMode::UpdateMode, vUser[0], vUser[1], vUser[2], vUser[3], vUser[4], Utils::Decryption(vUser[5]), stoi(vUser[6]));
    }

    static string _ConvertUserObjToLine(User UserObj, string Separator = "#//#")
    {
        string Line = "";
        Line += UserObj.Get_First_Name() + Separator;
        Line += UserObj.Get_Last_Name() + Separator;
        Line += UserObj.Get_Phone_Number() + Separator;
        Line += UserObj.Get_Email() + Separator;
        Line += UserObj._UserName + Separator;
        Line += Utils::Encryption(UserObj._Password) + Separator;
        Line += to_string(UserObj._Permissions);
        return Line;
    }

    static User _GetEmtyUserObj()
    {
        return User(enMode::EmtyMode, "", "", "", "", "", "", 0);
    }

    static vector<User>_LoadUserDataFromFile()
    {
        vector<User>vUsers;
        fstream File;
        File.open("Users.txt", ios::in);
        if (File.is_open())
        {
            string Line = "";
            while(getline(File, Line))
            {
                User UserData = _ConvertLineToUserObj(Line, "#//#");
                vUsers.push_back(UserData);
            }
            File.close();
        }
        return vUsers;
    }

    static void _SaveUserDataToFile(vector<User>vUser)
    {
        fstream File;
        File.open("Users.txt", ios::out); // write mode
        if (File.is_open())
        {
                for (User C : vUser)
                {
                    if (!C._MarkedForDelete)
                    {
                        File << _ConvertUserObjToLine(C) << "\n";
                    }
                }
            }
            File.close(); 
    }

    void _Update()
    {
        vector<User>_vUser = _LoadUserDataFromFile();
        for (User&C : _vUser)
        {
            if (C.UserName() == UserName())
            {
                C = *this;
                break;
            }
        }
        _SaveUserDataToFile(_vUser);
    }

    void _AddDataLineToFile(string Line)
    {
        fstream File;
        File.open("Users.txt", ios::app | ios::out); // Append mode
        if (File.is_open())
        {
            File << Line << '\n';
        }
        File.close();
    }

    void _AddNewRecord()
    {
        _AddDataLineToFile(_ConvertUserObjToLine(*this));
    }

    string _ConvertLoginRegisterToLine(string Separetor = "#//#")
    {
        string Line = "";
        Line += DateLib::CurrentDateTime() + Separetor;
        Line += this->_UserName + Separetor;
        Line += this->_Password + Separetor;
        Line += to_string(this->_Permissions);
        return Line;
    } 
    
    // struct stLoginRegister;
    // static stLoginRegister _ConvertLineToRegisterLoginObj(string Line, string Seperator = "#//#")
    // {
    //     stLoginRegister LoginRegisterObj;
    //     vector<string> LoginRegisterDataLine;
    //     LoginRegisterObj.DateTime = LoginRegisterDataLine[0];
    //     LoginRegisterObj.UserName = LoginRegisterDataLine[1];
    //     LoginRegisterObj.Password = LoginRegisterDataLine[2];
    //     LoginRegisterObj.Permissions = stoi(LoginRegisterDataLine[3]);
    //     return LoginRegisterObj;        
    // }

    // static vector<stLoginRegister> _LoadRegisterLoginFromFile()
    // {
    //     vector<stLoginRegister> vRegisterLoginList;
    //     fstream File;
    //     File.open("LoginRegister.txt", ios::in); // Read Mode
    //     if (File.is_open())
    //     {
    //         string Line = "";
    //         stLoginRegister LoginRegisterObj;
    //         while(getline(File, Line))
    //         {
    //             LoginRegisterObj = _ConvertLineToRegisterLoginObj(Line);
    //             vRegisterLoginList.push_back(LoginRegisterObj);
    //         }
    //         File.close();
    //     }
    //     return vRegisterLoginList;
    // }

public:
    enum enPermissions 
    {
        eAll = -1, pListClient = 1, pAddNewClient = 2, pDeleteClient = 4, 
        pUpdateClients = 8, pFindClient = 16, pTransactions = 32,
        pManageUsers = 64, pRegisterLogin = 128, pCurrencyexchange = 512
    };

    struct stLoginRegister
    {
        string DateTime = "", UserName = "", Password = "";
        int Permissions = 0;
    };

    // Constractor
    User(enMode Mode, string First_Name, string Last_Name, string Phone_Number, string Email, string UserName, string Password, int Permissions)
        : Person(First_Name, Last_Name, Phone_Number, Email)
    {
        this->_Mode = Mode;
        this->_UserName = UserName;
        this->_Password = Password;
        this->_Permissions = Permissions;
    }

    // Setters & Getters 
    void UserName(string UserName)
    {
        this->_UserName = UserName;
    }

    string UserName()
    {
        return this->_UserName;
    }

    void Password(string Password)
    {
        this->_Password = Password;
    }

    string Password()
    {
        return this->_Password;
    }

    void Permissions(int Permissions)
    {
        this->_Permissions = Permissions;
    }

    int Permissions()
    {
        return this->_Permissions;
    }

    bool MarkForDelete()
    {
        return _MarkedForDelete;
    }

    bool is_Empty()
    {
        return (_Mode == enMode::EmtyMode);
    }

    // Find Bank Client By User Name
    static User Find(string UserName)
    {   
        vector<User> vUser;
        fstream File;
        File.open("Users.txt", ios::in);
        if (File.is_open())
        {
            string Line = "";
            while(getline(File, Line))
            {
                User User = _ConvertLineToUserObj(Line, "#//#");
                if (User._UserName == UserName)
                {
                    File.close();
                    return User;
                }
            }
            File.close();
        }
        return _GetEmtyUserObj();
    }

    // Find Bank Client By User Name && Password 
    static User Find(string UserName, string Password)
    {   
        vector<User> vUser;
        fstream File;
        File.open("Users.txt", ios::in);
        if (File.is_open())
        {
            string Line = "";
            while(getline(File, Line))
            {
                User User = _ConvertLineToUserObj(Line, "#//#");
                if (User._UserName == UserName && User._Password == Password)
                {
                    File.close();
                    return User;
                }
            }
            File.close();
        }
        return _GetEmtyUserObj();
    }

    static bool IsUserExists(string UserName)
    {
        User user = User::Find(UserName);
        return (!user.is_Empty());
    }

    enum enSaveResults {svDefault = -1, svFailedEmptyObj = 0, svSucceeded = 1, svFailedUserNameExists = 2};

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
                if (User::IsUserExists(this->_UserName))
                {
                    return enSaveResults::svFailedUserNameExists;
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

    static User GetAddNewUser(string UserName)
    {
        return User(enMode::AddNewClient, "", "", "", "", UserName, "", 0);
    }

    bool Delete()
    {
        vector<User>vUsers;
        vUsers = _LoadUserDataFromFile();
        for (User&C : vUsers)
        {
            if (C.UserName() == this->_UserName)
            {  
                C._MarkedForDelete = true;
            }
        }
        _SaveUserDataToFile(vUsers);
        *this = _GetEmtyUserObj();
        return true;
    }

    static vector<User> GetUsersList()
    {
        return _LoadUserDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->_Permissions == enPermissions::eAll)
            return true;
        else if ((Permission & this->_Permissions) == Permission)
            return true;
        else 
            return false;
    }

    void RegisterLogin()
    {
        string Line = _ConvertLoginRegisterToLine("#//#");
        fstream File;
        File.open("LoginRegister.txt", ios::app | ios::out); 
        if (File.is_open())
        {
            File << Line << '\n';
            File.close();
        }
    }
    
    // ???
    static vector<stLoginRegister> GetRegisterLoginList()
    {
        vector<stLoginRegister> vRegisterLoginList;
        fstream File;
        File.open("LoginRegister.txt", ios::in); // Read Mode
        if (File.is_open())
        {
            string Line = "";
            stLoginRegister LoginRegisterObj;
            while(getline(File, Line))
            {
                // LoginRegisterObj = _ConvertLineToRegisterLoginObj(Line);

                // it should be in a private method 
                vector<string> LoginRegisterDataLine = Str::split(Line, "#//#");
                LoginRegisterObj.DateTime = LoginRegisterDataLine[0];
                LoginRegisterObj.UserName = LoginRegisterDataLine[1];
                LoginRegisterObj.Password = LoginRegisterDataLine[2];
                LoginRegisterObj.Permissions = stoi(LoginRegisterDataLine[3]);
                vRegisterLoginList.push_back(LoginRegisterObj);
                // it should be in a private method 
                
            }
            File.close();
        }
        return vRegisterLoginList;
    }
    
};
