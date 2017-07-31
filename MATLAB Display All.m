function Matlab_Arduino(sampleNumber)

%Matlab + Arduino Serial Communication
%Author: Mario Perez Esteso (modified by MIND)
y = zeros(1, 1000);

%Initialize serial port
delete(instrfind({'Port'}, {'COM4'}));
serialPort = serial('COM4'); %insert actual com port
serialPort.Baud = 9600; %baud rate
warning('off', 'MATLAB:serial:fscanf:UnsuccessfulRead');

%open the serial port
fopen(serialPort);

%declare a counter
counter = 1;

%Create a graph
figure(1)
subplot(2, 1, 1)
hold on;
title('Accelerometer Data')
ylabel('Percent Extension');
ylim([0 100]); %set y limit for accelerometer data
grid on;
hold off;

subplot(2, 1, 2)
hold on;
title('EMG Data')
xlabel('Time');
ylabel('Constriction Strength');
ylim([-255 255]); %set y limit for EMG
grid on;
hold off;

while counter <= sampleNumber
    
    x(counter, :) = fscanf(serialPort, '%f %f %f %f %f %f', [1,6]);
    subplot(2, 1, 1)
    bar(x(counter, 1:5))
    title('Accelerometer Data')
    ylabel('Percent Extension');
    ylim([0 100]); %set y limit for accelerometer data
    grid on;
    drawnow
    
    subplot(2, 1, 2)
    hold on;
    plot(x(counter, 6))
    title('EMG Data')
    xlabel('Time');
    ylabel('Constriction Strength');
    xlim([counter-20 counter+5]);
    ylim([-255 255]); %set y limit for EMG
    grid on;
    hold off;
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

    