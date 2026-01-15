clc; clear; close all;

%% Link lengths
l1 = 3;
l2 = 13;
l3 = 10;
a = [l1,l2,l3];
L(1) = Link('d', l1, 'a', 0,  'alpha',  pi/2);
L(2) = Link('d', 0,  'a', l2, 'alpha', 0);
L(3) = Link('d', 0,  'a', l3, 'alpha', 0);
robot = SerialLink(L, 'name', 'RRR_Spatial');

%% Desired tool-tip position (x, y, z)
p = [3, 4, 22];            % change as needed
q = ik_kine_3dof(p, a);
disp('Inverse Kinematics Solution (deg):');
disp(rad2deg(q));

%% Up and Down Configurations and Display
% DOWN Solution
q_d = q(1,:);
p_ch_up = ik_verify(q_d, a);
if round(p) == round(p_ch_up)
    disp("DOWN ANGLES CORRECT");
    disp(rad2deg(q_d));
else
    disp("!!!DOWN ANGLES WRONG!!!");
    disp(rad2deg(q_d));
end

% UP Solution
q_u = q(2,:);
p_ch_d = ik_verify(q_u, a);
if round(p) == round(p_ch_d)
    disp("UP ANGLES CORRECT");
    disp(rad2deg(q_u));
else
    disp("!!!UP ANGLES WRONG!!!");
    disp(rad2deg(q_u));
end

%% Visualization Down
f = figure;
robot.plot(q_d, 'workspace', [-25 25 -25 25 0 25]);
hold on
plot3(p(1),p(2),p(3),'ro','MarkerSize',10,'LineWidth',2);
drawnow;
saveas(f, 'DOWN.png');
title('Down Visualization')
% pts = workspace_3RRR(a);

%% Visualization UP
f = figure(2);
% robot.plot(q_u, 'workspace', [-25 25 -25 25 0 25]);
hold on
plot3(p(1),p(2),p(3),'ro','MarkerSize',10,'LineWidth',2);
drawnow;
saveas(f, 'UP.png');
title('Up-1 Visualization')

figure;
pts = workspace_3RRR(a);