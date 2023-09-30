#pragma once

#include <memory>
#include <set>
#include <string>
#include <vector>

class CommandHandler
{
public:
    virtual void handle(const std::vector<std::string>& commandBlock, std::uint64_t firstTime) = 0;
    virtual ~CommandHandler() {}
};

class CommandSender
{
public:
    virtual void notify_handlers(const std::vector<std::string>& commandBlock, std::uint64_t firstTime)
    {
        for(auto&& h : m_handlers)
        {
            h->handle(commandBlock, firstTime);
        }
    }

    virtual void add_handler(CommandHandler* handler)
    {
        m_handlers.insert(handler);
    }

    virtual void remove_handler(CommandHandler* handler)
    {
        m_handlers.erase(handler);
    }

    virtual ~CommandSender() {}

protected:
    std::set<CommandHandler*> m_handlers;
};
