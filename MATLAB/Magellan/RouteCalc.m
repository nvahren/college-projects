function varargout = RouteCalc(varargin)
% ROUTECALC MATLAB code for RouteCalc.fig
%   
%   SP13-EG11112-05
%   
%   Group 5 "Open Ended Design Project"
%       "RouteCalc" launches a GUI window designed to calculate the
%       shortest route and approximate travel time between two buildings
%       on the University of Notre Dame campus
%   
%   Authors:
%       Annabel Aman
%       Liam Chan
%       Mary Sue Kaetzer
%       Brynelle Rozario
%       Nathan Vahrenberg

% Edit the above text to modify the response to help RouteCalc

% Last Modified by GUIDE v2.5 21-Apr-2013 12:25:32

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @RouteCalc_OpeningFcn, ...
    'gui_OutputFcn',  @RouteCalc_OutputFcn, ...
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


% --- Executes just before RouteCalc is made visible.
function RouteCalc_OpeningFcn(hObject, eventdata, handles, varargin)

% Choose default command line output for RouteCalc
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% Enable or Disable Debug Panel

showDebugPanel = 1;


if ~showDebugPanel
    set(handles.uipanel3,'Visible','off')
    set(handles.PlotNetwork,'Visible','off')
    set(handles.Debug,'Visible','off')
end
% ----- MAP VALUES -----
% Buildings
xBuilding = [636	557	984	613	535	765	630	964	280	723	746	581	508	968	584	692	724	763	737	593	467	1173	1112	630	765	772	504	724	822	882	801	859	583	1042	738	812	624	891	707	851	684	774	531	708	891	745	946	972	718	561	852	604	681	691	814	633	1109	501	473	642	813	509	768	555	641	500	729	759	678	694	818	536	779	509	469	960	877	817	743	604	807	751	454	1019	991	611	865	481	813	784	609	546	677	684	717	840	780	692	1076	602	678	767	593	1002	397	719];
yBuilding = [507	470	428	369	430	340	292	237	385	338	368	471	261	817	360	425	500	591	775	508	609	503	666	689	300	200	513	538	234	466	348	230	321	468	228	178	685	494	443	359	690	101	469	467	411	843	452	584	255	590	292	468	387	574	703	256	452	412	451	330	446	609	662	71	592	445	414	252	611	392	616	605	485	402	514	396	271	280	178	325	426	448	496	560	491	648	853	115	308	512	397	513	314	255	250	134	413	646	787	443	364	176	604	257	468	309];
    
% Vertices
xVertex = [728	753	750	724	721	748	746	720	720	746	745	718	745	743	716	682	771	673	672	670	644	640	668	624	612	568	561	529	480	507	608	592	566	544	522	475	460	484	520	544	566	594	612	640	668	692	730	750	767	750	713	766	749	768	801	812	470	828	852	916	926	923	874	862	850	852	832	813	888	876	822	794	794	762	734	760	732	758	728	756	730	654	656	676	628	654	631	672	672	618	562	564	540	542	592	592	967	986	981	1020	941	931	917	917	931	634	663	827	845	843	828	851	841	839	912	909	661	662	571	535	413	597	607	621	653	652	675	674	456	935	1023	1025	934	788	791	791	789	879	1023	1027	1024	1019	1012	982	983	983	913	783	785	783	703	707	589	522	437	457	507	546	466	401	327	774	483	661	629	696	710	726	711	923	961	755	789	789	812	814	848	671	630	864	878	855	888];
yVertex = [754	754	705	706	666	665	647	634	624	624	602	590	584	555	554	556	552	572	542	532	525	502	500	556	545	547	572	572	592	550	502	503	504	506	508	508	480	480	478	476	476	476	474	474	471	471	469	469	468	496	498	496	496	517	531	514	578	512	499	514	500	430	434	434	434	466	414	390	386	331	356	358	374	359	358	321	321	282	282	252	253	454	464	412	412	394	376	373	388	396	416	444	418	445	415	443	486	510	476	468	536	572	576	599	599	456	456	332	304	282	244	242	236	212	268	337	261	288	304	389	462	600	628	662	663	692	693	658	508	819	816	754	760	756	819	699	649	665	656	602	528	418	268	267	214	184	188	193	144	83	197	97	68	103	194	246	282	308	414	439	414	437	422	346	349	322	368	433	470	379	427	230	209	320	246	294	290	318	316	468	500	413	413];

