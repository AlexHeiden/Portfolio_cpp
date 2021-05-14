#ifndef COMMANDS_FOR_TASK1_HPP
#define COMMANDS_FOR_TASK1_HPP

#include <iostream>
#include "queue-with-priority.hpp"

void add(QueueWithPriority<std::string>& queue, const std::string& data,
    const QueueWithPriority<std::string>::ElementPriority priority);
void get(QueueWithPriority<std::string>& queue, std::ostream& outputStream);
void accelerate(QueueWithPriority<std::string>& queue);
void printInvalidCommand(std::ostream& outputStream);

#endif 
