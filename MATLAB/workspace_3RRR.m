function pts = workspace_3RRR(a)

l1 = a(1); l2 = a(2); l3 = a(3);

q1 = linspace(0,pi,20);
q2 = linspace(0,pi,20);
q3 = linspace(-pi/2,pi/2,20);

x = zeros(1, length(q1)*length(q2)*length(q3));
y = zeros(1, length(q1)*length(q2)*length(q3));
z = zeros(1, length(q1)*length(q2)*length(q3));

pts = zeros(3, length(q1)*length(q2)*length(q3));
n = 1;

for i = 1:length(q1)
    for j = 1:length(q2)
        for k = 1:length(q3)
            x(1,n) = (l2*cos(q1(i)) + l3*cos(q2(j)+q3(k)))*cos(q1(i));
            y(1,n) = (l2*cos(q1(i)) + l3*cos(q2(j)+q3(k)))*sin(q1(i));
            z(1,n) = l1 + l2*sin(q2(j)) + l3*sin(q2(j)+q3(k));
            n = n + 1;
        end
    end
end

pts(1,:) = x;
pts(2,:) = y;
pts(3,:) = z;

% figure; grid on; hold on; axis equal;
plot3(pts(1,:),pts(2,:),pts(3,:),'r.');
xlabel('x'); ylabel('y'); zlabel('z');

end