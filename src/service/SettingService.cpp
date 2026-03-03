#include "service/SettingService.h"
#include <sstream>
#include <list>
#include <iostream>
#include <string>
#include <cstdio>

using json = nlohmann::json;
bool isConsoleDirected;
            
nlohmann::json SettingService::getBasicSetting(){
    return settingDao.getBasicSetting();
}

void SettingService::updateBasicSetting(int newLanguage, int backgroundColour, 
    const std::string& masterIp, const std::string& slaveIp){
    settingDao.updateBasicSetting(newLanguage, backgroundColour, masterIp, slaveIp);
}

nlohmann::json SettingService::getScheduledProgram(){
    return settingDao.getScheduledProgram();
}

void SettingService::updateScheduledProgram(const std::string& startTime, const std::string& endTime, int programId, int isRecycled){
    settingDao.updateScheduledProgram(startTime, endTime, programId, isRecycled);
}

// json SettingService::getBgcolorData(){
//     json result = json{
//         {"0", "white"},
//         {"1", "black"}      
//     };
//     return result;
// }

json SettingService::getBgcolorData(){
    json result;

    json itemJson1;
    itemJson1["id"] = 1;
    itemJson1["name"] = "白色";
    result.push_back(itemJson1);

    json itemJson2;
    itemJson2["id"] = 2;
    itemJson2["name"] = "黑色";
    result.push_back(itemJson2);

    return result;    
}

// json SettingService::getLanguageData(){
//     json result = json{
//         {"0", "english"},
//         {"1", "chinese"}      
//     };
//     return result;    
// }

json SettingService::getLanguageData(){
    json result;

    json itemJson1;
    itemJson1["id"] = 1;
    itemJson1["name"] = "中文";
    result.push_back(itemJson1);

    json itemJson2;
    itemJson2["id"] = 2;
    itemJson2["name"] = "english";
    result.push_back(itemJson2);

    return result;    
}


void SettingService::importAllFiles(){
    // fileService.syncAllFiles("/app/backup", "/app/resource");
    fs::path source_dir = "/app/backup";
    fs::path dest_dir = "/app/resource";
    
    std::cout << "开始导入资源: " << source_dir << " 到 " << dest_dir << std::endl;
    
    // 执行复制操作
    fileService.copy_directory(source_dir, dest_dir);

    std::cout << "开始导入database: " << source_dir << " 到 " << dest_dir << std::endl;
    fileService.copy_file("/app/backup/test.db", "/app/test.db");
    std::cout << "导入成功" <<  std::endl;
}

void SettingService::backupAllFiles(){
    // fileService.syncAllFiles("/app/resource", "/app/backup");    

    fs::path source_dir = "/app/resource";
    fs::path dest_dir = "/app/backup";
    
    std::cout << "开始备份源目录: " << source_dir << " 到 " << dest_dir << std::endl;
    
    // 执行复制操作
    fileService.copy_directory(source_dir, dest_dir);

    std::cout << "开始备份database: " << source_dir << " 到 " << dest_dir << std::endl;
    fileService.copy_file("/app/test.db", "/app/backup/test.db");
    std::cout << "备份成功" <<  std::endl;
}
