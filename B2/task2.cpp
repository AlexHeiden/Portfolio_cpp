#include <list>
#include <iostream>
#include "tasks.hpp"

void task2(std::istream& inputStream, std::ostream& outputStream)
{
  const int min = 1;
  const int max = 20;
  const int maxSize = 20;

  std::list<int> list;
  int temp = 0;
  while (inputStream >> temp)
  {
    if (temp > max || temp < min)
    {
      throw std::runtime_error("The appropriate range of numbers is 1 - 20");
    }

    if (list.size() == maxSize)
    {
      throw std::runtime_error("You can't input more than 20 values");
    }

    list.push_back(temp);
  }

  if (!inputStream.eof())
  {
    throw std::logic_error("File read error");
  }

  if (!list.empty())
  {
    auto begin = list.begin();
    auto end = list.end();

    while (begin != end)
    {
      outputStream << *begin << ' ';
      begin++;

      if (begin == end)
      {
        break;
      }

      end--;
      outputStream << *end << ' ';
    }

    outputStream << '\n';
  }
}
