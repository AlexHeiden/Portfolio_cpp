#define USE_MATH_DEFINES

#include <cmath>
#include <memory>
#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "circle.hpp"
#include "base-types.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

BOOST_AUTO_TEST_SUITE(tests_for_composite_shape)

const double epsilon = 0.001;
const double circleRadius = 5.0;
const stepanov::point_t circleCenter = { 4.0, 5.0 };
const double rectangleWidth = 5.0;
const double rectangleHeight = 6.0;
const stepanov::point_t rectangleCenter = { 3.0, 4.0 };

BOOST_AUTO_TEST_CASE(composite_shape_parameters_correctness_after_move_on_axis_test)
{
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circle(circleCenter, circleRadius);
  stepanov::Rectangle rectangle({ rectangleWidth, rectangleHeight, rectangleCenter });
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangle));
  const double dx = 5.0;
  const double dy = 6.0;
  const double width = compositeShape.getFrameRect().width;
  const double height = compositeShape.getFrameRect().height;
  const double xCenter = compositeShape.getCenter().x;
  const double yCenter = compositeShape.getCenter().y;
  const double area = compositeShape.getArea();

  compositeShape.move(dx, dy);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().x, xCenter + dx, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().y, yCenter + dy, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, width, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, height, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, xCenter + dx, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, yCenter + dy, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_shape_parameters_correctness_after_moving_in_point_test)
{
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circle(circleCenter, circleRadius);
  stepanov::Rectangle rectangle({ rectangleWidth, rectangleHeight, rectangleCenter });
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangle));
  const stepanov::point_t movePoint = { 0.0, 0.0 };
  const double width = compositeShape.getFrameRect().width;
  const double height = compositeShape.getFrameRect().height;
  const double area = compositeShape.getArea();

  compositeShape.move(movePoint);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().x, movePoint.x, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().y, movePoint.y, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, width, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, height, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, movePoint.x, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, movePoint.y, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_shape_inside_composite_shape_test)
{
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circle(circleCenter, circleRadius);
  stepanov::Rectangle rectangle({ rectangleWidth, rectangleHeight, rectangleCenter });
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangle));

  stepanov::CompositeShape newCompositeShape;
  newCompositeShape.add(std::make_shared<stepanov::CompositeShape>(compositeShape));
  BOOST_CHECK_EQUAL(newCompositeShape.getSize(), 1);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), newCompositeShape.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(composite_shape_adding_test)
{
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circle(circleCenter, circleRadius);
  stepanov::Rectangle rectangle({ rectangleWidth, rectangleHeight, rectangleCenter });
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangle));

  BOOST_CHECK_EQUAL(compositeShape.getSize(), 2);
  BOOST_CHECK_CLOSE(compositeShape[0]->getCenter().x, circleCenter.x, epsilon);
  BOOST_CHECK_CLOSE(compositeShape[0]->getCenter().y, circleCenter.y, epsilon);
  BOOST_CHECK_CLOSE(compositeShape[1]->getCenter().x, rectangleCenter.x, epsilon);
  BOOST_CHECK_CLOSE(compositeShape[1]->getCenter().y, rectangleCenter.y, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_shape_afterscaling_test)
{
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circle(circleCenter, circleRadius);
  stepanov::Rectangle rectangle({ rectangleWidth, rectangleHeight, rectangleCenter });
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangle));
  const double width = compositeShape.getFrameRect().width;
  const double height = compositeShape.getFrameRect().height;
  const double area = compositeShape.getArea();
  const stepanov::point_t center = compositeShape.getCenter();
  const double coefficient = 2.0;
  const stepanov::point_t firstShapeCenter = compositeShape[0]->getCenter();
  const stepanov::point_t secondShapeCenter = compositeShape[1]->getCenter();

  compositeShape.scale(coefficient);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area * coefficient * coefficient, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().x, center.x, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().y, center.y, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, width * coefficient, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, height * coefficient, epsilon);
  BOOST_CHECK_CLOSE(center.x + coefficient * (firstShapeCenter.x - center.x), compositeShape[0]->getCenter().x, epsilon);
  BOOST_CHECK_CLOSE(center.y + coefficient * (firstShapeCenter.y - center.y), compositeShape[0]->getCenter().y, epsilon);
  BOOST_CHECK_CLOSE(center.x + coefficient * (secondShapeCenter.x - center.x), compositeShape[1]->getCenter().x, epsilon);
  BOOST_CHECK_CLOSE(center.y + coefficient * (secondShapeCenter.y - center.y), compositeShape[1]->getCenter().y, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_shape_afterremoval_area_test)
{
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circle(circleCenter, circleRadius);
  stepanov::Rectangle rectangle({ rectangleWidth, rectangleHeight, rectangleCenter });
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangle));
  const size_t startSize = 2;
  const size_t indexOfRectangle = 1;
  const double area = compositeShape.getArea();
  const double secondShapeArea = compositeShape[1]->getArea();

  compositeShape.remove(indexOfRectangle);
  BOOST_CHECK_EQUAL(compositeShape.getSize(), startSize - 1);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area - secondShapeArea, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_shape_rotate_test)
{
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circle(circleCenter, circleRadius);
  stepanov::Rectangle rectangle({ rectangleWidth, rectangleHeight, rectangleCenter });
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangle));
  const double width = compositeShape.getFrameRect().width;
  const double height = compositeShape.getFrameRect().height;
  const double xCenter = compositeShape.getCenter().x;
  const double yCenter = compositeShape.getCenter().y;
  const double centerToCircleLength = std::sqrt((circleCenter.x - compositeShape.getCenter().x) * (circleCenter.x - compositeShape.getCenter().x)
      + (circleCenter.y - compositeShape.getCenter().y) * (circleCenter.y - compositeShape.getCenter().y));
  const double centerToRectangleLength = std::sqrt((rectangleCenter.x - compositeShape.getCenter().x) * (rectangleCenter.x - compositeShape.getCenter().x)
      + (rectangleCenter.y - compositeShape.getCenter().y) * (rectangleCenter.y - compositeShape.getCenter().y));
  const double area = compositeShape.getArea();


  compositeShape.rotate(30);
  BOOST_CHECK_CLOSE(compositeShape.getArea(), area, epsilon);
  BOOST_CHECK_CLOSE(std::fabs(compositeShape.getFrameRect().height - compositeShape.getFrameRect().width),
      std::fabs(height - width), epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().x, xCenter, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getCenter().y, yCenter, epsilon);
  BOOST_CHECK_CLOSE(std::sqrt((compositeShape[0]->getCenter().x - compositeShape.getCenter().x) * (compositeShape[0]->getCenter().x - compositeShape.getCenter().x)
      + (compositeShape[0]->getCenter().y - compositeShape.getCenter().y) * (compositeShape[0]->getCenter().y - compositeShape.getCenter().y)),
      centerToCircleLength, epsilon);
  BOOST_CHECK_CLOSE(std::sqrt((compositeShape[1]->getCenter().x - compositeShape.getCenter().x) * (compositeShape[1]->getCenter().x - compositeShape.getCenter().x)
      + (compositeShape[1]->getCenter().y - compositeShape.getCenter().y) * (compositeShape[1]->getCenter().y - compositeShape.getCenter().y)),
      centerToRectangleLength, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_shape_frame_rectangle_with_emty_composite_shape_inside_test)
{
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circle(circleCenter, circleRadius);
  stepanov::CompositeShape newCompositeShape;
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  compositeShape.add(std::make_shared<stepanov::CompositeShape>(newCompositeShape));

  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().width, 2 * circleRadius, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().height, 2 * circleRadius, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.x, circleCenter.x, epsilon);
  BOOST_CHECK_CLOSE(compositeShape.getFrameRect().pos.y, circleCenter.y, epsilon);
}

