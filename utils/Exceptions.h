#pragma once

#include <exception>
#include <string>

class GameException : public std::exception {
protected:
    std::string message;
public:
    explicit GameException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class InvalidCommandException : public GameException {
public:
    explicit InvalidCommandException(const std::string& cmd = "unknown")
        : GameException("Invalid command: " + cmd) {}
};

class AuthenticationException : public GameException {
public:
    explicit AuthenticationException(const std::string& msg = "Authentication required!")
        : GameException(msg) {}
};

class NotFoundException : public GameException {
public:
    explicit NotFoundException(const std::string& item = "Item")
        : GameException("Not found: " + item) {}
};

class NotEnoughItemsException : public GameException {
public:
    explicit NotEnoughItemsException(const std::string& item = "item")
        : GameException("Not enough: " + item) {}
};

class InsufficientFundsException : public GameException {
public:
    InsufficientFundsException(int required, int available)
        : GameException("Not enough money! Required: " + std::to_string(required)
                        + ", Available: " + std::to_string(available)) {}
};

class CapacityFullException : public GameException {
public:
    explicit CapacityFullException(const std::string& what = "capacity")
        : GameException("Cannot " + what) {}
};

class NegativeQuantityException : public GameException {
public:
    explicit NegativeQuantityException(const std::string& what = "quantity")
        : GameException("Cannot " + what) {}
};