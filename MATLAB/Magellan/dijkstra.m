% Dijkstra pathfinding algorithm
%   Nathan Vahrenberg

function [route,finaldist] = dijkstra(handles,origin,destination)

clc
dispDebug = get(handles.Debug,'Value');
error = 0;

%% Vertex Vectors
x = getappdata(handles.MapAxes,'x');
y = getappdata(handles.MapAxes,'y');
dist = zeros(1,length(x));

%% Path Vectors
pathStart = getappdata(handles.MapAxes,'pathStart');
pathEnd = getappdata(handles.MapAxes,'pathEnd');

%% Initial Setup

isIn = ones(1,length(x)); % Vector responsible for remembering if a point has been visited
isIn(1:106) = 0; % Buildings are out by default
isIn(origin) = 1;
isIn(destination) = 1;
pathLength = zeros(1,length(pathStart));

for currentPath = 1:length(pathStart) % Determine length of each path
    pathLength(currentPath) = distance(x(pathStart(currentPath)),y(pathStart(currentPath)),x(pathEnd(currentPath)),y(pathEnd(currentPath)));
end
for currentPoint = 1:length(x) % Set temporary distances to each point to infinity
    dist(currentPoint) = 1000000000000000000000; % Basically infinity...
    if currentPoint == origin % Set origin distance to 0
        dist(currentPoint) = 0;
        isIn(currentPoint) = 0;
    end
end

currentPoint = origin;
step = 1;
%pause(1)

%% Dijkstra Loop - Create map
while sum(isIn) ~= 0 % Begin loop that ends when no valid points are left
    
    for pathFinder = 1:length(pathStart) % Determine valid points for the current point
        if pathStart(pathFinder) == currentPoint % If a path exists, determine the distance to the next point
            tempPoint = pathEnd(pathFinder);
            if (dist(currentPoint) + pathLength(pathFinder)) < dist(tempPoint)
                dist(tempPoint) = dist(currentPoint) + pathLength(pathFinder);
                distSet(tempPoint) = 1; % More debugging
            end
        end
    end
    
    isIn(currentPoint) = 0; % Set current point as 'out'
    
    if sum(isIn) ~= 0 % If valid points remain
        
        oldPoint(step) = currentPoint; % Remember old 'currentPoint' as new 'currentPoint' values are considered
        
        for pathFinder = 1:length(pathStart) % Choose new point
            if (pathStart(pathFinder) == oldPoint(step)) && (isIn(pathEnd(pathFinder)) == 1)
                if dist(pathEnd(pathFinder)) < dist(currentPoint) || oldPoint(step) == currentPoint
                    currentPoint = pathEnd(pathFinder);
                    pointFound = 1;
                end
            end
        end
    end
    if pointFound == 0
        for n = 0:(step - 1)
            for pointFinder = 1:length(pathStart)
                if pathStart(pathFinder) == oldPoint(step - n) && isIn(pathEnd(pathFinder)) && distSet(pathEnd(pathFinder))
                    currentPoint = pathEnd(pathFinder);
                    pointFound = 1;
                end
            end
        end
    end
    if dispDebug
        disp(['Creating Route Map. Point ' num2str(currentPoint) '. Points Remaining: ' num2str(sum(isIn))])
    end
    if pointFound == 0 % Change locations if a dead end is hit
        for pointFinder = 1:length(x)
            if isIn(pointFinder) == 1 && pointFound == 0 && distSet(pointFinder) == 1
                currentPoint = pointFinder;
                pointFound = 1;
            end
        end
    end
    if pointFound && step < 184
        step = step + 1;
    end
    pointFound = 0;
end
if dispDebug
    disp('Route Map Created!')
end
%pause(3)

finaldist = dist(destination);
%% Dijkstra Loop - Retrace route

currentPoint = destination; % Set currentPoint as given destination to begin tracing backward
step = 1; % Used to create the route vector
routeFound = 0; % Used to break the 'for' loop when a route is found
isIn = ones(1,length(x)); % Reset 'isIn' to be used in retracing
errorC = 0;

while currentPoint ~= origin
    for pathFinder = 1:length(pathStart) % Determine valid points for the current point
        if dispDebug
            disp(['Tracing Route. Point: ' num2str(currentPoint)])
            disp(['Checking path ' num2str(pathFinder)])
        end
        if pathEnd(pathFinder) == currentPoint && routeFound == 0 % If a path exists, determine if it is the correct path
            if isIn(pathStart(pathFinder)) == 1
                tempPoint = pathStart(pathFinder);
                if dispDebug
                    disp(dist(currentPoint) - dist(tempPoint))
                    disp(pathLength(pathFinder))
                end
                %pause(2)
                if roundn((dist(currentPoint) - dist(tempPoint)),2) == roundn(pathLength(pathFinder),2)% Set route value to the path taken
                    tempRoute(step) = currentPoint;
                    isIn(currentPoint) = 0; % Set current point as 'out'
                    currentPoint = tempPoint; % Move to next point
                    if currentPoint == origin
                        break
                    end
                    routeFound = 1;
                    step = step + 1;
                    errorC = 0; % Reset error counter
                end
            end
        end
    end
    routeFound = 0;
    if currentPoint == origin
        break
    end
    errorC = errorC + 1; %Breaks loop if error has occurred
    if errorC == 1000
        if dispDebug
            disp('An error has occurred')
        end
        error = 1;
        break
    end
end
if dispDebug
    disp('Route Traced!')
end

%% Invert route
if ~error
    tempRoute(step) = origin; % Set inital point as origin
    route = zeros(1,length(tempRoute));
    
    for i = 1:step % Invert route vector
        route(i) = tempRoute(step + 1 - i);
    end
    if dispDebug
        disp('Dijkstra algorithm complete:')
        disp(route)
    end
else
    route = 0;
end