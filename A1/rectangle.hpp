#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const rectangle_t& rectangle);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& pos) override;
  void move(const double dx, const double dy) override;
  point_t getCenter() const;
    
private:
  rectangle_t rectangleData_;
};

#endif
