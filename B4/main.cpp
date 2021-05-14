#include <iostream>
#include <stdexcept>
#include "task.hpp"

int main()
{
  try
  {
    task(std::cin, std::cout);
  }
  catch (const std::runtime_error& error)
  {
    std::cerr << "Runtime error: " << error.what();
    return 2;
  }
  catch (const std::exception& error)
  {
    std::cerr << "An unexpected error occured";
    return 2;
  }
}
