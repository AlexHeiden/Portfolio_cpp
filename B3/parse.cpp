#include "parse.hpp"
#include <string>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <cctype>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include "commands.hpp"
#include "user-interface.hpp"

struct CommandParser 
{
  std::string command;
  CommandAfterParsing(*parseCommand)(std::istringstream&);
};

CommandAfterParsing parse(std::istringstream& stringStream)
{
  std::string command;
  stringStream >> command;

  if (!stringStream)
  {
    throw std::runtime_error("File reading error");
  }

  const CommandParser commandParserArray[6] 
  {
    {"add", &parseAdd},
    {"store", &parseStore},
    {"insert", &parseInsert},
    {"delete", &parseDelete},
    {"show", &parseShow},
    {"move", &parseMove}
  };
  
  auto iterator = std::find_if(commandParserArray, commandParserArray + 6, 
      [command](const CommandParser& parserInsideArray)
      {
        return std::strcmp(command.c_str(), parserInsideArray.command.c_str()) == 0;
      });

  if (iterator)
  {
    return iterator->parseCommand(stringStream);
  }
  else
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }
}

CommandAfterParsing parseAdd(std::istringstream& stringStream)
{
  std::string number = parseNumber(stringStream);

  if (!stringStream)
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  std::string name = parseName(stringStream);

  if (!stringStream)
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  std::string temp;
  std::getline((stringStream >> std::ws), temp);
  if (!temp.empty())
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  return [name, number](UserInterface& userInterface, std::ostream&)
  {
    add(userInterface, name, number);
  };
}

CommandAfterParsing parseStore(std::istringstream& stringStream)
{
  std::string markName = parseMark(stringStream);

  if (!stringStream)
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  std::string newMarkName = parseMark(stringStream);

  if (!stringStream)
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  std::string temp;
  std::getline((stringStream >> std::ws), temp);
  if (!temp.empty())
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  return [markName, newMarkName](UserInterface& userInterface, std::ostream& outputStream)
  {
    store(userInterface, markName, newMarkName, outputStream);
  };
}

CommandAfterParsing parseInsert(std::istringstream& stringStream)
{
  InsertPosition position = parseInsertPosition(stringStream);

  if (!stringStream)
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  std::string markName = parseMark(stringStream);

  if (!stringStream)
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  std::string number = parseNumber(stringStream);

  if (!stringStream)
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  std::string name = parseName(stringStream);

  if (!stringStream)
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  std::string temp;
  std::getline((stringStream >> std::ws), temp);
  if (!temp.empty())
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  switch (position)
  {
  case BEFORE:
  {
    return [markName, name, number](UserInterface& userInterface, std::ostream& outputStream)
    {
      insertBefore(userInterface, markName, name, number, outputStream);
    };
  }
  case AFTER:
  {
    return [markName, name, number](UserInterface& userInterface, std::ostream& outputStream)
    {
      insertAfter(userInterface, markName, name, number, outputStream);
    };
  }
  default:
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }
  }
}

CommandAfterParsing parseDelete(std::istringstream& stringStream)
{
  std::string markName = parseMark(stringStream);

  if (!stringStream)
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  std::string temp;
  std::getline((stringStream >> std::ws), temp);
  if (!temp.empty())
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  return [markName](UserInterface& userInterface, std::ostream& outputStream)
  {
    erase(userInterface, markName, outputStream);
  };
}

CommandAfterParsing parseShow(std::istringstream& stringStream)
{
  std::string markName = parseMark(stringStream);

  if (!stringStream)
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  std::string temp;
  std::getline((stringStream >> std::ws), temp);
  if (!temp.empty())
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  return [markName](UserInterface& userInterface, std::ostream& outputStream)
  {
    show(userInterface, markName, outputStream);
  };
}

