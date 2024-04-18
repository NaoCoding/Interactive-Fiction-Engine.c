<h2> #character </h2>

```c
id:[uint]
// between 0 ~ characterCount - 1
// (*required) all other attributions before id is invalid.
// id should be unqiue or the original character will be erased and covered by new character setting

name:[string]
// set the name of the character
// not required, the default is NULL

img:[path]
// set the character's image
// not required

place:[left,top,width,height]
// set the default showing place for the character
// expressions are as same as css (support % , px , any css expression)

```

<h3>Example Code</h3>

```c
#character // set a character
id: 0      // id : 0
name:"test" // set the charater's name to test
img:"images/character01.png" // set the character's img to character01.png
place:30%,30%,30%,30%  // set the character's default showing place at x=30%, y=30% , size = 30% * 30%
```
