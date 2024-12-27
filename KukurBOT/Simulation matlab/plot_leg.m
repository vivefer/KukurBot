function plot_leg(position, theta_hip, theta_knee, theta_side, thigh_length, shin_length, foot_length)
    % Hip to knee
    knee_position = position + [thigh_length*cosd(theta_hip)*cosd(theta_side); thigh_length*sind(theta_hip)];
    
    % Knee to foot
    foot_position = knee_position + [shin_length*cosd(theta_knee)*cosd(theta_side); shin_length*sind(theta_knee)];
    
    % Foot to ground
    foot_end = foot_position + [foot_length*cosd(theta_side); 0];
    
    % Draw leg
    plot([position(1), knee_position(1)], [position(2), knee_position(2)], 'r', 'LineWidth', 2); % Thigh
    plot([knee_position(1), foot_position(1)], [knee_position(2), foot_position(2)], 'g', 'LineWidth', 2); % Shin
    plot([foot_position(1), foot_end(1)], [foot_position(2), foot_end(2)], 'm', 'LineWidth', 2); % Foot
end
