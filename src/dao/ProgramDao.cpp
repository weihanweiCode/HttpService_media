#include "dao/ProgramDao.h"
#include "dao/Globals.h"
#include <sqlite3.h>
#include <sstream>
#include <list>
#include <iostream>
#include <string>

using json = nlohmann::json;
 
 //节目播放页面
json ProgramDao::getProgramDetails() {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    json result;

    const char* sql = 
        "SELECT p.id, p.name, p.orderId, l.id lightId, l.name, m.id musicId, m.name, v.id videoId, v.name, i.id imgId, i.name, l.duration FROM program p "
        " left join light l ON p.lightId = l.id "
        " left join music m ON p.musicId = m.id "
        " left join video v ON p.videoId = v.id "
        " left join image i ON p.imgId = i.id " 
        " order by p.orderId";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) { 
            json itemJson;
            itemJson["id"]  = sqlite3_column_int(stmt, 0);
            itemJson["name"]  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            itemJson["orderId"] = sqlite3_column_int(stmt, 2);

            itemJson["lightId"]  = sqlite3_column_int(stmt, 3);
            itemJson["lightName"]  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));    
            itemJson["duration"]  = sqlite3_column_int(stmt, 11);    
            
            int musicId = sqlite3_column_int(stmt, 5);
            if(musicId > 0){
                itemJson["musicId"]  = sqlite3_column_int(stmt, 5);
                itemJson["musicName"]  = extractName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));                
            }

            int videoId = sqlite3_column_int(stmt, 7);
            if(videoId > 0){
                itemJson["videoId"]  = sqlite3_column_int(stmt, 7);
                itemJson["videoName"]  = extractName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8)));                
            }

            // if (!optionalField.empty()) {
            //     data["optionalField"] = optionalField;
            // }
            int imgId = sqlite3_column_int(stmt, 9);
            if(imgId > 0){
                itemJson["imgId"]  = sqlite3_column_int(stmt, 9);
                itemJson["imgName"]  = extractName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 10)));                
            }
        
            result.push_back(itemJson);
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return result;
}
 

//节目管理页面
json ProgramDao::getProgramList() {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    json result;
    
    const char* sql = "SELECT id, name, orderId, lightId, musicId, videoId, imgId FROM program order by orderId";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            json itemJson;
            itemJson["id"] = sqlite3_column_int(stmt, 0);
            itemJson["name"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));            
            itemJson["orderId"] = sqlite3_column_int(stmt, 2);
            itemJson["lightId"] = sqlite3_column_int(stmt, 3);
            itemJson["musicId"] = sqlite3_column_int(stmt, 4);
            itemJson["videoId"] = sqlite3_column_int(stmt, 5);
            itemJson["imgId"] = sqlite3_column_int(stmt, 6);
            result.push_back(itemJson);
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return result;
}
 
//节目管理：查询
json ProgramDao::findProgramList(const std::string& name) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    json result;
    
    const char* sql = "SELECT id, name, orderId, lightId, musicId, videoId, imgId FROM program WHERE name LIKE ? order by orderId";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        std::string search_param = "%" + name + "%";
        sqlite3_bind_text(stmt, 1, search_param.c_str(), -1, SQLITE_TRANSIENT);
        
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            json itemJson;
            itemJson["id"] = sqlite3_column_int(stmt, 0);
            itemJson["name"] = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));            
            itemJson["orderId"] = sqlite3_column_int(stmt, 2);
            itemJson["lightId"] = sqlite3_column_int(stmt, 3);
            itemJson["musicId"] = sqlite3_column_int(stmt, 4);
            itemJson["videoId"] = sqlite3_column_int(stmt, 5);
            itemJson["imgId"] = sqlite3_column_int(stmt, 6);
            result.push_back(itemJson);
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return result;
}
 
void ProgramDao::updateProgram(int id, const std::string& name, int lightId, int musicId, int videoId, int imgId) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "UPDATE program SET name = ?, lightId = ?, musicId = ?, videoId = ?, imgId = ? WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, lightId);
        sqlite3_bind_int(stmt, 3, musicId);
        sqlite3_bind_int(stmt, 4, videoId);
        sqlite3_bind_int(stmt, 5, imgId);
        sqlite3_bind_int(stmt, 6, id);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
 
