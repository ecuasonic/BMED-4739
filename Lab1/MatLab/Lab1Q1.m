arduino = serial("COM3", "BaudRate", 9600);

fopen(arduino);

while true
    fprintf(arduino, '%f', 45);
    pause(1);
end

clear arduino;
