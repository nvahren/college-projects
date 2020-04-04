% TankSimV1.m
% A tank game / simulation
% V1: Confirmed - most bugs fixed, no explosion or movement animations, no dynamic terrain
%   Nathan Vahrenberg
clear
clc
hold off
clf

disp('Tank Combat Simulator')
pause(2)

%% TO DO

% Improve simulation speed - very slow while firing
% Improve tank graphic
% Add explosion animation
% Dynamic terrain? Maybe.
% Make firing angles more realistic / Adjust view axes
%   45 degrees fires nearly straight up with current axes


%% Variables and Debugging
%Terrain Generation
terrainGradeFactor = 20; %Affects how jagged the terrain is
%Gameplay
turn = randi(2); %Which player starts. randi(2) is a random player.
gameComplete = 0; %Do not change from 0
HealthP1 = 100; %Starting health of P1
HealthP2 = 100; %Starting health of P2
%Physics
grav = 0.09; %Gravitational constant
powerScale = 9; %Scales tank shot power
moveThreshold = 5; %How far the maximum movement in either direction can be
%Performance
framerate = 750; %Shot framerate. ~750 is recommended
speedBoost = 1; %Speeds up shot animation at the cost of smoothness of animation


%% Generate Terrain and Place Objects

generateTerrain = 1;
while generateTerrain == 1;
    generateTerrain = 0;
    clf
    clc
    disp('Generating Terrain...')
    xTerrain = linspace(1,100,100);
    yTerrain = zeros(1,100);
    yTerrain(1)=0;
    for terrainLoop = 1:99
        terrainGrade = randi(terrainGradeFactor)-terrainGradeFactor/2;
        yTerrain(terrainLoop+1) = yTerrain(terrainLoop) + sind(terrainGrade);
    end
    yTerrain = abs(yTerrain);
    plot(xTerrain, yTerrain, 'k-', 'LineWidth', 2)
    hold on
    area(xTerrain,yTerrain, 'FaceColor', 'g')
    hold on
    axis([0 100 0 5])
    xLocationP1 = 25;
    xLocationP2 = 75;
    yLocationP1 = yTerrain(xLocationP1);
    yLocationP2 = yTerrain(xLocationP2);
    
    plot(xLocationP1, yLocationP1, 'ro')
    hold on
    plot(xLocationP2, yLocationP2, 'bo')
    hold on
    axis([0 100 0 5])
    
    disp('Generate New Terrain?')
    terrainInput = input('Yes or No: ','s');
    if strcmpi(terrainInput,'y') || strcmpi(terrainInput,'yes')
        generateTerrain = 1;
    end
end


%% Simulation

