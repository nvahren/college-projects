function calculateTime(handles,dist)
switch get(handles.TransportationMenu,'Value')
    case 1
        time = dist*2/83.3;
    case 2
        time = dist*2/250;
    case 3
        time = dist*2/183.33;
end
if time == 0
    set(handles.TimeField,'String','Waiting for Input')
elseif round(time) == 1
    set(handles.TimeField,'String',[num2str(round(time)) ' minute'])
else
    set(handles.TimeField,'String',[num2str(round(time)) ' minutes'])
end