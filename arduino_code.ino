#include <Servo.h>

Servo x, x2, y;
int cam_width = 640, cam_height = 480;
int xpos_to_go = 90, ypos_to_go = 90, current_xpos = 90, current_ypos = 90;
int min_x = 20, max_x = 130;
int min_y = 20, max_y = 130;

void setup()
{

  Serial.begin(9600);

  x.attach(3);
  x2.attach(4);
  y.attach(2);

  x.write(xpos_to_go);
  x2.write(xpos_to_go);
  y.write(ypos_to_go);
}

void loop()
{
  if (Serial.available() > 0)
  {
    int x_coordinate, y_coordinate;

    if (Serial.read() == 'X')
    {
      x_coordinate = Serial.parseInt(); // read center x-coordinate
      if (Serial.read() == 'Y')
        y_coordinate = Serial.parseInt(); // read center y-coordinate
    }

    xpos_to_go = x_coordinate / (cam_width / (max_x - min_x));
    ypos_to_go = y_coordinate / (cam_height / (max_y - min_y));

    // if the servo degree is outside its range
    if (xpos_to_go >= max_y)
      xpos_to_go = max_x;
    else if (xpos_to_go <= min_y)
      xpos_to_go = min_x;

    if (ypos_to_go >= max_y)
      ypos_to_go = max_y;
    else if (ypos_to_go <= min_y)
      ypos_to_go = min_y;

    int diff = current_xpos - xpos_to_go;
    xpos_to_go = current_xpos;

    for (int i = 1; i < abs(diff); i++)
    {
      if (diff > 0)
      {
        xpos_to_go -= 1;
      }
      else
      {
        xpos_to_go += 1;
      }

      x.write(xpos_to_go);
      x2.write(xpos_to_go);
    }
    diff = current_ypos - ypos_to_go;
    ypos_to_go = current_ypos;

    for (int i = 1; i < abs(diff); i++)
    {
      if (diff > 0)
      {
        ypos_to_go -= 1;
      }
      else
      {
        ypos_to_go += 1;
      }

      y.write(ypos_to_go);
    }

    current_xpos = xpos_to_go;
    current_ypos = ypos_to_go;
  }
}