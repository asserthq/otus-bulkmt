#pragma once

#include "command_observer.h"
#include <fstream>
#include <sstream>
#include <algorithm>

class FileLogger : public CommandHandler
{
public:
    FileLogger(const std::string& relPath = "")
        : m_relPath(relPath), CommandHandler()
    {}

    void handle(const std::vector<std::string>& commandBlock, std::uint64_t firstTime) override
    {
        std::stringstream filePath{};
        filePath << m_relPath << "bulk" << firstTime << ".log";
        std::ofstream logFile(filePath.str());
        if(logFile.is_open())
        {
            std::ranges::copy(commandBlock, std::ostream_iterator<std::string>(logFile, "\n"));
            logFile << "\n\n";
        }
    }

private:
    std::string m_relPath{};
};