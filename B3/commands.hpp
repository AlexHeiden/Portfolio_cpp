#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include "user-interface.hpp"

void add(UserInterface& userInterface, const std::string& name, const std::string& number);
void store(UserInterface& userInterface, const std::string& markName, const std::string& newMarkName, std::ostream& output);
void insertBefore(UserInterface& userInterface, const std::string& markName, const std::string& name,
    const std::string& number, std::ostream& output);
void insertAfter(UserInterface& userInterface, const std::string& markName, const std::string& name,
    const std::string& number, std::ostream& output);
void erase(UserInterface& userInterface, const std::string& markName, std::ostream& output);
void show(UserInterface& userInterface, const std::string& markName, std::ostream& output);
void move(UserInterface& userInterface, const std::string& markName, const long int steps, std::ostream& output);
void move(UserInterface& userInterface, const std::string& markName, const UserInterface::MovePosition& position, std::ostream& output);
void printInvalidStep(std::ostream& outputStream);
void printInvalidCommand(std::ostream& outputStream); 

#endif
