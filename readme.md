# 3d rendering from scratch

<ins> Амеличев Константин, под руководством Трушина Дмитрия, ФКН</ins>
<ins> Amelichev Konstantin, with Dmitry Trushin mentorship, CS HSE</ins>

### Components
* World
* Camera
* Screen
* Objects
<ins> Амеличев Константин, под руководством Трушина Дмитрия, ФКН</ins>
* Renderer

### What it can do:
* Load .off-object as 3d object
* Decompose objects into triangles
* Projective transform
* Rotate, translate camera
* Draw shadows
* It is even possible to develop a game on top of this rendering engine

## Demo

Есть тесторое приложение с возможностью изучить объект со всех сторон в пространстве со следующим управлением: поворот камеры по WASD + QE, сдвиг камеры по стрелочкам + ZX, объекты двигаются по IJKL + UO.

Есть тестовая игрушка с управлением камером мышкой и хождением по стрелочкам.

## Have a look:


### Демо игры
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/demo_game.gif)

### Демо приложения для изучения объекта
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/cubes.gif)

### Кадры приложения изучения объектов с off-моделями
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/apple.png)
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/teapot.png)
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/heart.png)
![Output sample](https://github.com/kik0s/3d-framework/raw/master/example/mushroom.png)



Рекомендую дополнительно сделать checkout на последний тег из доступных.


                Инструкция по запуску на Linux:
                # опционально, чтобы поставить нужные пакеты на систему, так собирается в github actions 
                # apt-get -y install \
                #            cxxtest \
                #            libsfml-dev
                 git clone --recurse-submodules git@github.com:kik0s/3d-framework.git
                 cd 3d-framework
                 mkdir build && cd build
                 cmake ..
                 make
                 ./3d-drawer
                 

Пререквизиты: пакеты из списка:
                 
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
