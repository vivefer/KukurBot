% quadruped_simulation.m
clear;
clc;

% Frame dimensions
frame_length = 20; % Length of the frame
frame_width = 15;  % Width of the frame

% Leg lengths
thigh_length = 10;
shin_length = 8;
foot_length = 2;

% Initial joint angles for the center leg
theta_hip = pi/4;
theta_knee = pi/3;
theta_side = pi/6;

% Position of the four corner supports on the XY plane
frame_positions = [
    frame_length/2,  frame_width/2;
   -frame_length/2,  frame_width/2;
   -frame_length/2, -frame_width/2;
    frame_length/2, -frame_width/2
];

% Central leg position (assumed at origin)
center_leg_position = [0, 0, 0];

% Plot the frame and the center leg
figure;
hold on;
axis equal;
grid on;
xlabel('X-axis');
ylabel('Y-axis');
zlabel('Z-axis');
title('Quadruped Frame with Central Leg Simulation');

% Plot the four legs of the frame
for i = 1:4
    plot3([frame_positions(i,1), frame_positions(i,1)], ...
          [frame_positions(i,2), frame_positions(i,2)], ...
          [0, -thigh_length], 'k-', 'LineWidth', 2);
end

% Plot the center leg
plot_center_leg(center_leg_position, theta_hip, theta_knee, theta_side, thigh_length, shin_length, foot_length);

% Initial frame shift (no movement)
frame_shift = [0, 0];

% Interactive control loop (example using keyboard input)
while true
    key = input('Enter command (w/a/s/d for frame, j/k/l for leg): ', 's');
    
    switch key
        case 'w'
            frame_shift = frame_shift + [0, 1];  % Move frame up
        case 'a'
            frame_shift = frame_shift + [-1, 0]; % Move frame left
        case 's'
            frame_shift = frame_shift + [0, -1]; % Move frame down
        case 'd'
            frame_shift = frame_shift + [1, 0];  % Move frame right
        case 'j'
            theta_hip = theta_hip + pi/18;       % Rotate hip joint
        case 'k'
            theta_knee = theta_knee + pi/18;     % Rotate knee joint
        case 'l'
            theta_side = theta_side + pi/18;     % Rotate sideways joint
        otherwise
            disp('Invalid command');
            continue;
    end
    
    % Update the plot
    update_plot(frame_positions, center_leg_position, frame_shift, [theta_hip, theta_knee, theta_side], thigh_length, shin_length, foot_length);
end
