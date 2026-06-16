#pragma once

#include <iostream>
#include <string>

class User {
protected:
    int id;
    std::string username;
    std::string password;

public:
    User(int id, const std::string& username, const std::string& password);
    virtual ~User();

    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    bool checkPassword(const std::string& pass) const;

    virtual std::string getType() const = 0;
    virtual void profileInfo() const;
    void changePassword(const std::string& oldPass, const std::string& newPass);
};
