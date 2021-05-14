#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace stepanov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const rectangle_t& rectangle, double turn = 0);
    double getArea() const override;
    double getWidth() const;
    double getHeight() const;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(const double dx, const double dy) override;
    point_t getCenter() const override;
    void scale(const double coefficient) override;
    void rotate(const double turn) override;
    void print() const override;

  private:
    point_t center_;
    point_t positions_[4];
  };
};

#endif
