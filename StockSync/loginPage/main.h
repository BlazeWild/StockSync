#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class User
{
private:
    string Name, Address, UserRole, Username, Password;

public:
    User() {}
    User(string name_, string address_, string userRole_, string username_, string password_);
    string GetName();
    string GetAddress();
    string GetUserRole();
    string GetUsername();
    void HashPassword();
    void AddUser();
    User AuthenticateUser(string username, string password);
    void SaveToFile(string filename);
    static vector<User> ReadUserFile(string filename);
    bool IsEmpty();

private:
    void deserialize(ifstream &file)
    {
        // Read and extract each attribute from the file
        string::size_type nameSize;
        file.read(reinterpret_cast<char *>(&nameSize), sizeof(nameSize));
        Name.resize(nameSize);
        file.read(reinterpret_cast<char *>(&Name[0]), nameSize);

        string::size_type addressSize;
        file.read(reinterpret_cast<char *>(&addressSize), sizeof(addressSize));
        Address.resize(addressSize);
        file.read(reinterpret_cast<char *>(&Address[0]), addressSize);

        string::size_type userRoleSize;
        file.read(reinterpret_cast<char *>(&userRoleSize), sizeof(userRoleSize));
        UserRole.resize(userRoleSize);
        file.read(reinterpret_cast<char *>(&UserRole[0]), userRoleSize);

        string::size_type usernameSize;
        file.read(reinterpret_cast<char *>(&usernameSize), sizeof(usernameSize));
        Username.resize(usernameSize);
        file.read(reinterpret_cast<char *>(&Username[0]), usernameSize);

        string::size_type passwordSize;
        file.read(reinterpret_cast<char *>(&passwordSize), sizeof(passwordSize));
        Password.resize(passwordSize);
        file.read(reinterpret_cast<char *>(&Password[0]), passwordSize);
    }
};
