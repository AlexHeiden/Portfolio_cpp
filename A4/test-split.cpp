#include <memory>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "split-function.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "shape.hpp"
#include "matrix.hpp"

BOOST_AUTO_TEST_SUITE(tests_for_split_function)

BOOST_AUTO_TEST_CASE(split_correctness_test)
{
  std::unique_ptr<stepanov::Shape::Ptr[]> list = std::make_unique<stepanov::Shape::Ptr[]>(3);
  stepanov::Rectangle rectangleForFirstLayer({ 4.0, 2.0, {0.0, 0.0} });
  stepanov::CompositeShape compositeShapeForFirstLayer;
  stepanov::Circle circleForCompositeShape({ 0.0, 2.0 }, 1.0);
  stepanov::Rectangle rectangleForCompositeShape({ 4.0, 2.0, {3.0, 2.0} });
  stepanov::Circle circleForSecondLayer({ 2.0, 0.0 }, 1.0);
  compositeShapeForFirstLayer.add(std::make_shared<stepanov::Rectangle>(rectangleForCompositeShape));
  compositeShapeForFirstLayer.add(std::make_shared<stepanov::Circle>(circleForCompositeShape));
  list[0] = std::make_shared<stepanov::Rectangle>(rectangleForFirstLayer);
  list[1] = std::make_shared<stepanov::CompositeShape>(compositeShapeForFirstLayer);
  list[2] = std::make_shared<stepanov::Circle>(circleForSecondLayer);

  stepanov::Matrix matrix = split_function::split(list, 3);
  BOOST_CHECK_EQUAL(matrix.getLayers(), 2);
  BOOST_CHECK_EQUAL(matrix[0].getSize(), 2);
  BOOST_CHECK_EQUAL(matrix[1].getSize(), 1);
  BOOST_CHECK_EQUAL(matrix[0][0], list[0]);
  BOOST_CHECK_EQUAL(matrix[0][1], list[1]);
  BOOST_CHECK_EQUAL(matrix[1][0], list[2]);
}

BOOST_AUTO_TEST_CASE(split_nullptr_list_test)
{
  stepanov::Matrix matrix = split_function::split(nullptr, 0);
  BOOST_CHECK_EQUAL(matrix.getLayers(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
