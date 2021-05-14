#include <string>
#include <sstream>
#include <iostream>
#include "tasks.hpp"
#include "parse.hpp"
#include "queue-with-priority.hpp"

void task1(std::istream& inputStream, std::ostream& outputStream)
{
  QueueWithPriority<std::string> queue;
  std::string temp;

  while (std::getline(inputStream, temp))
  {
    std::stringstream stringStream(temp);
    if ((stringStream >> std::ws).eof())
    {
      continue;
    }

    CommandAfterParsing command(parse(stringStream));
    command(queue, outputStream);
  }

  if (!std::cin.eof())
  {
    throw std::runtime_error("File reading error");
  }
}
