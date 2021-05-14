#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP

#include <string>
#include <map>
#include "phone-book.hpp"

class UserInterface
{
public:
  enum MovePosition
  {
    MOVE_FIRST,
    MOVE_LAST
  };

  UserInterface();

  void add(const std::string& name, const std::string& number);
  void store(const std::string& markName, const std::string& newMarkName, std::ostream& output);
  void insertBefore(const std::string& markName, const std::string& name, const std::string& number, std::ostream& output);
  void insertAfter(const std::string& markName, const std::string& name, const std::string& number, std::ostream& output);
  void erase(const std::string& markName, std::ostream& output);
  void show(const std::string& markName, std::ostream& output);
  void move(const std::string& markName, const long int steps, std::ostream& output);
  void move(const std::string& markName, const MovePosition& position, std::ostream& output);
  void makeBookmarksValid();

private:
  PhoneBook phoneBook_;
  std::map<std::string, PhoneBook::iterator> bookmarkMap_;
};

#endif
