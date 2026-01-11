/*
- Copyright (c) 2026 Huzaifa Tahir, Aymen Jamil
- All rights reserved.
*/

#include <Servo.h>
// Defining the Pins of Servo Motors
#define F1_pin 9 
#define F2_pin 8
#define F3_pin 7

// Link Lengths of all the joins in centimeters
const int a1 = 3;         // May vary
const int a2 = 13;
const int a3 = 10;

// Target angles are where servo will move to.
// Set to 5 degrees because of the nails and screws in the base.
int ang_1 = 5;    // Can be set to 0 too.
int ang_2 = 5;
int ang_3 = 5;

// Declaring Servo objects
Servo F1, F2, F3;

// These are used to use move_step() function
int cur1 = 0;
int cur2 = 0;
int cur3 = 0;

// This array will hold all possible angles for desired position.
// q = [ [ {UP configuration angles} ], [ {DOWN configuration angles} ] ]
float q[3][2];

void setup()
{
  // Start serial communication
  Serial.begin(9600);
  
  // Initizlize servos
  F1.attach(F1_pin);
  F2.attach(F2_pin);
  F3.attach(F3_pin);

  // Move Servos to there initial position.
  F1.write(cur1);
  F2.write(cur2);
  F3.write(cur3);
}

void loop()
{
  Serial.println("Enter Positions (XYZ):");
  
  //Used for the Input Command given via Serial Monitor
  while (Serial.available() == 0) {}

  //Read the x, y and z Coordinates from Serial Input
  float x = Serial.parseFloat();
  float y = Serial.parseFloat();
  float z = Serial.parseFloat();

  // Call function for Inverse Kinematics
  ik_3dof(x, y, z, a1, a2, a3, q);        // Stores results in 'q'

  // Angles must be in degrees
  float q1   = round(rad2deg(q[0][0]));     // Theta 1 for Elbow up and Elbow down position
  float q2_u = round(rad2deg(q[1][0]));     // Theta 2 for Elbow up Joint
  float q3_u = round(rad2deg(q[2][0]));     // Theta 3 for Elbow up Joint
  float q2_d = round(rad2deg(q[1][1]));     // Theta 2 for Elbow Down Joint
  float q3_d = round(rad2deg(q[2][1]));     // Theta 3 for Elbow Down Joint

  // This one is tricky.
  // We align the joint angles of structure with the theory by mapping them to the range of corresponding servo angles
  // for actual structure, 0 degrees lies at -90 degrees and 180 degrees lies at 90 degrees.
  q3_u = map(q3_u, -90, 90, 0, 180);
  q3_d = map(q3_d, -90, 90, 0, 180);

  // If Condition for Elow Down Valid Positions for Servos 
  if ((q2_d <= 180) && (q2_d >= 0) && (q3_d <= 180) && (q3_d >= 0))
  {
    ang_1 = q1;
    ang_2 = q2_d;
    ang_3 = q3_d;

   // Moving Servos to Target Angles
    move_step(F1, cur1, ang_1);
    move_step(F2, cur2, ang_2);
    move_step(F3, cur3, ang_3);

    // Display the Elbow Down Angles on Serial Monitor
    Serial.println("============== DOWN ANGLES ================");
    Serial.print("q1 = "); Serial.println(ang_1);
    Serial.print("q2 = "); Serial.println(ang_2);
    Serial.print("q3 = "); Serial.println(ang_3);
    Serial.println("============== ----------- ================");
  }

  // If Condition for Elow Up Valid Positions for Servos 
  else if ((q2_u <= 180) && (q2_u >= 0) && (q3_u <= 180) && (q3_u >= 0))
  {
    ang_1 = q1;
    ang_2 = q2_u;
    ang_3 = q3_u;

    //Move Servos to Target Angles
    move_step(F1, cur1, ang_1);
    move_step(F2, cur2, ang_2);
    move_step(F3, cur3, ang_3);

    //Display Elbow Up Angles on Serial Monitor
    Serial.println("============== UP ANGLES ================");
    Serial.print("q1 = "); Serial.println(ang_1);
    Serial.print("q2 = "); Serial.println(ang_2);
    Serial.print("q3 = "); Serial.println(ang_3);
    Serial.println("============== ----------- ================");
  }
  else
  {
    //Point is unreachable if conditions aren't met
    Serial.println("ERROR! POSITION UNREACHABLE");
    Serial.println("ALL ANGLES");

    //Print all Angles
    Serial.print("q1_d = "); Serial.println(q1);
    Serial.print("q2_d = "); Serial.println(q2_d);
    Serial.print("q3_d = "); Serial.println(q3_d);
    Serial.print("q1_u = "); Serial.println(round(rad2deg(q1)));
    Serial.print("q2_u = "); Serial.println(rad2deg(q2_u));
    Serial.print("q3_u = "); Serial.println(rad2deg(q3_u));
    Serial.println("============== ----------- ================");
  }

  //Update the Positions to current angles 
  cur1 = ang_1;
  cur2 = ang_2;
  cur3 = ang_3;
}
