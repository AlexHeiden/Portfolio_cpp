#include "point-shape.hpp"
#include <cstddef>
#include <cmath>
#include <iterator>
#include <algorithm>
#include <iostream>
#include "utility.hpp"

typeOfShape getTypeOfShape(const Shape& shape)
{
  if (shape.size() == 3)
  {
    return TRIANGLE;
  }

  if (shape.size() == 4)
  {
    const double firstSide = std::sqrt((shape[1].x - shape[0].x) * (shape[1].x - shape[0].x) 
        + (shape[1].y - shape[0].y) * (shape[1].y - shape[0].y));
    const double secondSide = std::sqrt((shape[2].x - shape[1].x) * (shape[2].x - shape[1].x)
        + (shape[2].y - shape[1].y) * (shape[2].y - shape[1].y));
    const double thirdSide = std::sqrt((shape[3].x - shape[2].x) * (shape[3].x - shape[2].x)
        + (shape[3].y - shape[2].y) * (shape[3].y - shape[2].y));
    const double fourthSide = std::sqrt((shape[0].x - shape[3].x) * (shape[0].x - shape[3].x)
        + (shape[0].y - shape[3].y) * (shape[0].y - shape[3].y));

    if ((firstSide != thirdSide) || (secondSide != fourthSide))
    {
      return OTHER_TYPE;
    }

    if (firstSide * firstSide + fourthSide * fourthSide
        != firstSide * firstSide + secondSide * secondSide)
    {
      return OTHER_TYPE;
    }

    if ((firstSide == secondSide) && (firstSide == fourthSide))
    {
      return SQUARE;
    }
    else
    {
      return RECTANGLE;
    }
  }

  if (shape.size() == 5)
  {
    return PENTAGON;
  }

  return OTHER_TYPE;
}

std::istream& operator>>(std::istream& inputStream, Shape& shape)
{
  std::istream::sentry sentry(inputStream);

  if (sentry)
  {
    StreamGuard streamGuard(inputStream);

    inputStream >> std::noskipws;
    inputStream >> std::ws;

    size_t numberOfPoints;
    inputStream >> numberOfPoints;
    if (!inputStream)
    {
      return inputStream;
    }

    if (!numberOfPoints)
    {
      inputStream.setstate(std::ios::failbit);
      return inputStream;
    }

    Shape temp;

    for (size_t i = 0; i < numberOfPoints; i++)
    {
      Point point;
      inputStream >> point;
      temp.push_back(point);
    }

    shape = std::move(temp);
  }

  return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const Shape& shape)
{
  std::ostream::sentry sentry(outputStream);

  if (sentry)
  {
    outputStream << shape.size() << ' ';
    std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(outputStream, " "));
  }

  return outputStream;
}

std::istream& operator>>(std::istream& inputStream, Point& point)
{
  std::istream::sentry sentry(inputStream);

  if (sentry)
  {
    StreamGuard streamGuard(inputStream);

    inputStream >> std::noskipws;
    inputStream >> skip_ws;

    char firstRoundBracket;
    inputStream >> firstRoundBracket;

    if (!inputStream)
    {
      return inputStream;
    }

    if (firstRoundBracket != '(')
    {
      inputStream.unget();
      inputStream.setstate(std::ios::failbit);
      return inputStream;
    }

    inputStream >> skip_ws;

    int x;
    inputStream >> x;

    if (!inputStream)
    {
      return inputStream;
    }

    inputStream >> skip_ws;

    char semicolon;
    inputStream >> semicolon;

    if (!inputStream)
    {
      return inputStream;
    }

    if (semicolon != ';')
    {
      inputStream.unget();
      inputStream.setstate(std::ios::failbit);
      return inputStream;
    }

    inputStream >> skip_ws;

    int y;
    inputStream >> y;

    if (!inputStream)
    {
      return inputStream;
    }

    inputStream >> skip_ws;

    char secondRoundBracket;
    inputStream >> secondRoundBracket;

    if (!inputStream)
    {
      return inputStream;
    }

    if (secondRoundBracket != ')')
    {
      inputStream.unget();
      inputStream.setstate(std::ios::failbit);
      return inputStream;
    }

    point = { x, y };
  }

  return inputStream;
}

std::ostream& operator<<(std::ostream& outputStream, const Point& point)
{
  std::ostream::sentry sentry(outputStream);

  if (sentry)
  {
    outputStream << '(' << point.x << "; " << point.y << ')';
  }

  return outputStream;
}
