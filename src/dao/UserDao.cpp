#include "dao/UserDao.h"
#include <iostream>
#include <sqlite3.h>

using json = nlohmann::json;

bool UserDao::updatePassword(int id, const std::string& oldPassword, const std::string& newPassword) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection();

    if (db) {
        sqlite3_stmt* stmt;
        const char * verifySql = "select 1 from users where id = ? and password = ?;";
        
        bool isValidPassword = false;
        if (sqlite3_prepare_v2(db, verifySql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_bind_text(stmt, 2, oldPassword.c_str(), -1, SQLITE_TRANSIENT);     
                        
            int stepResult = sqlite3_step(stmt);
            if (stepResult == SQLITE_ROW) {
                isValidPassword = true;
                // userFlag = sqlite3_column_int(stmt, 0);
            }   
        }

        if (isValidPassword){
            const char *sql = "update users set password = ? where id = ?;";
            // 预编译SQL语句
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, newPassword.c_str(), -1, SQLITE_TRANSIENT);
                sqlite3_bind_int(stmt, 2, id);
                sqlite3_step(stmt);
            }
        }

        sqlite3_finalize(stmt);
        DatabaseConnectionPool::getInstance().release_connection(db);
        return isValidPassword;
    } else {
        return false;
    }            
}


json UserDao::verifyUser(const std::string& username, const std::string& password) {
    json itemJson;    
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection();

    if (db) {
        sqlite3_stmt* stmt;        
        const char *sql = "SELECT id, name, isAdmin FROM users WHERE name =? AND password =?;";

        // 预编译SQL语句
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);            
        }

        // 执行查询
        int stepResult = sqlite3_step(stmt);
        if (stepResult == SQLITE_ROW) {
            itemJson["userId"] = sqlite3_column_int(stmt, 0); 
            itemJson["userName"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            itemJson["isAdmin"] = (sqlite3_column_int(stmt, 2) != 0);
            itemJson["message"] = "success";
            // userLevel = sqlite3_column_int(stmt, 0);
        } else {
            const char *sql = "SELECT id, name, isAdmin FROM users WHERE name =?";
            // 预编译SQL语句
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
                sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);       
            }                

            int stepResult = sqlite3_step(stmt);
            if (stepResult != SQLITE_ROW) {
                itemJson["userId"] = -1;
                itemJson["userName"] = "";
                itemJson["isAdmin"] = false;
                itemJson["message"] = "user incorrect";    
            } else {
                itemJson["userId"] = -2; 
                itemJson["userName"] = "";
                itemJson["isAdmin"] = false;                       
                itemJson["message"] = "password incorrect"; 
            }
        }

        sqlite3_finalize(stmt);
        DatabaseConnectionPool::getInstance().release_connection(db);
    }
    
    return itemJson;
}