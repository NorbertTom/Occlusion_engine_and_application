# Occlusion engine and application
## Purpouse of the program
<i>Occlusion engine and application</i> is a program that calculates current attenuation of each <b>source</b> for an active <b>receiver</b>
based on the source's characteristics, distance between them and occlusion by any <b>obstacles</b> on the way in two-dimensional space.

[screenshot of the GUI]

User may add multiple sound sources, obstacles and receivers, but only one receiver can be active at any given moment.
## Architecture
##### Occlusion engine and application consists of 3 projects:
* Windows application with GUI (SoundEngineAppWindows.exe)
* Dynamic library containing occlusion engine (Occlusion_engine.dll)
* Static library with sound engine tests embeded in occlusion engine (Tests.lib)
## Functionalities
##### Walk with active Receiver
Using buttons user can move acive receiver by one unit in any direction they want and observe what happens with sound sources - how it
affects attenuation and occlusion.
##### Load & Save
User can save current state of the program and load it whenever they want. Data is stored in binary file.
##### Memory
If using NorMemoryPool (more details in <i>Occlusion_Engine</i> folder readme file)
information regarding available and in-use memory is displayed. 
##### Adding, deleting and editting objects
Objects can be added, deleted or edited using GUI. All objects' values can be changed apart from the ID which is added automatically
by the occlusion engine.
###### Sound Sources
[img of sound sources edit window]
* <i>x</i> and <i>y</i> are coordinates of the source [m]
* <i>Lwa</i> is a power level of the source. During first iterations of the program it was meant to play a role in
attenuation calculations, but the idea was abandoned. Value stayed in the engine as a number that describe the source. [dbA]
* <i>maxDistance</i> is a maximum distance for which attenuation is calculated; if actualDistance > maxDistance attenuation
is set to maximum [m]
* <i>isOccludable</i> determines if current attenuation should take into account any obstacles that are placed between sound source
and receiver. If set to false attenuation only depends on the distance.
* <i>AttenuationType</i> can be set to PointSource, LineSource or NoAttenuation; it describes how much distance affects source's attenuation.
For PointSource it's 6dB when doubling the distance, for LineSource - 3dB, NoAttenuation means that no distance attenuation is taken into account.
Please note that NoAttenuation source still can be occluded by obstacles.
###### Obstacles
[img of obstacles edit window]
* <i>x1</i>, <i>y1</i>, <i>x2</i> and <i>y2</i> are coordinates of two points between which the obstacle exist. Sound wave which has to travel
through that segment is occluded and gets dampened. [m]
* <i>dampening</i> is the value by which sound source gets attenuated if the obstacle is in the way of sound wave [dB]
###### Receivers
[img of receivers edit window]
* <i>x</i> and <i>y</i> are coordinates of the receiver [m]
* <i>isActive</i> determines if chosen receiver should be set to active. Please note that one receiver has to be active at any time.