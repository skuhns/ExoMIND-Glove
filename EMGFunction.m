function EMGFunction(sampleNumber)

%Matlab + Arduino Serial Communication
%Author: Mario Perez Esteso (modified by MIND)
y = zeros(1, 1000);

%Initialize serial port
delete(instrfind({'Port'}, {'COM9'}));
serialPort = serial('COM9'); %insert actual com port
serialPort.Baud = 9600; %baud rate
warning('off', 'MATLAB:serial:fscanf:UnsuccessfulRead');

%open the serial port
fopen(serialPort);

%declare a counter
counter = 1;

%Create a graph
figure(1);
hold on;
title('EMG Data')
xlabel('Time');
ylabel('Constriction Strength');
ylim([0 10]); %set y limit for EMG
grid on;

while counter <= sampleNumber
    
    x(counter, :) = fscanf(serialPort, '%f');
    plot(counter,x(counter, 1), '-r')
    title('EMG Data')
    xlabel('Time');
    ylabel('Muscle Activity');
    xlim([counter-20 counter+5]);
    ylim([0 10]); %set y limit for EMG
    grid on;
%     plot(counter, x(counter, 1), 'X-r');
%     plot(counter, x(counter, 2), 'X-b');
%     plot(counter, x(counter, 3), 'X-g');
    drawnow
    
    counter = counter + 1;
end

fclose(serialPort);
delete(serialPort);
clear all;

end

    