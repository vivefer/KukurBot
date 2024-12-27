% update_plot.m
function update_plot(frame_positions, center_leg_position, frame_shift, angles, thigh_length, shin_length, foot_length)
    clf;
    hold on;
    axis equal;
    grid on;
    xlabel('X-axis');
    ylabel('Y-axis');
    zlabel('Z-axis');
    title('Quadruped Frame with Central Leg Simulation');
    
    % Plot the four legs of the frame
    for i = 1:4
        plot3([frame_positions(i,1) + frame_shift(1), frame_positions(i,1) + frame_shift(1)], ...
              [frame_positions(i,2) + frame_shift(2), frame_positions(i,2) + frame_shift(2)], ...
              [0, -thigh_length], 'k-', 'LineWidth', 2);
    end
    
    % Update center leg position based on frame shift
    center_leg_position = center_leg_position + [frame_shift(1), frame_shift(2), 0];
    
    % Plot the center leg
    plot_leg(center_leg_position, angles(1), angles(2), angles(3), thigh_length, shin_length, foot_length);
end
