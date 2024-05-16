
Ts = 0.001;

R1 = 40;
R2 = 25;

L1 = 100;
L2 = 150;
L3 = 80;
La = 50;
Lb = 5; %Side length of EE
xo = L2/2 + L3 + Lb/2; %For initial position.

W1 = 20;
W2 = 20;
W3 = 20;
Wa = 50;

Ho = 3;
H1 = 45;
H2 = 50;
H3 = 20;
H4 = 20;

y = 11;
x = 10;

[ROBOT, ArmInfo] = importrobot('robot');

wp = 1e-3.*[xo              xo + L2/4    xo - L2/4   L2/2 + (L3+Lb)*cos(pi/4)    L2/2 + (L3+Lb)*cos(pi/3)   L2/3 + (L3+Lb)*cos(pi/2)  L2/2 + (L3+Lb)*cos(pi/4)  L2/2 + (L3+Lb)*cos(-pi/6)      L2/2 + (L3+Lb)*cos(-pi/2)  xo;
            0               0            0           (L3+Lb)*sin(pi/4)           (L3+Lb)*sin(pi/3)          (L3+Lb)*sin(pi/2)         (L3+Lb)*sin(pi/4)         (L3+Lb)*sin(-pi/6)             (L3+Lb)*sin(-pi/2)         0;
            10.5            10.5         10.5        10.5                        10.5                       10.5                       10.5                      10.5                          10.5                       10.5];