while gameComplete == 0
%% Player 1
    if turn == 1                   
        turnComplete = 0;
        clc
        clf
        plot(xTerrain, yTerrain, 'k-', 'LineWidth', 2)
        hold on
        area(xTerrain,yTerrain, 'FaceColor', 'g')
        hold on
        plot(xLocationP1, yLocationP1, 'ro')
        hold on
        plot(xLocationP2, yLocationP2, 'bo')
        hold on
        axis([0 100 0 5])
        disp(['Player 1 (Red): ',num2str(HealthP1),'%'])
        disp('Possible Actions: ''Move Left'' or ''Move Right'' or ''Fire'' or ''Pass''')
        while turnComplete == 0
            action = input('Action: ','s');
            %% Move Left
            if strcmpi(action,'move left') && xLocationP1 >= (1+moveThreshold) %Moving Left
                disp('Moving...')
                pause(1)
                xLocationP1 = xLocationP1 - randi(moveThreshold);
                yLocationP1 = yTerrain(xLocationP1);
                clf
                plot(xTerrain, yTerrain, 'k-', 'LineWidth', 2)
                hold on
                area(xTerrain,yTerrain, 'FaceColor', 'g')
                hold on
                plot(xLocationP1, yLocationP1, 'ro')
                hold on
                plot(xLocationP2, yLocationP2, 'bo')
                hold on
                axis([0 100 0 5])
                turnComplete = 1;
            %% Move Right
            elseif strcmpi(action,'move right') && xLocationP1 <= (99-moveThreshold) %Moving Right
                disp('Moving...')
                pause(1)
                xLocationP1 = xLocationP1 + randi(moveThreshold);
                yLocationP1 = yTerrain(xLocationP1);
                clf
                plot(xTerrain, yTerrain, 'k-', 'LineWidth', 2)
                hold on
                area(xTerrain,yTerrain, 'FaceColor', 'g')
                hold on
                plot(xLocationP1, yLocationP1, 'ro')
                hold on
                plot(xLocationP2, yLocationP2, 'bo')
                hold on
                axis([0 100 0 5])
                turnComplete = 1;
            %% Fire
            elseif strcmpi(action,'fire') %Firing
                validInput = 0;
                xProjectile = zeros(1,100);
                yProjectile = zeros(1,100);
                while validInput == 0;
                    disp('Firing...')
                    angleFire = input('Angle (0-180): ');
                    powerFire = input('Power (1-100): ')/100;
                    if angleFire <= 180 && angleFire >= 0 && powerFire <= 1 && powerFire >= 0
                        validInput = 1;
                    else
                        disp('Invalid Input')
                    end
                end
                xProjectile(1) = xLocationP1;
                yProjectile(1) = yLocationP1 + 0.05;
                frame = 1;
                impact = 0;
                while impact == 0
                    xProjectile(frame+1) = xProjectile(frame) + (powerFire*powerScale*cosd(angleFire)*frame)/framerate;
                    yProjectile(frame+1) = yProjectile(frame) + (powerFire*powerScale*frame - grav* frame^2)/framerate;
                    plot(xProjectile(1:speedBoost:frame), yProjectile(1:speedBoost:frame), 'r-')
                    axis([0 100 0 5])
                    drawnow
                    hold on
                    if yProjectile(frame) <= yTerrain(round(xProjectile(frame))) || xProjectile(frame) >= 99 || xProjectile(frame) <= 1
                        impact = 1;
                        xImpact = xProjectile(frame);
                        yImpact = yProjectile(frame);
                    end
                    frame = frame + 1;
                    pause(0.1)
                end
                plot(xImpact, yImpact, 'rx')
                axis([0 100 0 5])
                factorMiss = sqrt((xImpact-xLocationP2)^2 + (yImpact-yLocationP2)^2);
                if factorMiss <= 2;
                    HealthP2 = HealthP2 - round(20 - 10*factorMiss);
                    disp(['Damage Inflicted: ',num2str(round(20 - 10*factorMiss)),'%'])
                end
                turnComplete = 1;
            %% Pass
            elseif strcmpi(action,'pass')
                turnComplete = 1;
            %% Error
            else
                disp('Invalid Command')
            end
        end
        %% Assess Results
        if HealthP2 <= 0
            clc
            gameComplete = 1;
            disp('**** Player 1: Victory! ****')
            pause(5)
        else
            disp('Player 1: Turn Complete')
            pause(3)
            turn = 2;
        end
        %% Player 2
    elseif turn == 2
        turnComplete = 0;
        clc
        clf
        plot(xTerrain, yTerrain, 'k-', 'LineWidth', 2)
        hold on
        area(xTerrain,yTerrain, 'FaceColor', 'g')
        hold on
        plot(xLocationP1, yLocationP1, 'ro')
        hold on
        plot(xLocationP2, yLocationP2, 'bo')
        hold on
        axis([0 100 0 5])
        disp(['Player 2 (Blue): ',num2str(HealthP2),'%'])
        disp('Possible Actions: ''Move Left'' or ''Move Right'' or ''Fire'' or ''Pass''')
        while turnComplete == 0
            action = input('Action: ','s');
            %% Move Left
            if strcmpi(action,'move left') && xLocationP2 >= (1+moveThreshold) %Moving Left
                disp('Moving...')
                pause(1)
                xLocationP2 = xLocationP2 - randi(moveThreshold);
                yLocationP2 = yTerrain(xLocationP2);
                clf
                plot(xTerrain, yTerrain, 'k-', 'LineWidth', 2)
                hold on
                area(xTerrain,yTerrain, 'FaceColor', 'g')
                hold on
                plot(xLocationP1, yLocationP1, 'ro')
                hold on
                plot(xLocationP2, yLocationP2, 'bo')
                hold on
                axis([0 100 0 5])
                turnComplete = 1;
            %% Move Right
            elseif strcmpi(action,'move right') && xLocationP2 <= (99-moveThreshold) %Moving Right
                disp('Moving...')
                pause(1)
                xLocationP2 = xLocationP2 + randi(moveThreshold);
                yLocationP2 = yTerrain(xLocationP2);
                clf
                plot(xTerrain, yTerrain, 'k-', 'LineWidth', 2)
                hold on
                area(xTerrain,yTerrain, 'FaceColor', 'g')
                hold on
                plot(xLocationP1, yLocationP1, 'ro')
                hold on
                plot(xLocationP2, yLocationP2, 'bo')
                hold on
                axis([0 100 0 5])
                turnComplete = 1;
            %% Fire
            elseif strcmpi(action,'fire') %Firing
                validInput = 0;
                xProjectile = zeros(1,100);
                yProjectile = zeros(1,100);
                while validInput == 0;
                    disp('Firing...')
                    angleFire = input('Angle (0-180): ');
                    powerFire = input('Power (1-100): ')/100;
                    if angleFire <= 180 && angleFire >= 0 && powerFire <= 1 && powerFire >= 0
                        validInput = 1;
                    else
                        disp('Invalid Input')
                    end
                end
                xProjectile(1) = xLocationP2;
                yProjectile(1) = yLocationP2 + 0.05;
                frame = 1;
                impact = 0;
                while impact == 0
                    xProjectile(frame+1) = xProjectile(frame) + (powerFire*powerScale*cosd(angleFire)*frame)/framerate;
                    yProjectile(frame+1) = yProjectile(frame) + (powerFire*powerScale*frame - grav*frame^2)/framerate;
                    plot(xProjectile(1:speedBoost:frame), yProjectile(1:speedBoost:frame), 'b-')
                    axis([0 100 0 5])
                    drawnow
                    hold on
                    if yProjectile(frame) <= yTerrain(round(xProjectile(frame))) || xProjectile(frame) <= 1 || xProjectile(frame) >= 99
                        impact = 1;
                        xImpact = xProjectile(frame);
                        yImpact = yProjectile(frame);
                    end
                    frame = frame + 1;
                    pause(0.1)
                end
                plot(xImpact, yImpact, 'bx')
                axis([0 100 0 5])
                factorMiss = sqrt((xImpact-xLocationP1)^2 + (yImpact-yLocationP1)^2);
                if factorMiss <= 2;
                    HealthP1 = HealthP1 - round(20 - 10*factorMiss);
                    disp(['Damage Inflicted: ',num2str(round(20 - 10*factorMiss)),'%'])
                end
                turnComplete = 1;
            %% Pass
            elseif strcmpi(action,'pass')
                turnComplete = 1;
            %% Error
            else
                disp('Invalid Command')
            end
        end
        %% Assess Results
        if HealthP1 <= 0
            clc
            gameComplete = 1;
            disp('**** Player 2: Victory! ****')
            pause(5)
        else
            disp('Player 2: Turn Complete')
            pause(3)
            turn = 1;
        end
    end
end