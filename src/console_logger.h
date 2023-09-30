#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include "command_observer.h"

class ConsoleLogger : public CommandHandler
{
public:
    void handle(const std::vector<std::string>& commandBlock, std::uint64_t firstTime) override
    {
        std::cout << "bulk: ";
        std::ranges::copy(
            commandBlock.cbegin(), std::prev(commandBlock.cend()), 
            std::ostream_iterator<std::string>(std::cout, ", ")
        );
        std::cout << commandBlock.back() << '\n';
    }
};
