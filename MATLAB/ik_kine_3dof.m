function q = ik_kine_3dof(xyz, a)

x = xyz(1); 
y = xyz(2); 
z = xyz(3);

a1 = a(1); 
a2 = a(2); 
a3 = a(3);

% Joint 1
q1 = atan2(y, x);

% Reduce to planar problem
r  = sqrt(x^2 + y^2);

k1 = x / cos(q1);
k2 = y / sin(q1);
k3 = z - a1;

cos_q3 = (k1^2 + k3^2 - a2^2 - a3^2) / (2 * a2 * a3);
sin_q3 = sqrt(1 - cos_q3^2);

q3_d = atan2(sin_q3 , cos_q3 );
q3_u = atan2(-sin_q3, cos_q3 );

% Joint 2
q2_d = atan2(k3, r) - atan2(a3*sin(q3_d), a2 + a3*cos(q3_d));
q2_u = atan2(k3, r) - atan2(a3*sin(q3_u), a2 + a3*cos(q3_u));

q = [ q1, q2_d, q3_d;
      q1, q2_u, q3_u ];

disp("Parameters");
disp("q1: ");
disp(q1);
disp("k1:");
disp(k1);
disp("k2:");
disp(k2);
disp("k3:");
disp(k3);
disp("r:");
disp(r);
disp("cos_q3:");
disp(cos_q3);
disp("sin_q3:");
disp(sin_q3);
end

