#include "task.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "data-struct.hpp"

void task(std::istream& inputStream, std::ostream& outputStream)
{
  std::istream_iterator<DataStruct> inputIterator(inputStream);
  std::istream_iterator<DataStruct> endIterator;
  std::vector<DataStruct> vector(inputIterator, endIterator);

  if (!inputStream.eof())
  {
    throw std::runtime_error("Invalid input");
  }

  std::sort(vector.begin(), vector.end());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(outputStream));
}
