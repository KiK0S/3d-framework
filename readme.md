Фреймворк для отрисовки 3д-объектов

Версия v0.2
Умеет на текущий момент:
Нарисовать произвольный объект, покрутить и подвигать камеру с помощью клавиатуры.

Тестовое приложение поворачивает камеру по WASD + QE, сдвиг камеры по стрелочкам + ZX, объекты двигаются по IJKL + UO

Пример использования:
test.cpp

![Output sample](https://github.com/kik0s/3d-framework/raw/dima-review/cube.gif)
![Output sample](https://github.com/kik0s/3d-framework/raw/dima-review/cubes.gif)


                Инструкция по запуску на Linux:
                apt-get -y install \
                            cxxtest \
                            libsfml-dev
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