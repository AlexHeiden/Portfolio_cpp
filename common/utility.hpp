#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <iostream>

class StreamGuard
{
public:
  StreamGuard(std::istream& inputStream);
  ~StreamGuard();
private:
  std::istream& inputStream_;
  std::istream::fmtflags flags_;
};

std::istream& skip_ws(std::istream& inputStream);

#endif
