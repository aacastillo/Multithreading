Alan Castillo
Youtube Video Link: https://youtu.be/PCf7NuJP1BE

a) Binary semaphores are used to protect critical regions of code around set of lines (20,22), (34,37, 42), and (61,63).

c) The counting semaphore for operators is used at the set of lines (50, 58).

d) Semaphores are initialized and destroyed in the main function around lines 80 and 98 respectively.

e) There are two thread functions, one for phonecall at line 18, and one for the timer at line 72. 

f) All the phonecall threads are created in the for loop located at line 86, and the timer thread is created at line 93.
   The phonecall threads detach at the end (line 69) and the timer thread is joined at line 95 in main.

g) A global variable next_id is initialized and declared at line 16. next_id is updated at line 21 in the phonecall thread,
   and is used to set the caller's id (line 25).

h) In the phonecall thread, the number of connected callers is updated at lines 41 and 62.

i) All the program outprint is located on lines 29, 47, 52, 56, and 66.

j) The mutexes are used all over the code so im not going to list all the lines, all the static and global
   variables are used only in the phonecall thread function and in main.
