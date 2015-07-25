# rtld_solaris
Using RTLD to audit dynamic linker in Solaris

Install Oracle Visual studio to get started. I am working on a virtual machine. 

The audit.c file is compiled with the command: 
`cc -o audit.so.1 -G -K pic -z defs audit.c -lmapmalloc -lc `


Inorder to run the program:
`LD_AUDIT=./audit.so.1 gedit`

This would output all the objects that are dynamically loaded by the linker. 
`la_version()`:
This routine provides the initial handshake between the runtime linker and the audit library. This interface must be provided for the audit library to be loaded.
`la_objopen()`:
This routine is called when a new object is loaded by the runtime linker.
