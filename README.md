# Occlusion engine and application
## About the project
<i>Occlusion engine and application</i> is a program that calculates current attenuation of each <b>sound source</b> for an active <b>receiver</b>
based on the source's characteristics, distance between them and occlusion by any <b>obstacles</b> on the way in two-dimensional space.<br>
Below you can find information regarding program features from a user perspective followed by some code implementation details.

<img src="https://github.com/NorbertTom/Occlusion_engine_and_application/raw/readmeUpdate/readme_imgs/Main_window.jpg" alt="Main window" width="500"><br>

GUI made using <a href="https://www.wxwidgets.org/">wxWidgets</a>.

## Architecture

##### Occlusion engine and application consists of 3 projects:
* Windows application with GUI (SoundEngineAppWindows.exe)
* Dynamic library containing occlusion engine (Occlusion_engine.dll)
* Static library with sound engine tests embedded in occlusion engine (Tests.lib)

## Features

#### Walk with active Receiver
User can move active receiver by one meter in any direction they want and observe what happens with sound sources - how it
affects attenuation and occlusion.

#### Load & Save
User can save the current state of the program and load it whenever they want. Data is stored in a binary file.

#### Memory
<img src = "https://github.com/NorbertTom/Occlusion_engine_and_application/raw/readmeUpdate/readme_imgs/Memory_window.jpg" alt = "Memory Window" width = "200"><br>

If using NorMemoryPool (more details in <i>Implementation details</i> section)
information regarding available and in-use memory is displayed.

#### Adding, deleting and editing objects
Objects can be added, deleted or edited using GUI. All objects' parameters can be changed apart from the ID which is assigned automatically
by the engine.

##### Sound Sources
<img src = "https://github.com/NorbertTom/Occlusion_engine_and_application/raw/readmeUpdate/readme_imgs/SoundSources_window.jpg" alt="Sound sources Window" width = "700" ><br>

* <i>x</i>, <i>y</i> - coordinates of the source;
* <i>Lwa</i> - power level of the source. This parameter only describes the source and is not taken into account during calculations;
* <i>maxDistance</i> - maximum distance for which attenuation is calculated. If distance > maxDistance, then attenuation is set to maximum value;
* <i>isOccludable</i> - determines if current attenuation should take into account any obstacles that are placed between sound source
and receiver;
* <i>AttenuationType</i> - can be set to PointSource, LineSource or NoAttenuation; it affects how much source is attenuated at given distance.

##### Obstacles
<img src = "https://github.com/NorbertTom/Occlusion_engine_and_application/raw/readmeUpdate/readme_imgs/Obstacles_window.jpg" alt="Obstacles window" width="600"><br>

* <i>x1</i>, <i>y1</i>, <i>x2</i>, <i>y2</i> - coordinates of two points of line segment that define the obstacle;
* <i>dampening</i> - this value is added to source's attenuation if occlusion from that obstacle happens.

##### Receivers
<img src="https://github.com/NorbertTom/Occlusion_engine_and_application/raw/readmeUpdate/readme_imgs/Receivers_window.jpg" alt="Receivers window" width="400"><br>

* <i>x</i>, <i>y</i> - coordinates of the receiver;
* <i>isActive</i> - determines if chosen receiver should be set to active. Engine works only when precisely one receiver is active.

## Implementation details

### SoundEngineAppWindows
GUI for this program was created with wxWidgets v3.1.3. Application communicates with the <i>Occlusion Engine</i> directly using classes that are exposed to it
in the dll file. Each input field is checked in the application to make sure valid values are being sent to the engine.

### Occlusion Engine

#### Main structure
Three classes are the foundation of the engine: <b>SoundSource</b>, <b>Obstacle</b> and <b>Receiver</b>.
Each of them has its own interface to ensure that their public methods won’t change during development of the project.
<br>Engine communicates with source, receiver and obstacle objects by dedicated list classes: <b>ListOfSources</b>,
<b>ListOfObstacles</b> and <b>ListOfReceivers</b>. Those list classes also inherit their own interfaces. Each list is a global singleton.
<br>The heart of <i>Occlusion Engine</i> is the <b>SoundSourceCalculator</b> class, which calculates all the attenuations for sound sources
and checks if occlusion should be applied.
<br><b>UpdateFunctions</b> class is used to update all sources every time user changes any value in the application.

#### Memory
In <b>PerformanceDefines.h</b> there are three defines that enable using specially designed memory pools for keeping SoundSource, Obstacle
and Receiver objects - <b>NorMemoryPool</b>. To disable using that pool simply comment out defines you don’t want to use
and the engine will use default memory allocation.

### Tests
Tests were written to check if most important functions behave correctly and to ensure that code changes didn't break other functionalities.
They were introduced in the middle of engine development and were being added together with new engine's functionalities since then.
<br>Tests are run during the engine initialization. When compiling you can choose which tests (if any) you’d like to run
in <b>SoundEngineInitializer.cpp</b>. Logs are saved to disk after every launch of the program in <i>!TestsLog.txt</i> file.

### What could have been done better
* Tests could have been developed from the beginning together with the program.
They would have been more robust and would have helped to keep some methods simpler than they are.
* Objects’ lists could have been constructed differently so that singletons wouldn’t need to exist.
I’m aware that singleton is a bad practice, but I couldn’t think of anything better at the time of writing the <i>Occlusion Engine</i>.
I tried using template class, but it resulted in more complicated code, so that I got back to the idea of using three singletons.
* ListOfSources, ListOfObstacles and ListOfReceivers could have been wrapped in some class and then exposed as extern,
instead of being declared as globals that can be accessed from outside the engine. On the other hand that would add complexity to the engine itself.