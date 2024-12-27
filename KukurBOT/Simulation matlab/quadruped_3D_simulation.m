function quadruped_3D_simulation()
    % Parameters
    frame_length = 20;  % Length of the frame 
    frame_width = 15;   % Width of the frame
    frame_height = -40;   % Height of the frame
    thigh_length = 20;  % Length of the thigh
    shin_length = 20;    % Length of the shin
    foot_length = 1;    % Length of the foot
    
    % Initial positions and angles
    frame_position = [0; 0; 0];   % XYZ position of the frame
    frame_shift = [0; 0; 0];      % To control frame movement
    theta_hip = 0;  % Hip joint angle (forward/backward)
    theta_knee = -30; % Knee joint angle
    theta_side = -90; % Sideways rotation at the hip
    
    % Set up figure
    figure;
    axis equal;
    axis([-50 50 -50 50 -10 40]);
    hold on;
    grid on;
    
    while true
        % Update the plot
        update_3D_plot(frame_position + frame_shift, theta_hip, theta_knee, theta_side, ...
            frame_length, frame_width, frame_height, thigh_length, shin_length, foot_length);
        
        % Get user input for joint angles and frame movement
        key = input('Enter command (q to quit, w/s for forward/backward, a/d for left/right, u/j/h/k for joints, i/o for up/down): ', 's');
        
        % Process commands
        switch key
            case 'q'
                break;
            case 'w'
                frame_shift = frame_shift + [0; 1; 0];
            case 's'
                frame_shift = frame_shift - [0; 1; 0];
            case 'a'
                frame_shift = frame_shift - [1; 0; 0];
            case 'd'
                frame_shift = frame_shift + [1; 0; 0];
            case 'i'
                frame_shift = frame_shift + [0; 0; 1]; % Move frame up
            case 'o'
                frame_shift = frame_shift - [0; 0; 1]; % Move frame down
            case 'u'
                theta_hip = theta_hip + 5;  % Increase hip angle
            case 'j'
                theta_hip = theta_hip - 5;  % Decrease hip angle
            case 'h'
                theta_knee = theta_knee + 5;  % Increase knee angle
            case 'k'
                theta_knee = theta_knee - 5;  % Decrease knee angle
            case 'z'
                theta_side = theta_side + 5;  % Increase sideways angle
            case 'x'
                theta_side = theta_side - 5;  % Decrease sideways angle
        end
    end
end
