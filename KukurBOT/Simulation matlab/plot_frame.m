function plot_frame(position, frame_length, frame_width)
    % Draw the frame
    rectangle('Position', [position(1)-frame_length/2, position(2)-frame_width/2, frame_length, frame_width], 'EdgeColor', 'b');
end
