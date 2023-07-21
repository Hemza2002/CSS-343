# Self-Evaluation

## Name(s): Ali Elgazzar, Hemza Al-Shamari

Out of 25 points. Use output.txt created using 
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: Yes

- If the program does not compile or gives a segmentation error when run, 
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: All have been implemented

- -2 for each functionality not implemented

For each command, state Full, Partial or None to indicate 
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: TODO(student) Full
History: TODO(student) Full
Borrow: TODO(student) Full
Return: TODO(student) Partial

Return has been implemented, but does not work as intended


Q: -1 for each compilation warning, min -3: 0

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: 0

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: 0

- Check under *4. clang-format does not find any formatting issues*


Q: -2 for any detected memory leak: -1

- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code: Yes

- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are all functions in .h and .cpp file documents (min -3): All

- -1 for each function not documented

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: Main.cpp, createCommand

invalid movie type: main.cpp, makeMovies

invalid customer ID: customer.cpp
 
invalid movie: main.cpp, verify

factory classes: dvdFactory

hashtable: Hashtable stores the customer accounts based on ID

container used for comedy movies: class

function for sorting comedy movies: makeMovies

function where comedy movies are sorted: makeMovies, set

functions called when retrieving a comedy movie based on title and year: inventory, borrow, remove

functions called for retrieving and printing customer history: history

container used for customer history: vector

functions called when borrowing a movie: borrow

explain borrowing a movie that does not exist: if verify, then borrow

explain borrowing a movie that has 0 stock: if the stock variable is less or equal to 0, print error and return

explain returning a movie that customer has not checked out: if not in history then return

any static_cast or dynamic_cast used: static for hashtable and set, dynamic for customer, commands, dvd


Q: Total points: 22 (max 25)