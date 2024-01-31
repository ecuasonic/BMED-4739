% disconnects COM3 before attempting
if ~isempty(instrfindall)
    fclose(instrfind);
    delete(instrfind);
end
clear;

% connects to COM3
s = serial("COM3", 'BaudRate', 9600);

% same rpm used in Arduino code
% used to calculate time for motor to finish
RPM = 30;
ARD_TIME = 0.5;

% degrees
A = 180;

% radians
OMEGA = (rpm / 60)*2*pi;
theta = 0;

try
    fopen(s);

    % waits for everything to catch up, just in case
    pause(2); 

    % time it takes for motor to finish
    time = A / OMEGA;

    while true

        % sends data to Arduino through serial
        fprintf(s, '%d\n',  degA);
        disp(degA);

        % waits for motor to finish
        pause(time + ardTime);
        
        degA = A*sin(OMEGA*t) - degA;
    end
    
    fclose(s);

catch e
    disp('An error occurred:')
    disp(e.message)
end

delete(s);
