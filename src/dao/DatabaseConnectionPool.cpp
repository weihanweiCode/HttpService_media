#include "dao/DatabaseConnectionPool.h" 
#include <iostream> 

DatabaseConnectionPool& DatabaseConnectionPool::getInstance() {
    static DatabaseConnectionPool instance;
    return instance;
}

DatabaseConnectionPool::DatabaseConnectionPool() {
    for (int i = 0; i < POOL_SIZE; ++i) {
        sqlite3* db;
        if (sqlite3_open_v2(DB_NAME.c_str(), &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, nullptr) == SQLITE_OK) {
            db_pool.push(db);
            // 创建表
            const char* sql = "CREATE TABLE IF NOT EXISTS users ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                              "name TEXT NOT NULL,"
                              "password TEXT NOT NULL);";
            char* errMsg;
            if (sqlite3_exec(db, sql, nullptr, 0, &errMsg) != SQLITE_OK) {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
        }
    }
}

DatabaseConnectionPool::~DatabaseConnectionPool() {
    while (!db_pool.empty()) {
        sqlite3* db = db_pool.front();
        db_pool.pop();
        sqlite3_close(db);
    }
}

sqlite3* DatabaseConnectionPool::acquire_connection() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!db_pool.empty()) {
        sqlite3* db = db_pool.front();
        db_pool.pop();
        return db;
    }
    return nullptr;
}

void DatabaseConnectionPool::release_connection(sqlite3* db) {
    std::lock_guard<std::mutex> lock(mutex_);
    db_pool.push(db);
}    