#pragma once
#include <iostream>

using namespace std;

class Person
{
private:
    string _First_Name = "", _Last_Name = "", _Phone_Number = "", _Email = "";

public:
    Person(string First_Name, string Last_Name, string Phone_Number, string Email)
    {
        _First_Name = First_Name;
        _Last_Name = Last_Name;
        _Phone_Number = Phone_Number;
        _Email = Email;
    }

    // Setters and Getters properties 
    void First_Name(string First_Name)
    {
        _First_Name = First_Name;
    }

    string Get_First_Name()
    {
        return _First_Name;
    }

    void Last_Name(string Last_Name)
    {
        _Last_Name = Last_Name;
    }

    string Get_Last_Name()
    {
        return _Last_Name;
    }

    void Phone_Number(string Phone_Number)
    {
        _Phone_Number = Phone_Number;
    }

    string Get_Phone_Number()
    {
        return _Phone_Number;
    }

    void Email(string Email)
    {
        _Email = Email;
    }

    string Get_Email()
    {
        return _Email;
    }

    string FullName()
    {
        return _First_Name + " " + _Last_Name;
    }
};