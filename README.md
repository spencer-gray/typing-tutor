# typing-tutor

A simple tool used to practice typing than can be run inside the terminal. Randomly generated characters fall from the top of the window and players aim to increase their score by typing the corresponding keys before they reach the bottom. The ncurses library was used to build the user interface.

## Prerequisites

The ncurses library is required.

Linux:
```
Sudo apt-get install libncurses5-dev libncursesw5-dev
```
Mac:
```
brew install pkg-config
brew install ncurses
```

## Running the tests

```
make typing-tutor
make run
```
