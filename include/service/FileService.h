#ifndef PISHTTP_FILE_SERVICE_H
#define PISHTTP_FILE_SERVICE_H
#include <string>
#include <filesystem>
#include <nlohmann/json.hpp>

#pragma once
namespace fs = std::filesystem;

class FileService{
    public:        
        // nlohmann::json getSubDirectories(fs::string directory);
        nlohmann::json getFileNames(std::string directory, std::vector<std::string> extensions);
        void importFiles(std::string srcDir, std::string dstDir, std::vector<std::string> files);        
        void syncAllFiles(std::string srcDir, std::string dstDir);

        nlohmann::json getLightDirectories(std::string rootDir);
        void importLightFiles(std::string srcDir, std::string dstDir, std::vector<std::string> input_dirs);

        void copy_file(const fs::path source, const fs::path destination);
        void copy_directory(const fs::path source_dir, const fs::path dest_dir);

        int initResourceFolder(const fs::path& resourcePath);
    };
#endif //PISHTTP_FILE_SERVICE_H
