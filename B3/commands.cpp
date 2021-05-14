#include "commands.hpp"
#include <iostream>
#include <string>
#include "user-interface.hpp"

void add(UserInterface& userInterface, const std::string& name, const std::string& number)
{
  userInterface.add(name, number);
}

void store(UserInterface& userInterface, const std::string& markName, const std::string& newMarkName, std::ostream& output)
{
  userInterface.store(markName, newMarkName, output);
}

void insertBefore(UserInterface& userInterface, const std::string& markName, const std::string& name, 
    const std::string& number, std::ostream& output)
{
  userInterface.insertBefore(markName, name, number, output);
}

void insertAfter(UserInterface& userInterface, const std::string& markName, const std::string& name, 
    const std::string& number, std::ostream& output)
{
  userInterface.insertAfter(markName, name, number, output);
}

void erase(UserInterface& userInterface, const std::string& markName, std::ostream& output)
{
  userInterface.erase(markName, output);
}

void show(UserInterface& userInterface, const std::string& markName, std::ostream& output)
{
  userInterface.show(markName, output);
  }

void move(UserInterface& userInterface, const std::string& markName, const long int steps, std::ostream& output)
{
  userInterface.move(markName, steps, output);
}

void move(UserInterface& userInterface, const std::string& markName, const UserInterface::MovePosition& position, std::ostream& output)
{
  userInterface.move(markName, position, output);
}

void printInvalidStep(std::ostream& outputStream)
{
  outputStream << "<INVALID STEP>\n";
}

void printInvalidCommand(std::ostream& outputStream)
{
  outputStream << "<INVALID COMMAND>\n";
}
