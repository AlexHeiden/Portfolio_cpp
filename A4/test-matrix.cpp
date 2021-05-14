#include <memory>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "shape.hpp"
#include "matrix.hpp"

BOOST_AUTO_TEST_SUITE(tests_for_matrix)

BOOST_AUTO_TEST_CASE(empty_matrix_correctness_test)
{
  stepanov::Matrix matrix;
  BOOST_CHECK_EQUAL(matrix.getLayers(), 0);
}

BOOST_AUTO_TEST_CASE(correct_adding_layers_and_elements_in_matrix_test)
{
  stepanov::Matrix matrix;
  const size_t layers = matrix.getLayers();
  const size_t columns = 0;
  stepanov::Rectangle rectangle({ 4.0, 2.0, {0.0, 0.0} });
  matrix.addLayer();
  stepanov::Shape::Ptr shapeRectangle = std::make_shared<stepanov::Rectangle>(rectangle);

  matrix[0].add(shapeRectangle);
  BOOST_CHECK_EQUAL(layers + 1, matrix.getLayers());
  BOOST_CHECK_EQUAL(columns + 1, matrix[0].getSize());
  BOOST_CHECK_EQUAL(matrix[0][0], shapeRectangle);
}

BOOST_AUTO_TEST_CASE(copy_constructor_check_test)
{
  stepanov::Matrix matrix;
  matrix.addLayer();
  matrix.addLayer();
  stepanov::Rectangle rectangle({ 4.0, 2.0, {0.0, 0.0} });
  stepanov::Shape::Ptr shapeRectangle = std::make_shared<stepanov::Rectangle>(rectangle);
  stepanov::Circle circle({ 2.0, 0.0 }, 1.0);
  stepanov::Shape::Ptr shapeCircle = std::make_shared<stepanov::Circle>(circle);
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circleForCompositeShape({ 0.0, 2.0 }, 1.0);
  stepanov::Rectangle rectangleForCompositeShape({ 4.0, 2.0, {3.0, 2.0} });
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangleForCompositeShape));
  compositeShape.add(std::make_shared<stepanov::Circle>(circleForCompositeShape));
  stepanov::Shape::Ptr shapeCompositeShape = std::make_shared<stepanov::CompositeShape>(compositeShape);
  matrix[0].add(shapeRectangle);
  matrix[0].add(shapeCircle);
  matrix[1].add(shapeCompositeShape);

  stepanov::Matrix copiedMatrix(matrix);
  BOOST_CHECK_EQUAL(copiedMatrix.getLayers(), matrix.getLayers());
  BOOST_CHECK_EQUAL(copiedMatrix[0].getSize(), matrix[0].getSize());
  BOOST_CHECK_EQUAL(copiedMatrix[1].getSize(), matrix[1].getSize());
  BOOST_CHECK_EQUAL(matrix[0][0], copiedMatrix[0][0]);
  BOOST_CHECK_EQUAL(matrix[0][1], copiedMatrix[0][1]);
  BOOST_CHECK_EQUAL(matrix[1][0], copiedMatrix[1][0]);
}

BOOST_AUTO_TEST_CASE(copy_operator_check_test)
{
  stepanov::Matrix matrix;
  matrix.addLayer();
  matrix.addLayer();
  stepanov::Rectangle rectangle({ 4.0, 2.0, {0.0, 0.0} });
  stepanov::Shape::Ptr shapeRectangle = std::make_shared<stepanov::Rectangle>(rectangle);
  stepanov::Circle circle({ 2.0, 0.0 }, 1.0);
  stepanov::Shape::Ptr shapeCircle = std::make_shared<stepanov::Circle>(circle);
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circleForCompositeShape({ 0.0, 2.0 }, 1.0);
  stepanov::Rectangle rectangleForCompositeShape({ 4.0, 2.0, {3.0, 2.0} });
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangleForCompositeShape));
  compositeShape.add(std::make_shared<stepanov::Circle>(circleForCompositeShape));
  stepanov::Shape::Ptr shapeCompositeShape = std::make_shared<stepanov::CompositeShape>(compositeShape);
  matrix[0].add(shapeRectangle);
  matrix[0].add(shapeCircle);
  matrix[1].add(shapeCompositeShape);

  stepanov::Matrix copiedMatrix = matrix;
  BOOST_CHECK_EQUAL(copiedMatrix.getLayers(), matrix.getLayers());
  BOOST_CHECK_EQUAL(copiedMatrix[0].getSize(), matrix[0].getSize());
  BOOST_CHECK_EQUAL(copiedMatrix[1].getSize(), matrix[1].getSize());
  BOOST_CHECK_EQUAL(matrix[0][0], copiedMatrix[0][0]);
  BOOST_CHECK_EQUAL(matrix[0][1], copiedMatrix[0][1]);
  BOOST_CHECK_EQUAL(matrix[1][0], copiedMatrix[1][0]);
}

BOOST_AUTO_TEST_CASE(incorrect_adding_elements_in_matrix_test)
{
  stepanov::Matrix matrix;
  stepanov::Rectangle rectangle({ 4.0, 2.0, {0.0, 0.0} });
  matrix.addLayer();
  BOOST_CHECK_THROW(matrix[0].add(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(incorrect_first_index_test)
{
  stepanov::Matrix matrix;
  stepanov::Rectangle rectangle({ 4.0, 2.0, {0.0, 0.0} });
  BOOST_CHECK_THROW(matrix[2].add(std::make_shared<stepanov::Rectangle>(rectangle)), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(incorrect_second_index_test)
{
  stepanov::Matrix matrix;
  matrix.addLayer();
  BOOST_CHECK_THROW(matrix[0][5]->print(), std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()
