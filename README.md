# csdl_test

goal of this project is making a 2d game that can use maps created by tiled mapeditor.
current assets are temporary and will be replaced by original ones later on.
it's made in plain c, and only has sdl2 as dependency.
it can be built with just `make` and cleaned with `make clean`.

current state: working on collisions and gravity system.

<li>load and parse a tiled map</li>
<li>build collision map</li>
<li>build and render map</li>
<li>move map and collision layer</li>
<li>player sprite animation</li>
<li>handle collisions with player and map</li>
<li>handle gravity</li>

<br>
use arrow keys to move the player.
press `f` for fullscreen.
press `d` to render collision map.
press `esc` to quit.

<br>
<br>
<img src="https://github.com/nsklaus/csdl_test/blob/main/screenshots/screen1.png?raw=true" width="250" > &nbsp; &nbsp;
<img src="https://github.com/nsklaus/csdl_test/blob/main/screenshots/screen2.png?raw=true" width="250">
