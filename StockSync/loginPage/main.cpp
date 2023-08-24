#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "./main.h"
#include "../bcrypt/bcrypt.h"
#include "../bcrypt/node_blf.h"
#include "../bcrypt/openbsd.h"

using namespace std;

User::User(string name_, string address_, string userRole_, string username_, string password_)
{
    Name = name_;
    Address = address_;
    UserRole = userRole_;
    Username = username_;
    Password = password_;
}
string User::GetName()
{
    return Name;
}
string User::GetAddress()
{
    return Address;
}
string User::GetUserRole()
{
    return UserRole;
}
string User::GetUsername()
{
    return Username;
}
void User::HashPassword()
{
    Password = bcrypt::generateHash(Password);
}
void User::AddUser()
{
    this->HashPassword();
    if (this->UserRole == "Admin")
        SaveToFile("Admin.txt");
    if (this->UserRole == "Supplier")
        SaveToFile("Supplier.txt");
    if (this->UserRole == "Client")
        SaveToFile("Client.txt");
}
User User::AuthenticateUser(string username_, string password_)
{
    User user;
    vector<User> users = User::ReadUserFile("Admin.txt");
    for (User user : users)
    {
        if (bcrypt::validatePassword(password_, user.Password))
        {
            if (user.Username == username_)
            {
                return user;
            }
        }
    }
    users = User::ReadUserFile("Supplier.txt");
    for (User user : users)
    {
        if (bcrypt::validatePassword(password_, user.Password))
        {
            if (user.Username == username_)
            {
                return user;
            }
        }
    }
    users = User::ReadUserFile("Client.txt");
    for (User user : users)
    {
        if (bcrypt::validatePassword(password_, user.Password))
        {
            if (user.Username == username_)
            {
                return user;
            }
        }
    }

    return user;
}

void User::SaveToFile(string filename)
{
    ofstream file(filename, ios::app | ios::binary);
    if (!file)
    {
        cout << "Error opening file" << endl;
        return;
    }

    string::size_type nameSize = Name.size();
    file.write(reinterpret_cast<const char *>(&nameSize), sizeof(nameSize));
    file.write(reinterpret_cast<const char *>(&Name[0]), nameSize);

    string::size_type addressSize = Address.size();
    file.write(reinterpret_cast<const char *>(&addressSize), sizeof(addressSize));
    file.write(reinterpret_cast<const char *>(&Address[0]), addressSize);

    string::size_type userRoleSize = UserRole.size();
    file.write(reinterpret_cast<const char *>(&userRoleSize), sizeof(userRoleSize));
    file.write(reinterpret_cast<const char *>(&UserRole[0]), userRoleSize);

    string::size_type usernameSize = Username.size();
    file.write(reinterpret_cast<const char *>(&usernameSize), sizeof(usernameSize));
    file.write(reinterpret_cast<const char *>(&Username[0]), usernameSize);

    string::size_type passwordSize = Password.size();
    file.write(reinterpret_cast<const char *>(&passwordSize), sizeof(passwordSize));
    file.write(reinterpret_cast<const char *>(&Password[0]), passwordSize);

    file.close();
}

vector<User> User::ReadUserFile(string filename)
{
    vector<User> users;
    ifstream file(filename, ios::binary);
    if (!file)
    {
        cout << "Error opening file" << endl;
        return users;
    }

    while (file.peek() != EOF)
    {
        User user;
        user.deserialize(file);
        users.push_back(user);
    }

    file.close();
    return users;
}

bool User::IsEmpty()
{
    if (this->Name.length() != 0)
        return false;
    return true;
}
