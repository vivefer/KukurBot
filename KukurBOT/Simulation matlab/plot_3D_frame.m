function plot_3D_frame(position, frame_length, frame_width, frame_height)
    % Define the vertices of the cuboid
    vertices = [
        -frame_length/2, -frame_width/2,  0;  % Bottom face
         frame_length/2, -frame_width/2,  0;
         frame_length/2,  frame_width/2,  0;
        -frame_length/2,  frame_width/2,  0;
        -frame_length/2, -frame_width/2, frame_height;  % Top face
         frame_length/2, -frame_width/2, frame_height;
         frame_length/2,  frame_width/2, frame_height;
        -frame_length/2,  frame_width/2, frame_height
    ];
    
    % Ensure the position is a row vector with the same number of columns as vertices
    if size(position, 2) == 1
        position = position';  % Convert column vector to row vector if necessary
    end
    
    % Add position to each vertex
    vertices = vertices + repmat(position, size(vertices, 1), 1);
    
    % Define the faces of the cuboid (each face has 4 vertices)
    faces = [
        1 2 3 4;  % Bottom face
        5 6 7 8;  % Top face
        1 2 6 5;  % Side face 1
        2 3 7 6;  % Side face 2
        3 4 8 7;  % Side face 3
        4 1 5 8   % Side face 4
    ];
    
    % Plot the cuboid
    patch('Vertices', vertices, 'Faces', faces, 'FaceColor', 'b', 'FaceAlpha', 0.5);
end
