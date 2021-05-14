#include <iostream>
#include <algorithm>
#include <iterator>
#include "point-shape.hpp"
#include "tasks.hpp"

void task2(std::istream& inputStream, std::ostream& outputStream)
{
  std::istream_iterator<Shape> inputIterator(inputStream);
  std::istream_iterator<Shape> endIterator;
  std::vector<Shape> vectorOfShapes(inputIterator, endIterator);

  if (!inputStream.eof())
  {
    throw std::runtime_error("File reading error");
  }

  size_t numberOfVertices = 0;
  size_t numberOfTriangles = 0;
  size_t numberOfSquares = 0;
  size_t numberOfRectangles = 0;

  std::for_each(vectorOfShapes.begin(), vectorOfShapes.end(),
      [&numberOfVertices, &numberOfTriangles, &numberOfSquares, &numberOfRectangles](const Shape& shape)
      {
        numberOfVertices += shape.size();

        switch (getTypeOfShape(shape))
        {
        case TRIANGLE:
        {
          numberOfTriangles++;
          break;
        }
        case RECTANGLE:
        {
          numberOfRectangles++;
          break;
        }
        case SQUARE:
        {
          numberOfRectangles++;
          numberOfSquares++;
          break;
        }
        default:
        {
          break;
        }
        }
      });

  vectorOfShapes.erase(std::remove_if(vectorOfShapes.begin(), vectorOfShapes.end(),
      [](const Shape& shape)
      {
        return getTypeOfShape(shape) == PENTAGON;
      }), vectorOfShapes.end());

  std::vector<Point> vectorOfPoints;

  std::transform(vectorOfShapes.begin(), vectorOfShapes.end(),
      std::back_inserter(vectorOfPoints),
      [](const Shape& shape)
      {
        return shape[0];
      });

  std::sort(vectorOfShapes.begin(), vectorOfShapes.end(),
      [](const Shape& first, const Shape& second)
      {
        return (getTypeOfShape(first) < getTypeOfShape(second));
      });
  
  outputStream << "Vertices: " << numberOfVertices << '\n'
      << "Triangles: " << numberOfTriangles << '\n'
      << "Squares: " << numberOfSquares << '\n'
      << "Rectangles: " << numberOfRectangles << '\n'
      << "Points: ";
  std::copy(vectorOfPoints.begin(), vectorOfPoints.end(), std::ostream_iterator<Point>(outputStream, " "));
  outputStream << '\n' << "Shapes:\n";
  std::copy(vectorOfShapes.begin(), vectorOfShapes.end(), std::ostream_iterator<Shape>(outputStream, "\n"));
}
