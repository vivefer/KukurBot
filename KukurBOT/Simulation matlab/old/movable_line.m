function movable_line()
    fig = figure('Name','Movable Line example','NumberTitle','off');
    
    ax = axes('Parent', fig);
    view(3);
    grid on;
    
    x = [0 5];
    y = [0 5];
    z = [0 5];
    
    hold(ax, 'on');
    hLine = line(x, y, z, 'Color', 'r', 'LineWidth', 2);
    
    set(fig, 'WindowButtonDownFcn', @startDragFcn);
    set(fig, 'WindowButtonUpFcn', @stopDragFcn);
    
    function startDragFcn(src, event)
        set(fig, 'WindowButtonMotionFcn', @draggingFcn);
    end

    function stopDragFcn(src, event)
        set(fig, 'WindowButtonMotionFcn', '');
    end

    function draggingFcn(src, event)
        currentPoint = get(ax, 'CurrentPoint');
        
        newX = currentPoint(1, 1);
        newY = currentPoint(1, 2);
        newZ = currentPoint(1, 3);
        
        set(hLine, 'XData', [newX x+newX], 'YData', [newY y+newY], 'ZData', [newZ z+newZ]);
       % set(hLine, 'XData', [newX newX], 'YData', [newY newY], 'ZData', [newZ, newZ]);
        
       % newX = currentPoint(1,1);
       % set(hLine, 'XData', [newX, newX]);
    end
end