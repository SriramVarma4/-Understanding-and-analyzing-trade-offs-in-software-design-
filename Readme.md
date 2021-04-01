# COP290 Assignment1 Subtask3

##Contents of my code folder:

1)code file for method1 time(method1time.cpp)
2)code file for method1 utility(method1utility.cpp)
3)code file for method2 time(method2time.cpp)
4)code file for method2 utility(method2utility.cpp)
5)code file for method3 (method3.cpp) (prints qd and dd in a text file)
6)code file for method4 (m4.cpp) (prints qd and dd in a text file)
7)code file which calculates utility for methods 3 and 4 (util_calc.cpp)
8)code file for method 3 and 4 using singlethread (single.cpp)(prints qd and dd)
5)A makefile(which contains commands to execute our code file)
6)A readme file(which helps us,how to execute commands from make file)
7)An image "empty.png"

##Aim:

This task's aim is to reduce the runtime for the program used in subtask 2. The task describes about utility, runtime trade off using four methods.

##Setup:

##Compiling and running using makefile

Step1: open terminal
step2: open the directory or folder in which your code is present on terminal
step3: 
	For method1:
	compiling and running for method1time use command line:
		$ make method1time
	compiling and running for method1utility use command line:
		$ make method1utility
	compiling and running for both method1time and method1utility:
		$ make method1
	For method2:
	compiling and running for method2time use command line:
		$ make method2time
	compiling and running for method2utility use command line:
		$ make method2utility
	compiling and running for both method2time and method2utility:
		$ make method2
	
	For compiling all files required for method3 and method4 use command line:
		$ make compilemethod3and4
	For qd and dd of method3 use command line:
		$ make exe_m3 
	For qd and dd of method4 use command line:
		$ make exe_m4
	For qd and dd of single thread use command line:
		$ make exe_1thread
	For method3utility use command line:
		$ make m3util
	For method4utility use command line:
		$ make m4util
	For utilty using single thread use command line:
		$ make s1util
	For plotting graph in method 1 and 2 we need to combine two text files and for that we used command lines:
	For method1:
		$ make plot1txt
	For method2:
		$ make plot2txt
				
step4: It starts printing execution and done for each parameter used in methods.
step8: After execting the complete video it will print end of video and done.
step9: Text files will be created which will be used to plot graphs.

note:The video,reference image and output of basefile(outo.txt) should be in same repository
