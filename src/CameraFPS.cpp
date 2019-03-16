#include<glm/glm.hpp>
#include "../include/Camera.hpp"
#include "../include/Input.hpp"
#include "../include/CameraFPS.hpp"

CameraFPS::CameraFPS ()
{
    Camera();
}

CameraFPS::CameraFPS (float fov, float aspact, float nearPlane, float farPlane)
{
    Camera(fov, aspact, nearPlane, farPlane);
}

void CameraFPS::update (Window& win)
{
  if (Input::isPressed(win, MOVE_FORWARD))
  {
      positionOffset( CAMERA_SPEED * -forward() );
  }
  else if (Input::isPressed(win, MOVE_BACKWARD))
  {
      positionOffset( CAMERA_SPEED * forward() );
  }
  else if (Input::isPressed(win, MOVE_RIGHT))
  {
      positionOffset( CAMERA_SPEED * -right() );
  }
  else if (Input::isPressed(win, MOVE_LEFT))
  {
      positionOffset( CAMERA_SPEED * right() );
  }
  double mousex, mousey;
  Input::getCurPos(win, &mousex, &mousey);
  orientationOffset(mousey*MOUSE_SENSITIVITY, mousex*MOUSE_SENSITIVITY);
  Input::setCurPos(win, 0,0);
}
