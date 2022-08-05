# Computational Geometry pedagogical animations

This project aims to provideanimation of usual computational geometry algorithm for pedagogical purpose (plus a bunch of other stuff)

Those algorithms are from the book **Computational Geometry** written by _Mark de Berg_, _Otfried Cheong_, _Marc van Kreveld_ and _Mark Overmars_. You can find more information about it on the [Springer website](https://link.springer.com/book/10.1007/978-3-540-77974-2).

The whole project was developed on Linux. If you want to use it on Windows, you will certainly need some work to get it working...

## Dependencies

tl;dr : in your terminal
```bash
sudo apt install libboost-dev
sudo apt install libsfml-dev
```

The project needs the [boost](https://www.boost.org/) library.

You can install it on linux using ``sudo apt install libboost-dev`` on Ubuntu or ``sudo pacman -S boost`` on Arch. More information about the installation can be found [here](https://www.boost.org/users/download/).

The graphical animation use the [SFML library](https://www.sfml-dev.org/index.php).

You can install it on linux using ``sudo apt install libsfml-dev`` on Ubuntu or ``sudo pacman -S sfml`` on Arch. More information about installation can be found [here](https://www.sfml-dev.org/tutorials/2.5/start-linux.php) for Linux, and [here](https://www.sfml-dev.org/tutorials/2.5/start-vc.php) for Windows (but still, you should have less trouble building this project using a VM or a dual boot).

## Build

The project is a [CMake](https://cmake.org/) project. Information on how to install CMake can be found [here](https://cgold.readthedocs.io/en/latest/first-step/installation.html).

Then the project can be built using
```bash
#in the Project directory
mkdir build && cd build
cmake ..
make
```
This will produce a ``bin`` directory that contains all the executables
