#ifndef PISHTTP_GLOBALS_H
#define PISHTTP_GLOBALS_H

#pragma once
#include <string>

inline int light_type = 1; 
inline int music_type = 2; 
inline int video_type = 3; 
inline int image_type = 4; 

inline int light_type_light = 1; 
inline int light_type_scene_lamp = 2; 
inline int light_type_scene_channel = 3; 

inline const std::string& db_path = "/app/test.db";
inline const std::string& init_sql_file = "../resources/init.sql";
inline const std::string& resource_path = "/app/resources";

#endif //PISHTTP_GLOBALS_H
