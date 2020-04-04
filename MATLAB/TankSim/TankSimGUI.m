% TankSimGUI.m
% Tank simulation with GUI
%   Nathan Vahrenberg

function varargout = TankSimGUI(varargin)
% TANKSIMGUI MATLAB code for TankSimGUI.fig
%      TANKSIMGUI, by itself, creates a new TANKSIMGUI or raises the existing
%      singleton*.
%
%      H = TANKSIMGUI returns the handle to a new TANKSIMGUI or the handle to
%      the existing singleton*.
%
%      TANKSIMGUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in TANKSIMGUI.M with the given input arguments.
%
%      TANKSIMGUI('Property','Value',...) creates a new TANKSIMGUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before TankSimGUI_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to TankSimGUI_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help TankSimGUI

% Last Modified by GUIDE v2.5 22-Feb-2013 12:48:45

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @TankSimGUI_OpeningFcn, ...
    'gui_OutputFcn',  @TankSimGUI_OutputFcn, ...
    'gui_LayoutFcn',  [] , ...
    'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT

% --- Executes just before TankSimGUI is made visible.
function TankSimGUI_OpeningFcn(hObject, eventdata, handles, varargin)

% Choose default command line output for TankSimGUI
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

cla
[xTerrain, yTerrain] = PlotTerrain(handles);
axis([0 100 0 10])
setappdata(handles.P1HealthIndicator,'xLocation',25)
setappdata(handles.P1HealthIndicator,'yLocation',yTerrain(25))
setappdata(handles.P2HealthIndicator,'xLocation',75)
setappdata(handles.P2HealthIndicator,'yLocation',yTerrain(75))
plot(handles.plotAxes,getappdata(handles.P1HealthIndicator,'xLocation'),getappdata(handles.P1HealthIndicator,'yLocation'),'ro')
plot(handles.plotAxes,getappdata(handles.P2HealthIndicator,'xLocation'),getappdata(handles.P2HealthIndicator,'yLocation'),'bo')
set(handles.P1HealthIndicator,'String',num2str(100))
set(handles.P2HealthIndicator,'String',num2str(100))
setappdata(handles.plotAxes,'xTerrain',xTerrain)
setappdata(handles.plotAxes,'yTerrain',yTerrain)

% UIWAIT makes TankSimGUI wait for user response (see UIRESUME)
% uiwait(handles.figure1);

% --- Outputs from this function are returned to the command line.
function varargout = TankSimGUI_OutputFcn(hObject, eventdata, handles)
varargout{1} = handles.output;


% --- Executes on slider movement.
function PowerSlider_Callback(hObject, eventdata, handles)
p = get(handles.PowerSlider,'Value');
set(handles.PowerIndicator,'String',num2str(round(p)))

% --- Executes during object creation, after setting all properties.
function PowerSlider_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end

% --- Executes on slider movement.
function AngleSlider_Callback(hObject, eventdata, handles)
a = get(handles.AngleSlider,'Value');
a = 180 - a;
set(handles.AngleIndicator,'String',num2str(round(a)))

% --- Executes during object creation, after setting all properties.
function AngleSlider_CreateFcn(hObject, eventdata, handles)
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end


% --- Executes on button press in MoveRightButton.
function MoveRightButton_Callback(hObject, eventdata, handles)
if str2double(get(handles.PlayerIndicator,'String')) == 1
    xLocation = getappdata(handles.P1HealthIndicator,'xLocation');
    yTerrain = getappdata(handles.plotAxes,'yTerrain');
    xLocation = xLocation + randi(5);
    if xLocation > 99
        xLocation = 99;
    end
    yLocation = yTerrain(xLocation);
    setappdata(handles.P1HealthIndicator,'xLocation',xLocation)
    setappdata(handles.P1HealthIndicator,'yLocation',yLocation)
    set(handles.PlayerIndicator,'String','2')