BOOST_AUTO_TEST_CASE(composite_shape_invalid_adding_test)
{
  stepanov::CompositeShape compositeShape;
  BOOST_CHECK_THROW(compositeShape.add(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_actions_with_empty_composite_shape_test)
{
  stepanov::CompositeShape newCompositeShape;
  BOOST_CHECK_THROW(newCompositeShape.remove(1), std::runtime_error);
  BOOST_CHECK_THROW(newCompositeShape.getCenter(), std::runtime_error);
  BOOST_CHECK_THROW(newCompositeShape.move(circleCenter), std::runtime_error);
  BOOST_CHECK_THROW(newCompositeShape.move(circleCenter.x, circleCenter.y), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(composite_shape_invalid_scale_coefficient_test)
{
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circle(circleCenter, circleRadius);
  stepanov::Rectangle rectangle({ rectangleWidth, rectangleHeight, rectangleCenter });
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangle));

  BOOST_CHECK_THROW(compositeShape.scale(-2), std::invalid_argument);
  BOOST_CHECK_THROW(compositeShape.scale(0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(composite_shape_invalid_removing_index_test)
{
  stepanov::CompositeShape newCompositeShape;
  stepanov::Circle circle(circleCenter, circleRadius);
  newCompositeShape.add(std::make_shared<stepanov::Circle>(circle));
  BOOST_CHECK_THROW(newCompositeShape.remove(2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(adding_composite_shape_inside_itself_test)
{
  stepanov::CompositeShape compositeShape;
  stepanov::Circle circle(circleCenter, circleRadius);
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  std::shared_ptr<stepanov::CompositeShape> newCompositeShape = std::make_shared<stepanov::CompositeShape>(compositeShape);
  BOOST_CHECK_THROW(newCompositeShape->add(newCompositeShape), std::logic_error);
}

BOOST_AUTO_TEST_CASE(empty_constructor_test)
{
  stepanov::CompositeShape newCompositeShape;
  BOOST_CHECK_EQUAL(newCompositeShape.getSize(), 0.0);
  BOOST_CHECK_CLOSE(newCompositeShape.getArea(), 0.0, epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().width, 0.0, epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().height, 0.0, epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().pos.x, 0.0, epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().pos.y, 0.0, epsilon);
}

BOOST_AUTO_TEST_CASE(copy_constructor_test)
{
  stepanov::Circle circle(circleCenter, circleRadius);
  stepanov::Rectangle rectangle({ rectangleWidth, rectangleHeight, rectangleCenter });
  stepanov::CompositeShape compositeShape;
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangle));

  stepanov::CompositeShape newCompositeShape(compositeShape);
  BOOST_CHECK_EQUAL(newCompositeShape.getSize(), compositeShape.getSize());
  BOOST_CHECK_CLOSE(newCompositeShape.getArea(), compositeShape.getArea(), epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().width, compositeShape.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().height, compositeShape.getFrameRect().height, epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().pos.x, compositeShape.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().pos.y, newCompositeShape.getFrameRect().pos.y, epsilon);
}

BOOST_AUTO_TEST_CASE(copy_operator_test)
{
  stepanov::Circle circle(circleCenter, circleRadius);
  stepanov::Rectangle rectangle({ rectangleWidth, rectangleHeight, rectangleCenter });
  stepanov::CompositeShape compositeShape;
  compositeShape.add(std::make_shared<stepanov::Circle>(circle));
  compositeShape.add(std::make_shared<stepanov::Rectangle>(rectangle));

  stepanov::CompositeShape newCompositeShape = compositeShape;
  BOOST_CHECK_EQUAL(newCompositeShape.getSize(), compositeShape.getSize());
  BOOST_CHECK_CLOSE(newCompositeShape.getArea(), compositeShape.getArea(), epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().width, compositeShape.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().height, compositeShape.getFrameRect().height, epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().pos.x, compositeShape.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(newCompositeShape.getFrameRect().pos.y, newCompositeShape.getFrameRect().pos.y, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
