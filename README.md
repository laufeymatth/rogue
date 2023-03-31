# PA5 Rouge

# Contributors

PA5Group 50:

Daníel Kárason - danielk21@ru.is

Laufey Matthildur Friðriksdóttir - laufeyf20@ru.is

Markús Víðir Fjölnisson - markusf21@ru.is

# Project Description

## External Libraries used
* We used ncurses to render the game window
* it can be installed with this command: "sudo apt-get install libncurses5-dev libncursesw5-dev"

## Setting up and Running the Project
* Install this package: "sudo apt-get install libncurses5-dev libncursesw5-dev" (do so by typing that in the console).
* The commandline window MUST be in full screen for the program to function correctly!
* If the window renders oddly, you can try to zoom out a bit.
* To compile the program, type "g++ -o <program name> *.cpp -lncurses" in the terminal to compile the program.
* Then simply run the program by typing ./<program name> in the terminal.
* The program will be pretty self explanitory once operating.

## Some pointers about the game:
* 'H' - Health boost.
* 'S' - Strength boost.
* '#' - Stair to next floor.
* 'O' - Your position.
* 'Z' - Monster.
* To move, use the arrow keys.
* To attack monsters, you need to walk into them.
* Monsters have more reach than you, and can attack you diagonally.

