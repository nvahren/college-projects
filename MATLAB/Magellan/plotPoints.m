% Point Plotting Function
%   Nathan Vahrenberg
function plotPoints(handles)

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

origin = get(handles.OriginMenu,'Value') - 1;
if origin ~= 0
    plot(handles.MapAxes,x(origin),y(origin),'b.', 'MarkerSize', 25)
end

destination = get(handles.DestinationMenu,'Value') - 1;
if destination ~= 0
    plot(handles.MapAxes,x(destination),y(destination),'r.', 'MarkerSize', 25)
end