#include "matrix.hpp"
#include <stdexcept>
#include <iostream>
#include <memory>
#include "shape.hpp"

stepanov::Matrix::Matrix() :
  layers_(0),
  columns_(0),
  array_(nullptr)
{

}

stepanov::Matrix::Matrix(const Matrix& matrix) :
  layers_(matrix.layers_),
  columns_(matrix.columns_),
  array_(nullptr)
{
  if (matrix.layers_ != 0)
  {
    array_ = std::make_unique<stepanov::Shape::Ptr[]>(matrix.layers_ * matrix.columns_);
    for (size_t i = 0; i < matrix.layers_ * matrix.columns_; i++)
    {
      array_[i] = matrix.array_[i];
    }
  }
}

stepanov::Matrix::Matrix(Matrix&& matrix) noexcept :
  layers_(matrix.layers_),
  columns_(matrix.columns_),
  array_(std::move(matrix.array_))
{
  matrix.layers_ = 0;
  matrix.columns_ = 0;
}

stepanov::Matrix& stepanov::Matrix::operator=(const Matrix& matrix)
{
  if (this != &matrix)
  {
    if (matrix.layers_ == 0)
    {
      array_ = nullptr;
      layers_ = 0;
      columns_ = 0;
    }
    else
    {
      std::unique_ptr<Shape::Ptr[]> temp(std::make_unique<stepanov::Shape::Ptr[]>(matrix.layers_ * matrix.columns_));
      for (size_t i = 0; i < matrix.layers_ * matrix.columns_; i++)
      {
        temp[i] = matrix.array_[i];
      }
      array_ = std::move(temp);
      layers_ = matrix.layers_;
      columns_ = matrix.columns_;
    }
  }

  return *this;
}

stepanov::Matrix& stepanov::Matrix::operator=(Matrix&& matrix) noexcept
{
  if (this != &matrix)
  {
    layers_ = matrix.layers_;
    columns_ = matrix.columns_;
    matrix.layers_ = 0;
    matrix.columns_ = 0;
    array_ = std::move(matrix.array_);
  }

  return *this;
}

stepanov::Matrix::ConstLayer stepanov::Matrix::operator[](const size_t layerIndex) const
{
  if (layerIndex >= layers_)
  {
    throw std::invalid_argument("The row index must not exceed the number of rows");
  }

  return ConstLayer(layerIndex, *this);
}

stepanov::Matrix::NonConstLayer stepanov::Matrix::operator[](const size_t layerIndex)
{
  if (layerIndex >= layers_)
  {
    throw std::out_of_range("The row index must not exceed the number of rows");
  }

  return NonConstLayer(layerIndex, *this);
}

size_t stepanov::Matrix::getLayers() const
{
  return layers_;
}

void stepanov::Matrix::addShapeToLayer(const Shape::Ptr& shape, const size_t layerIndex)
{
  if (columns_ == 0)
  {
    addColumn();
    array_ = std::make_unique<stepanov::Shape::Ptr[]>(layers_ * columns_);
  }

  for (size_t i = 0; i < columns_; i++)
  {
    if (array_[layerIndex * columns_ + i] == nullptr)
    {
      std::unique_ptr<Shape::Ptr[]> temp(std::make_unique<stepanov::Shape::Ptr[]>(layers_ * columns_));
      for (size_t i = 0; i < layers_ * columns_; i++)
      {
        temp[i] = array_[i];
      }
      temp[layerIndex * columns_ + i] = shape;
      array_ = std::move(temp);
      break;
    }
    if (i == columns_ - 1)
    {
      addColumn();
      std::unique_ptr<Shape::Ptr[]> temp(std::make_unique<stepanov::Shape::Ptr[]>(layers_ * columns_));
      for (size_t i = 0; i < layers_ * columns_; i++)
      {
        temp[i] = array_[i];
      }
      temp[layerIndex * columns_ + columns_ - 1] = shape;
      array_ = std::move(temp);
      break;
    }
  }
}

stepanov::Matrix::NonConstLayer stepanov::Matrix::addLayer()
{
  if (array_ == nullptr)
  {
    layers_++;
  }
  else
  {
    std::unique_ptr<Shape::Ptr[]> temp(std::make_unique<stepanov::Shape::Ptr[]>((layers_ + 1) * columns_));
    for (size_t rowIndex = 0; rowIndex < layers_; rowIndex++)
    {
      for (size_t columnIndex = 0; columnIndex < columns_; columnIndex++)
      {
        temp[rowIndex * columns_ + columnIndex] = array_[rowIndex * columns_ + columnIndex];
      }
    }
    array_ = std::move(temp);
    layers_++;
  }

  return NonConstLayer(layers_ - 1, *this);
}

void stepanov::Matrix::print() const
{
  std::cout << "Matrix's number of rows equals: " << layers_
      << "\nMatrix's number of columns equals: " << columns_ << '\n';
  for (size_t i = 0; i < layers_ * columns_; i++)
  {
    std::cout << "The data of element with number " << i << '\n';
    if (array_[i] == nullptr)
    {
      std::cout << "This element doesn't contain any shape\n";
    }
    else
    {
      array_[i]->print();
    }
  }
}

void stepanov::Matrix::addColumn()
{
  std::unique_ptr<Shape::Ptr[]> temp(std::make_unique<stepanov::Shape::Ptr[]>(layers_ * (columns_ + 1)));
  for (size_t rowIndex = 0; rowIndex < layers_; rowIndex++)
  {
    for (size_t columnIndex = 0; columnIndex < columns_; columnIndex++)
    {
      temp[rowIndex * columns_ + columnIndex] = array_[rowIndex * columns_ + columnIndex];
    }
  }
  array_ = std::move(temp);
  columns_++;
}

stepanov::Matrix::ConstLayer::ConstLayer(const size_t layerIndex, const Matrix& matrix) :
  layerIndex_(layerIndex),
  matrix_(&matrix)
{

}

stepanov::Shape::Ptr stepanov::Matrix::ConstLayer::operator[](const size_t index) const
{
  if (index >= getSize())
  {
    throw std::out_of_range("The column index must not exceed the number of actual columns");
  }

  return matrix_->array_[layerIndex_ * matrix_->columns_ + index];
}

size_t stepanov::Matrix::ConstLayer::getSize() const
{
  size_t size = 0;
  for (size_t i = 0; i < matrix_->columns_; i++)
  {
    if (matrix_->array_[layerIndex_ * matrix_->columns_ + i] == nullptr)
    {
      return size;
    }
    size++;
  }

  return size;
}

stepanov::Matrix::NonConstLayer::NonConstLayer(const size_t layerIndex, Matrix& matrix) :
  ConstLayer(layerIndex, matrix),
  matrix_(&matrix)
{

}

void stepanov::Matrix::NonConstLayer::add(const Shape::Ptr& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("You can't add empty shape in layer");
  }

  matrix_->addShapeToLayer(shape, layerIndex_);
}
