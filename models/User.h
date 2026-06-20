#pragma once

#include <iostream>
#include <string>

class Barn;
class Farm;

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

    virtual int  getBalance() const { return 0; }
    virtual int  getScore()   const { return 0; }
    virtual int  getCycle()   const { return 0; }
    virtual void addBalance(int)    {}
    virtual void removeBalance(int) {}
    virtual void addScore(int)      {}
    virtual void advanceCycle()     {}
    virtual void setCycle(int)      {}
    virtual void addItem(const std::string&, int) {}
    virtual bool removeItem(const std::string&, int) { return false; }
    virtual int  getItemQty(const std::string&) const { return 0; }
    virtual void printBarn() const  {}
    virtual Barn& getBarn()         { static Barn dummy; return dummy; }
    virtual Farm& getFarm()         { static Farm dummy; return dummy; }
    virtual void checkFarm() const  {}
    virtual void expandCropland()   {}
    virtual void expandFarmland()   {}
    virtual bool isPlayer() const   { return false; }
};
