% plot_leg.m
function plot_leg(position, theta_hip, theta_knee, theta_side, thigh_length, shin_length, foot_length)
    % Ensure position is a column vector
    position = position(:);
    
    % Calculate joint positions
    knee_position = position + [thigh_length*cos(theta_hip); 0; thigh_length*sin(theta_hip)];
    ankle_position = knee_position + [shin_length*cos(theta_hip + theta_knee); 0; shin_length*sin(theta_hip + theta_knee)];
    foot_position = ankle_position + [foot_length*cos(theta_hip + theta_knee); foot_length*sin(theta_side); 0];
    
    % Plot the leg
    plot3([position(1), knee_position(1), ankle_position(1), foot_position(1)], ...
          [position(2), knee_position(2), ankle_position(2), foot_position(2)], ...
          [position(3), knee_position(3), ankle_position(3), foot_position(3)], 'r-o', 'LineWidth', 2);
end
