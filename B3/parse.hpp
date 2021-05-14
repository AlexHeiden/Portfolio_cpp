#ifndef PARSE_HPP
#define PARSE_HPP

#include <functional>
#include <sstream>
#include "user-interface.hpp"

enum InsertPosition
{
  BEFORE,
  AFTER
};

using CommandAfterParsing = std::function<void(UserInterface&, std::ostream& outputStream)>;
CommandAfterParsing parse(std::istringstream& stringStream);
CommandAfterParsing parseAdd(std::istringstream& stringstream);
CommandAfterParsing parseStore(std::istringstream& stringStream);
CommandAfterParsing parseInsert(std::istringstream& stringStream);
CommandAfterParsing parseDelete(std::istringstream& stringStream);
CommandAfterParsing parseShow(std::istringstream& stringStream);
CommandAfterParsing parseMove(std::istringstream& stringStream);
std::string parseNumber(std::istringstream& stringstream);
std::string parseName(std::istringstream& stringstream);
std::string parseMark(std::istringstream& stringStream);
InsertPosition parseInsertPosition(std::istringstream& stringStream);


#endif
