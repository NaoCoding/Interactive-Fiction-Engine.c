<h2> #scene </h2>

```c
id:[string]
// set the scene's id, (*required)
// it should be placed at the first line after the #scene tag,
// any attributions comes before id:[string] will not be actived

first:[True]
// set the scene to the first scene when the website is opened
// not required, the default is False
// any description except True will not be effective.

background:[path]
// set the background of the scene to img
// not required, the default is None
// the path should be img or it may cause errors

click.change_scene:[scene's id]
// set while player clicked the screen, change the scene to target scene
// not required
// the target scene should be exist or it may cause errors

character.show:[id/name],[x(uint)],[y(uint)]
// show the img of the character (id / name are both supported) to x,y at screen
// not required
// support same character show multiple times
// img show first will be placed at lower z-index.

```

<h3>Example Code</h3>

```c
#scene
id:"example01"  // set the scene's id to example01
first:True      // set the scene example01 to be the first scene of the game
background:"images/bg.png"  // set the background to images/bg.png
click.change_scene:"test01" // when player click example01, redirect to scene test01
```
