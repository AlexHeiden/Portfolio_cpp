#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

const int maxKey = 5;

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

bool operator<(const DataStruct& first, const DataStruct& second);
std::istream& operator>>(std::istream& inputStream, DataStruct& dataStruct);
std::ostream& operator<<(std::ostream& outputStream, const DataStruct& dataStruct);

#endif
