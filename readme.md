# Vi editor
C++-based Vi editor replica for CSC 326 at College of Staten Island.

## Purpose
Practice utilizing different data structures

## Current state
* reads and displays text from file; keywords colored blue
* moves cursor appropriately with h j k l keys
* edit with i and I, delete line with dd, char with x
* cursor stays within bounds of line and file

## To-Do
### Soon
* ~~implement line deletion (dd command)
* ~~move cursor to appropriate line end when moving from longer line to shorter one
* ~~display keywords in color
* clean up code in commands
* move longer command code to separate functions
* display INSERT mode tag at bottom of console

### Eventually
* save changes
* extra commands: dw, dl, o/O, a/A, yanks, search with ?...
* display last change time? [last_write_time](https://en.cppreference.com/w/cpp/experimental/fs/last_write_time)
* command mode?
