-Run make to compile
-Run Question1 (it doesn't requires arguments)

- The development environment is the following: It creates a Node for each arithmetic operations and it replicates the behaviour requested. 
The Node struct: - Type of operation (ADD, MUL, SUB, DIV, FIBO, VALUE)
		 - Value (stores the result of arithmetic operation or the value of the node)
		 - Operation (pointer to function)
		 - Node left (posible other operation)
		 - Node right (posible other operation)
Fibonacci is implemented with Dynamic programming: It creates an array with a malloc for all the n fibonacci numbers and recursively calculates
the ones that aren't already defined in the array, if they are defined then just returns its value. This saves a lot of calculation time and resources.
The program has the values and operations hardcoded because I understood that I had to replicate only this particular case but it can be easly modified to request
operations(list of operations) and values(list of values).