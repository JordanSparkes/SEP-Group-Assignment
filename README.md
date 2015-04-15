# Gary Keen - AI & NPC + Sprite & Player collab.

####To Do List

Task|Priority|Description
----|--------|-----------
Create Sprite Handler|High|This is the basic framework that all sprites will use to load, render and update from.
Create First Pass of Enemies|Medium|Placeholder sprites, making sure they render, move, spawn and update correctly.
Create Basic Collision Detection|Medium|Basic collision detection is purely how the sprites should react to hitting walls and whether walking near a player object is detected. Testing inc.
Create Basic AI|Low|This is a simple AI that will move on its own, react to a player and react properly to hitting walls.
Create Advanced Collision Detection|Low|This will include multiple layers of collision detection against the player for different actions (I.E attacks, move towards, stop following etc.).
Create Advanced AI|Low|This will include the enemies attacks, pre-emptive avoiding of walls and a core script/class to handle AI movement based off of either A* or Dijkstra/Depth-First Search.
Create Projectiles|Low|Projectiles include any attacks the enemy uses and consists of creating sprites, velocity and variable changes such as damage and health.
Create Sprite Sheets|Low|The art side of the project, must create each frame of the enemies and all the different direction and animations.
Create Variables|Low|This is the gameplay aspect of the enemies programming. Variables include health, damage, attack timers etc. They are essential but not a priority.

####Notes:
- Use rebase/merge command more to take updates from master rather than pulling from the master and switching branches.
- Collab with Mikey for Sprite Handler stuff so he can work with collision detection and player too.
- Work with Jordan on framework stuff so we can both get an idea of how things can be put together.
- Work with Jordan for UI stuff. Necessary?
- Work with Rhys for fair loot values against enemies. Necessary?
- Stop adding everything as inconsistencies in the binary files are a pain in the ass for something so flexible. Push only the files you edit.
- AI dependancies: Tile-based level system - Mikey [I need his method of tile based levels so I can correctly integrate them into a pathfinding code.]
