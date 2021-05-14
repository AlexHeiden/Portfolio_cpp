#include <vector>
#include <iostream>
#include <stdexcept>
#include "additional-functions.hpp"
#include "tasks.hpp"

void task3()
{
  int temp = -1;
  std::vector<int> vector;
  while (std::cin >> temp)
  {
    if (temp == 0)
    {
      break;
    }

    vector.push_back(temp);
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("File read error");
  }

  if (!vector.empty())
  {
    if (temp != 0)
    {
      throw std::runtime_error("You must input 0 to stop the input");
    }

    auto iterator = vector.begin();

    if (vector.back() == 1)
    {
      while (iterator != vector.end())
      {
        if (*iterator % 2 == 0)
        {
          iterator = vector.erase(iterator);
        }
        else
        {
          iterator++;
        }
      }
    }

    if (vector.back() == 2)
    {
      while (iterator != vector.end())
      {
        if (*iterator % 3 == 0)
        {
          iterator = vector.insert(iterator + 1, 3, 1) + 3;
        }
        else
        {
          iterator++;
        }
      }
    }

    print(vector);
  }
}
