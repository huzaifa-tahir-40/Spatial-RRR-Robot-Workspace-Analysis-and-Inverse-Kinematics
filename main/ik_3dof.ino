#include <math.h>
void ik_3dof(float Px, float Py, float Pz, float a1, float a2, float a3, float q[3][2])
{
/*
- This function is used to perform inverse kinematics calculations
- Px, Py, Pz are XYZ coordinate position where the end-effector should move to.
- a1, a2, a3 are link lengths.
- q[3][2] is an array of possible joint angles for the desired XYZ coordinate position.
- There are two possible joint angle answers for each coordinate position in the workspace.
*/
  //Calculate the Angle for Joint 1 (Thetha 1) 
  float q1 = atan2(Py, Px);
  //Projection of Universal Frame on Target Frame
  float r  = sqrt(Px*Px + Py*Py);

  //Intermediate parameters
  float k1 = Px / cos(q1);
  float k2 = Py / sin(q1);
  float k3 = Pz - a1;

  float cos_q3 = ((k1*k1) + (k3*k3) - (a2*a2) - (a3*a3)) / (2 * a2 * a3);
  float sin_q3 = sqrt(1 - (cos_q3*cos_q3));

  //Joint Angles for Elbow Down and Elbow Up Configuration.
  float q3_d = atan2( sin_q3 , cos_q3 );  //Theta 3 for Elbow Down
  float q3_u = atan2(-sin_q3, cos_q3 );  // Theta 3 for Elbow Up

  float q2_d = atan2(k3, r) - atan2(a3*sin(q3_d), a2 + a3*cos(q3_d)); //Theta 2 for Elbow Down
  float q2_u = atan2(k3, r) - atan2(a3*sin(q3_u), a2 + a3*cos(q3_u)); //Thata 2 for Elbow Up

  // For Displaying Output in Serial Monitor
  Serial.println("====================== IK Calculations ==========================");
  Serial.println("====================== Parameters      ==========================");
  Serial.print("k1 = "); Serial.println(k1);
  Serial.print("k2 = "); Serial.println(k2);
  Serial.print("k3 = "); Serial.println(k3);
  Serial.print("r = "); Serial.println(r);
  Serial.print("cos_q3 = "); Serial.println(cos_q3);
  Serial.print("sin_q3 = "); Serial.println(sin_q3);

  // For Displaying Elbow Up Output in Serial Monitor
  Serial.println("====================== UP              ==========================");
  Serial.print("q1 = "); Serial.println(round(rad2deg(q1)));
  Serial.print("q2_up = "); Serial.println(rad2deg(q2_u));
  Serial.print("q3_up = "); Serial.println(rad2deg(q3_u));
  
  // For Displaying Elow Down Output in Serial Monitor
  Serial.println("====================== DOWN            ==========================");
  Serial.print("q1 = "); Serial.println(round(rad2deg(q1)));
  Serial.print("q2_d = "); Serial.println(round(rad2deg(q2_d)));
  Serial.print("q3_d = "); Serial.println(round(rad2deg(q3_d)));
  Serial.println("====================== END             ==========================");

  //Store Result in Output Matrix
  //Elbow Up Configuration 
  q[0][0] = q1;
  q[1][0] = q2_u;
  q[2][0] = q3_u;

  //Elbow Down Configuration
  q[0][1] = q1;
  q[1][1] = q2_d;
  q[2][1] = q3_d;
}
