#include "dao/Globals.h"
#include "service/LightRecordService.h"
#include <sstream>
#include <list>
#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>

namespace fs = std::filesystem;

bool LightRecordService::startRecordLight(int lightType, LightDto lightDto) {
    std::cout << "startRecordLight"  << std::endl;
    const fs::path tmpDir = "/app/resource/light/" + parseMappingName(lightType) + "/tmp";

    try {
        // 处理tmp目录
        if (fs::exists(tmpDir)) {
            std::cout << "删除现有tmp目录..." << std::endl;
            fs::remove_all(tmpDir);
        }

        // 创建新的tmp目录
        std::cout << "创建新的tmp目录..." << std::endl;
        fs::create_directory(tmpDir);

        if(lightDto.port1 > 0) {
            std::string filename = std::to_string(lightDto.port1) + ".rec";
            std::ofstream(tmpDir / filename).close();
        }
        if(lightDto.port2 > 0) {
            std::string filename = std::to_string(lightDto.port2) + ".rec";
            std::ofstream(tmpDir / filename).close();
        }
        if(lightDto.port3 > 0) {
            std::string filename = std::to_string(lightDto.port3) + ".rec";
            std::ofstream(tmpDir / filename).close();
        }
        if(lightDto.port4 > 0) {
            std::string filename = std::to_string(lightDto.port4) + ".rec";
            std::ofstream(tmpDir / filename).close();
        }

        std::cout << "startRecordLight: create file successfully"  << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "文件系统操作错误: " << e.what() << std::endl;
        return false;
    }

    return true;
}
 
void LightRecordService::stopRecordLight(int lightType) {
    std::cout << "stopRecordLight"  << std::endl;
}
 
void LightRecordService::testRecordedLight(int lightType) {
    std::cout << "testRecordedLight: "  << std::endl;
}

void LightRecordService::stopTestRecordedLight(int lightType){
    std::cout << "stopTestRecordedLight: "  << std::endl;
}

void LightRecordService::truncRecordedLight(int lightType, int milliSeconds) {
    std::cout << "truncRecordedLight: "  << std::endl;
}

void LightRecordService::saveLight(int lightType, LightDto lightDto) {
    std::cout << "saveLight"  << std::endl;
    std::string subpath = parseMappingName(lightType);
    const fs::path oldPath = "/app/resource/light/" + subpath + "/tmp";
    const fs::path newPath = "/app/resource/light/" + subpath + "/" + lightDto.name;

    try {
        if (!fs::exists(oldPath)) {
            std::cerr << "错误: 原文件不存在" << std::endl;
        }
        
        // 重命名文件
        fs::rename(oldPath, newPath);
        std::cout << "saveLight: rename successfully"  << std::endl;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "文件系统操作错误: " << e.what() << std::endl;
    }

    lightDao.saveLight(lightDto);
}


std::string LightRecordService::verifyLightName(std::string lightName){    
    bool isExisting = lightDao.hasDuplicateName(lightName);
    return isExisting ? "fail" : "success";
}


std::string LightRecordService::parseMappingName(int lightType) {
    std::string name;
    if(lightType == light_type_light){
        name = "light";
    } else if(lightType == light_type_scene_lamp){
        name = "lamp";
    } else if(lightType == light_type_scene_channel){
        name = "channel";
    }
    return name;
}