% Full vertex vectors
x = [xBuilding,xVertex];
y = [yBuilding,yVertex];
setappdata(handles.MapAxes,'x',x)
setappdata(handles.MapAxes,'y',y)

% Paths
pathStart = [107	107	107	108	108	109	109	109	110	110	111	111	111	112	112	113	114	113	115	115	115	116	116	117	117	118	118	118	118	119	119	120	120	121	122	122	122	123	123	123	116	113	124	125	125	125	126	126	126	127	127	127	127	127	127	128	128	128	128	129	130	130	131	131	132	132	133	134	134	135	136	137	137	137	138	138	138	139	139	140	140	140	140	141	141	141	132	142	142	143	143	143	144	145	146	146	147	147	148	149	149	150	150	150	150	151	151	151	151	151	152	152	153	153	154	154	153	155	155	155	156	156	156	158	158	159	120	160	161	163	164	161	162	165	165	165	165	165	166	166	166	167	167	167	168	169	169	170	171	171	173	174	174	174	174	175	176	176	176	177	177	178	179	180	180	180	181	181	181	182	182	183	183	184	184	184	185	185	185	186	187	131	188	188	188	188	188	189	189	190	190	190	190	190	191	191	191	191	192	192	193	193	270	224	188	194	193	197	197	197	197	197	197	198	198	198	198	199	199	201	203	203	204	204	205	206	206	207	204	208	208	209	210	210	191	214	215	176	216	216	216	217	218	217	218	219	220	220	221	218	221	221	168	223	225	226	226	227	228	229	229	230	231	231	231	232	110	111	109	108	233	236	236	236	236	238	238	239	240	240	242	113	243	244	245	246	248	168	249	250	251	252	253	254	254	255	257	258	259	260	261	262	263	265	266	161	136	155	268	142	266	145	205	276	175	222	248	171	286	166	178	182	280	194	194	193	225	271	193	272	272	195	153	154	282	279	279	270	175	288	170	171	186	278	254	145	144	284	163	217	281];
pathEnd = [108	109	110	109	110	110	111	112	111	112	112	113	114	113	114	114	115	116	116	117	118	117	118	118	119	119	120	121	124	120	121	121	123	122	124	125	130	160	161	243	243	243	234	126	129	130	127	128	129	128	129	150	151	152	157	129	150	137	149	130	131	234	132	133	133	136	134	136	135	163	163	138	148	149	148	149	139	147	140	147	146	145	141	145	142	136	139	144	235	235	144	227	145	146	147	200	148	198	149	150	191	212	188	189	151	189	188	213	152	157	275	190	154	156	155	156	181	156	158	174	157	158	159	159	160	160	159	161	162	235	165	164	164	172	170	171	169	166	167	207	209	168	203	207	169	170	175	171	172	173	174	177	178	179	175	176	214	222	221	178	214	179	180	181	182	183	182	273	183	183	184	184	185	185	186	187	186	187	224	187	257	228	189	190	191	212	213	212	213	191	192	194	195	213	192	193	196	201	193	194	194	226	284	284	192	195	196	198	199	200	201	202	226	199	200	201	202	200	226	202	204	205	205	247	206	247	248	208	207	209	211	210	211	244	212	215	216	215	217	218	219	220	220	219	219	220	254	253	253	221	222	250	276	224	264	264	265	266	229	230	234	231	232	234	233	233	232	233	242	240	234	241	237	239	238	239	245	240	241	242	243	243	244	245	246	247	249	277	250	251	252	253	254	255	257	256	258	259	260	261	262	263	264	269	267	243	142	268	171	145	269	269	277	277	276	276	277	286	287	287	280	280	282	273	270	271	285	285	225	273	284	274	275	275	283	280	281	271	288	289	288	288	278	279	279	269	200	285	268	281	282];

