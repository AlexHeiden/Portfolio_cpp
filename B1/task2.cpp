#include <fstream>
#include <vector>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <memory>
#include "tasks.hpp"

void task2(const char* file)
{
  if (file == nullptr)
  {
    throw std::invalid_argument("The name of the file must contain at least 1 symbol");
  }

  std::ifstream inputFile(file);
  if (!inputFile)
  {
    throw std::runtime_error("File open error");
  }

  size_t maxMemory = 100;
  size_t readMemory = 0;
  const double goldenRatioCoefficient = 1.61;
  std::unique_ptr<char[], decltype(&free)> array(static_cast<char*>(calloc(maxMemory, 1)), free);
  if (!array)
  {
    throw std::bad_alloc();
  }

  while (inputFile)
  {
    inputFile.read(&array[readMemory], maxMemory - readMemory);
    readMemory += inputFile.gcount();

    if (readMemory == maxMemory)
    {
      maxMemory = static_cast<size_t>(maxMemory * goldenRatioCoefficient);
      std::unique_ptr<char[], decltype(&free)> tmpArray(static_cast<char*>(realloc(array.get(), maxMemory)), free);
      if (!tmpArray)
      {
        throw std::bad_alloc();
      }

      std::swap(array, tmpArray);
      tmpArray.release();
    }
  }

  if (readMemory)
  {
    std::vector<char> vector(array.get(), array.get() + readMemory);
    for (size_t i = 0; i < vector.size(); i++)
    {
      std::cout << vector[i];
    }
  }
}
