% "Random Path" Algorithm
%   Annabel Aman
function [route,dist] = RandomPath(handles,origin,destination)

%% Initial Setup

% Import Map Data
x = getappdata(handles.MapAxes,'x');
y = getappdata(handles.MapAxes,'y');
pathStart = getappdata(handles.MapAxes,'pathStart');
pathEnd = getappdata(handles.MapAxes,'pathEnd');

% Set Path Lengths
pathLength = zeros(1,length(pathStart));
for pathFinder = 1:length(pathLength)
    pathLength(pathFinder) = distance(x(pathStart(pathFinder)),y(pathStart(pathFinder)),x(pathEnd(pathFinder)),y(pathEnd(pathFinder)));
end

% Initialize Variables
dispDebug = get(handles.Debug,'Value'); % Gets value of 'Display Debug info'
dist = 100000000000000000000000; % Initial distance is infinity

%% for thousands of repetitions
for possibleRoutes = 1:1500
    if dispDebug
        disp(['Testing route ' num2str(possibleRoutes)])
    end
    % Initialize variables for each run
    currentPoint = origin; % Start at origin
    isIn = ones(1,length(x)); % Set all points as 'in'
    isIn(1:106) = 0; % Set all buildings as 'out'
    isIn(destination) = 1; % Set destination as 'in'
    tempdist = 0; % Reset temporary distance
    temproute = 0; % Reset temporary route
    step = 2; % Reset path step value
    route(1) = origin; % First point is origin
    
    %% Create route until destination is found
    while currentPoint ~= destination
        
        % Determine valid next steps
        i = 1;
        for pathFinder = 1:length(pathStart)
            if (pathStart(pathFinder) == currentPoint) && (isIn(pathEnd(pathFinder)) == 1)
                possibleNextPoints(i) = pathEnd(pathFinder);
                i = i + 1;
            end
        end
        i = i - 1;
        
        % Choose a next step at random (or directionally random)
        nextPoint = possibleNextPoints(randi(i));
        
        % Add step to route vector and update route distance
        temproute(step) = nextPoint;
        tempdist = tempdist + distance(x(currentPoint),y(currentPoint),x(nextPoint),y(nextPoint));
        
        % Move current point to next point and repeat
        currentPoint = nextPoint;
        step = step + 1;
        
    end
    %% Overwrite route with new route if new distance is less than old
    if tempdist < dist
        dist = tempdist;
        route = temproute;
        if dispDebug
            disp(['Route Overwritten: ' num2str(route)])
            disp(['Distance: ' num2str(dist)])
        end
    end
end

%% Set values and return from function
if dispDebug
    disp('Route Traced')
    disp(['Route: ' num2str(route)])
    disp(['Distance: ' num2str(dist)])
end
