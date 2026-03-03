#include "dao/LightDao.h"
#include <sqlite3.h>
#include <sstream>
#include <list>
#include <iostream>
#include <string>

using json = nlohmann::json;

//为了灯光和场景共用代码，所以传入两个lightType(场景包括两种type)，灯光只有一个lightType，传入相同即可
json LightDao::getLightList(int lightType1, int lightType2) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    json result;

    const char* sql = "SELECT id, name, lightType, orderId FROM light where lightType in (?, ?) order by orderId";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, lightType1);
        sqlite3_bind_int(stmt, 2, lightType2);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            json itemJson;
            itemJson["id"] = sqlite3_column_int(stmt, 0);
            itemJson["name"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            itemJson["lightType"] = sqlite3_column_int(stmt, 2);
            itemJson["orderId"] = sqlite3_column_int(stmt, 3);
            result.push_back(itemJson);
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return result;
}
 
//为了灯光和场景共用代码，所以传入两个lightType，灯光只有一个lightType，传入相同即可
json LightDao::findLightList(int lightType1, int lightType2, const std::string& name) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    json result;
    
    const char* sql = "SELECT id, name, lightType, orderId FROM light WHERE lightType in (?, ?) and name LIKE ? order by orderId";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {       
        std::string search_param = "%" + name + "%";
        sqlite3_bind_int(stmt, 1, lightType1);
        sqlite3_bind_int(stmt, 2, lightType2);
        sqlite3_bind_text(stmt, 3, search_param.c_str(), -1, SQLITE_TRANSIENT);
        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            json itemJson;
            itemJson["id"] = sqlite3_column_int(stmt, 0);
            itemJson["name"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            itemJson["lightType"] = sqlite3_column_int(stmt, 2);
            itemJson["orderId"] = sqlite3_column_int(stmt, 3);
            result.push_back(itemJson);
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return result;
}
 
 
LightDto LightDao::findLight(int id) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    LightDto light;

    const char* sql = 
        " SELECT id, name, lightType, port1, param1, port2, param2, " 
        " port3, param3, port4, param4 FROM light WHERE id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            light.id  = sqlite3_column_int(stmt, 0);
            light.name  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            light.lightType  = sqlite3_column_int(stmt, 2);

            light.port1  = sqlite3_column_int(stmt, 3);
            light.param1  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

            light.port2  = sqlite3_column_int(stmt, 5);
            light.param2  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));

            light.port3  = sqlite3_column_int(stmt, 7);
            light.param3  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));

            light.port4  = sqlite3_column_int(stmt, 9);
            light.param4  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10));
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return light;
}

void LightDao::updateLight(int id, const std::string& name) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "UPDATE light SET name = ? WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, id);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
 
void LightDao::delLight(int id) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "DELETE FROM light WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
 
void LightDao::delLights(const std::string& ids) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM light WHERE id = ?";

    std::stringstream ss(ids);
    std::string item;
    while (std::getline(ss, item, '-')) {
        std::cout << "delete id: " << item << std::endl;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, std::stoi(item));
            sqlite3_step(stmt);  
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}

// TODO: to confirm ids format 
void LightDao::sortLights(std::vector<int> ids) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    char* errMsg = nullptr;

    // 开启事务以提高性能
    int rc = sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "开启事务时出错: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return;
    }

    for (size_t i = 0; i < ids.size(); ++i) {
        std::string sql = "UPDATE light SET orderId = " + std::to_string(static_cast<int>(i)) + 
                          " WHERE id = " + std::to_string(ids[i]) + ";";

        rc = sqlite3_exec(db, sql.c_str(), nullptr, 0, &errMsg);
        if (rc != SQLITE_OK) {
            std::cerr << "执行 SQL 语句时出错: " << errMsg << std::endl;
            sqlite3_free(errMsg);
            // 回滚事务
            sqlite3_exec(db, "ROLLBACK;", nullptr, 0, nullptr);
            return;
        }
    }

    // 提交事务
    rc = sqlite3_exec(db, "COMMIT;", nullptr, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "提交事务时出错: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    
    DatabaseConnectionPool::getInstance().release_connection(db); 
}


void LightDao::saveLight(LightDto lightBo) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = 
        " INSERT INTO light (name, lightType, duration, orderId, "
        "    port1, param1, port2, param2, port3, param3, port4, param4) "
        " VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, lightBo.name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, lightBo.lightType);
        sqlite3_bind_double(stmt, 3, lightBo.duration);
        sqlite3_bind_int(stmt, 4, 0);

        sqlite3_bind_int(stmt, 5, lightBo.port1);
        sqlite3_bind_text(stmt, 6, lightBo.param1.c_str(), -1, SQLITE_TRANSIENT);

        sqlite3_bind_int(stmt, 7, lightBo.port2);
        sqlite3_bind_text(stmt, 8, lightBo.param2.c_str(), -1, SQLITE_TRANSIENT);

        sqlite3_bind_int(stmt, 9, lightBo.port3);
        sqlite3_bind_text(stmt, 10, lightBo.param3.c_str(), -1, SQLITE_TRANSIENT);

        sqlite3_bind_int(stmt, 11, lightBo.port4);
        sqlite3_bind_text(stmt, 12, lightBo.param4.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}

bool LightDao::hasDuplicateName(std::string lightName) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    bool hasValue = false;

    const char* sql = " SELECT id FROM light WHERE name = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, lightName.c_str(), -1, SQLITE_TRANSIENT);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            hasValue = true;
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return hasValue;
}
