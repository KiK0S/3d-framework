Фреймворк для отрисовки 3д-объектов

Версия v0.1
Умеет на текущий момент:
Нарисовать произвольный wire-объект, покрутить и подвигать его с помощью клавиатуры.

Пример использования:
test.cpp

![Output sample](https://github.com/kik0s/3d-framework/raw/dima-review/cube.gif)


                Инструкция по запуску на Linux:
                 `git clone --recurse-submodules git@github.com:kik0s/3d-framework.git`
                 `mkdir build && cd build`
                 `cmake ..`
                 `make`
                 `./3d-drawer`

Возможно надо будет доставить какие-то библиотеки из списка:
                 
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