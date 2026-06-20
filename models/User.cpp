#include "../models/User.h"

User::User(int id_, const std::string& username_, const std::string& password_)
    : id(id_), username(username_), password(password_) {}

User::~User() = default;

int User::getId() const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }

bool User::checkPassword(const std::string& pass) const { return password == pass; } // TODO

void User::profileInfo() const {
    std::cout << "ID: " << id << "\n"
    << "Username: " << username  << "\n"
    << "Type: " << getType() << "\n";
}

void User::changePassword(const std::string& oldPass, const std::string& newPass) {
    if (password != oldPass) {
        std::cout << "Incorrect old password!\n";
        return;
    }
    if (newPass.size() < 3) {
        std::cout << "Password too short!\n";
        return;
    }
    password = newPass;
    std::cout << "Password changed successfully!\n";
}
