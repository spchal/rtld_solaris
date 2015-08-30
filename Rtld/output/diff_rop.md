-------------------snippet---------------------
---
> PltEnter: /lib/libc.so.1  ->  /lib/libc.so.1: getenv(0xfe52ce64, 0xfe486c3d, 0xfeffe974)
155c155
< PltEnter: rop             ->  /lib/libc.so.1: __fpstart(0x2, 0xfeffe984, 0xfeffe990)
---
> PltEnter: rop             ->  /lib/libc.so.1: __fpstart(0x2, 0xfeffe968, 0xfeffe974)
158,169c158,168
< PltEnter: rop             ->  /lib/libc.so.1: strcpy(0xfeffe926, 0xfeffeabe, 0xfeffe970)
< PltExit: rop             ->  /lib/libc.so.1: strcpy - 0xfeffe926
< Symbind: rop                          /lib/libc.so.1               exit
< PltEnter: rop             ->  /lib/libc.so.1: exit(0x0, 0x0, 0xfeffe990)
< PltEnter: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset(0xfe580180, 0x0, 0x40)
< PltExit: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset - 0xfe580180
< PltEnter: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset(0xfe580140, 0x0, 0x40)
< PltExit: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset - 0xfe580140
< PltEnter: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset(0xfe5800c0, 0x0, 0x40)
< PltExit: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset - 0xfe5800c0
< PltEnter: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset(0xfe580000, 0x0, 0x40)
< PltExit: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset - 0xfe580000
---
> PltEnter: rop             ->  /lib/libc.so.1: strcpy(0xfeffe906, 0xfeffeaa2, 0x4)
> PltExit: rop             ->  /lib/libc.so.1: strcpy - 0xfeffe906
> Symbind: rop                          /lib/libc.so.1               system
> PltEnter: rop             ->  /lib/libc.so.1: system(0x8050e18, 0xfeffe900, 0xfeffe938)
> PltEnter: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset(0xfeffe600, 0x0, 0x20)
> PltExit: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset - 0xfeffe600
> PltEnter: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset(0xfe5801c0, 0x0, 0x40)
> PltExit: /lib/libc.so.1  ->  /lib/libc.so.1:  _memset - 0xfe5801c0
> PltExit: rop             ->  /lib/libc.so.1: system - 0x0
> Process 27460 got signal 11
> Enforcement code to exit(0)
-------------------snippet---------------------
