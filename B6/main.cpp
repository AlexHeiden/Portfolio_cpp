#include <iostream>
#include <algorithm>
#include <iterator>
#include "statistics-functor.hpp"

int main()
{
  std::istream_iterator<long int> inputIterator(std::cin);
  std::istream_iterator<long int> endIterator;
  StatisticFunctor statisticFunctor = std::for_each(inputIterator, endIterator, StatisticFunctor());

  if (!std::cin.eof())
  {
    std::cerr << "File reading error";
    return 2;
  }

  std::cout << statisticFunctor;

  return 0;
}
