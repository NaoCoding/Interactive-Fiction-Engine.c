## Interactive Fiction Engine, IFE

<h2>Run Example Script</h2>

```py
make
./engine ./example-game/
```

## How to create your own game / story

```
Create a new folder/dir and ready for saving all of your file.

To run your own story/game, you need to write a script.yaml
It contains all of your game's / story's settings.
```

<h3>script.yaml</h3>

```c
Format :

tags:
#script  // must be placed at the first line of your script.yaml (*required)
#general // general settings of your script.yaml (*required)
#character // config of a character
#scene   // create a scene for your script


```
<h3>Attributes / Elements of tags</h3>

[#general](/doc/general.md)<br>
[#scene](/doc/scene.md)<br>
[#character](/doc/character.md)<br>
