## Runtime linker auditing 

Using RTLD to audit dynamic linker in Solaris for building a runtime dynamic library checker. 

####Setup - Working

Install Oracle Visual studio to get started. 
(I am working on a virtual machine.)
The audit.c file is compiled with the command: 
`cc -o audit.so.1 -G -K pic -z defs env.c audit.c -lmapmalloc -lc `
Inorder to run the program:
`LD_AUDIT=./audit.so.1 gedit` //Here gedit is the program binary being run.
This would output all the objects that are dynamically loaded by the linker.

