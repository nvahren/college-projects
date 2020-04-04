function [HealthP2] = FireP1(handles)
yTerrain = getappdata(handles.plotAxes, 'yTerrain');
xLocationP1 = getappdata(handles.P1HealthIndicator, 'xLocation');
yLocationP1 = getappdata(handles.P1HealthIndicator, 'yLocation');
xLocationP2 = getappdata(handles.P2HealthIndicator, 'xLocation');
yLocationP2 = getappdata(handles.P2HealthIndicator, 'yLocation');
HealthP2 = str2double(get(handles.P2HealthIndicator, 'String'));
xProjectile = zeros(1,1000);
yProjectile = zeros(1,1000);
xProjectile(1) = xLocationP1;
yProjectile(1) = yLocationP1 + 0.05;
impact = 0;
power = get(handles.PowerSlider, 'Value');
angle = 180 - get(handles.AngleSlider, 'Value');
i = 2;
while impact == 0;
    xProjectile(i) = xProjectile(1) + (power * i * cosd(angle)) / 750;
    yProjectile(i) = yProjectile(1) + (power * i * sind(angle)) / 750 - (0.09 * (i)^2) / 750;
    plot(handles.plotAxes,xProjectile(1:i),yProjectile(1:i),'r-')
    if yProjectile(i) <= yTerrain(round(xProjectile(i)))
        impact = 1;
        plot(handles.plotAxes,xProjectile(1:i),yProjectile(1:i),'r-',xProjectile(i),yProjectile(i),'rx')
    else
        i = i + 1;
    end
    drawnow
end
factorMiss = Distance(xProjectile(i),yProjectile(i),xLocationP2,yLocationP2);
if factorMiss <= 2;
    HealthP2 = HealthP2 - (20 - 10 * factorMiss);
end