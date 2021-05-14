#include <vector>
#include <cstddef>
#include "policies.hpp"
#include "additional-functions.hpp"
#include "tasks.hpp"

void task4(const TypeOfSort& typeOfSort, const int size)
{
  std::vector<double> vector(size);
  fillRandom(&vector[0], size);
  print(vector);

  sort <SquareBracketsOperatorPolicy>(vector, typeOfSort);
  print(vector);
}
