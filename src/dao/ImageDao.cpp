#include "dao/ImageDao.h"
#include <sqlite3.h>
#include <sstream>
#include <list>
#include <iostream>
#include <string>

using json = nlohmann::json;
 
// json ImageDao::getImageList() {
//     sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
//     sqlite3_stmt* stmt;
//     json result;
    
//     const char* sql = "SELECT id, name FROM image";
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


std::vector<ImageDto>  ImageDao::getImageList() {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    std::vector<ImageDto> result;
    
    const char* sql = "SELECT id, name FROM image";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            ImageDto imageDto;
            imageDto.id = sqlite3_column_int(stmt, 0);
            imageDto.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            result.push_back(imageDto);
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return result;
}


json ImageDao::findImageList(const std::string& name) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    json result;
    
    const char* sql = "SELECT id, name FROM image WHERE name LIKE ?";
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
 
void ImageDao::updateImage(int id, const std::string& name) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "UPDATE image SET name = ? WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, id);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
 
ImageDto ImageDao::findImage(int id) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    ImageDto image;
    
    const char* sql = "SELECT id, name FROM image WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            image.id  = sqlite3_column_int(stmt, 0);
            image.name  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return image;
}
 
void ImageDao::delImage(int id) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "DELETE FROM image WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
 
void ImageDao::delImages(const std::string& ids) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;    
    //std::istringstream iss(ids);
    //std::string id;
    const char* sql = "DELETE FROM image WHERE id = ?";
    
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

void ImageDao::insertImages(std::vector<std::string> fileNames) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;    
    const char* sql = "INSERT INTO image (name) VALUES (?);";
        
    for (const std::string& fileName : fileNames) {
        std::cout << "insert image: " << fileName << std::endl;
        if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_text(stmt, 1, fileName.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_step(stmt);  
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
