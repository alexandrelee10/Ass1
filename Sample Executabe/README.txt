To assist you in understanding the instructor's implementation for Assignment-1, a sample executable file has been provided. 
Please review the details below regarding the two versions of the executable files.


ass1 (Dynamically Linked Executable):
=====================================
- This version is dynamically linked to external libraries.
- Running this executable requires your system to have the latest versions of the required libraries installed.
- If your system lacks these libraries or has incompatible versions, you may encounter errors when attempting to run this file.


ass1_static_linked (Statically Linked Executable):
==================================================
- This version is statically linked, meaning all the necessary libraries, dependencies, and execution frameworks are included within the file itself.
- As a result, the file size is significantly larger than the dynamically linked version (ass1).
- However, you can execute this file without worrying about the versions or availability of underlying libraries on your system.


Important Notes:
===============
- The instructor's implementation is provided solely for reference purposes.
- You are encouraged to adopt your own approach to the implementation, as long as it meets all the requirements specified in the assignment guidelines.


Execution Instructions:
=======================
- To run the dynamically linked executable:
	./ass1

- If the above does not work due to library issues, use the statically linked executable instead:
	./ass1_static_linked


How create a Dynamically Linked Executable?
===========================================
- Use the -static option with gcc to force static linking of libraries. 	
	gcc -static hello.c -o sol

- After building the executable, you can check if it is statically linked using the ldd command
	ldd sol