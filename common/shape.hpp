#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>

namespace stepanov
{
  struct point_t;
  struct rectangle_t;

  class Shape
  {
  public:
    using Ptr = std::shared_ptr<Shape>;
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& pos) = 0;
    virtual void move(const double x, const double y) = 0;
    virtual void scale(const double coefficient) = 0;
    virtual void rotate(const double turn) = 0;
    virtual void print() const = 0;
    virtual point_t getCenter() const = 0;
  };
};

#endif
