#include "dao/MusicDao.h"
#include <sqlite3.h>
#include <sstream>
#include <list>
#include <iostream>
#include <string>

using json = nlohmann::json;
 
// json MusicDao::getMusicList() {
//     sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
//     sqlite3_stmt* stmt;
//     json result;
    
//     const char* sql = "SELECT id, name FROM music";
//     if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
//         while (sqlite3_step(stmt) == SQLITE_ROW) {
//             json itemJson;
//             itemJson["id"] = sqlite3_column_int(stmt, 0);
//             itemJson["name"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
//             result.push_back(itemJson);
//         }
//     }
//     sqlite3_finalize(stmt);
//     DatabaseConnectionPool::getInstance().release_connection(db); 
//     return result;
// }
 
std::vector<MusicDto>  MusicDao::getMusicList() {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    std::vector<MusicDto> result;
    
    const char* sql = "SELECT id, name FROM music";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            MusicDto musicDto;
            musicDto.id = sqlite3_column_int(stmt, 0);
            musicDto.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            result.push_back(musicDto);
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return result;
}

json MusicDao::findMusicList(const std::string& name) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    json result;
    
    const char* sql = "SELECT id, name FROM music WHERE name LIKE ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        std::string search_param = "%" + name + "%";
        sqlite3_bind_text(stmt, 1, search_param.c_str(), -1, SQLITE_TRANSIENT);
        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            json itemJson;
            itemJson["id"] = sqlite3_column_int(stmt, 0);
            itemJson["name"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            result.push_back(itemJson);
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return result;
}
 
void MusicDao::updateMusic(int id, const std::string& name) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "UPDATE music SET name = ? WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, id);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
 
MusicDto MusicDao::findMusic(int id) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    MusicDto music;
    
    const char* sql = "SELECT id, name FROM music WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            music.id  = sqlite3_column_int(stmt, 0);
            music.name  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return music;
}
 
void MusicDao::delMusic(int id) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "DELETE FROM music WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
 
void MusicDao::delMusics(const std::string& ids) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;    
    //std::istringstream iss(ids);
    //std::string id;
    const char* sql = "DELETE FROM music WHERE id = ?";
    
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

void MusicDao::insertMusics(std::vector<std::string> fileNames) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;        
    const char* sql = "INSERT INTO music (name) VALUES (?);";
        
    for (const std::string& fileName : fileNames) {
        std::cout << "insert music: " << fileName << std::endl;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, fileName.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt);  
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
