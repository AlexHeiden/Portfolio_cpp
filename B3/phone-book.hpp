#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <string>
#include <list>
#include <iterator>

class PhoneBook
{
public:
  struct Recording
  {
    std::string name;
    std::string number;
  };

  using iterator = std::list<Recording>::iterator; 
  using const_iterator = std::list<Recording>::const_iterator;

  void push_back(const std::string& name, const std::string& number);
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;
  void insertBefore(iterator iterator, const std::string& name, const std::string& number);
  void insertAfter(iterator iterator, const std::string& name, const std::string& number);
  void replaceRecording(iterator iterator, const std::string& name, const std::string& number);
  void erase(iterator iterator);
  bool isEmpty() const;

private:
  std::list<Recording> listOfRecordings_;
};

#endif
