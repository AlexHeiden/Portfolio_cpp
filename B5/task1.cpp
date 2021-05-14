#include <unordered_set>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "tasks.hpp"

void task1(std::istream& inputStream, std::ostream& outputStream)
{
  std::istream_iterator<std::string> inputIterator(inputStream);
  std::istream_iterator<std::string> endIterator;
  std::unordered_set<std::string> wordSet(inputIterator, endIterator);

  if (!inputStream.eof())
  {
    throw std::runtime_error("File reading error");
  }

  std::copy(wordSet.begin(), wordSet.end(), std::ostream_iterator<std::string>(outputStream, "\n"));
}
