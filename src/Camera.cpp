#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../include/Camera.hpp"
Camera::Camera() {}
Camera::Camera( float fov, float aspact, float nearPlane, float farPlane ) : fov_(fov), aspact_( aspact ), nearPlane_( nearPlane ), farPlane_( farPlane )
{
  position_ = glm::vec3( 0,0,0 );
  verticleAngle_ = 0;
  horizontalAngle_ = 0;
}

void Camera::setFOV( float angle )
{
  fov_ = glm::radians(angle);
}
float Camera::fov() const
{
  return glm::degrees(fov_);
}

void Camera::setAspect( float x )
{
  aspact_ = x;
}
float Camera::aspect() const
{
  return aspact_;
}

void Camera::setClipZ( float x, float y )
{
  nearPlane_ = x;
  farPlane_ = y;
}
float Camera::nearPlane() const
{
  return nearPlane_;
}
float Camera::farPlane() const
{
  return farPlane_;
}

void Camera::setPosition( glm::vec3 x)
{
  position_ = x;
}
glm::vec3 Camera::position() const
{
  return position_;
}

void Camera::lookAt( glm::vec3 target )
{
  glm::vec3 dir = glm::normalize(target - position_);
  horizontalAngle_ = asinf(glm::dot(dir, glm::vec3(0,1,0)));
  verticleAngle_ = asinf(glm::dot(dir, glm::vec3(1,0,0)));
  normalizeAngle();

}

glm::mat4 Camera::Orientation()
{
  glm::mat4 view(1.0);
  view = glm::rotate( view, verticleAngle_, glm::vec3( -1, 0, 0 ) );
  view = glm::rotate( view, horizontalAngle_, glm::vec3( 0, -1, 0 ) );
  return view;
}

glm::mat4 Camera::View()
{
  return (Orientation()*glm::translate( glm::mat4(1.0), -position_ ));
}

glm::mat4 Camera::cameraMatrix()
{
  glm::mat4 camera = glm::perspective( fov_, aspact_, nearPlane_, farPlane_ );
  camera *= View();
  return camera;
}
void Camera::positionOffset( glm::vec3 target )
{
  position_ += target;
}

glm::vec3 Camera::up()
{
  glm::vec3 u = glm::inverse(Orientation()) * glm::vec4( 0, 1, 0, 1 );
  return u;
}

glm::vec3 Camera::forward()
{
  glm::vec3 v = glm::inverse(Orientation()) * glm::vec4( 0, 0, 1, 1);
  return v;
}

glm::vec3 Camera::right()
{
  glm::vec3 n = glm::inverse(Orientation()) * glm::vec4( 1, 0, 0, 1 );
  return n;
}
void Camera::info()
{
  std::cout << fov_ << '\n';
  std::cout << aspact_ << '\n';
  std::cout << nearPlane_ << '\n';
  std::cout << farPlane_ << '\n';
  std::cout << horizontalAngle_ << '\n';
  std::cout << verticleAngle_ << '\n';
  float* temp = glm::value_ptr(position_ );
  for( int i = 0; i < 3; ++i)
    std::cout << "position" << temp[i] << '\n';
}

void Camera::orientationOffset( float upAngle, float rightAngle )
{
  horizontalAngle_ += rightAngle;
  verticleAngle_ += upAngle;
  normalizeAngle();
}

void Camera::normalizeAngle()
{
  horizontalAngle_ = fmodf( horizontalAngle_, 2*3.14 );
  if(horizontalAngle_ < 0 )
    horizontalAngle_ += 2*M_PI ;
  if(verticleAngle_ > MAX_VERTICLE_ANGLE )
    verticleAngle_ = MAX_VERTICLE_ANGLE;
  if(verticleAngle_ < -MAX_VERTICLE_ANGLE )
    verticleAngle_ = -MAX_VERTICLE_ANGLE;
}
