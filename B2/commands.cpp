#include "commands.hpp"
#include <iostream>
#include "queue-with-priority.hpp"

void add(QueueWithPriority<std::string>& queue, const std::string& data, 
    const QueueWithPriority<std::string>::ElementPriority priority)
{
  queue.put(data, priority);
}

void get(QueueWithPriority<std::string>& queue, std::ostream& outputStream)
{
  if (queue.isEmpty())
  {
    outputStream << "<EMPTY>\n";
  }
  else
  {
    outputStream << queue.get() << '\n';
    queue.removeFirst();
  }
}

void accelerate(QueueWithPriority<std::string>& queue)
{
  queue.accelerate();
}

void printInvalidCommand(std::ostream& outputStream)
{
  outputStream << "<INVALID COMMAND>\n";
}
