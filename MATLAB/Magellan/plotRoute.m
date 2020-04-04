% Route Plotting Function
%   Nathan Vahrenberg

function plotRoute(handles)

cla(handles.MapAxes)
x = getappdata(handles.MapAxes,'x');
y = getappdata(handles.MapAxes,'y');
pathStart = getappdata(handles.MapAxes,'pathStart');
pathEnd = getappdata(handles.MapAxes,'pathEnd');

if get(handles.MapButton,'Value') == 1
    setappdata(handles.MapAxes,'Map',imread('CampusMap.png','png')) % Map
else
    setappdata(handles.MapAxes,'Map',imread('CampusMapSatellite.jpg','jpg'))
end
image(getappdata(handles.MapAxes,'Map'))
hold on
set(handles.MapAxes,'ytick',[]) % Disable map tick marks
set(handles.MapAxes,'xtick',[])


if get(handles.PlotNetwork,'Value')
    for i = 1:length(pathStart)
        xmap = [x(pathStart(i)),x(pathEnd(i))];
        ymap = [y(pathStart(i)),y(pathEnd(i))];
        plot(handles.MapAxes,xmap,ymap,'b-')
        hold on
    end
end

origin = get(handles.OriginMenu,'Value') - 1;
if origin ~= 0
    plot(handles.MapAxes,x(origin),y(origin),'b.', 'MarkerSize', 25)
end

destination = get(handles.DestinationMenu,'Value') - 1;
if destination ~= 0
    plot(handles.MapAxes,x(destination),y(destination),'r.', 'MarkerSize', 25)
end

if origin > 0 && destination > 0
    if origin ~= destination && get(handles.DijkstraButton,'Value')
        [route,dist] = dijkstra(handles,origin,destination); % Run dijkstra algorithm
        if route ~= 0
            for i = 1:(length(route))
                xroute(i) = x(route(i));
                yroute(i) = y(route(i));
            end
            setappdata(handles.MapAxes,'RouteDistance',dist)
            plot(handles.MapAxes,xroute,yroute,'g-','LineWidth', 2)
            calculateTime(handles,dist)
        else
            [route,dist] = dijkstra(handles,destination,origin); % If any error occurs, run in reverse
            if route ~= 0
                for i = 1:(length(route))
                    xroute(i) = x(route(i));
                    yroute(i) = y(route(i));
                end
                setappdata(handles.MapAxes,'RouteDistance',dist)
                plot(handles.MapAxes,xroute,yroute,'g-', 'LineWidth', 2)
                calculateTime(handles,dist)
            else
                set(handles.TimeField,'String','Error')
            end
        end
    else
        [route,dist] = RandomPath(handles,origin,destination);
        for i = 1:(length(route))
            xroute(i) = x(route(i));
            yroute(i) = y(route(i));
        end
        setappdata(handles.MapAxes,'RouteDistance',dist)
        plot(handles.MapAxes,xroute,yroute,'c-','LineWidth',2)
        calculateTime(handles,dist)
    end
end