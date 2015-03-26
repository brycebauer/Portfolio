# Code adapted from http://www.marcell-dietl.de/downloads/eratosthenes.s
	
	.data			# the data segment to store global data
space:	.asciiz	" "		# whitespace to separate prime numbers

	.text			# the text segment to store instructions
	.globl 	main		# define main to be a global label
main:
	li	$s1, 1	# initialize $s1 with ones
	li	$t9, 200	# find prime numbers from 2 to $t9
	

	add	$s2, $sp, 0	# backup bottom of stack address in $s2
	
	li	$t0, 1		# reset counter variable to 1 byte count

outer:	add 	$t0, $t0, 1	# increment counter variable (start at 2)

	bgt	$t0, $t9, exit	# start printing prime numbers when $t1 > 

check:	
	add	$t8, $s2, $t0
	
	lb	$t7, ($t8)

	beq   	$t7, $s1, outer	# only 1's? go back to the outer


	li	$v0, 1		# system code to print integer
	add	$a0, $t0, 0	# the argument will be our prime number in $t3
	syscall			# print it!

	li	$v0, 4		# system code to print string
	la	$a0, space	# the argument will be a whitespace
	syscall			# print it!

inner:	
	sb	$s1, ($t8)

	add	$t8, $t8, $t0	# do this for every multiple of $t0
	sub 	$t6, $t8, $s2
	ble	$t6, $t9, inner	# every multiple done? go back to outer loop

	j	outer		# some multiples left? go back to inner loop

exit:	li	$v0,10		# set up system call 10 (exit)
	syscall	
