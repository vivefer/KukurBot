function update_3D_plot(frame_position, theta_hip, theta_knee, theta_side, frame_length, frame_width, frame_height, thigh_length, shin_length, foot_length)
    % Clear current plot
    cla;
    
    % Plot the 3D frame
    plot_3D_frame(frame_position, frame_length, frame_width, frame_height);
    
    % Calculate and plot the 3D leg based on joint angles
    plot_3D_leg(frame_position, theta_hip, theta_knee, theta_side, thigh_length, shin_length, foot_length);
end
