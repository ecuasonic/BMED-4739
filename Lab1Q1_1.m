if ~isempty(instrfindall)
    fclose(instrfind);
    delete(instrfind);
end
clear;

s = serial("COM3", 'BaudRate', 9600);

rpm = 30; % constant
ardTime = 0.5; % constant
omega = (rpm / 60)*2*pi; % constant (rad)

t = 0;
degA = 180; % deg
A = degA * (pi/180); % rad

try
    fopen(s);
    pause(2);
    time = A / omega;

    while true

        fprintf(s, '%d\n',  degA);
        disp(degA);

        pause(time + ardTime);
        
        degA = -degA;
    end
    
    fclose(s);

catch e
    disp('An error occurred:')
    disp(e.message)
end

delete(s);