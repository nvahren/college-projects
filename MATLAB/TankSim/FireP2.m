function [HealthP1] = FireP2(handles)
yTerrain = getappdata(handles.plotAxes, 'yTerrain');
xLocationP1 = getappdata(handles.P1HealthIndicator, 'xLocation');
yLocationP1 = getappdata(handles.P1HealthIndicator, 'yLocation');
xLocationP2 = getappdata(handles.P2HealthIndicator, 'xLocation');
yLocationP2 = getappdata(handles.P2HealthIndicator, 'yLocation');
HealthP1 = str2double(get(handles.P1HealthIndicator, 'String'));
xProjectile = zeros(1,1000);
yProjectile = zeros(1,1000);
xProjectile(1) = xLocationP2;
yProjectile(1) = yLocationP2 + 0.05;
impact = 0;
power = get(handles.PowerSlider, 'Value');
angle = 180 - get(handles.AngleSlider, 'Value');
i = 2;
while impact == 0;
    xProjectile(i) = xProjectile(1) + (power * i * cosd(angle)) / 750;
    yProjectile(i) = yProjectile(1) + (power * i * sind(angle)) / 750 - (0.09 * (i)^2) / 750;
    plot(handles.plotAxes,xProjectile(1:i),yProjectile(1:i),'b-')
    if yProjectile(i) <= yTerrain(round(xProjectile(i)))
        impact = 1;
        plot(handles.plotAxes,xProjectile(1:i),yProjectile(1:i),'b-',xProjectile(i),yProjectile(i),'bx')
    else
        i = i + 1;
    end
    drawnow
end
factorMiss = Distance(xProjectile(i),yProjectile(i),xLocationP1,yLocationP1);
if factorMiss <= 2;
    HealthP1 = HealthP1 - (20 - 10 * factorMiss);
end