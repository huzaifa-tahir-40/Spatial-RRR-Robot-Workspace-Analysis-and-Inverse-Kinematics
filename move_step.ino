void move_step(Servo &s, int &current, int target)
{
  while (current != target)
  {
    if (current < target)
      current += 2;
    else
      current -= 2;

    // prevent overshoot
    if (abs(current - target) < 2)
      current = target;

    s.write(current);
    delay(25);   // controls speed
  }
}