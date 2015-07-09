# rtld_solaris
Using RTLD to audit dynamic linker in Solaris

Install Oracle Visual studio to get started. I am working on a virtual machine. 

The audit.c file is compiled with the command: 
cc -o audit.so.1 -G -K pic -z defs audit.c -lmapmalloc -lc

Inorder to run the program:
LD_AUDIT=./audit.so.1 gedit

This would output all the libraries that are dynamically accessed by the linker. 
