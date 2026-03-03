#include "service/FileService.h"
#include <fstream> 
#include <sstream>
#include <list>
#include <iostream>
#include <string>
#include <cstdio>

namespace fs = std::filesystem;

nlohmann::json FileService::getFileNames(std::string directory, std::vector<std::string> extensions) {
    nlohmann::json audio_files;

    try {
        for (const auto& entry : fs::recursive_directory_iterator(directory)) {
            if (entry.is_regular_file()) {
                std::string ext = entry.path().extension().string();
                std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower); // 统一转为小写
                if (std::find(extensions.begin(), extensions.end(), ext) != extensions.end()) {
                    audio_files.push_back(entry.path().filename().string());
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    std::cout << "---------to_import: "  << audio_files << std::endl;
    return audio_files;
}


void FileService::importFiles(std::string srcDir, std::string dstDir, std::vector<std::string> files) {
    printf("import file\n");
    
    try {
        for (const auto& filename : files) {
            const fs::path src_path = fs::path(srcDir + filename);
            // const fs::path dst_path = fs::path(dstDir + "/" + filename);
            // const fs::path src_path = fs::path(filename);
            const fs::path dst_path = fs::path(dstDir);

            if (!fs::exists(src_path)) {
                std::cerr << "Warning: source file no exists - " << src_path << std::endl;
                continue;
            }

            // 执行复制（覆盖已存在文件）
            fs::copy(src_path, dst_path, fs::copy_options::overwrite_existing);
            std::cout << "copied: " << src_path << " → " << dst_path << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void FileService::syncAllFiles(std::string srcDir, std::string dstDir){
    const fs::path src_path = fs::path(srcDir);
    const fs::path dst_path = fs::path(dstDir);

    try {
        if (fs::exists(src_path)) {
            fs::copy(src_path, dst_path, fs::copy_options::overwrite_existing);
            std::cout << "copied: " << src_path << " → " << dst_path << std::endl;
        } else {
            std::cerr << "Warning: source file no exists - " << src_path << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }    
}


// 用以导入灯光
nlohmann::json FileService::getLightDirectories(std::string rootDir) {
    nlohmann::json audio_files;
    
    // 检查目录是否存在
    if (!fs::exists(rootDir) || !fs::is_directory(rootDir)) {
        std::cerr << "Error: " << rootDir << " is not a valid directory." << std::endl;
        return audio_files;
    }

    try {
        // 遍历第一级目录
        for (const auto& first_level : fs::directory_iterator(rootDir)) {
            if (!first_level.is_directory()) {
                continue;
            }

            std::string first_level_name = first_level.path().filename().string();

            // 遍历第二级目录
            for (const auto& second_level : fs::directory_iterator(first_level.path())) {
                if (second_level.is_directory()) {
                    std::string second_level_name = second_level.path().filename().string();
                    std::string fullName = first_level_name + "/" + second_level_name;
                    audio_files.push_back(fullName);
                    // std::cout << first_level_name << "/" << second_level_name << std::endl;
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return audio_files;
}


void FileService::importLightFiles(std::string srcDir, std::string dstDir, std::vector<std::string> input_dirs) {
    try {
        // 确保目标目录存在
        // fs::create_directories(target_dir);

        // 遍历输入的目录列表
        for (const auto& dir : input_dirs) {
            fs::path full_path = fs::path(srcDir) / dir;

            if (!fs::exists(full_path)) {
                std::cerr << "警告：目录不存在 - " << full_path << std::endl;
                continue;
            }

            // if (!fs::is_directory(full_path)) {
            //     std::cerr << "警告：不是目录 - " << full_path << std::endl;
            //     continue;
            // }

            // 遍历该目录下的所有文件
            for (const auto& entry : fs::directory_iterator(full_path)) {
                fs::copy(entry, dstDir, fs::copy_options::overwrite_existing);
                
                // if (entry.is_regular_file()) {
                //     fs::path source_file = entry.path();
                //     fs::path target_file = fs::path(target_dir) / source_file.filename();

                //     try {
                //         fs::copy_file(source_file, target_file, fs::copy_options::overwrite_existing);
                //         std::cout << "已复制: " << source_file << " -> " << target_file << std::endl;
                //     } catch (const fs::filesystem_error& e) {
                //         std::cerr << "复制失败: " << e.what() << std::endl;
                //     }
                // }
            }
            std::cout << "已复制: " << dir << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "文件系统错误: " << e.what() << std::endl;
        // return 1;
    } catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        // return 1;
    }
}

// void FileService::importFilesForLight(std::string srcDir, std::string dstDir, std::vector<std::string> files) {
//     printf("import file\n");
    
//     try {
//         for (const auto& filename : files) {
//             const fs::path src_path = fs::path(srcDir + filename);
//             // const fs::path dst_path = fs::path(dstDir + "/" + filename);
//             // const fs::path src_path = fs::path(filename);
//             const fs::path dst_path = fs::path(dstDir);

//             if (!fs::exists(src_path)) {
//                 std::cerr << "Warning: source file no exists - " << src_path << std::endl;
//                 continue;
//             }

//             // 执行复制（覆盖已存在文件）
//             fs::copy(src_path, dst_path, fs::copy_options::overwrite_existing);
//             std::cout << "copied: " << src_path << " → " << dst_path << std::endl;
//         }
//     } catch (const fs::filesystem_error& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }
// }

// 复制单个文件
void FileService::copy_file(const fs::path source, const fs::path destination) {
    try {
        // 打开源文件和目标文件
        std::ifstream src(source, std::ios::binary);
        std::ofstream dest(destination, std::ios::binary);
        
        if (!src) {
            throw std::runtime_error("无法打开源文件: " + source.string());
        }
        if (!dest) {
            throw std::runtime_error("无法创建目标文件: " + destination.string());
        }
        
        // 复制文件内容
        dest << src.rdbuf();
        
        // 复制文件权限
        fs::permissions(destination, fs::status(source).permissions());
        
        std::cout << "已复制文件: " << source << " -> " << destination << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "复制文件时出错: " << e.what() << std::endl;
    }
}

// 递归复制目录
void FileService::copy_directory(const fs::path source_dir, const fs::path dest_dir) {
    try {
        // 检查源目录是否存在
        if (!fs::exists(source_dir) || !fs::is_directory(source_dir)) {
            throw std::runtime_error("源目录不存在或不是一个目录: " + source_dir.string());
        }
        
        // 创建目标目录（如果不存在）
        if (!fs::exists(dest_dir)) {
            fs::create_directories(dest_dir);
            std::cout << "已创建目录: " << dest_dir << std::endl;
        }
        
        // 遍历源目录中的所有条目
        for (const auto& entry : fs::directory_iterator(source_dir)) {
            const auto& source_path = entry.path();
            const auto& dest_path = dest_dir / source_path.filename();
            
            if (fs::is_directory(source_path)) {
                // 如果是目录，递归复制
                copy_directory(source_path, dest_path);
            }
            else if (fs::is_regular_file(source_path)) {
                // 如果是文件，直接复制
                copy_file(source_path, dest_path);
            }
            else {
                std::cout << "跳过非文件和非目录项: " << source_path << std::endl;
            }
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "文件系统错误: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
    }
}


int FileService::initResourceFolder(const fs::path& basePath) {
    try {
        // 1. 判断 /app/resource 是否存在，不存在则创建
        if (!fs::exists(basePath)) {
            std::cout << "目录 " << basePath << " 不存在，正在创建..." << std::endl;
            if (fs::create_directory(basePath)) {
                std::cout << "目录 " << basePath << " 创建成功。" << std::endl;
            } else {
                std::cerr << "目录 " << basePath << " 创建失败！" << std::endl;
                return 1;
            }
        } else {
            std::cout << "目录 " << basePath << " 已存在，无需创建。" << std::endl;
        }

        // 2. 创建子目录：music, video, light
        std::vector<std::string> subDirs = {"light", "music", "video", "image"};
        for (const auto& dir : subDirs) {
            fs::path dirPath = fs::path(basePath) / dir;
            if (!fs::exists(dirPath)) {
                std::cout << "子目录 " << dirPath << " 不存在，正在创建..." << std::endl;
                if (fs::create_directory(dirPath)) {
                    std::cout << "子目录 " << dirPath << " 创建成功。" << std::endl;
                } else {
                    std::cerr << "子目录 " << dirPath << " 创建失败！" << std::endl;
                    // 可以选择继续而不是退出
                }
            } else {
                std::cout << "子目录 " << dirPath << " 已存在，无需创建。" << std::endl;
            }
        }

        // 2. 创建light子目录：light, channel
        std::vector<std::string> lightSubDirs = {"light", "lamp", "channel"};
        for (const auto& dir : lightSubDirs) {
            fs::path dirPath = fs::path(basePath / "light") / dir;
            if (!fs::exists(dirPath)) {
                std::cout << "子目录 " << dirPath << " 不存在，正在创建..." << std::endl;
                if (fs::create_directory(dirPath)) {
                    std::cout << "子目录 " << dirPath << " 创建成功。" << std::endl;
                } else {
                    std::cerr << "子目录 " << dirPath << " 创建失败！" << std::endl;
                    // 可以选择继续而不是退出
                }
            } else {
                std::cout << "子目录 " << dirPath << " 已存在，无需创建。" << std::endl;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "文件系统错误: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "发生异常: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "目录结构初始化完成。" << std::endl;
    return 0;
}