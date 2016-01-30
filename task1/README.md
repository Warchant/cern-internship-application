# parallel-sudoku-solver

Your task is to implement in Java language a multithreaded program to solve a set of Sudoku puzzles. The most performance-critical methods should be implemented in C/C++ language and invoked through JNI (Java Native Interface) specification.

Your main program (in Java) should process single command line argument: a path to a file specifying set of puzzles. This file will contain paths to files with Sudoku tasks, one path per line. Sample set specification would look like this:
```
1.txt
simple.txt
hard/200.txt
<EOF>
```
Files with Sudoku problems will look like this:
```
4 . . . . . 8 . 5
. 3 . . . . . . .
. . . 7 . . . . .
. 2 . . . . . 6 .
. . . . 8 . 4 . .
. . . . 1 . . . .
. . . 6 . 3 . 7 .
5 . . 2 . . . . .
1 . 4 . . . . . .
```
