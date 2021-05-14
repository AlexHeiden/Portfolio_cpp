#include <algorithm>
#include <iostream>
#include "factorial-container.hpp"
#include "tasks.hpp"

void task2(std::ostream& outputStream)
{
  const size_t lastElementIndex = 10;
  FactorialContainer factorialContainer(lastElementIndex);
  std::copy(factorialContainer.begin(), factorialContainer.end(), std::ostream_iterator<size_t>(outputStream, " "));
  outputStream << '\n';
  std::copy(factorialContainer.rbegin(), factorialContainer.rend(), std::ostream_iterator<size_t>(outputStream, " "));
  outputStream << '\n';
}