CommandAfterParsing parseMove(std::istringstream& stringStream)
{
  std::string markName = parseMark(stringStream);

  if (!stringStream)
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  std::string steps;
  stringStream >> steps;

  if (!stringStream)
  {
    throw std::runtime_error("File reading error");
  }

  if (steps.empty())
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidStep(outputStream);
    };
  }

  std::string temp;
  std::getline((stringStream >> std::ws), temp);
  if (!temp.empty())
  {
    return [](UserInterface&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  if (std::strcmp(steps.c_str(), "first") == 0)
  {
    UserInterface::MovePosition position = UserInterface::MovePosition::MOVE_FIRST;
    return [markName, position](UserInterface& userInterface, std::ostream& outputStream)
    {
      move(userInterface, markName, position, outputStream);
    };
  }
  else if (std::strcmp(steps.c_str(), "last") == 0)
  {
    UserInterface::MovePosition position = UserInterface::MovePosition::MOVE_LAST;
    return [markName, position](UserInterface& userInterface, std::ostream& outputStream)
    {
      move(userInterface, markName, position, outputStream);
    };
  }
  else
  {
    char* end = nullptr;
    long int intSteps = std::strtol(steps.c_str(), &end, 10);
    
    if (((intSteps == 0) && (errno == EINVAL))
        || (errno == ERANGE)
        || (steps.c_str() == end)
        || (*end != '\x00'))
    {
      return [](UserInterface&, std::ostream& outputStream)
      {
        printInvalidStep(outputStream);
      };
    }

    return [markName, intSteps](UserInterface& userInterface, std::ostream& outputStream)
    {
      move(userInterface, markName, intSteps, outputStream);
    };
  }
}

std::string parseNumber(std::istringstream& stringStream)
{
  std::string number;
  stringStream >> number;

  if (!stringStream)
  {
    throw std::runtime_error("File reading error");
  }

  if (number.empty())
  {
    stringStream.setstate(std::ios::failbit);
    return number;
  }

  for (size_t i = 0; i < number.length(); i++)
  {
    if (!std::isdigit(number[i]))
    {
      stringStream.setstate(std::ios::failbit);
      return number;
    }
  }

  return number;
}

std::string parseName(std::istringstream& stringStream)
{
  std::string returnableName;
  stringStream >> std::ws;

  char tempSymbol;
  if (stringStream.peek() != '\"')
  {
    stringStream.setstate(std::ios::failbit);
    return returnableName;
  }

  stringStream.get();

  bool isNameValid = false;
  while (stringStream.peek() != '\n' && stringStream.peek() != EOF)
  {
    if (stringStream.peek() == '\\')
    {
      stringStream.get();
      if (stringStream.peek() == '\"')
      {
        stringStream.get(tempSymbol);
        returnableName += tempSymbol;
      }
    }
    else if (stringStream.peek() == '\"')
    {
      isNameValid = true;
      stringStream.get();
      break;
    }
    else
    {
      stringStream.get(tempSymbol);
      returnableName += tempSymbol;
    }
  }
  
  if (!isNameValid)
  {
    stringStream.setstate(std::ios::failbit);
    return returnableName;
  }

  return returnableName;
}

std::string parseMark(std::istringstream& stringStream)
{
  std::string markName;
  stringStream >> markName;

  if (!stringStream)
  {
    throw std::runtime_error("File reading error");
  }

  if (markName.empty())
  {
    stringStream.setstate(std::ios::failbit);
    return markName;
  }

  for (size_t i = 0; i < markName.length(); i++)
  {
    if (!((std::isalnum(markName[i])) || markName[i] == '-'))
    {
      stringStream.setstate(std::ios::failbit);
      return markName;
    }
  }

  return markName;
}

InsertPosition parseInsertPosition(std::istringstream& stringStream)
{
  std::string insertPlace;
  stringStream >> insertPlace;

  if (!stringStream)
  {
    throw std::runtime_error("File reading error");
  }

  if (std::strcmp(insertPlace.c_str(), "before") == 0)
  {
    return InsertPosition::BEFORE;
  }
  else if (std::strcmp(insertPlace.c_str(), "after") == 0)
  {
    return InsertPosition::AFTER;
  }
  else
  {
    stringStream.setstate(std::ios::failbit);
    return InsertPosition::BEFORE;
  }
}
