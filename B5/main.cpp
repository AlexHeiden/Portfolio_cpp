#include <iostream>
#include <stdexcept>
#include <sstream>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "You must input only a number of task";
      return 1;
    }

    std::istringstream numberOfTaskStream(argv[1]);
    size_t numberOfTask = 0;
    numberOfTaskStream >> numberOfTask;
    if (!numberOfTaskStream)
    {
      std::cerr << "Number of task read error";
      return 1;
    }

    switch (numberOfTask)
    {
    case 1:
    {
      try
      {
        task1(std::cin, std::cout);
      }
      catch (const std::runtime_error& error)
      {
        std::cerr << "Runtime error: " << error.what();
        return 2;
      }

      break;
    }
    case 2:
    {
      try
      {
        task2(std::cin, std::cout);
      }
      catch (const std::runtime_error& error)
      {
        std::cerr << "Runtime error: " << error.what();
        return 2;
      }

      break;
    }
    default:
    {
      std::cerr << "Invalid argument: the first parameter must contain the number of the task";
      return 1;
    }
    }
  }
  catch (const std::exception& error)
  {
    std::cerr << "An unexpected error occured";
    return 2;
  }

  return 0;
}
