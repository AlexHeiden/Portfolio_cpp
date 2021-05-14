#include "factorial-container.hpp"
#include <cstddef>
#include <climits>
#include <stdexcept>

FactorialContainer::const_iterator::const_iterator(const size_t index, const value_type value, const size_t endIndex):
  index_(index),
  value_(value),
  endIndex_(endIndex)
{

}

FactorialContainer::const_iterator::value_type FactorialContainer::const_iterator::operator*() const
{
  if (index_ == endIndex_)
  {
    throw std::out_of_range("You can't get access to end element");
  }

  return value_;
}

FactorialContainer::const_iterator& FactorialContainer::const_iterator::operator++()
{
  if (index_ == endIndex_)
  {
    throw std::out_of_range("You can't increment end element");
  }

  index_++;
  value_ *= index_;

  return *this;
}

FactorialContainer::const_iterator FactorialContainer::const_iterator::operator++(int)
{
  const_iterator temp = *this;
  ++(*this);
  return temp;
}

FactorialContainer::const_iterator& FactorialContainer::const_iterator::operator--()
{
  if (index_ == 1)
  {
    throw std::out_of_range("You can't dencrement end element");
  }

  value_ /= index_;
  index_--;

  return *this;
}

FactorialContainer::const_iterator FactorialContainer::const_iterator::operator--(int)
{
  const_iterator temp = *this;
  --(*this);
  return temp;
}

bool FactorialContainer::const_iterator::operator==(const const_iterator& iterator) const
{
  return (index_ == iterator.index_);
}

bool FactorialContainer::const_iterator::operator!=(const const_iterator& iterator) const
{
  return (index_ != iterator.index_);
}

FactorialContainer::FactorialContainer():
  lastElementIndex_(0),
  endValue_(0)
{

}

FactorialContainer::FactorialContainer(const size_t lastElementIndex)
{
  if (!lastElementIndex)
  {
    throw std::invalid_argument("Your lastElementIndex must be equal or greater than 1");
  }

  size_t factorialValue = 1;

  for (size_t i = 2; i <= lastElementIndex + 1; i++)
  {
    if (factorialValue > UINT_MAX / i)
    {
      throw std::overflow_error("Your lastElementIndex causes overflow of the variable");
    }

    factorialValue *= i;
  }

  lastElementIndex_ = lastElementIndex;
  endValue_ = factorialValue;
}

FactorialContainer::const_iterator FactorialContainer::begin() const
{
  return const_iterator(1, 1, lastElementIndex_ + 1);
}

FactorialContainer::const_iterator FactorialContainer::end() const
{
  return const_iterator(lastElementIndex_ + 1, endValue_, lastElementIndex_ + 1);
}

FactorialContainer::const_reverse_iterator FactorialContainer::rbegin() const
{
  return const_reverse_iterator(end());
}

FactorialContainer::const_reverse_iterator FactorialContainer::rend() const
{
  return const_reverse_iterator(begin());
}
