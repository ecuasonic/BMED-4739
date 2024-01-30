if ~isempty(instrfindall)
    fclose(instrfind);
    delete(instrfind);
end
clear;

s = serial("COM3", 'BaudRate', 9600);

rpm = 25; % constant
ardTime = 0.6; % constant

t = 0;
theta = 0;
omega = rpm / 60;

try
    fopen(s);
    pause(2);

    while true

        fprintf(s, '%d\n',  theta);
        disp(theta);

        time = (60 / rpm) * (abs(theta) / 360);
        pause(time + ardTime);
        
        t = t + 0.5;
        theta = floor(180*sin(omega*t));
    end
    
    fclose(s);

catch e
    disp('An error occurred:')
    disp(e.message)
end

delete(s);