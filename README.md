#QPacman

This project is a Pacman inspired game where the player follows the rule on quantum computing. More precisely, the inputs correspond to quantum operations over the 4 (quantum) bits storing the current player's direction (Hadamar, swap, reverse, etc.). Thus the player can be in a superposition of multiple states with different probabilities. The regular gameplay elements then act with respect to the probability of the player being in a given position.

For technical reasons, some elements of a classic Pacman game couldn't make it (walls, for instance, are a pain to handle in reversible programming).

A more detailed manual will detail the math behind the Quantum part of the game and precise the game’s mechanics. Meanwhile, some game-play rules are explained in src/QPSolution/Q-Pacman/rules.txt and directly into the source code (in particular, look for QuantumState.h for a more detailed insight of the quantum aspect).

Source code created in Visual Studio, you /should* be able to compile directly from the repository's solution file src/QPSolution/QPSolution.sln .

If you want to test it, note that **the inputs are mapped to the numpad keys 1 to 9**.

Powered by SFML for graphic rendering.

#####Content
- The binary folder contains an optimized executable of the game with all required files, not thoroughly tested though so it may not work.
- The manual folder will contain a proper manual detailing the nasty tidbits about quantum mechanics and its emulation within the game as well as the LaTex source for it.
- the src folder contains the VS's solution for the project as well as the required headers and .lib files from SFML
- the VS's solution is split in three projects
  - ProtoEng is a SFML wrapper acting as a very basic game engine. Also it's a good excuse to play with dll in VS.
  - Test is just that, a test project for ProtoEng.
  - Q-Pacman is the main project and contains all the game code.


#####Notes
- Emulating a 16 bits (technically 13 bits) quantum register is a computationally costly operation, while the project could definitely be better optimized, don't expect it to run too smoothly in debug mode.
- I am aware that Quantum libraries exist in C++, but then where's the fun ? Also, a general purpose quantum library might not be suited for the very specific needs this project has.

###TODO
- Graphic overhaul (right now everything is ugly)
- Manual
- Game play tweaks
- Profiling/optimize
- Test Binary and release version
- Add additional inputs. 