% Building Connections
buildingPathStart = [1	1	2	2	3	3	4	5	6	6	7	7	8	8	9	10	10	11	11	12	12	12	12	13	13	14	14	15	15	16	16	17	17	18	18	18	18	18	19	19	20	20	20	20	20	21	22	23	23	24	24	24	25	25	26	26	27	27	27	28	28	29	29	29	30	30	31	31	32	32	32	33	34	34	35	35	36	37	38	38	39	40	40	40	40	40	41	41	41	42	42	43	43	43	44	44	45	45	45	46	47	47	47	48	48	48	49	50	51	51	52	52	53	53	54	54	54	54	55	55	56	57	58	59	59	59	60	60	61	61	62	63	63	63	63	63	64	64	65	66	66	66	67	67	68	69	69	69	70	71	71	71	71	71	71	71	72	73	73	74	74	75	76	77	78	79	80	81	82	82	82	83	83	84	84	85	85	85	86	86	87	87	88	88	89	90	90	91	92	93	93	94	95	95	96	97	97	98	98	98	99	99	100	100	100	101	102	103	104	104	104	104	105	106	106	96	47	3	61	59	60	60	60	60	10	10	67	16	39	44	25	29	78	89	78	89	93	7	30	38	45];
buildingPathEnd = [128	137	146	147	248	168	193	199	180	182	223	224	250	251	267	181	183	180	181	147	148	198	202	262	263	236	237	193	226	190	213	159	156	116	117	119	120	123	107	108	131	132	137	138	139	135	247	238	245	230	231	232	182	184	254	257	136	141	142	120	121	217	219	220	165	167	177	178	218	219	220	225	206	247	186	187	254	230	165	166	213	174	175	176	177	214	110	111	233	255	256	145	146	200	152	153	168	169	175	241	167	168	203	207	208	211	187	133	176	215	148	149	195	181	118	121	122	124	240	242	223	247	265	143	144	265	193	194	171	172	135	109	112	113	242	243	259	260	130	144	145	265	190	179	186	115	118	234	195	243	244	210	209	166	165	164	134	155	158	226	265	142	168	216	216	257	225	173	153	154	155	143	235	246	247	204	205	206	229	230	236	241	260	261	215	160	161	196	140	224	194	223	185	187	255	174	179	111	114	233	237	238	191	202	212	194	254	228	249	250	251	252	227	183	185	220	277	248	268	269	270	271	284	285	272	273	274	274	274	275	280	281	282	282	283	283	284	285	286	287	289];
pathStart = [pathStart,buildingPathStart];
pathEnd = [pathEnd,buildingPathEnd];
pathStartTemp = pathStart;
pathStart = [pathStart,pathEnd];
pathEnd = [pathEnd,pathStartTemp];
setappdata(handles.MapAxes,'pathStart',pathStart)
setappdata(handles.MapAxes,'pathEnd',pathEnd)
% ----------------------

plotPoints(handles)

% --- Outputs from this function are returned to the command line.
function varargout = RouteCalc_OutputFcn(hObject, eventdata, handles)
varargout{1} = handles.output;


% --- Executes on selection change in OriginMenu.
function OriginMenu_Callback(hObject, eventdata, handles)

plotPoints(handles)

% --- Executes during object creation, after setting all properties.
function OriginMenu_CreateFcn(hObject, eventdata, handles)

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on selection change in DestinationMenu.
function DestinationMenu_Callback(hObject, eventdata, handles)

plotPoints(handles)

% --- Executes during object creation, after setting all properties.
function DestinationMenu_CreateFcn(hObject, eventdata, handles)

if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes when selected object is changed in MapButtonGroup.
function MapButtonGroup_SelectionChangeFcn(hObject, eventdata, handles)

plotPoints(handles)

% --- Executes on selection change in TransportationMenu.
function TransportationMenu_Callback(hObject, eventdata, handles)

calculateTime(handles,getappdata(handles.MapAxes,'RouteDistance'))


% --- Executes during object crea6tion, after setting all properties.
function TransportationMenu_CreateFcn(hObject, eventdata, handles)
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in RouteButton.
function RouteButton_Callback(hObject, eventdata, handles)

plotRoute(handles)

% --- Executes on button press in ClearButton.
function ClearButton_Callback(hObject, eventdata, handles)

set(handles.OriginMenu,'Value',1)
set(handles.DestinationMenu,'Value',1)
set(handles.TimeField,'String','Waiting for Input')
setappdata(handles.MapAxes,'RouteDistance',0)
plotRoute(handles)

% --- Executes on button press in PlotNetwork.
function PlotNetwork_Callback(hObject, eventdata, handles)

plotRoute(handles)


% --- Executes on button press in Debug.
function Debug_Callback(hObject, eventdata, handles)
