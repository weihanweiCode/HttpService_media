#ifndef PISHTTP_USERDAO_H
#define PISHTTP_USERDAO_H

#pragma once
#include <sqlite3.h>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "dao/DatabaseConnectionPool.h" 

struct UserDto {
    int id;
    std::string name;
    std::string password;
    int isAdmin;
};

class UserDao {
    public:
        bool updatePassword(int id, const std::string& oldPassword, const std::string& newPassword);
        nlohmann::json verifyUser(const std::string& name, const std::string& password);
    };    
    
#endif //PISHTTP_APIHANDLER_H    