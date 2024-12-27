function update_plot(frame_position, theta_hip, theta_knee, theta_side, frame_length, frame_width, thigh_length, shin_length, foot_length)
    % Clear current plot
    cla;
    
    % Plot the frame
    plot_frame(frame_position, frame_length, frame_width);
    
    % Calculate and plot the leg based on joint angles
    plot_leg(frame_position, theta_hip, theta_knee, theta_side, thigh_length, shin_length, foot_length);
end
