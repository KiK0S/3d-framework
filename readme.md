# 3d rendering from scratch


<ins> Amelichev Konstantin, with Dmitry Trushin mentorship, CS HSE</ins>

### Components
* World
* Camera
* Screen
* Objects
* Renderer

### What it can do:
* Load .off-object as 3d object
* Decompose objects into triangles
* Perform projective transformation
* Rotate, translate camera
* Apply diffusal lighting

## Demo app

Camera rotations: WASD + QE
Camera translations: arrows + ZX
Move objects: IJKL + UO.

There is also a test first-person "game" with mouse-controlled camera and walking using arrows.

## Have a look:


### First-person "game"
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/demo_game.gif)

### Mesh viewer
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/cubes.gif)

### Different .off-models
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/apple.png)
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/teapot.png)
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/heart.png)
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/mushroom.png)




## Build (Linux):
```
                # this is optional as done in github actions 
                # apt-get -y install \
                #            cxxtest \
                #            libsfml-dev
                 git clone --recurse-submodules git@github.com:kik0s/3d-framework.git
                 cd 3d-framework
                 mkdir build && cd build
                 cmake ..
                 make
                 ./3d-drawer
```              

Also probably these packages should be installed:
                 
<ul>
<li>freetype</li>
<li>x11</li>
<li>xrandr</li>
<li>udev</li>
<li>opengl</li>
<li>flac</li>
<li>ogg</li>
<li>vorbis</li>
<li>vorbisenc</li>
<li>vorbisfile</li>
<li>openal</li>
<li>pthread</li>
</ul>

Если что-то не работает, есть смысл свериться с Dockerfile.
