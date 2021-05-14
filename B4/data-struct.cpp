#include "data-struct.hpp"
#include <iostream>
#include <cmath>
#include <string>
#include "utility.hpp"

bool operator<(const DataStruct& first, const DataStruct& second)
{
  if (first.key1 != second.key1)
  {
    return (first.key1 < second.key1);
  }
  else if (first.key2 != second.key2)
  {
    return (first.key2 < second.key2);
  }
  else
  {
    return (first.str.length() < second.str.length());
  }
}

std::istream& operator>>(std::istream& inputStream, DataStruct& dataStruct)
{
  std::istream::sentry sentry(inputStream);

  if (sentry)
  { 
    inputStream >> std::ws;

    int key1;
    inputStream >> std::noskipws >> key1;
    if (!inputStream)
    {
      return inputStream;
    }

    if (std::abs(key1) > maxKey)
    {
      inputStream.setstate(std::ios::failbit);
      return inputStream;
    }

    char firstComma;
    inputStream >> std::noskipws >> firstComma;
    if (!inputStream)
    {
      return inputStream;
    }

    if (firstComma != ',')
    {
      inputStream.unget();
      inputStream.setstate(std::ios::failbit);
      return inputStream;
    }

    inputStream >> skip_ws;
    
    int key2;
    inputStream >> key2;
    if (!inputStream)
    {
      return inputStream;
    }

    if (std::abs(key2) > maxKey)
    {
      inputStream.setstate(std::ios::failbit);
      return inputStream;
    }

    char secondComma;
    inputStream >> std::noskipws >> secondComma;
    if (!inputStream)
    {
      return inputStream;
    }

    if (secondComma != ',')
    {
      inputStream.unget();
      inputStream.setstate(std::ios::failbit);
      return inputStream;
    }

    inputStream >> skip_ws;

    std::string str;
    std::getline(inputStream, str);
    if (!inputStream)
    {
      return inputStream;
    }

    dataStruct = { key1, key2, str };
  }

  return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const DataStruct& dataStruct)
{
  std::ostream::sentry sentry(outputStream);

  if (sentry)
  {
    outputStream << dataStruct.key1 << ',' << dataStruct.key2 << ',' << dataStruct.str << '\n';
  }

  return outputStream;
}
