This folder contains the result of running various test cases with RTLD-Audit tool. 

Benign programs:

Markup: 1. date.out : Date program in solaris.

        2. gedit.out : Application for editing called - Gedit 

        3. vim.out : Application for editing called VIM

        4. firefox.out : For browser Firefox latest version for solaris. 

Two vulnerable test cases are made for testing the tool.
Their normal execuion, without any exploit has the following result:

Markup: 1. nolibc.txt

        2. rop_normal

They are again tested with attaching an exploit to the program. The result is :

Markup: 1. libc.txt

        2. rop-exploited

The above two cases are compared by taking the diff. The files include: 

Markup: 1. diff_libc.txt

        2. diff_rop.txt
