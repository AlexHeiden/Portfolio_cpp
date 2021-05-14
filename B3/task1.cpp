#include <string>
#include <sstream>
#include "parse.hpp"
#include "tasks.hpp"
#include "user-interface.hpp"

void task1(std::istream& inputStream, std::ostream& outputStream)
{
  UserInterface userInterface;
  std::string temp;

  while (std::getline(inputStream, temp))
  {
    std::istringstream stringStream(temp);
    if ((stringStream >> std::ws).eof())
    {
      continue;
    }

    CommandAfterParsing command(parse(stringStream));
    command(userInterface, outputStream);
  }

  if (!std::cin.eof())
  {
    throw std::runtime_error("File reading error");
  }
}
