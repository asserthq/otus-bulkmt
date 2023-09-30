#include <iostream>
#include "bulk.h"
#include "console_logger.h"
#include "file_logger.h"

int main(int argc, char** argv)
{
    auto blockSize = 1;

    if(argc > 1)
    {
        blockSize = std::atoi(argv[1]);
    }

    BulkProcessor bulkProc(blockSize);
    ConsoleLogger clog{};
    //FileLogger flog("logs/");

    bulkProc.add_handler(&clog);
    //bulkProc.add_handler(&flog);

    std::string command{};
    while(std::cin >> command)
    {
        bulkProc.process(command);
    }
    bulkProc.shutdown();

    return 0;
}