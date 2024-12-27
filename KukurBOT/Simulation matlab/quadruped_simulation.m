function quadruped_simulation()
    % Parameters
    frame_length = 20;  % Length of the frame (arbitrary units)
    frame_width = 15;   % Width of the frame
    thigh_length = 10;  % Length of the thigh
    shin_length = 8;    % Length of the shin
    foot_length = 5;    % Length of the foot
    
    % Initial positions and angles
    frame_position = [0; 0];   % XY position of the frame
    frame_shift = [0; 0];      % To control frame movement
    theta_hip = 0;  % Hip joint angle
    theta_knee = 0; % Knee joint angle
    theta_side = 0; % Sideways rotation angle
    
    % Set up figure
    figure;
    axis equal;
    axis([-50 50 -50 50]);
    hold on;
    grid on;
    
    while true
        % Update the plot
        update_plot(frame_position + frame_shift, theta_hip, theta_knee, theta_side, ...
            frame_length, frame_width, thigh_length, shin_length, foot_length);
        
        % Get user input for joint angles and frame movement
        key = input('Enter command (q to quit, w/s for forward/backward, a/d for left/right, u/j/h/k for joints): ', 's');
        
        % Process commands
        switch key
            case 'q'
                break;
            case 'w'
                frame_shift = frame_shift + [0; 1];
            case 's'
                frame_shift = frame_shift - [0; 1];
            case 'a'
                frame_shift = frame_shift - [1; 0];
            case 'd'
                frame_shift = frame_shift + [1; 0];
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
