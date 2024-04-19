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

character.show:[id/name],[left,top,width,height]
// show the img of the character (id / name are both supported) to the screen
// not required
// support same character show multiple times
// img show first will be placed at lower z-index.
// the method to set left top width height are as same as css description
// if left,top,width,height are not being set, image will appear at the default setting of character's place.

character.speak:[name : string],[conversation : string]
// set character name say conversation
// note that character name here can be any string, no need to be one of the character's name

player.active:True
// active and show the player in this scene
player.left:True
// enable left movement of player
player.right:True
// enable right movement of player

```

<h3>Example Code</h3>

```c
#scene
id:"example01"  // set the scene's id to example01
first:True      // set the scene example01 to be the first scene of the game
background:"images/bg.png"  // set the background to images/bg.png
click.change_scene:"test01" // when player click example01, redirect to scene test01
character.show:"capoo",20px,25px,30%,30% // show character's img (character named capoo) to x=20,y=25,size = 30% * 30%
character.show:3,36px,24px,250px,150px  // show character's img (character's id = 3) to x=36,y=24, size = 250px * 150px
character.show:3               // show character id:3 at its default place.
character.speak:"capoo","hello!" // character capoo say hello
```
