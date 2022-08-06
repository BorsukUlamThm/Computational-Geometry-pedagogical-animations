# Computational Geometry pedagogical animations

This project aims to provideanimation of usual computational geometry algorithm for pedagogical purpose (plus a bunch of other stuff).

Those algorithms are from the book **Computational Geometry** written by _Mark de Berg_, _Otfried Cheong_, _Marc van Kreveld_ and _Mark Overmars_.
You can find more information about it on the [Springer website](https://link.springer.com/book/10.1007/978-3-540-77974-2).

The whole project was developed on Linux.
It could probably be made to work on Windows, but I would recommend using a VM or dual boot instead.

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
Information on how to install CMake can be found [here](https://cgold.readthedocs.io/en/latest/first-step/installation.html).

Then the project can be built using :

```bash
mkdir build && cd build
cmake ..
make
```

This will produce a ``bin`` directory that contains all the executables.
