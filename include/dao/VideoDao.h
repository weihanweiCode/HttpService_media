#ifndef PISHTTP_VIDEODAO_H
#define PISHTTP_VIDEODAO_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "DatabaseConnectionPool.h"
 
struct VideoDto {
    int id;
    std::string name;
};
 
class VideoDao {
    
public:    
    std::vector<VideoDto> getVideoList();
    nlohmann::json findVideoList(const std::string& name);
    void updateVideo(int id, const std::string& name);
    VideoDto findVideo(int id);
    void delVideo(int id);
    void delVideos(const std::string& ids);
    void insertVideos(std::vector<std::string> fileNames);
};
#endif //PISHTTP_VIDEODAO_H