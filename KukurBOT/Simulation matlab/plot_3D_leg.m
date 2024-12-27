function plot_3D_leg(position, theta_hip, theta_knee, theta_side, thigh_length, shin_length, foot_length)
    % Hip to knee (3D coordinates)
    knee_position = position + [thigh_length*cosd(theta_hip)*cosd(theta_side); thigh_length*sind(theta_hip); thigh_length*sind(theta_side)];
    
    % Knee to foot (3D coordinates)
    foot_position = knee_position + [shin_length*cosd(theta_knee)*cosd(theta_side); shin_length*sind(theta_knee); shin_length*sind(theta_side)];
    
    % Foot to ground (3D coordinates)
    foot_end = foot_position + [foot_length*cosd(theta_side); 0; foot_length*sind(theta_side)];
    
    % Draw leg in 3D
    plot3([position(1), knee_position(1)], [position(2), knee_position(2)], [position(3), knee_position(3)], 'r', 'LineWidth', 2); % Thigh
    plot3([knee_position(1), foot_position(1)], [knee_position(2), foot_position(2)], [knee_position(3), foot_position(3)], 'g', 'LineWidth', 2); % Shin
    plot3([foot_position(1), foot_end(1)], [foot_position(2), foot_end(2)], [foot_position(3), foot_end(3)], 'm', 'LineWidth', 2); % Foot
end
