# 50.051 PLC Project - Wordle Game
Authors: [Ernest Tan](https://github.com/Qaisel), [Elliot Phua](https://github.com/ElliotMonde), [Christabel Lim](https://github.com/christableh), [Yap Jing Yee](https://github.com/jingyeeyap)

<img width="476" alt="image" src="https://github.com/user-attachments/assets/edd85e2b-0e41-4dff-a4e1-b7d332116b7e" />

## Table Of Content

- [50.051 PLC Project - Wordle Game](#50051-plc-project---wordle-game)
  - [Table Of Content](#table-of-content)
  - [Introduction](#introduction)
  - [Installation Instructions](#installation-instructions)
  - [Inputs/Outputs](#inputsoutputs)

## Introduction
A Wordle-style game displayed within the terminal or command line where players guess words selected from a provided text file. The game randomly selects a target word (of any length) and the number of turns for a round of Wordle is dependent on the length of the selected word. Users can also choose to save their progress to a binary file and load up previous saves if they wish.

> [!NOTE]  
> A text file (.txt) containing English words is necessary to start the game. The text should only contain words.

The text is processed using our parser into a word frequency dictionary containing only unique words, with a built-in stop-word list ensuring that common function words like “this”, “that” and “them” are excluded. All words within the dictionary are used as potential words for the Wordle game.

### Rules
The number of turns in a round of Wordle is dependent on the current word that is selected by the program. For example, if the word is 7 letters long, the player is given 7 turns to guess the word.

Display feedback on the terminal:
- For letters in the correct position, the letter will be color-coded green (🟩) with a line under the position of the letter.   
  
- For letters in the word but not in the correct position, it will be color-coded yellow (🟨)  

#### Win/Lose Conditions
Win condition: Guess the word correctly before the 'Turns Left' counter hits 0

Lose condition: If the word is not guessed correctly after the 'Turns Left' counter hits 0

### Features
- Custom word lists utilizing player provided text files as the game's dictionary
- An autosave system that tracks the player's statistics, allowing players to pick the game back up from where they last left off
- Visual feedback for correct/incorrect letters
- Cross-platform compatibility (Windows(WSL)/macOS/Linux)

## Installation Instructions

Clone the repository:

```
git clone https://github.com/Qaisel/PLC_Wordle.git
```


### Windows (via WSL) / Linux

Compile the program using:
```
gcc -Wall -Werror -pedantic -ansi src/main.c -lm -o main
```
src/main.c assumes that we are currently in the root directory of the project. Change the path accordingly to the currently directory you are in.
Once the above command is executed, an `main` file will be generated.

To start to the Wordle game, call the following in the terminal:
```
./main
```

-----

### Mac

Compile the program using:
```
gcc -Wall -Werror -pedantic -ansi src/main.c -o main
```
src/main.c assumes that we are currently in the root directory of the project. Change the path accordingly to the currently directory you are in.
Once the above command is executed, an `main` file will be generated.

To start to the Wordle game, call the following in the terminal:
```
./main
```

## Inputs/Outputs

### Input

**Loading a text or save file:**  
When prompted by the program for the respective files, please enter the **_relative path_** to the text/save file. Any style or genre of text can be used as input as long as the text only contains English words.

For example (assuming that the current directory is the root directory):

```
save file (located in src folder):
  src/test.bin

text file (located in root directory):
  test_inp.txt
```

### Output

There is one main output file which is the save file and will only be created if the player wishes to save the game. For pre-existing save files, the program will simply write onto it.

The save file will store the following:
- Number of wins
- Number of losses
- Current streak count
- Information on the current round of Wordle
- All the words guessed by the user
