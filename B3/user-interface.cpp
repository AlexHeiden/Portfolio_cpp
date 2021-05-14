#include "user-interface.hpp"
#include <iterator>
#include <cstdlib>
#include <string>

UserInterface::UserInterface()
{
  bookmarkMap_["current"] = phoneBook_.begin();
}

void UserInterface::add(const std::string& name, const std::string& number)
{
  phoneBook_.push_back(name, number);
  makeBookmarksValid();
}

void UserInterface::store(const std::string& markName, const std::string& newMarkName, std::ostream& output)
{
  if (bookmarkMap_.find(markName) == bookmarkMap_.end())
  {
    output << "<INVALID BOOKMARK>\n";
  }
  else
  {
    bookmarkMap_[newMarkName] = bookmarkMap_[markName];
  }
}

void UserInterface::insertBefore(const std::string& markName, const std::string& name, const std::string& number, std::ostream& output)
{
  if (bookmarkMap_.find(markName) == bookmarkMap_.end())
  {
    output << "<INVALID BOOKMARK>\n";
  }
  else
  {
    phoneBook_.insertBefore(bookmarkMap_[markName], name, number);
  }

  makeBookmarksValid();
}

void UserInterface::insertAfter(const std::string& markName, const std::string& name, const std::string& number, std::ostream& output)
{
  if (bookmarkMap_.find(markName) == bookmarkMap_.end())
  {
    output << "<INVALID BOOKMARK>\n";
  }
  else
  {
    phoneBook_.insertAfter(bookmarkMap_[markName], name, number);
  }

  makeBookmarksValid();
}

void UserInterface::erase(const std::string& markName, std::ostream& output)
{
  if (bookmarkMap_.find(markName) == bookmarkMap_.end())
  {
    output << "<INVALID BOOKMARK>\n";
  }
  else if (bookmarkMap_[markName] == phoneBook_.end())
  {
    output << "<EMPTY>\n";
  }
  else 
  {
    auto iterator = bookmarkMap_[markName];

    for (auto i = bookmarkMap_.begin(); i != bookmarkMap_.end(); i++)
    {
      if (i->second == iterator)
      {
        i->second++;
      }
    }
    
    phoneBook_.erase(iterator);
    if (!phoneBook_.isEmpty())
    {
      makeBookmarksValid();
    }
  }
}

void UserInterface::show(const std::string& markName, std::ostream& output)
{
  if (bookmarkMap_.find(markName) == bookmarkMap_.end())
  {
    output << "<INVALID BOOKMARK>\n";
  }
  else if (phoneBook_.isEmpty())
  {
    output << "<EMPTY>\n";
  }
  else
  {
    output << bookmarkMap_[markName]->number << ' ' << bookmarkMap_[markName]->name << '\n';
  }
}

void UserInterface::move(const std::string& markName, const long int steps, std::ostream& output)
{
  if (bookmarkMap_.find(markName) == bookmarkMap_.end())
  {
    output << "<INVALID BOOKMARK>\n";
  }
  else if (phoneBook_.isEmpty())
  {
    output << "<EMPTY>\n";
  }
  else
  {
    if ((steps < 0) && (std::distance(phoneBook_.begin(), bookmarkMap_[markName]) < -steps))
    {
      bookmarkMap_[markName] = phoneBook_.begin();
    }
    else if ((steps > 0) && (std::distance(bookmarkMap_[markName], --phoneBook_.end()) < -steps))
    {
      bookmarkMap_[markName] = --phoneBook_.end();
    }
    else
    {
      std::advance(bookmarkMap_[markName], steps);
    }
  }
}

void UserInterface::move(const std::string& markName, const MovePosition& position, std::ostream& output)
{
  if (bookmarkMap_.find(markName) == bookmarkMap_.end())
  {
    output << "<INVALID BOOKMARK>\n";
  }
  else if (phoneBook_.isEmpty())
  {
    output << "<EMPTY>\n";
  }
  else 
  {
    switch (position)
    {
    case MOVE_FIRST:
    {
      bookmarkMap_[markName] = phoneBook_.begin();
      break;
    }
    case MOVE_LAST:
    {
      bookmarkMap_[markName] = --phoneBook_.end();
      break;
    }
    default:
    {
      output << "<INVALID STEP>\n";
      break;
    }
    }
  }
}

void UserInterface::makeBookmarksValid()
{
  for (auto iterator = bookmarkMap_.begin(); iterator != bookmarkMap_.end(); iterator++)
  {
    if (iterator->second == phoneBook_.end())
    {
      iterator->second--;
    }
  }
}
