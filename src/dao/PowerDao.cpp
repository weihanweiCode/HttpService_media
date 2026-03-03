#include "dao/PowerDao.h"
#include <sqlite3.h>
#include <sstream>
#include <list>
#include <iostream>
#include <string>

using json = nlohmann::json;
 
json PowerDao::getRouteList(int cabinetId) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    json result;
    
    const char* sql = "SELECT id, name, cabinetId FROM power_route WHERE cabinetId =  ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, cabinetId);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            json itemJson;
            itemJson["id"] = sqlite3_column_int(stmt, 0);
            itemJson["name"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            itemJson["cabinetId"] = sqlite3_column_int(stmt, 2);
            result.push_back(itemJson);
        }
    }

    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return result;
}
 
void PowerDao::updateRoute(int id, const std::string& name) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "UPDATE power_route SET name = ? WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, id);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
 