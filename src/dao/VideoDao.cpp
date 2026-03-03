#include "dao/VideoDao.h"
#include <sqlite3.h>
#include <sstream>
#include <list>
#include <iostream>
#include <string>

using json = nlohmann::json;

// json VideoDao::getVideoList() {
//     sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
//     sqlite3_stmt* stmt;
//     json result;
    
//     const char* sql = "SELECT id, name FROM video";
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

std::vector<VideoDto>  VideoDao::getVideoList() {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    std::vector<VideoDto> result;
    
    const char* sql = "SELECT id, name FROM video";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            VideoDto videoDto;
            videoDto.id = sqlite3_column_int(stmt, 0);
            videoDto.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            result.push_back(videoDto);
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return result;
}


json VideoDao::findVideoList(const std::string& name) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    json result;    
    const char* sql = "SELECT id, name FROM Video WHERE name LIKE ?";
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
 
void VideoDao::updateVideo(int id, const std::string& name) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "UPDATE video SET name = ? WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, id);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
 
VideoDto VideoDao::findVideo(int id) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    VideoDto video;
    
    const char* sql = "SELECT id, name FROM video WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            video.id  = sqlite3_column_int(stmt, 0);
            video.name  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return video;
}
 
void VideoDao::delVideo(int id) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "DELETE FROM video WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
 
void VideoDao::delVideos(const std::string& ids) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;    
    //std::istringstream iss(ids);
    //std::string id;
    const char* sql = "DELETE FROM video WHERE id = ?";
    
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


void VideoDao::insertVideos(std::vector<std::string> fileNames) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;    
    const char* sql = "INSERT INTO video (name) VALUES (?);";
        
    for (const std::string& fileName : fileNames) {
        std::cout << "insert video: " << fileName << std::endl;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, fileName.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt);  
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
