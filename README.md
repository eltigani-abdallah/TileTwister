# TileTwister

---

A clone of the hit game 2048 created in C++ using SDL

<<<<<<< HEAD

---

### Game logic

---

- create 4x4 grid and generate two random tiles with values 2 or 4

|     |     |     |     |
| --- | --- | --- | --- |
|     | 2   |     |     |
|     |     |     | 4   |
|     |     |     |     |

- then allow the user to move them horizontally or vertically using keyboard arrows.
- when a tile is in contact with an identical tile (2 and 2) add their values and create a new tile with a random value
  - a new random tile is to be made after every valid move
- the game ends once there are no empty tiles and no tiles can be added together, so once no more valid moves can be made

create game situations and observe events (up/down/left/right) and compare results obtained to results expected to test game integrity

### SDL

---

create a simple rendering engine by including a `Window`class to initialize a window with pre-established parameters.

use and abstract class `GameObject` to represent the elements shown on the screen with coordinates and a size, allowing them to be shown as a geometric form or as an SDL image

reuse game logic to show the grid with graphics for the tiles and allow the user to interact using the keyboard ot move the tiles. add an animation to tile movements for an immersive visual experience.

do not forget integration tests to avoid regressions during development

### Extras

---

- add tile movement animation
- allow for save and loading of sessions
- add different objectives
- special tiles (obstacles, bonus)

### Expected skills

---

→ install and configure work environment depending on project
→ develop user interfaces
→ develop business components
→ contribute to a programming project
→ analyse needs and create application drafts
→ define software architecture of an application
→ prepare and execute testing plans of an application

### output

---

presentation with slides and code review. slides must contain:

- team organisation
- problems encountered and solutions
- playable demonstration of game

---

### Work repartition

---

#### Game Logic

- input manager
- grid setup
- tile construction and generation
- tile removal and addition
- win/loss conditions
- game manager

#### Visual output

- Window
- animation manager
- tile renderer (change tile color)
