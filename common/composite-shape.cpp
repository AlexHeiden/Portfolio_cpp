#include "composite-shape.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <memory>
#include "base-types.hpp"
#include "split-function.hpp"

stepanov::CompositeShape::CompositeShape() :
  size_(0),
  array_(nullptr)
{

}

stepanov::CompositeShape::CompositeShape(const CompositeShape& compositeShape) :
  size_(compositeShape.size_),
  array_(nullptr)
{
  if (compositeShape.size_ != 0)
  {
    array_ = std::make_unique<Ptr[]>(compositeShape.size_);
    for (size_t i = 0; i < compositeShape.size_; i++)
    {
      array_[i] = compositeShape.array_[i];
    }
  }
}

stepanov::CompositeShape::CompositeShape(CompositeShape&& compositeShape) noexcept :
  size_(compositeShape.size_),
  array_(std::move(compositeShape.array_))
{
  compositeShape.size_ = 0;
}

stepanov::CompositeShape& stepanov::CompositeShape::operator=(const CompositeShape& compositeShape)
{
  if (this != &compositeShape)
  {
    if (compositeShape.size_ == 0)
    {
      array_ = nullptr;
      size_ = 0;
    }
    else
    {
      std::unique_ptr<Ptr[]> temp(std::make_unique<Ptr[]>(compositeShape.size_));
      for (size_t i = 0; i < size_; i++)
      {
        temp[i] = compositeShape.array_[i];
      }
      array_ = std::move(temp);
      size_ = compositeShape.size_;
    }
  }

  return *this;
}

stepanov::CompositeShape& stepanov::CompositeShape::operator=(CompositeShape&& compositeShape) noexcept
{
  if (this != &compositeShape)
  {
    size_ = compositeShape.size_;
    array_ = std::move(compositeShape.array_);
    compositeShape.size_ = 0;
  }

  return *this;
}

stepanov::Shape::Ptr stepanov::CompositeShape::operator[](const size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("The index is invalid");
  }

  return array_[index];
}

void stepanov::CompositeShape::add(const Ptr& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Shape parameter can't be empty");
  }

  if (this == shape.get())
  {
    throw std::logic_error("You can't add composite-shape into itself");
  }

  std::unique_ptr<Ptr[]> temp(std::make_unique<Ptr[]>(size_ + 1));
  for (size_t i = 0; i < size_; i++)
  {
    temp[i] = array_[i];
  }
  temp[size_] = shape;
  array_ = std::move(temp);
  size_++;
}

void stepanov::CompositeShape::remove(const size_t index)
{
  if (size_ == 0)
  {
    throw std::runtime_error("You can't remove elements from empty composite-shape");
  }

  if (index >= size_)
  {
    throw std::out_of_range("The index of removable element can't be greater than its size or be equal to it");
  }

  std::unique_ptr<Ptr[]> temp(std::make_unique<Ptr[]>(size_));
  for (size_t i = 0; i < size_; i++)
  {
    temp[i] = array_[i];
  }

  for (size_t i = index + 1; i < size_ - 1; i++)
  {
    temp[i] = temp[i + 1];
  }
  temp[size_ - 1].reset();
  array_ = std::move(temp);
  size_--;
}

stepanov::point_t stepanov::CompositeShape::getCenter() const
{
  if (size_ == 0)
  {
    throw std::runtime_error("Composite-shape is empty, so it has no center");
  }

  return getFrameRect().pos;
}

size_t stepanov::CompositeShape::getSize() const
{
  return size_;
}

double stepanov::CompositeShape::getArea() const
{
  double commonArea = 0.0;
  for (size_t i = 0; i < size_; i++)
  {
    commonArea += array_[i]->getArea();
  }

  return commonArea;
}

stepanov::rectangle_t stepanov::CompositeShape::getFrameRect() const
{
  if (size_ == 0)
  {
    return rectangle_t{ 0, 0, {0 , 0} };
  }

  rectangle_t temp = array_[0]->getFrameRect();
  double leftSide = temp.pos.x - temp.width / 2;
  double topSide = temp.pos.y + temp.height / 2;
  double rightSide = temp.pos.x + temp.width / 2;
  double bottomSide = temp.pos.y - temp.height / 2;

  for (size_t i = 1; i < size_; i++)
  {
    if (array_[i]->getFrameRect().width == 0)
    {
      continue;
    }

    if (leftSide == 0 && rightSide == 0)
    {
      temp = array_[i]->getFrameRect();
      leftSide = temp.pos.x - temp.width / 2;
      topSide = temp.pos.y + temp.height / 2;
      rightSide = temp.pos.x + temp.width / 2;
      bottomSide = temp.pos.y - temp.height / 2;
    }

    temp = array_[i]->getFrameRect();
    leftSide = std::min(leftSide, temp.pos.x - temp.width / 2);
    topSide = std::max(topSide, temp.pos.y + temp.height / 2);
    rightSide = std::max(rightSide, temp.pos.x + temp.width / 2);
    bottomSide = std::min(bottomSide, temp.pos.y - temp.height / 2);
  }

  return stepanov::rectangle_t{ rightSide - leftSide, topSide - bottomSide,
      { rightSide - (rightSide - leftSide) / 2, topSide - (topSide - bottomSide) / 2 } };
}

void stepanov::CompositeShape::move(const point_t& pos)
{
  if (size_ == 0)
  {
    throw std::runtime_error("You can't move composite-shape while it's empty");
  }

  move(pos.x - getCenter().x, pos.y - getCenter().y);
}

void stepanov::CompositeShape::move(const double dx, const double dy)
{
  if (size_ == 0)
  {
    throw std::runtime_error("You can't move composite-shape while it's empty");
  }

  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move(dx, dy);
  }
}

void stepanov::CompositeShape::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Scale coefficient can't be negative or equal zero");
  }

  for (size_t i = 0; i < size_; i++)
  {
    array_[i]->move({ coefficient * (array_[i]->getCenter().x - getCenter().x) + getCenter().x,
        coefficient * (array_[i]->getCenter().y - getCenter().y) + getCenter().y });
    array_[i]->scale(coefficient);
  }
}

void stepanov::CompositeShape::rotate(const double turn)
{
  const point_t currentCenterOfShape = getCenter();

  for (size_t i = 0; i < size_; i++)
  {
    const point_t shapeCenter = array_[i]->getCenter();
    array_[i]->move(functions::getRotatedPointAroundPoint(shapeCenter, currentCenterOfShape, turn));
    array_[i]->rotate(turn);
  }
}

stepanov::Matrix stepanov::CompositeShape::split() const
{
  return split_function::split(array_, getSize());
}

void stepanov::CompositeShape::print() const
{
  std::cout << "The size of composite-shape equals " << size_ << '\n';
  for (size_t i = 0; i < size_; i++)
  {
    std::cout << "The data of the element of composite-shape with number " << i << ":\n";
    array_[i]->print();
  }
}
