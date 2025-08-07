#pragma once
#include <iostream>

#include "../../../Libraries/InputValidate.h"
#include "../User.h"
#include "../Global.h"
#include "Screen.h"
#include "MainMenuScreen.h"

#include "../../../Libraries/DateLib.h"


class LoginScreen : protected Screen
{
private:
    static bool _Login()
    {
        string UserName = "", Password = "";
        
        bool Loggedin = false;
        short LoginTrials = 3;
        
        do
        {
            UserName = InputValidate::ReadStr("Enter your User Name: ");
            Password = InputValidate::ReadStr("Enter Password      : ");
            CurrentLogin = User::Find(UserName, Password);
            Loggedin = CurrentLogin.is_Empty();
            
            if (Loggedin)
            {
                cout << "\nInvalid UserName/Password!" << endl;
                LoginTrials--;
                cout << "You have " << LoginTrials << " trials to login.\n" << endl;
            }

            if (LoginTrials == 0)
            {
                cout << "You are Looked after 3 trials." << endl;
                return false;
            }

        } 
        while (Loggedin);
        
        // Register Login 
        CurrentLogin.RegisterLogin();
        MainMenuScreen::ShowMainMenuScreen();
        return true;
    }

public:
    static bool ShowLoginScreen()
    {
        _ClearScreen();
        _ScreenHeader("\t\tLogin Screen");
        return _Login();
    }
};