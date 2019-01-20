# Castle Game 3D

A 3D game written in C using my [TEngine](https://github.com/thomaslienbacher/TEngine).

### How to play
* Look around: Mouse
* Movement: W, S, A, D
* Jump: Space
* Activate switch: F
* The goal of the game is to collect the purple gem at the top of all platforms.

### Config
Graphical settings can be changed in `data/game.cfg`.

Available settings:

| Keyname | Type | Explanation |
| :---: | :---: | :---: |
| `width` | Integer | width of the window |
| `height` | Integer | height of the window |
| `fullscreen` | Boolean (0,1) | if window should fullscreen |
| `renderscale` | Float | scale of the opengl backbuffer |
| `fov` | Integer | field of view of the camera |
| `vsync` | Boolean (0,1) | enable vsync |

