#define USE_MATH_DEFINES

#include <cmath>
#include <boost/test/unit_test.hpp>
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(tests_for_new_functions)

const double epsilon = 0.0001;

BOOST_AUTO_TEST_CASE(rotate_point_around_point_correctness_test)
{
  const stepanov::point_t center = { 1.0, 2.1 };
  const stepanov::point_t oldPosition = { 3.0, 4.5 };
  const double turn = 30 / 180 * M_PI;
  stepanov::point_t checkPosition = oldPosition;

  checkPosition = functions::getRotatedPointAroundPoint(checkPosition, center, turn);
  BOOST_CHECK_CLOSE(checkPosition.x, center.x + (oldPosition.x - center.x) * std::cos(turn)
      - (oldPosition.y - center.y) * std::sin(turn), epsilon);
  BOOST_CHECK_CLOSE(checkPosition.y, center.y + (oldPosition.x - center.x) * std::sin(turn)
      + (oldPosition.y - center.y) * std::cos(turn), epsilon);

  checkPosition = functions::getRotatedPointAroundPoint(checkPosition, center, -turn);
  BOOST_CHECK_CLOSE(checkPosition.x, oldPosition.x, epsilon);
  BOOST_CHECK_CLOSE(checkPosition.y, oldPosition.y, epsilon);
}

BOOST_AUTO_TEST_CASE(crossing_rectangles_correctness_test)
{
  const stepanov::rectangle_t firstRectangle = { 4.0, 2.0, {0.0, 0.0} };
  const stepanov::rectangle_t secondRectangle = { 4.0, 2.0, {2.0, 0.0} };

  BOOST_CHECK_EQUAL(functions::isCrossed(firstRectangle, secondRectangle), 1);
}

BOOST_AUTO_TEST_CASE(not_crossing_rectangles_correctness_test)
{
  const stepanov::rectangle_t firstRectangle = { 4.0, 2.0, {0.0, 0.0} };
  const stepanov::rectangle_t secondRectangle = { 4.0, 2.0, {5.0, 0.0} };

  BOOST_CHECK_EQUAL(functions::isCrossed(firstRectangle, secondRectangle), 0);
}

BOOST_AUTO_TEST_CASE(not_crossing_borders_touching_rectangles_correctness_test)
{
  const stepanov::rectangle_t firstRectangle = { 4.0, 2.0, {0.0, 0.0} };
  const stepanov::rectangle_t secondRectangle = { 4.0, 2.0, {4.0, 0.0} };

  BOOST_CHECK_EQUAL(functions::isCrossed(firstRectangle, secondRectangle), 0);
}

BOOST_AUTO_TEST_CASE(crossing_rectangle_inside_rectangle_correctness_test)
{
  const stepanov::rectangle_t firstRectangle = { 4.0, 2.0, {0.0, 0.0} };
  const stepanov::rectangle_t secondRectangle = { 1.0, 1.0, {0.0, 0.0} };

  BOOST_CHECK_EQUAL(functions::isCrossed(firstRectangle, secondRectangle), 1);
}

BOOST_AUTO_TEST_SUITE_END()
