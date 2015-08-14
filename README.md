# rtld_solaris
Using RTLD to audit dynamic linker in Solaris for building a runtime dynamic library checker 

Install Oracle Visual studio to get started. I am working on a virtual machine. 

The audit.c file is compiled with the command: 
`cc -o audit.so.1 -G -K pic -z defs env.c audit.c -lmapmalloc -lc `

Inorder to run the program:
`LD_AUDIT=./audit.so.1 gedit`

This would output all the objects that are dynamically loaded by the linker. Following are the functions from the rtld_audit librayr that are used in this tool. The usage of the function is mentioned from : http://docs.oracle.com/cd/E19683-01/817-1983/6mhm6r4ff/index.html. 

`la_version()`:
This routine provides the initial handshake between the runtime linker and the audit library. This interface must be provided for the audit library to be loaded.

`la_objopen()`:
This routine is called when a new object is loaded by the runtime linker.

`la_symbind32()`:
This routine is called when a binding occurs between two objects that have been tagged for binding notification from `la_objopen()`. The argument refcook identifies the object making reference to this symbol. This identifier is the same identifier as passed to the `la_objopen()` routine that returned `LA_FLG_BINDFROM`. defcook identifies the object defining this symbol. This identifier is the same as passed to the `la_objopen()` that returned `LA_FLG_BINDTO`.

`la_pltenter` : 
These functions are called when a procedure linkage table entry, between two objects that have been tagged for binding notification, is called. regs points to the out registers on a SPARC system, and the stack and frame registers on a x86 system, as defined in /usr/include/link.h.
flags points to a data item that can convey information regarding the binding. This data can be used to modify the continuing auditing of this procedure linkage table entry. This data item is the same as pointed to by the flags from la_symbind(). This value is a mask of the following flags defined in /usr/include/link.h:

`LA_SYMB_NOPLTENTER – la_pltenter()` is not be called again for this symbol.

`LA_SYMB_NOPLTEXIT – la_pltexit()` is not be called for this symbol.

The return value indicates the address to which control should be passed following this call. An audit library that simply monitors symbol binding should return the value of sym->st_value so that control is passed to the bound symbol definition. An audit library can intentionally redirect a symbol binding by returning a different value.

`la_pltexit()`
This function is called when a procedure linkage table entry, between two objects that have been tagged for binding notification, returns. This function is called before control reaches the caller.

`sym`, `ndx`, `refcook`, `defcook` and `sym_name` provide the same information as passed to `la_symbind()`. `retval` is the return code from the bound function. An audit library that simply monitors symbol binding should return retval. An audit library can intentionally return a different value.

