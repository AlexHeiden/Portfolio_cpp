#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "shape.hpp"

namespace stepanov
{
  class Matrix
  {
  public:
    class ConstLayer
    {
    public:
      Shape::Ptr operator[] (const size_t index) const;
      size_t getSize() const;

    protected:
      size_t layerIndex_;

    private:
      const Matrix* matrix_;
      ConstLayer(const size_t rowIndex, const Matrix& matrix);
      friend class Matrix;
    };

    class NonConstLayer : public ConstLayer
    {
    public:
      void add(const Shape::Ptr& shape);

    private:
      NonConstLayer(const size_t rowIndex, Matrix& matrix);
      Matrix* matrix_;
      friend class Matrix;
    };

    Matrix();
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix) noexcept;
    ~Matrix() = default;

    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& matrix) noexcept;
    ConstLayer operator[](const size_t layerIndex) const;
    NonConstLayer operator[](const size_t layerIndex);

    size_t getLayers() const;
    NonConstLayer addLayer();
    void print() const;

  private:
    size_t layers_;
    size_t columns_;
    std::unique_ptr<Shape::Ptr[]> array_;
    void addShapeToLayer(const Shape::Ptr& shape, const size_t layerIndex);
    void addColumn();
  };
}

#endif
