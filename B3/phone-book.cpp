#include "phone-book.hpp"
#include <list>
#include <stdexcept>
#include <cstddef>
#include <iterator>
#include <iostream>
#include <string>

void PhoneBook::push_back(const std::string& name, const std::string& number)
{
  if (name.empty())
  {
    throw std::invalid_argument("The name must contain at least 1 symbol");
  }

  if (number.empty())
  {
    throw std::invalid_argument("The number must contain at least 1 symbol");
  }

  listOfRecordings_.push_back({ name, number });
}

PhoneBook::iterator PhoneBook::begin()
{
  return listOfRecordings_.begin();
}

PhoneBook::iterator PhoneBook::end()
{
  return listOfRecordings_.end();
}

PhoneBook::const_iterator PhoneBook::begin() const
{
  return listOfRecordings_.begin();
}

PhoneBook::const_iterator PhoneBook::end() const
{
  return listOfRecordings_.end();
}

void PhoneBook::insertBefore(PhoneBook::iterator iterator, const std::string& name, const std::string& number)
{
  if (name.empty())
  {
    throw std::invalid_argument("The name must contain at least 1 symbol");
  }

  if (number.empty())
  {
    throw std::invalid_argument("The number must contain at least 1 symbol");
  }

  listOfRecordings_.insert(iterator, { name, number });
}

void PhoneBook::insertAfter(PhoneBook::iterator iterator, const std::string& name, const std::string& number)
{
  if (name.empty())
  {
    throw std::invalid_argument("The name must contain at least 1 symbol");
  }

  if (number.empty())
  {
    throw std::invalid_argument("The number must contain at least 1 symbol");
  }

  if (isEmpty())
  {
    listOfRecordings_.push_back({ name, number });
  }
  else
  {
    if (iterator != listOfRecordings_.end())
    {
      listOfRecordings_.insert(std::next(iterator), { name, number });
    }
  }
}

void PhoneBook::replaceRecording(PhoneBook::iterator iterator, const std::string& name, const std::string& number)
{
  if (name.empty())
  {
    throw std::invalid_argument("The name must contain at least 1 symbol");
  }

  if (number.empty())
  {
    throw std::invalid_argument("The number must contain at least 1 symbol");
  }

  iterator->name = name;
  iterator->number = number;
}

void PhoneBook::erase(iterator iterator)
{
  listOfRecordings_.erase(iterator);
}

bool PhoneBook::isEmpty() const 
{
  return listOfRecordings_.empty();
}