void ProgramDao::saveProgram(const std::string& name, int lightId, int musicId, int videoId, int imgId) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "INSERT INTO program (name, orderId, lightId, musicId, videoId, imgId) VALUES (?, 1, ?, ?, ?, ?)";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, lightId);
        sqlite3_bind_int(stmt, 3, musicId);
        sqlite3_bind_int(stmt, 4, videoId);
        sqlite3_bind_int(stmt, 5, imgId);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}
 
ProgramDetailDto ProgramDao::findProgram(int id) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    // json itemJson;
    ProgramDetailDto programDetail;

    const char* sql = 
        "SELECT p.id, p.name, p.orderId, lightId, l.name, musicId, m.name, videoId, v.name, imgId, i.name FROM program p "
        " left join light l ON p.lightId = l.id "
        " left join music m ON p.musicId = m.id  "
        " left join video v ON p.videoId = v.id "
        " left join image i ON p.imgId = i.id "
        " where p.id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {                        
            programDetail.id  = sqlite3_column_int(stmt, 0);
            programDetail.name  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            programDetail.orderId = sqlite3_column_int(stmt, 2);

            programDetail.lightId  = sqlite3_column_int(stmt, 3);
            programDetail.lightName  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));                

            // std::cout << "music id: "  << sqlite3_column_int(stmt, 5) << std::endl;
            // std::cout << "music name: "  << reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)) << std::endl;

            int musicId = sqlite3_column_int(stmt, 5);
            if(musicId > 0){
                programDetail.musicId  = musicId;
                // programDetail.musicName  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));                
                const unsigned char* musicName = sqlite3_column_text(stmt, 6);
                if(musicName != nullptr){
                    programDetail.musicName  = reinterpret_cast<const char*>(musicName);
                }
            }

            int videoId = sqlite3_column_int(stmt, 7);
            if(videoId > 0){
                programDetail.videoId  = videoId;
                // programDetail.videoName  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));   
                
                const unsigned char* videoName = sqlite3_column_text(stmt, 8);
                if(videoName != nullptr){
                    programDetail.videoName  = reinterpret_cast<const char*>(videoName);
                }                
            }

            // if (!optionalField.empty()) {
            //     data["optionalField"] = optionalField;
            // }
            int imgId = sqlite3_column_int(stmt, 9);
            if(imgId > 0){
                programDetail.imgId  = imgId;                
                const unsigned char* imgName = sqlite3_column_text(stmt, 10);
                if(imgName != nullptr){
                    programDetail.imgName  = reinterpret_cast<const char*>(imgName);                
                }
            }
            // programDetail.duration  = sqlite3_column_int(stmt, 11);
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return programDetail;
}
 
void ProgramDao::delProgram(int id) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    
    const char* sql = "DELETE FROM program WHERE id = ?";
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        sqlite3_step(stmt);
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
}

void ProgramDao::sortPrograms(std::vector<int> ids) {
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
        std::string sql = "UPDATE program SET orderId = " + std::to_string(static_cast<int>(i)) + 
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


//用以验证音乐，视频和图片的删除
bool ProgramDao::findProgram(int type, int id) {
    sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
    sqlite3_stmt* stmt;
    // json itemJson;
    bool ret = false;

    const char* sql = "";
    if(type == light_type) {
        sql = "SELECT id FROM program where lightId = ?";
    } else if(type == music_type) {
        sql = "SELECT id FROM program where musicId = ?";
    } else if(type == video_type) {
        sql = "SELECT id FROM program where videoId = ?";
    } else if(type == image_type) {
        sql = "SELECT id FROM program where imageId = ?";
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmt, 1, id);
        if (sqlite3_step(stmt) == SQLITE_ROW) {                        
            ret = sqlite3_column_int(stmt, 0) > 0;
        }
    }
    sqlite3_finalize(stmt);
    DatabaseConnectionPool::getInstance().release_connection(db); 
    return ret;
}
