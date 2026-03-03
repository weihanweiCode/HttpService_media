#ifndef PISHTTP_DB_CONNECTION_H
#define PISHTTP_DB_CONNECTION_H

#include <queue>
#include <mutex>
#include <sqlite3.h>

class DatabaseConnectionPool {
public:
    static DatabaseConnectionPool& getInstance();
    sqlite3* acquire_connection();
    void release_connection(sqlite3* db);

private:
    DatabaseConnectionPool();
    ~DatabaseConnectionPool();
    DatabaseConnectionPool(const DatabaseConnectionPool&) = delete;
    DatabaseConnectionPool& operator=(const DatabaseConnectionPool&) = delete;

    std::queue<sqlite3*> db_pool;
    std::mutex mutex_;
    const std::string DB_NAME = "/app/test.db";
    const int POOL_SIZE = 1;
};    
#endif //PISHTTP_DB_CONNECTION_H
