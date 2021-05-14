#include "statistics-functor.hpp"
#include <iostream>
#include <algorithm>

StatisticFunctor::StatisticFunctor():
  max_(0),
  min_(0),
  mean_(0),
  numberOfPositiveValues_(0),
  numberOfNegativeValues_(0),
  numberOfValues_(0),
  oddSum_(0),
  evenSum_(0),
  first_(0),
  firstEqualsLast_(false)
{

}

void StatisticFunctor::operator()(const long int number)
{
  if (!numberOfValues_)
  {
    max_ = number;
    min_ = number;
    first_ = number;
  }
  else
  {
    max_ = std::max(number, max_);
    min_ = std::min(number, min_);
  }

  numberOfValues_++;

  if (number > 0)
  {
    numberOfPositiveValues_++;
  }
  else if (number < 0)
  {
    numberOfNegativeValues_++;
  }

  if (number % 2 != 0)
  {
    oddSum_ += number;
  }
  else
  {
    evenSum_ += number;
  }

  mean_ = (oddSum_ + evenSum_) / numberOfValues_;

  firstEqualsLast_ = (first_ == number);
}

std::ostream& operator<<(std::ostream& outputStream, const StatisticFunctor& statisticFunctor)
{
  std::ostream::sentry sentry(outputStream);

  if (sentry)
  {
    if (!statisticFunctor.numberOfValues_)
    {
      outputStream << "No Data\n";
    }
    else
    {
      outputStream << "Max: " << statisticFunctor.max_ << '\n'
          << "Min: " << statisticFunctor.min_ << '\n'
          << "Mean: " << statisticFunctor.mean_ << '\n'
          << "Positive: " << statisticFunctor.numberOfPositiveValues_ << '\n'
          << "Negative: " << statisticFunctor.numberOfNegativeValues_ << '\n'
          << "Odd Sum: " << statisticFunctor.oddSum_ << '\n'
          << "Even Sum: " << statisticFunctor.evenSum_ << '\n'
          << "First/Last Equal: ";

      if (statisticFunctor.firstEqualsLast_)
      {
        outputStream << "yes\n";
      }
      else
      {
        outputStream << "no\n";
      }
    }
  }

  return outputStream;
}
