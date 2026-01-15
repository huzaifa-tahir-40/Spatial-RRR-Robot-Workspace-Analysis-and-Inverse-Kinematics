function p_check = ik_verify(q, a)
% It performs forward kinematics to get the position vector for given joint angles.
% Purpose: to validate whether the joint angles from inverse kinematics are correct or not.
    l1 = a(1); l2 = a(2); l3 = a(3);
    q1 = q(1); q2 = q(2); q3 = q(3);

    x = cos(q1)*(l3*cos(q2 + q3) + l2*cos(q2));
    y = sin(q1)*(l3*cos(q2 + q3) + l2*cos(q2));
    z = l1 + l3*sin(q2 + q3) + l2*sin(q2);
    
    p_check = [x, y, z];


end
