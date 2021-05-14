#include <stdexcept>
#include "split-function.hpp"
#include "base-types.hpp"
#include "shape.hpp"

stepanov::Matrix split_function::split(const std::unique_ptr<stepanov::Shape::Ptr[]>& listForSplit, const size_t size)
{
  stepanov::Matrix matrix;

  if (size)
  {
    matrix.addLayer();
    for (size_t i = 0; i < size; i++)
    {
      bool crossingIndex = false;
      size_t crossingLineIndex = 0;
      for (size_t j = 0; j < matrix.getLayers(); j++)
      {
        for (size_t k = 0; k < matrix[j].getSize(); k++)
        {
          if (functions::isCrossed(matrix[j][k]->getFrameRect(), listForSplit[i]->getFrameRect()))
          {
            crossingIndex = true;
            crossingLineIndex = j;
            break;
          }
        }

        if (!crossingIndex)
        {
          matrix[j].add(listForSplit[i]);
          break;
        }

        if (crossingLineIndex == matrix.getLayers() - 1)
        {
          matrix.addLayer();
          matrix[matrix.getLayers() - 1].add(listForSplit[i]);
          break;
        }
      }
    }
  }
  return matrix;
}
