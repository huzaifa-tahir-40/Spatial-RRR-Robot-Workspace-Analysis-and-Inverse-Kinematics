#include <math.h>

// const int a1 = 3;
// const int a2 = 13;
// const int a3 = 10;

void ik_3dof(float Px, float Py, float Pz, float a1, float a2, float a3, float q[3][2])
{
  float q1 = atan2(Py, Px);

  float r  = sqrt(Px*Px + Py*Py);

  float k1 = Px / cos(q1);
  float k2 = Py / sin(q1);
  float k3 = Pz - a1;

  float cos_q3 = ((k1*k1) + (k3*k3) - (a2*a2) - (a3*a3)) / (2 * a2 * a3);
  float sin_q3 = sqrt(1 - (cos_q3*cos_q3));

  float q3_d = atan2( sin_q3 , cos_q3 );
  float q3_u = atan2(-sin_q3, cos_q3 );

  float q2_d = atan2(k3, r) - atan2(a3*sin(q3_d), a2 + a3*cos(q3_d));
  float q2_u = atan2(k3, r) - atan2(a3*sin(q3_u), a2 + a3*cos(q3_u));

  Serial.println("====================== IK Calculations ==========================");
  Serial.println("====================== Parameters      ==========================");
  Serial.print("k1 = "); Serial.println(k1);
  Serial.print("k2 = "); Serial.println(k2);
  Serial.print("k3 = "); Serial.println(k3);
  Serial.print("r = "); Serial.println(r);
  Serial.print("cos_q3 = "); Serial.println(cos_q3);
  Serial.print("sin_q3 = "); Serial.println(sin_q3);
  Serial.println("====================== UP              ==========================");
  Serial.print("q1 = "); Serial.println(round(rad2deg(q1)));
  Serial.print("q2_up = "); Serial.println(rad2deg(q2_u));
  Serial.print("q3_up = "); Serial.println(rad2deg(q3_u));
  Serial.println("====================== DOWN            ==========================");
  Serial.print("q1 = "); Serial.println(round(rad2deg(q1)));
  Serial.print("q2_d = "); Serial.println(round(rad2deg(q2_d)));
  Serial.print("q3_d = "); Serial.println(round(rad2deg(q3_d)));
  Serial.println("====================== END             ==========================");

  q[0][0] = q1;
  q[1][0] = q2_u;
  q[2][0] = q3_u;

  q[0][1] = q1;
  q[1][1] = q2_d;
  q[2][1] = q3_d;
}
