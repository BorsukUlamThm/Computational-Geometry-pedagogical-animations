# Computational Geometry pedagogical animations

This project aims to provideanimation of usual computational geometry algorithm
for pedagogical purpose (plus a bunch of other stuff).

Those algorithms are from the book **Computational Geometry** written by _Mark
de Berg_, _Otfried Cheong_, _Marc van Kreveld_ and _Mark Overmars_.
You can find more information about it on
the [Springer website](https://link.springer.com/book/10.1007/978-3-540-77974-2)
.

The whole project was developed on Linux.
It could probably be made to work on Windows, but I would recommend using a VM
or dual boot instead.

## Dependencies

- [Boost](https://www.boost.org/)
- [SFML](https://www.sfml-dev.org/index.php)

### Ubuntu

```bash
apt install libboost-dev
apt install libsfml-dev
```

### Arch Linux

```bash
pacman -S boost
pacman -S sfml
```

## Build

The project is a [CMake](https://cmake.org/) project.
Information on how to install CMake can be
found [here](https://cgold.readthedocs.io/en/latest/first-step/installation.html)
.

Then the project can be built using :

```bash
mkdir build && cd build
cmake ..
make
```

This will produce a ``bin`` directory that contains all the executables.

## Quickstart

Once the project is built, cd into the ``bin`` directory and run
the ``convex-hull`` executable

```bash
cd bin/chapter-1
./convex-hull
```

A window should open and display 20 random points. Press space to start and stop
the animation, and use the mouse to move and zoom on the figures.

## Animations

### Chapter 1

``bin/chapter-1`` contains binaries of some convex hull algorithms presented on
the first chapter of the book, with the following options

- ``-r, --random <nb_points>`` the point set will be generated randomly,
  with ``nb_points`` points
- ``-s, --seed`` specifies the random seed
- ``-i, --input <input_file>`` the point set will be loaded from the specified
  input file
- ``-a, --acquisition`` the point set will be acquired on the screen with a
*multiple acquisition* (see [Acquisitions](#Acquisitions))

By default, 20 random points are generated with a random seed based on the
computer clock

### Chapter 2

``bin/chapter-1`` contains a binary ``segment-intersections`` with an animation
of the algorithm presented on the second chapter of the book, with the same
options as in chapter 1

- ``-r, --random <nb_segments>`` the segment set will be generated randomly,
  with ``nb_segments`` segments
- ``-s, --seed`` specifies the random seed
- ``-i, --input <input_file>`` the segment set will be loaded from the specified
  input file
- ``-a, --acquisition`` the segment set will be acquired on the screen with a
*multiple acquisition* (see [Acquisitions](#Acquisitions))

By default, 20 random points are generated with a random seed based on the
computer clock\
The handled event point is displayed in green, and the segments of the tree are
displayed in red with indexes corresponding to their left - right order

Note that after running an animation from ``bin/chapter-1`` or ``bin/chapter-2``
, you can find the input set in the ``data/log`` directory\
For exemple if you just used ``./convex-hull`` can run the animation again on
the same point set using ``./convex-hull -i data/log/chapter-1/convex-hull``

### Other stuff

A bunch of other things not related to the book

## Graphics controls

### Global controls

Those can be used both in Animations and Acquisitions

- **left click hold and move** : move the figure
- **mouse wheel** : zoom int and zoom out
- **right click** : reset the zoom to default
- **ESC** : close window

### Animations

An animation is a sequence of frames

- **SPACE** : start / stop the animation
- **LEFT / RIGHT** : go to previous / next frame
- **UP / DOWN** : increase / decrease animation speed
- **0 - 9** : go to 0% - 90% of the animation. For example if there are 100 
frames, press 4 to go to frame 40

### Acquisitions

The current acquisition is indicated in the bottom right corner, press **SPACE**
to acquire a point (you need 2 points to make a segment)

If you have a *multiple* acquisition, make an arbitrary number of acquisitions,
and then press **ENTER** to move on. Else, make the required number of
acquisitions

You can run ``bin/examples/acquisition-example`` to try it