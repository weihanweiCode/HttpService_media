#ifndef SQLITE_INITIALIZER_H
#define SQLITE_INITIALIZER_H

#include <string>
#include <sqlite3.h>
#include "DatabaseConnectionPool.h"

class DbInitializer {
private:
    std::string dbPath;
    std::string initSqlPath;
    sqlite3* db;

    // 执行单条SQL语句
    bool executeStatement(const std::string& sql);
    
    // 读取SQL文件内容
    std::string readSqlFile(const std::string& filePath);
    
    // 分割SQL语句（处理多行和分号分隔的语句）
    bool executeSqlScript(const std::string& sqlContent);

public:
    // 构造函数：数据库路径和初始化SQL文件路径
    explicit DbInitializer(const std::string& dbPath, const std::string& initSqlPath);
    // explicit DbInitializer(const std::string& dbPath);

    // ~DbInitializer();

    // 检查数据库是否已初始化
    bool isInitialized();
    
    // 初始化数据库（如果未初始化）
    bool initialize();
    
    // 获取最后一次错误信息
    std::string getLastError() const;
};

#endif // SQLITE_INITIALIZER_H
