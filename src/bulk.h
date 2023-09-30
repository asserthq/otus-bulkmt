#pragma once

#include "command_observer.h"
#include <vector>
#include <chrono>

class BulkProcessor : public CommandSender
{
public:
    BulkProcessor(std::size_t blockSize)
        : m_blockSize(blockSize)
    {}

    void process(const std::string& command)
    {
        if(m_commands.empty())
        {
            using namespace std::chrono;
            m_firstCommandTime = duration_cast<nanoseconds>(system_clock::now().time_since_epoch()).count();
        }
    
        if(command == "{")
        {
            open_brace();
            return;
        }
        else if(command == "}")
        {
            close_brace();
            return;
        }

        m_commands.push_back(command);

        if(m_braceCount == 0 && m_commands.size() == m_blockSize)
        {
            process_bulk();
            return;
        }
    }

    void shutdown()
    {
        if(m_braceCount == 0)
        {
            process_bulk();
        }
    }

private:
    void open_brace()
    {
        if(m_braceCount == 0)
        {
            process_bulk();
        }
        ++m_braceCount;
    }
    
    void close_brace()
    {
        if(m_braceCount == 1)
        {
            process_bulk();
        }
        // Extra closing braces are ignored
        m_braceCount = std::max(m_braceCount - 1, 0);
    }

    void process_bulk()
    {
        if(!m_commands.empty())
        {
            // Bad for MT
            notify_handlers(m_commands, m_firstCommandTime);
            m_commands.clear();
        }
    }

private:
    std::vector<std::string> m_commands{};
    std::uint64_t m_firstCommandTime{};
    std::size_t m_blockSize{};
    int m_braceCount{};
};