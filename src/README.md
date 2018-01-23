# Steering

This is our steering project. What we do is a target-seeker system, that creates a permanent boid (__target boid__), and all the new boids created have to follow the original one. The target boid moves using a wander algorithm

How to run it:

* Make sure **_SFML_** is installed in your system.
* Move into `src/` folder.
* There you can find a Makefile, to compile or clean previous compilations of our project.
    * `make main` to compile.
    * `make clean`.
    * PS: `make` raises an error. Don't use it.
* Run the program using `./main`.

We have some options for the program:

* __Button "Q"__: Activate/deactivate avoid control.
* __Button "C"__: Clear all boids.
* __Button "X"__: Clear all blocks.
* __Button "D"__: Erase last block added.
* __Button "F"__: Erase last boid added.
* __Button "M"__: Mute music.
* __Button "U"__: Unmute.
* __Button "Esc"__: Close the program.
