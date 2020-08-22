Author: Andrés Gregorio Borrego

This project recreates the 7th level of NES Battletoads: The Volkmire's Inferno. 

[![Youtube](_layouts/gameplay.png)](https://www.youtube.com/embed/xd6BhImHuY4)

Description: This game was created originaly created for the NES and got some reeditions over the time for diferent platforms. It is considered really hard game and it has quite a big fanbase. It is a mix between platform, beat em up and, in some cases, racing genres. It is a fast game that was considered really dificult back then.

Objective: Reach the end of the level eliminating every Rat in the way!

| Controls  |    |
|---|---|
|WASD  | movement |
|SpaceBar | Jump  |
| K  |  Main Attack  |
| L  | Secondary attack  |
|Enter|  Re-start when dead / Ends the level. |



# Linux

Tested on Ubuntu 20.04

Dependencies

```
make dep compile run
```


# Mac

```
make dep-mac compile run
```

# Docker

Allow access from localhost

```
xhost + 127.0.0.1
```

Docker

```
make docker-compile
```

```
make docker-run
```
or

```
make docker-run-mac
```


# Ref

* [x11-windows-within-docker-on-mac](https://medium.com/@mreichelt/how-to-show-x11-windows-within-docker-on-mac-50759f4b65cb)

* [running-a-docker-soundbox-on-mac](https://devops.datenkollektiv.de/running-a-docker-soundbox-on-mac.html)