else
    xLocation = getappdata(handles.P2HealthIndicator,'xLocation');
    yTerrain = getappdata(handles.plotAxes,'yTerrain');
    xLocation = xLocation + randi(5);
    if xLocation > 99
        xLocation = 99;
    end
    yLocation = yTerrain(xLocation);
    setappdata(handles.P2HealthIndicator,'xLocation',xLocation)
    setappdata(handles.P2HealthIndicator,'yLocation',yLocation)
    set(handles.PlayerIndicator,'String','1')
end
cla
plot(handles.plotAxes,getappdata(handles.plotAxes,'xTerrain'),getappdata(handles.plotAxes,'yTerrain'),'k-','LineWidth',2)
area(handles.plotAxes,getappdata(handles.plotAxes,'xTerrain'),getappdata(handles.plotAxes,'yTerrain'),'FaceColor', 'g')
plot(handles.plotAxes,getappdata(handles.P1HealthIndicator,'xLocation'),getappdata(handles.P1HealthIndicator,'yLocation'),'ro')
plot(handles.plotAxes,getappdata(handles.P2HealthIndicator,'xLocation'),getappdata(handles.P2HealthIndicator,'yLocation'),'bo')


% --- Executes on button press in MoveLeftButton.
function MoveLeftButton_Callback(hObject, eventdata, handles)
if str2double(get(handles.PlayerIndicator,'String')) == 1
    xLocation = getappdata(handles.P1HealthIndicator,'xLocation');
    yTerrain = getappdata(handles.plotAxes,'yTerrain');
    xLocation = xLocation - randi(5);
    if xLocation < 1
        xLocation = 1;
    end
    yLocation = yTerrain(xLocation);
    setappdata(handles.P1HealthIndicator,'xLocation',xLocation)
    setappdata(handles.P1HealthIndicator,'yLocation',yLocation)
    set(handles.PlayerIndicator,'String','2')
else
    xLocation = getappdata(handles.P2HealthIndicator,'xLocation');
    yTerrain = getappdata(handles.plotAxes,'yTerrain');
    xLocation = xLocation - randi(5);
    if xLocation < 1
        xLocation = 1;
    end
    yLocation = yTerrain(xLocation);
    setappdata(handles.P2HealthIndicator,'xLocation',xLocation)
    setappdata(handles.P2HealthIndicator,'yLocation',yLocation)
    set(handles.PlayerIndicator,'String','1')
end
cla
plot(handles.plotAxes,getappdata(handles.plotAxes,'xTerrain'),getappdata(handles.plotAxes,'yTerrain'),'k-','LineWidth',2)
area(handles.plotAxes,getappdata(handles.plotAxes,'xTerrain'),getappdata(handles.plotAxes,'yTerrain'),'FaceColor', 'g')
plot(handles.plotAxes,getappdata(handles.P1HealthIndicator,'xLocation'),getappdata(handles.P1HealthIndicator,'yLocation'),'ro')
plot(handles.plotAxes,getappdata(handles.P2HealthIndicator,'xLocation'),getappdata(handles.P2HealthIndicator,'yLocation'),'bo')


% --- Executes on button press in PassButton.
function PassButton_Callback(hObject, eventdata, handles)
if str2double(get(handles.PlayerIndicator, 'String')) == 1
    set(handles.PlayerIndicator, 'String', '2')
else
    set(handles.PlayerIndicator, 'String', '1')
end

% --- Executes on button press in FireButton.
function FireButton_Callback(hObject, eventdata, handles)
if str2double(get(handles.PlayerIndicator, 'String')) == 1
    [HealthP2] = FireP1(handles);
    set(handles.P2HealthIndicator,'String',num2str(round(HealthP2)))
    pause(2)
    cla
    hold on
    plot(handles.plotAxes,getappdata(handles.plotAxes,'xTerrain'),getappdata(handles.plotAxes,'yTerrain'),'k-','LineWidth',2)
    area(handles.plotAxes,getappdata(handles.plotAxes,'xTerrain'),getappdata(handles.plotAxes,'yTerrain'),'FaceColor', 'g')
    plot(handles.plotAxes,getappdata(handles.P1HealthIndicator,'xLocation'),getappdata(handles.P1HealthIndicator,'yLocation'),'ro')
    plot(handles.plotAxes,getappdata(handles.P2HealthIndicator,'xLocation'),getappdata(handles.P2HealthIndicator,'yLocation'),'bo')
    set(handles.PlayerIndicator,'String','2')
