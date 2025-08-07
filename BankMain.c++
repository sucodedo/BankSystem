#include <iostream>
// #include "BankLibrary/BankUI/MainMenuScreen.h"
#include "BankLibrary/BankUI/LoginScreen.h"


using namespace std;

int main()
{
    // MainMenuScreen::ShowMainMenuScreen();
    while(true)
    {
        if (!LoginScreen::ShowLoginScreen())
        {
            break;
        }
    }

    return 0;
}