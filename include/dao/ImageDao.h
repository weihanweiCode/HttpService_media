#ifndef PISHTTP_IMAGE_H
#define PISHTTP_IMAGE_H

#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include "DatabaseConnectionPool.h"
 
struct ImageDto {
    int id;
    std::string name;
};
 
class ImageDao {
    
public:    
    // nlohmann::json getImageList();
    std::vector<ImageDto> getImageList();
    nlohmann::json findImageList(const std::string& name);
    void updateImage(int id, const std::string& name);
    ImageDto findImage(int id);
    void delImage(int id);
    void delImages(const std::string& ids);
    void insertImages(std::vector<std::string> names);
};
#endif //PISHTTP_IMAGE_H