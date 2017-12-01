CS35L-LAB6
readme.txt
Feilan Wang
104796844

Before implementing multithread, performance is shown as follows:

	$ time ./srt 1-test.ppm >1-test.ppm.tmp

	real	0m44.972s
	user	0m44.968s
	sys	0m0.001s

//This is almost same as implementing multithread but only using 1 thread. 

After implementing multithread:

	$ time ./srt 1-test.ppm >1-test.ppm.tmp

	real	0m44.926s
	user	0m44.921s
	sys	0m0.001s

	$ time ./srt 2-test.ppm >2-test.ppm.tmp

	real	0m23.140s
	user	0m45.447s
	sys	0m0.002s

	$ time ./srt 4-test.ppm >4-test.ppm.tmp

	real	0m11.646s
	user	0m46.273s
	sys	0m0.000s

	$ time ./srt 8-test.ppm >8-test.ppm.tmp

	real	0m5.976s
	user	0m46.278s
	sys	0m0.002s

As we can see: 
There's a significant decrease in amount of real time required.
When thread number doubles, real time required is roughly halfed. 
However, there's a minor increase in user time. 
This is the time required to create threads.

Issues:
1.	At first, I didn't declare global variables outside the functions. There's compilation error. 
2.	At first, I didn't create a three-dimentional array to hold the data. As a result, there's race conditions problem.