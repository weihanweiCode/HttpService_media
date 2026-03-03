#include "dao/SettingDao.h"
#include <iostream>
#include <sqlite3.h>

using json = nlohmann::json;

nlohmann::json SettingDao::getBasicSetting() {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    json itemJson;
    
    const char* sql = "SELECT languageCode, bgcolourCode, masterip, slaveip FROM setting_basic";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {        
        if (sqlite3_step(stmt) == SQLITE_ROW) {            
            itemJson["languageCode"] = sqlite3_column_int(stmt, 0);
            itemJson["bgColourCode"] = sqlite3_column_int(stmt, 1);
            itemJson["primaryConsoleIp"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            itemJson["backupConsoleIp"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        }        
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return itemJson;
}


void SettingDao::updateBasicSetting(int languageCode, int bgColourCode, 
    const std::string& masterIp, const std::string& slaveIp) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection();
    sqlite3_stmt* stmt;

    if (db) {        
        const char *sql = "INSERT OR REPLACE INTO setting_basic (id, languageCode, bgcolourCode, masterip, slaveip) VALUES (1, ?, ?, ?, ?)";
        // 预编译SQL语句
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, languageCode);
            sqlite3_bind_int(stmt, 2, bgColourCode);
            sqlite3_bind_text(stmt, 3, masterIp.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 4, slaveIp.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt);
        }
        sqlite3_finalize(stmt);
        DatabaseConnectionPool::getInstance().release_connection(db);
    }        
}


nlohmann::json SettingDao::getScheduledProgram() {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    json itemJson;
    
    const char* sql = "SELECT starttime, endtime, programId, is_recycled FROM setting_schedule";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {        
        if (sqlite3_step(stmt) == SQLITE_ROW) {            
            itemJson["startTime"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            itemJson["endTime"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            itemJson["programId"] = sqlite3_column_int(stmt, 2);
            itemJson["_recycled"] = bool(sqlite3_column_int(stmt, 3));
        }        
    }

    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return itemJson;
}


void SettingDao::updateScheduledProgram(const std::string& startTime, const std::string& endTime, int programId, int isRecycled) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection();
    sqlite3_stmt* stmt;

    if (db) {
        const char *sql = "INSERT OR REPLACE INTO setting_schedule (id, starttime, endtime, programId, is_recycled) VALUES (1, ?, ?, ?, ?);";
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, startTime.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, endTime.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmt, 3, programId);
            sqlite3_bind_int(stmt, 4, isRecycled);
            sqlite3_step(stmt);
        }

        sqlite3_finalize(stmt);
        DatabaseConnectionPool::getInstance().release_connection(db);
    }        
}

