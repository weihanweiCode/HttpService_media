#include "service/ProgramManagerService.h"
#include <sstream>
#include <list>
#include <iostream>
#include <string>
#include <cstdio>

using json = nlohmann::json;

nlohmann::json ProgramManagerService::getProgramList(){
    return programDao.getProgramList();
}

nlohmann::json ProgramManagerService::findProgramList(const std::string& name){
    return programDao.findProgramList(name);
}

void ProgramManagerService::delProgram(int id) {
    programDao.delProgram(id);
}

void ProgramManagerService::playProgram(int programId){
    printf("play program\n");
    ProgramDetailDto program = programDao.findProgram(programId);
    if(program.id > 0) {
        LightDto lightDto = lightDao.findLight(program.lightId);

        if(program.musicId > 0) {
            MediaService::instance().play("/app/resource/video/" + program.musicName);
        } else {
            MediaService::instance().play("/app/resource/video/" + program.videoName);
        }
        
        if(program.imgId > 0) {
            // program.imgName
        }
    }
}

void ProgramManagerService::sortPrograms(std::vector<int> ids) {
    printf("reorder program\n");
    programDao.sortPrograms(ids);
}

//数据用来初始化更新页面
json ProgramManagerService::findProgram(int id){
    json itemJson;
    ProgramDetailDto program = programDao.findProgram(id);
    
    if(program.id > 0) {
        itemJson["id"]  = program.id;
        itemJson["name"]  = program.name;
        itemJson["orderId"] = program.orderId;

        itemJson["lightId"]  = program.lightId;
        itemJson["lightName"]  = program.lightName;

        itemJson["musicId"]  = program.musicId;
        itemJson["musicName"]  = program.musicName;

        itemJson["videoId"]  = program.videoId;
        itemJson["videoName"]  = program.videoName;

        itemJson["imgId"]  = program.imgId;
        itemJson["imgName"]  = program.imgName;
    }
    return itemJson;
}

// json ProgramDao::findProgram(int id) {
//     sqlite3* db = DatabaseConnectionPool::getInstance().acquire_connection(); 
//     sqlite3_stmt* stmt;
//     json itemJson;
//     //ProgramDetailDto program;

//     const char* sql = 
//         "SELECT p.id, p.name, orderId, lightId, l.name, musicId, m.name, videoId, v.name, imgId, i.name FROM program p "
//         " left join light l ON p.lightId = l.id "
//         " left join music m ON p.musicId = m.id  "
//         " left join video v ON p.videoId = v.id "
//         " left join image i ON p.imgId = i.id "
//         " where p.id = ?";

//     if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) == SQLITE_OK) {
//         sqlite3_bind_int(stmt, 1, id);
//         if (sqlite3_step(stmt) == SQLITE_ROW) {            
//             itemJson["id"]  = sqlite3_column_int(stmt, 0);
//             itemJson["name"]  = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
//             itemJson["orderId"] = sqlite3_column_int(stmt, 2);

//             itemJson["lightId"]  = sqlite3_column_int(stmt, 3);
//             itemJson["light_name"]  = sqlite3_column_int(stmt, 4);

//             itemJson["musicId"]  = sqlite3_column_int(stmt, 5);
//             itemJson["music_name"]  = sqlite3_column_int(stmt, 6);

//             itemJson["videoId"]  = sqlite3_column_int(stmt, 7);
//             itemJson["video_name"]  = sqlite3_column_int(stmt, 8);

//             itemJson["imgId"]  = sqlite3_column_int(stmt, 9);
//             itemJson["img_name"]  = sqlite3_column_int(stmt, 10);
//         }
//     }
//     sqlite3_finalize(stmt);
//     DatabaseConnectionPool::getInstance().release_connection(db); 
//     return itemJson;
// }


//更新节目
void ProgramManagerService::updateProgram(int id, const std::string& name, int lightId, int musicId, int videoId, int imgId) {
    programDao.updateProgram(id, name, lightId, musicId, videoId, imgId);
} 

//保存新节目
void ProgramManagerService::saveProgram(const std::string& name, int lightId, int musicId, int videoId, int imgId) {
    programDao.saveProgram(name, lightId, musicId, videoId, imgId);
}
