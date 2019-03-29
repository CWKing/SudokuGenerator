# SudokuGenerator
A now graded attempt at something I have tried and failed to do thrice (c++ attempt 1, python attempt, c++ attempt 2, now c++ attempt 3!); generate solvable sudoku puzzles

A WIP that may forever be; or until I can figure out how to do things better.
Compiles but may crash for various reasons (mostly integer division by zero or the like because a cell is found with no potential numbers which may occupy it).
Also the sudoku it prints in the chance it DOESN'T crash may still be erroneous.
It's pretty self-explanatory otherwise; run it, tell it whether or not you want to debug (protip: you don't; or maybe you do who am I to
judge), feed it a seed (an integer or something convertible to an integer; also not after midnight), and watch it churn and whir and spit
out a sudoku puzzle for you to copy on a piece of paper and do!

In the event I ever get it working to produce consistent sudokus 100% of the time, I THEN want to:
1) Add difficulty scaling (Hardest mode would give the least information [fewest numbers to start], easiest mode would give quite a lot)
2) Modify printGrid() to either print to console or to a textfile by user choice (this would be easy but I am lazy and stubborn)
3) Add a GUI so that the user doesn't have to stare at the console (maybe if I warm-up to Qt)
4) Add a GUI so that the user can try to solve the puzzle ON THE COMPUTER WHOOOOA
a) Add a timer in that case and save the top 5 best solve times for unshared notoriety
