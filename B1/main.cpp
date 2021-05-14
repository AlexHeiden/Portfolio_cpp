#include <iostream>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc < 2)
    {
      std::cerr << "You must input the number of the task";
      return 1;
    }
    
    std::srand(std::time(0));

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
      if (argc != 3)
      {
        std::cerr << "You need to input order for task1 and nothing more";
        return 1;
      }
      
      try
      {
        const TypeOfSort typeOfSort = getTypeOfSort(argv[2]);
        task1(typeOfSort);
      }
      catch (const std::runtime_error& error)
      {
        std::cerr << "Runtime error: " << error.what();
        return 2;
      }
      catch (const std::invalid_argument& error)
      {
        std::cerr << "Invalid argument error: " << error.what();
        return 1;
      }

      break;
    }
    case 2:
    {
      if (argc != 3)
      {
        std::cerr << "You need to input name of the file for task2 and nothing more";
        return 1;
      }

      try
      {
        task2(argv[2]);
      }
      catch (const std::invalid_argument& error)
      {
        std::cerr << "Invalid argument error: " << error.what();
        return 1;
      }
      catch (const std::runtime_error& error)
      {
        std::cerr << "Runtime error: " << error.what();
        return 2;
      }
      catch (const std::bad_alloc& error)
      {
        std::cerr << "Memory allocation error";
        return 2;
      }

      break;
    }
    case 3:
    {
      if (argc != 2)
      {
        std::cerr << "Excess arguments for task3";
        return 1;
      }

      try
      {
        task3();
      }
      catch (const std::runtime_error& error)
      {
        std::cerr << "Runtime error: " << error.what();
        return 2;
      }

      break;
    }
    case 4:
    {
      if (argc != 4)
      {
        std::cerr << "You need to input order and size of array for task 4 and nothing more";
        return 1;
      }

      std::istringstream sizeArgumentStream(argv[3]);
      int sizeArgument = 0;
      sizeArgumentStream >> sizeArgument;
      if (!sizeArgumentStream)
      {
        std::cerr << "Size argument read error";
        return 1;
      }

      if (sizeArgument <= 0)
      {
        std::cerr << "The size of array must exceed 0";
        return 1;
      }

      try
      {
        const TypeOfSort typeOfSort = getTypeOfSort(argv[2]);
        task4(typeOfSort, sizeArgument);
      }
      catch (const std::invalid_argument& error)
      {
        std::cerr << "Invalid argument error: " << error.what();
        return 1;
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
