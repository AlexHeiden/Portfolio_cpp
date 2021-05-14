#include "utility"
#include <iostream>
#include <cctype>
#include "utility.hpp"

std::istream& skip_ws(std::istream& inputStream)
{
  while (std::isblank(inputStream.peek()))
  {
    inputStream.ignore();
  }

  return inputStream;
}

StreamGuard::StreamGuard(std::istream& inputStream):
  inputStream_(inputStream),
  flags_(inputStream.flags())
{

}

StreamGuard::~StreamGuard()
{
  inputStream_.setf(flags_);
}
