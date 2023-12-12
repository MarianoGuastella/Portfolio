- Run make to compile
- Run Question2 with (1 or 2 or 3) depending on what fibonacci method you want to use and then pass the fibonacci number.
	Example: ./Question2 2 15

- Development:
	- Fibonacci1: Traditional recursive Fibonacci but using Dynamic Programming so it isn't ineficient by recalculating 
previous calculations. It requires memory for an array conteining the Fibonacci sequence. It uses an array of n+1 positions, 
it initialize the array with -1 and sets 0, 1 for the 0, 1 positions. When all the array is defined with the Fibonacci 
sequence, it returns the n number. 
	- Fibonacci2: A more eficient Fibonacci that it only saves the last 2 numbers of the sequence in order to calculate the 
next one. It uses less memory than the other Fibonacci's functions and it's the fastest one.
	- Fibonacci3: Traditional recursive Fibonacci. It requires a lot of memory because of the recursive calls and it's 
very ineficient as it has to calculate the same fibonacci sequences a lot, so it's very slow.