#include "service/ProgramService.h"
#include <sstream>
#include <list>
#include <iostream>
#include <string>


nlohmann::json ProgramService::getProgramDetails(){
    return programDao.getProgramDetails();
}

void ProgramService::playProgram(int id){
    std::cout << "play program: " << id << std::endl;
    printf("play program\n");
    ProgramDetailDto program = programDao.findProgram(id);
    if(program.id > 0) {
        LightDto lightDto = lightDao.findLight(program.lightId);

        if(program.musicId > 0) {
            MediaService::instance().play("/app/resource/music/" + program.musicName);
        } else {
            MediaService::instance().play("/app/resource/video/" + program.videoName);
        }
        
        if(program.imgId > 0) {
            // program.imgName
        }
    }
}

void ProgramService::pauseProgram(int id){
    std::cout << "pause program: " << id << std::endl;
    MediaService::instance().pause();
}

void ProgramService::resumeProgram(int id){
    std::cout << "resume program: " << id << std::endl;
    MediaService::instance().resume();
}

void ProgramService::recycleProgram(int id){
    std::cout << "recycle program: " << id << std::endl;
}

void ProgramService::blackout(int status){
    std::cout << "blackout status: " << status << std::endl;
}

void ProgramService::adjustVolume(int volumn){
    std::cout << "adjust volume: " << volumn << std::endl;
}
