# Sudoku
This is a project of COMP10002 Foundation of Algorithms.

## Reading and Printing
Read an input of a set of a set of 81 one-digit numbers and print the output as below.

<img width="253" alt="Screen Shot 2022-05-21 at 7 32 58 pm" src="https://user-images.githubusercontent.com/62505313/169645522-db214374-ddf8-4f11-bbe5-e650288c22c4.png">

## Grid Checking
Checks the input grid for mistakes, to ensure that none of the 27 sets in the supplied puzzle have duplicate elements.

## Implement Strategy To Solve The Sudoku
To implement this strategy, iterate over all cells, in row-major order, computing the valid options for each cell. Then go through again, using that information, looking for cells that only have one valid option available, assigning those labels. If any cells did get assigned during that pass, recompute all the options, and make another pass. Each pass is shown separately in the output. Only when a complete pass takes place with no new cells being labeled, or when every cell has been labeled, should the program print the current state of the puzzle, and then end. 

<img width="282" alt="Screen Shot 2022-05-21 at 7 37 19 pm" src="https://user-images.githubusercontent.com/62505313/169645688-7342b370-2c44-4081-a7a4-bd46fe804512.png">

