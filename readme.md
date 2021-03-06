Фреймворк для отрисовки 3д-объектов

*Последний доступный тег v0.3*
Умеет на текущий момент:
* Нарисовать произвольный объект
* Проективное преобразование
* Покрутить и подвигать камеру с помощью клавиатуры.
* Распарсить .off-объект
* Тени

Тестовое приложение поворачивает камеру по WASD + QE, сдвиг камеры по стрелочкам + ZX, объекты двигаются по IJKL + UO

Пример использования:

![Output sample](https://github.com/kik0s/3d-framework/raw/dima-review/example/cube.gif)
![Output sample](https://github.com/kik0s/3d-framework/raw/dima-review/example/cubes.gif)
![Output sample](https://github.com/kik0s/3d-framework/raw/dima-review/example/apple.png)
![Output sample](https://github.com/kik0s/3d-framework/raw/dima-review/example/teapot.png)
![Output sample](https://github.com/kik0s/3d-framework/raw/dima-review/example/heart.png)
![Output sample](https://github.com/kik0s/3d-framework/raw/dima-review/example/mushroom.png)

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