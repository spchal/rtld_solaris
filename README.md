# rtld_solaris
Using RTLD to audit dynamic linker in Solaris

Install Oracle Visual studio to get started. I am working on a virtual machine. 

The audit.c file is compiled with the command: 
`cc -o audit.so.1 -G -K pic -z defs env.c audit.c -lmapmalloc -lc `


Inorder to run the program:
`LD_AUDIT=./audit.so.1 gedit`

This would output all the objects that are dynamically loaded by the linker. 

`la_version()`:
This routine provides the initial handshake between the runtime linker and the audit library. This interface must be provided for the audit library to be loaded.

`la_objopen()`:
This routine is called when a new object is loaded by the runtime linker.

`la_symbind32()`:
This routine is called when a binding occurs between two objects that have been tagged for binding notification from `la_objopen()`. The argument refcook identifies the object making reference to this symbol. This identifier is the same identifier as passed to the `la_objopen()` routine that returned `LA_FLG_BINDFROM`. defcook identifies the object defining this symbol. This identifier is the same as passed to the `la_objopen()` that returned `LA_FLG_BINDTO`.
