#include <cstring>
#include <cstddef>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include "additional-functions.hpp"

TypeOfSort getTypeOfSort(const char* order)
{
  if (!order)
  {
    throw std::invalid_argument("The order must not be empty");
  }

  if (std::strcmp(order, "ascending") == 0)
  {
    return SORT_ASCENDING;
  }

  if (std::strcmp(order, "descending") == 0)
  {
    return SORT_DESCENDING;
  }

  throw std::invalid_argument("There's no such type of sort");
}

void fillRandom(double* array, int size)
{
  if (!array)
  {
    throw std::invalid_argument("You must input array that can contain something");
  }

  for (size_t i = 0; i < static_cast<size_t>(size); i++)
  {
    array[i] = -1 + static_cast<double>(std::rand()) / RAND_MAX * 2;
  }
}
