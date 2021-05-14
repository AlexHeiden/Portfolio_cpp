#ifndef SPLIT_FUNCTION_HPP
#define SPLIT_FUNCTION_HPP

#include "shape.hpp"
#include "matrix.hpp"

namespace split_function
{
  stepanov::Matrix split(const std::unique_ptr<stepanov::Shape::Ptr[]>& listForSplit, const size_t size);
}

#endif
