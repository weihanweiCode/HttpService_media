#include "dao/DbInitializer.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

DbInitializer::DbInitializer(const std::string& dbPath, const std::string& initSqlPath)
    : dbPath(dbPath), initSqlPath(initSqlPath), db(nullptr) {}

// DbInitializer::DbInitializer(const std::string& dbPath)


// DbInitializer::~DbInitializer() {
//     if (db != nullptr) {
//         sqlite3_close(db);
//         db = nullptr;
//     }
// }

bool DbInitializer::executeStatement(const std::string& sql) {
    char* errMsg = nullptr;
    int result = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (result != SQLITE_OK) {
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

std::string DbInitializer::readSqlFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool DbInitializer::executeSqlScript(const std::string& sqlContent) {
    // 简单分割SQL语句（处理分号+换行的情况）
    std::stringstream ss(sqlContent);
    std::string line;
    std::string currentStatement;

    while (std::getline(ss, line)) {
        // 忽略注释行
        size_t commentPos = line.find("--");
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }

        // 移除行首尾空格
        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) continue;
        
        size_t end = line.find_last_not_of(" \t");
        std::string trimmedLine = line.substr(start, end - start + 1);
        
        currentStatement += trimmedLine + " ";
        
        // 检查是否遇到语句结束符
        if (currentStatement.find(';') != std::string::npos) {
            // 执行当前语句
            if (!executeStatement(currentStatement)) {
                return false;
            }
            currentStatement.clear();
        }
    }

    // 执行最后一条可能没有分号结束的语句
    if (!currentStatement.empty()) {
        if (!executeStatement(currentStatement)) {
            return false;
        }
    }

    return true;
}

bool DbInitializer::isInitialized() {
    // 尝试打开数据库
    int result = sqlite3_open(dbPath.c_str(), &db);
    if (result != SQLITE_OK) {
        return false;
    }

    // 检查是否存在初始化标记表（可根据实际项目修改表名）
    const std::string checkTableSql = "SELECT name FROM users;";
    
    sqlite3_stmt* stmt;
    result = sqlite3_prepare_v2(db, checkTableSql.c_str(), -1, &stmt, nullptr);
    
    if (result != SQLITE_OK) {
        sqlite3_finalize(stmt);
        return false;
    }

    // 如果存在标记表，则认为已初始化
    bool initialized = (sqlite3_step(stmt) == SQLITE_ROW);
    
    sqlite3_finalize(stmt);
    return initialized;
}

bool DbInitializer::initialize() {
    // 如果已经初始化，直接返回成功
    if (isInitialized()) {
        return true;
    }
    
    // 读取SQL初始化文件
    std::string sqlContent = readSqlFile(initSqlPath);
    if (sqlContent.empty()) {
        return false;
    }

    // 执行SQL脚本
    if (!executeSqlScript(sqlContent)) {
        return false;
    }

    // 创建初始化标记表，标记为已初始化
    // const std::string createMetaTableSql = 
    //     "CREATE TABLE IF NOT EXISTS db_metadata ("
    //     "key TEXT PRIMARY KEY,"
    //     "value TEXT,"
    //     "updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
    //     ");"
    //     "INSERT OR IGNORE INTO db_metadata (key, value) "
    //     "VALUES ('initialized', 'true');";

    // return executeStatement(createMetaTableSql);
    return true;
}

std::string DbInitializer::getLastError() const {
    if (db != nullptr) {
        return sqlite3_errmsg(db);
    }
    return "No database connection";
}
