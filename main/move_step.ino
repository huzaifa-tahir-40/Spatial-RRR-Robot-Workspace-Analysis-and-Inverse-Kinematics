void move_step(Servo &s, int &current, int target)
{
/*
- The robot should move in incremental steps to reach the next angle.
- The purpose is to avoid gear damange in servo motors and to keep their motion steady.
*/
  // Loop continues till Servo reaches Target Angle
  while (current != target)
  {
    //If Current Angle is smaller than Target Angle
    if (current < target)
      //Increment by 2 steps
      current += 2;
    else
    //Decrement by 2 steps 
      current -= 2;

    // Prevent Overshoot
    //If Difference of angles is smaller then Step Size
    if (abs(current - target) < 2)
    //Current Angle = Target Angle
      current = target;

    //Send Undated Angle to Servo
    s.write(current);
    delay(25);   // controls speed
  }
}