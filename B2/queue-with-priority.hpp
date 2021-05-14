#ifndef QUEUE_WITH_PRIORITY_HPP
#define QUEUE_WITH_PRIORITY_HPP

#include <list>
#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename TypeOfElement>
class QueueWithPriority
{
public:
  enum ElementPriority
  {
    LOW,
    NORMAL,
    HIGH,
  };

  void put(const TypeOfElement& data, const ElementPriority& priority);
  TypeOfElement get();
  void removeFirst();
  void accelerate();
  bool isEmpty() const;

private:
  std::list<TypeOfElement> highPriorityList_;
  std::list<TypeOfElement> normalPriorityList_;
  std::list<TypeOfElement> lowPriorityList_;
}; 

template <typename TypeOfElement>
void QueueWithPriority<TypeOfElement>::put(const TypeOfElement& data, const ElementPriority& priority)
{
  switch (priority)
  {
    case HIGH:
    {
      highPriorityList_.push_back(data);
      break;
    }
    case NORMAL:
    {
      normalPriorityList_.push_back(data);
      break;
    }
    case LOW:
    {
      lowPriorityList_.push_back(data);
      break;
    }
    default:
    {
      throw std::invalid_argument("The priority must contain value");
    }
  }
}

template <typename TypeOfElement>
TypeOfElement QueueWithPriority<TypeOfElement>::get()
{
  if (highPriorityList_.size())
  {
    return highPriorityList_.front();
  }
  else if (normalPriorityList_.size())
  {
    return normalPriorityList_.front();
  }
  else if (lowPriorityList_.size())
  {
    return lowPriorityList_.front();
  } 
  else
  {
    throw std::runtime_error("There are no elements to get from this queue");
  }
}

template <typename TypeOfElement>
void QueueWithPriority<TypeOfElement>::removeFirst()
{
  if (highPriorityList_.size())
  {
    highPriorityList_.pop_front();
  }
  else if (normalPriorityList_.size())
  {
    normalPriorityList_.pop_front();
  }
  else if (lowPriorityList_.size())
  {
    lowPriorityList_.pop_front();
  }
  else
  {
    throw std::runtime_error("There are no elements to remove from this queue");
  }
}

template <typename TypeOfElement>
void QueueWithPriority<TypeOfElement>::accelerate()
{
  if (!isEmpty())
  {
    highPriorityList_.splice(highPriorityList_.end(), lowPriorityList_);
  }
}

template <typename TypeOfElement>
bool QueueWithPriority<TypeOfElement>::isEmpty() const
{
  return (!highPriorityList_.size() && !normalPriorityList_.size() && !lowPriorityList_.size());
}

#endif
