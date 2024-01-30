if ~isempty(instrfindall)
    fclose(instrfind);
    delete(instrfind);
end
clear;

s = serial("COM3", 'BaudRate', 9600);

RPM = 25;

OMEGA_DEG = (RPM / 60) * 180; 
OMEGA_RAD = (RPM / 60) * 2 * pi;

% wait() in the ardiuno code
ARD_TIME = 0.6;

t = 0;
theta = 0;

try
    fopen(s);
    pause(2);

    while true

        fprintf(s, '%d\n',  theta);
        disp(theta);

        % waits for motor to finish before sending next motion
        time = abs(theta) / OMEGA_DEG;
        pause(time + ardTime);
        
        t = t + 0.1;
        theta = floor(180*sin(OMEGA_RAD*t));
    end
    
    fclose(s);

catch e
    disp('An error occurred:')
    disp(e.message)
end

delete(s);
