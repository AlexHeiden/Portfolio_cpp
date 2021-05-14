#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace stepanov
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& center, const double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(const double dx, const double dy) override;
    point_t getCenter() const override;
    double getRadius() const;
    void scale(const double coefficient) override;
    void rotate(const double turn) override;
    void print() const;

  private:
    point_t center_;
    double radius_;
  };
};

#endif
