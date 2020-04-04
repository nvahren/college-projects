function [xTerrain, yTerrain] = PlotTerrain(handles)
xTerrain = linspace(1,100,100);
yTerrain = zeros(1,100);
yTerrain(1) = 1;
terrainGradeFactor = 20;
for terrainLoop = 1:99
    terrainGrade = randi(terrainGradeFactor)-terrainGradeFactor/2;
    yTerrain(terrainLoop+1) = yTerrain(terrainLoop) + sind(terrainGrade);
end
yTerrain = abs(yTerrain);
plot(handles.plotAxes,xTerrain, yTerrain, 'k-', 'LineWidth', 2)
hold on
area(handles.plotAxes,xTerrain, yTerrain, 'FaceColor', 'g')
hold on