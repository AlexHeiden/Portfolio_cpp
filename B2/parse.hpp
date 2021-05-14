#ifndef PARSER_HPP
#define PARSER_HPP

#include <functional>
#include <sstream>
#include <string>
#include <ostream>
#include "queue-with-priority.hpp"

using CommandAfterParsing = std::function<void(QueueWithPriority<std::string>&, std::ostream& outputStream)>;
CommandAfterParsing parse(std::stringstream& stringStream);

#endif
