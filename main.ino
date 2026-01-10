#include <Servo.h>

#define F1_pin 9
#define F2_pin 8
#define F3_pin 7

const int a1 = 3;
const int a2 = 13;
const int a3 = 10;

int ang_1 = 5;
int ang_2 = 5;
int ang_3 = 5;

Servo F1, F2, F3;

int cur1 = 0;
int cur2 = 0;
int cur3 = 0;

float q[3][2];

void setup()
{
  Serial.begin(9600);

  F1.attach(F1_pin);
  F2.attach(F2_pin);
  F3.attach(F3_pin);

  F1.write(cur1);
  F2.write(cur2);
  F3.write(cur3);
}

void loop()
{
  Serial.println("Enter Positions (XYZ):");

  while (Serial.available() == 0) {}

  float x = Serial.parseFloat();
  float y = Serial.parseFloat();
  float z = Serial.parseFloat();

  ik_3dof(x, y, z, a1, a2, a3, q);

  float q1   = round(rad2deg(q[0][0]));     // fixed
  float q2_u = round(rad2deg(q[1][0]));
  float q3_u = round(rad2deg(q[2][0]));
  float q2_d = round(rad2deg(q[1][1]));
  float q3_d = round(rad2deg(q[2][1]));

  q3_u = map(q3_u, -90, 90, 0, 180);
  q3_d = map(q3_d, -90, 90, 0, 180);

  if ((q2_d <= 180) && (q2_d >= 0) && (q3_d <= 180) && (q3_d >= 0))
  {
    ang_1 = q1;
    ang_2 = q2_d;
    ang_3 = q3_d;

    move_step(F1, cur1, ang_1);
    move_step(F2, cur2, ang_2);
    move_step(F3, cur3, ang_3);
    Serial.println("============== DOWN ANGLES ================");
    Serial.print("q1 = "); Serial.println(ang_1);
    Serial.print("q2 = "); Serial.println(ang_2);
    Serial.print("q3 = "); Serial.println(ang_3);
    Serial.println("============== ----------- ================");
  }
  else if ((q2_u <= 180) && (q2_u >= 0) && (q3_u <= 180) && (q3_u >= 0))
  {
    ang_1 = q1;
    ang_2 = q2_u;
    ang_3 = q3_u;

    move_step(F1, cur1, ang_1);
    move_step(F2, cur2, ang_2);
    move_step(F3, cur3, ang_3);
    Serial.println("============== UP ANGLES ================");
    Serial.print("q1 = "); Serial.println(ang_1);
    Serial.print("q2 = "); Serial.println(ang_2);
    Serial.print("q3 = "); Serial.println(ang_3);
    Serial.println("============== ----------- ================");
  }
  else
  {
    Serial.println("ERROR! POSITION UNREACHABLE");
    Serial.println("ALL ANGLES");
    Serial.print("q1_d = "); Serial.println(q1);
    Serial.print("q2_d = "); Serial.println(q2_d);
    Serial.print("q3_d = "); Serial.println(q3_d);
    Serial.print("q1_u = "); Serial.println(round(rad2deg(q1)));
    Serial.print("q2_u = "); Serial.println(rad2deg(q2_u));
    Serial.print("q3_u = "); Serial.println(rad2deg(q3_u));
    Serial.println("============== ----------- ================");
  }

  cur1 = ang_1;
  cur2 = ang_2;
  cur3 = ang_3;
}
