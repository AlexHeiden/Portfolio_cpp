#ifndef STATISTIC_FUNCTOR_HPP
#define STATISTIC_FUNCTOR_HPP

#include <ostream>

class StatisticFunctor
{
public:
  StatisticFunctor();
  void operator()(const long int number);

private:
  long int max_;
  long int min_;
  long int mean_;
  long int numberOfPositiveValues_;
  long int numberOfNegativeValues_;
  long int numberOfValues_;
  long int oddSum_;
  long int evenSum_;
  long int first_;
  bool firstEqualsLast_;
  friend std::ostream& operator<<(std::ostream& outputStream, const StatisticFunctor& statisticFunctor);
};

#endif
