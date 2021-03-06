# Occlusion engine and application
## About the project
<i>Occlusion engine and application</i> is a program that calculates current attenuation of each <b>source</b> for an active <b>receiver</b>
based on the source's characteristics, distance between them and occlusion by any <b>obstacles</b> on the way in two-dimensional space.<br>
Below you can find information regarding program features from a user perspective followed by some code implementation details.

<img src="https://github.com/NorbertTom/Occlusion_engine_and_application/raw/readmeUpdate/readme_imgs/Main_window.jpg" alt="Main window" width="700"><br>

GUI made using <a href="https://www.wxwidgets.org/">wxWidgets</a>.

## Architecture

##### Occlusion engine and application consists of 3 projects:
* Windows application with GUI (SoundEngineAppWindows.exe)
* Dynamic library containing occlusion engine (Occlusion_engine.dll)
* Static library with sound engine tests embedded in occlusion engine (Tests.lib)

## Features

##### Walk with active Receiver
Using buttons user can move active receiver by one unit (meter) in any direction they want and observe what happens with sound sources - how it
affects attenuation and occlusion.

##### Load & Save
User can save the current state of the program and load it whenever they want. Data is stored in a binary file.

##### Memory
<img src = "https://github.com/NorbertTom/Occlusion_engine_and_application/raw/readmeUpdate/readme_imgs/Memory_window.jpg" alt = "Memory Window" width = "200"><br>
If using NorMemoryPool (more details in <i>Implementation details</i> section)
information regarding available and in-use memory is displayed.

##### Adding, deleting and editing objects
Objects can be added, deleted or edited using GUI. All objects' values can be changed apart from the ID which is added automatically
by the occlusion engine.

###### Sound Sources
<img src = "https://github.com/NorbertTom/Occlusion_engine_and_application/raw/readmeUpdate/readme_imgs/SoundSources_window.jpg" alt="Sound sources Window" width = "600" ><br>
* <i>x</i> and <i>y</i> are coordinates of the source. [m]
* <i>Lwa</i> is a power level of the source. During first iterations of the program it was meant to play a role in
attenuation calculations, but the idea was abandoned. Value stayed in the engine as a number that describes the source. [dbA]
* <i>maxDistance</i> is a maximum distance for which attenuation is calculated. [m]
* <i>isOccludable</i> determines if current attenuation should take into account any obstacles that are placed between sound source
and receiver.
* <i>AttenuationType</i> can be set to PointSource, LineSource or NoAttenuation; it describes how much distance affects source's attenuation.

###### Obstacles
<img src = "https://github.com/NorbertTom/Occlusion_engine_and_application/raw/readmeUpdate/readme_imgs/Obstacles_window.jpg" alt="Obstacles window" width="500"><br>
* <i>x1</i>, <i>y1</i>, <i>x2</i> and <i>y2</i> are coordinates of two points between which the obstacle exists. [m]
* <i>dampening</i> is the value by which sound source gets attenuated if the obstacle is in the way of sound wave. [dB]

###### Receivers
<img src="https://github.com/NorbertTom/Occlusion_engine_and_application/raw/readmeUpdate/readme_imgs/Receivers_window.jpg" alt="Receivers window" width="400"><br>
* <i>x</i> and <i>y</i> are coordinates of the receiver [m]
* <i>isActive</i> determines if chosen receiver should be set to active. Please note that one receiver has to be active at any time.

## Implementation details

### SoundEngineAppWindows
GUI for this program was made with wxWidgets v3.1.3. Application communicates with the occlusion_engine directly using classes that are exposed to it in the dll file.
Every user input field is checked in the application to make sure valid values are being sent to the engine.

### Occlusion Engine

#### Main structure
Three classes are the foundation of the engine: <b>SoundSource</b>, <b>Obstacle</b> and <b>Receiver</b>.
Each one has its own interface that it inherits, so that their public methods won’t change during development of the project.
<br>Each of those classes have their dedicated list classes, by which the engine communicates with them - <b>ListOfSources</b>,
<b>ListOfObstacles</b> and <b>ListOfReceivers</b>. Those list classes also inherit their own interfaces. Each list is a global singleton.
<br>The heart of <i>Occlusion_Engine</i> is the <b>SoundSourceCalculator</b> class, which makes all the attenuation calculations for sound sources
and checks if occlusion should be applied.
<br><b>UpdateFunctions</b> class is used to update all sources every time user changes any value in the application.

#### Memory
In <b>PerformanceDefines.h</b> there are three defines that enable using specially designed memory pools for keeping SoundSource, Obstacle
and Receiver objects - <b>NorMemoryPool</b>. To disable using that pool simply comment out defines you don’t want to use
and the engine will use default memory allocation.
<br>It was noticed during performance tests that on full load update function takes slightly less when using NorMemoryPool than when using default memory allocation.

### Tests
Tests were written to check if most important functions behave correctly and to ensure that there is no regression after some code changes / refactoring.
They were introduced in the middle of engine development and were added together with new engine's functionalities since then.
<br>Tests are run during the engine initialization. When compiling you can choose which tests (if any) you’d like to run
in <b>SoundEngineInitializer.cpp</b>. Logs are saved to disk after every launch of the program in <i>!TestsLog.txt</i> file.

### What could have been done better
* Tests could have been developed from the beginning together with the program.
They would have been more robust and would have helped to keep some methods simpler than they are.
* Objects’ lists could have been constructed differently so that singletons wouldn’t need to exist.
I’m aware that singleton is a bad practice, but I couldn’t think of anything better at the time of writing the Occlusion engine.
I tried using template class, but it resulted in more complicated code, so that I got back to the idea of using three singletons.
* ListOfSources, ListOfObstacles and ListOfReceivers could have been wrapped in some class and then exposed as extern,
instead of being declared as globals that can be accessed from outside the engine. On the other hand that would add complexity to the engine itself.