#include <pistache/endpoint.h>
#include "handler/ApiHandler.h"
#include "service/FileService.h"
#include "dao/DbInitializer.h"
#include "dao/Globals.h"
// #include "dao/DatabaseConnectionPool.h" 

using namespace Pistache;

int main() {
    const std::string db_name = "/app/test.db";  
    // DbInitializer dbInit(dbPath);
    // std::string dbPath = "mydatabase.db";

    DbInitializer dbInit(db_path, init_sql_file);
    // initializer.initialize();

    if (dbInit.isInitialized()) {
        std::cout << "数据库已经初始化过，无需重复初始化。" << std::endl;
    } else {
        std::cout << "检测到数据库未初始化，开始初始化..." << std::endl;
        if (dbInit.initialize()) {
            std::cout << "数据库初始化完成！" << std::endl;
        } else {
            std::cerr << "数据库初始化失败！" << std::endl;
            return 1;
        }        
    }

    FileService fileService; 
    fileService.initResourceFolder(resource_path);

    Address addr(Ipv4::any(), Port(8080));
    auto opts = Http::Endpoint::options().threads(1).flags(Pistache::Tcp::Options::ReuseAddr);
    Http::Endpoint server(addr);
    server.init(opts);
    server.setHandler(Http::make_handler<ApiHandler>());

    server.serve();
    std::cout << "1. Stopping new connections..." << std::endl;
    server.shutdown();
    return 0;
}
