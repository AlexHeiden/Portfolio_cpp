#include "parse.hpp"
#include <sstream>
#include <iostream>
#include <cstddef>
#include <string>
#include <stdexcept>
#include "queue-with-priority.hpp"
#include "commands.hpp"

struct CommandParser
{
  std::string command;
  CommandAfterParsing(*parseCommand)(std::stringstream&);
};

QueueWithPriority<std::string>::ElementPriority parsePriority(const std::string& priority)
{
  QueueWithPriority<std::string>::ElementPriority elementPriority;

  if (priority == "high")
  {
    elementPriority = QueueWithPriority<std::string>::ElementPriority::HIGH;
  }
  else if (priority == "normal")
  {
    elementPriority = QueueWithPriority<std::string>::ElementPriority::NORMAL;
  }
  else if (priority == "low")
  {
    elementPriority = QueueWithPriority<std::string>::ElementPriority::LOW;
  }
  else
  {
    throw std::invalid_argument("Input of invalid priority");
  }

  return elementPriority;
}

CommandAfterParsing parseAdd(std::stringstream& stringStream)
{
  std::string priority;
  std::string data;
  stringStream >> priority;
  if (!stringStream)
  {
    throw std::runtime_error("File reading error");
  }

  std::getline((stringStream >> std::ws), data);

  if (data.empty())
  {
    return [](QueueWithPriority<std::string>&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  try
  {
    QueueWithPriority<std::string>::ElementPriority priorityAfterParse = parsePriority(priority);
    return [data, priorityAfterParse](QueueWithPriority<std::string>& queue, std::ostream&)
    {
      add(queue, data, priorityAfterParse);
    };
  }
  catch (const std::invalid_argument&)
  {
    return [](QueueWithPriority<std::string>&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }
}

CommandAfterParsing parseGet(std::stringstream& stringStream)
{
  std::string temp;
  std::getline((stringStream >> std::ws), temp);
  if (!temp.empty())
  {
    return [](QueueWithPriority<std::string>&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  return [](QueueWithPriority<std::string>& queue, std::ostream& outputStream)
  {
    get(queue, outputStream);
  };
}

CommandAfterParsing parseAccelerate(std::stringstream& stringStream)
{
  std::string temp;
  std::getline((stringStream >> std::ws), temp);
  if (!temp.empty())
  {
    return [](QueueWithPriority<std::string>&, std::ostream& outputStream)
    {
      printInvalidCommand(outputStream);
    };
  }

  return [](QueueWithPriority<std::string>& queue, std::ostream&)
  {
    accelerate(queue);
  };
}

CommandAfterParsing parse(std::stringstream& stringStream)
{
  std::string command;
  stringStream >> command;

  if (!stringStream)
  {
    throw std::runtime_error("File reading error");
  }

  const CommandParser commandParserArray[3] =
  {
    {"add", &parseAdd},
    {"get", &parseGet},
    {"accelerate", &parseAccelerate}
  };

  for (size_t i = 0; i < sizeof(commandParserArray)/sizeof(commandParserArray[0]); i++)
  {
    if (command == commandParserArray[i].command)
    {
      return commandParserArray[i].parseCommand(stringStream);
    }
  }

  return [](QueueWithPriority<std::string>&, std::ostream& outputStream)
  {
    printInvalidCommand(outputStream);
  };
}
