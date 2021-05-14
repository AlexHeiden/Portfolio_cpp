#ifndef COMPOSITE_SHAPE_HPP
#define COMPOSITE_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace stepanov
{
  class Matrix;
  struct point_t;
  struct rectangle_t;

  class CompositeShape : public Shape
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape& compositeShape);
    CompositeShape(CompositeShape&& compositeShape) noexcept;
    ~CompositeShape() = default;

    CompositeShape& operator=(const CompositeShape& compositeShape);
    CompositeShape& operator=(CompositeShape&& compositeShape) noexcept;
    Ptr operator[](const size_t index) const;

    void add(const Ptr& shape);
    void remove(const size_t index);
    point_t getCenter() const override;
    size_t getSize() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& pos) override;
    void move(const double dx, const double dy) override;
    void scale(const double coefficient) override;
    void rotate(const double turn);
    Matrix split() const;
    void print() const override;

  private:
    size_t size_;
    std::unique_ptr<Ptr[]> array_;
  };
}

#endif
