arduino = serial("COM3", "BaudRate", 9600);

fopen(arduino);

A = 90
omega = 1
dt = 0.5
t = 0
while true
    theta = A*sin(omega*t)
    fprintf(arduino, '%f', theta);
    disp(theta)
    pause(3);
    t = t+dt
end

clear arduino;