else
    [HealthP1] = FireP2(handles);
    set(handles.P1HealthIndicator,'String',num2str(round(HealthP1)))
    pause(2)
    cla
    hold on
    plot(handles.plotAxes,getappdata(handles.plotAxes,'xTerrain'),getappdata(handles.plotAxes,'yTerrain'),'k-','LineWidth',2)
    area(handles.plotAxes,getappdata(handles.plotAxes,'xTerrain'),getappdata(handles.plotAxes,'yTerrain'),'FaceColor', 'g')
    plot(handles.plotAxes,getappdata(handles.P1HealthIndicator,'xLocation'),getappdata(handles.P1HealthIndicator,'yLocation'),'ro')
    plot(handles.plotAxes,getappdata(handles.P2HealthIndicator,'xLocation'),getappdata(handles.P2HealthIndicator,'yLocation'),'bo')
    set(handles.PlayerIndicator,'String','1')
end
HealthP1 = str2double(get(handles.P1HealthIndicator,'String'));
HealthP2 = str2double(get(handles.P2HealthIndicator,'String'));
if HealthP1 <= 0
    set(handles.P1HealthIndicator,'String','0')
    set(handles.P2HealthIndicator,'String','WIN')
    pause(5)
    delete(gcf)
elseif HealthP2 <= 0
    set(handles.P1HealthIndicator,'String','WIN')
    set(handles.P2HealthIndicator,'String','0')
    pause(5)
    delete(gcf)
end

function PowerIndicator_Callback(hObject, eventdata, handles)
p = get(handles.PowerIndicator,'String');
set(handles.PowerSlider,'Value',str2double(p))


% --- Executes during object creation, after setting all properties.
function PowerIndicator_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function AngleIndicator_Callback(hObject, eventdata, handles)
a = get(handles.AngleIndicator,'String');
a = str2double(a);
a = 180 - a;
set(handles.AngleSlider,'Value',a)

% --- Executes during object creation, after setting all properties.
function AngleIndicator_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function PlayerIndicator_Callback(hObject, eventdata, handles)


% --- Executes during object creation, after setting all properties.
function PlayerIndicator_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in ResetButton.
function ResetButton_Callback(hObject, eventdata, handles)
cla
[xTerrain, yTerrain] = PlotTerrain(handles);
axis([0 100 0 10])
setappdata(handles.P1HealthIndicator,'xLocation',25)
setappdata(handles.P1HealthIndicator,'yLocation',yTerrain(25))
setappdata(handles.P2HealthIndicator,'xLocation',75)
setappdata(handles.P2HealthIndicator,'yLocation',yTerrain(75))
plot(handles.plotAxes,getappdata(handles.P1HealthIndicator,'xLocation'),getappdata(handles.P1HealthIndicator,'yLocation'),'ro')
plot(handles.plotAxes,getappdata(handles.P2HealthIndicator,'xLocation'),getappdata(handles.P2HealthIndicator,'yLocation'),'bo')
set(handles.P1HealthIndicator,'String',num2str(100))
set(handles.P2HealthIndicator,'String',num2str(100))
setappdata(handles.plotAxes,'xTerrain',xTerrain)
setappdata(handles.plotAxes,'yTerrain',yTerrain)
% assignin('base','xLocationP1',handles.xLocationP1)

function P1HealthIndicator_Callback(hObject, eventdata, handles)


% --- Executes during object creation, after setting all properties.
function P1HealthIndicator_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end



function P2HealthIndicator_Callback(hObject, eventdata, handles)


% --- Executes during object creation, after setting all properties.
function P2HealthIndicator_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
