#include <stdexcept>
#include <iostream>
#include <vector>
#include <forward_list>
#include "policies.hpp"
#include "additional-functions.hpp"
#include "tasks.hpp"

void task1(const TypeOfSort& typeOfSort)
{
  std::vector<int> squareBracketsSortVector;
  int temp = 0;
  while (std::cin >> temp)
  {
    squareBracketsSortVector.push_back(temp);
  }

  if (!std::cin.eof())
  {
    throw std::runtime_error("File read error");
  }
  
  if (!squareBracketsSortVector.empty())
  {
    std::vector<int> atMethodSortVector = squareBracketsSortVector;
    std::forward_list<int> iteratorSortList(squareBracketsSortVector.begin(), squareBracketsSortVector.end());

    sort<SquareBracketsOperatorPolicy>(squareBracketsSortVector, typeOfSort);
    sort<AtMethodPolicy>(atMethodSortVector, typeOfSort);
    sort<IteratorPolicy>(iteratorSortList, typeOfSort);

    print(squareBracketsSortVector);
    print(atMethodSortVector);
    print(iteratorSortList);
  }
}
