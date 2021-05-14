#include <boost/test/unit_test.hpp>
#include <cmath>
#include "rectangle.hpp"
#include "base-types.hpp"

BOOST_AUTO_TEST_SUITE(tests_for_rectangles)

const double epsilon = 0.0001;
const double width = 6.1;
const double height = 5.0;
const double area = width * height;
const stepanov::point_t center = { 5.6, 6.7 };

BOOST_AUTO_TEST_CASE(rectangle_parameters_immutability_after_move_on_axis_test)
{
  stepanov::Rectangle rectangle(stepanov::rectangle_t{ width, height, center });
  const double dx = 5.0;
  const double dy = 6.0;
  rectangle.move(dx, dy);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, center.x + dx, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, center.y + dy, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, center.x + dx, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, center.y + dy, epsilon);
}

BOOST_AUTO_TEST_CASE(rectangle_parameters_immutability_after_moving_in_point_test)
{
  stepanov::Rectangle rectangle(stepanov::rectangle_t{ width, height, center });
  const stepanov::point_t newCenter = { 1.2, 3.4 };
  rectangle.move(newCenter);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, newCenter.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, newCenter.y, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, newCenter.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, newCenter.y, epsilon);
}

BOOST_AUTO_TEST_CASE(rectangle_afterscale_area_test)
{
  stepanov::Rectangle rectangle(stepanov::rectangle_t{ width, height, center });
  const double coefficient = 4.0;
  rectangle.scale(coefficient);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area * coefficient * coefficient, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getWidth(), width * coefficient, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), height * coefficient, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, rectangle.getWidth(), epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, rectangle.getHeight(), epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, center.y, epsilon);
}

BOOST_AUTO_TEST_CASE(rectangle_valid_arguments_test)
{
  stepanov::Rectangle rectangle(stepanov::rectangle_t{ width, height, center });
  BOOST_CHECK_CLOSE(rectangle.getWidth(), width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getHeight(), height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, width, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, height, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, center.y, epsilon);
}

BOOST_AUTO_TEST_CASE(rectangle_rotate_test)
{
  stepanov::Rectangle rectangle(stepanov::rectangle_t{ width, height, center });
  rectangle.rotate(45);
  BOOST_CHECK_CLOSE(rectangle.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(fabs(rectangle.getFrameRect().height - rectangle.getFrameRect().width),
      std::fabs(height - width), epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, center.x, epsilon);
  BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, center.y, epsilon);
}

BOOST_AUTO_TEST_CASE(rectangle_invalid_width_test)
{
  BOOST_CHECK_THROW(stepanov::Rectangle({ -width, height, center }), std::invalid_argument);
  const double zeroWidth = 0.0;
  BOOST_CHECK_THROW(stepanov::Rectangle({ zeroWidth, height, center }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectangle_invalid_height_test)
{
  BOOST_CHECK_THROW(stepanov::Rectangle({ width, -height, center }), std::invalid_argument);
  const double zeroHeight = 0.0;
  BOOST_CHECK_THROW(stepanov::Rectangle({ width, zeroHeight, center }), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(rectangle_invalid_scale_coefficient_test)
{
  stepanov::Rectangle rectangle({ width, height, center });
  double coefficient = -4.0;
  BOOST_CHECK_THROW(rectangle.scale(coefficient), std::invalid_argument);
  coefficient = 0.0;
  BOOST_CHECK_THROW(rectangle.scale(coefficient), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()
