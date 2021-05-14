#ifndef ADDITIONAL_FUNCTIONS_H
#define ADDITIONAL_FUNCTIONS_H

#include <iostream>
#include <algorithm>
#include <cstddef>
#include "policies.hpp"

enum TypeOfSort
{
  SORT_ASCENDING,
  SORT_DESCENDING
};

TypeOfSort getTypeOfSort(const char* order);
void fillRandom(double* array, int size);

template <typename Collection>
void print(const Collection& collection)
{
  if (!collection.empty())
  {
    const auto begin = collection.begin();
    const auto end = collection.end();

    for (auto i = begin; i != end; i++)
    {
      std::cout << *i << ' ';
    }
    std::cout << '\n';
  }
}

template <template <typename Collection> typename Policy, typename Collection>
void sort(Collection& collection, const TypeOfSort& typeOfSort)
{
  if (!collection.empty())
  {
    const auto begin = Policy<Collection>::begin(collection);
    const auto end = Policy<Collection>::end(collection);

    for (auto i = begin; i != end; i++)
    {
      for (auto j = i; j != end; j++)
      {
        if (typeOfSort == SORT_ASCENDING ? (Policy<Collection>::element(collection, i) > Policy<Collection>::element(collection, j))
            : (Policy<Collection>::element(collection, i) < Policy<Collection>::element(collection, j)))
        {
          std::swap(Policy<Collection>::element(collection, i),
              Policy<Collection>::element(collection, j));
        }
      }
    }
  }   
}

#endif
