# 目的： 本程序将输入文件的所有字母转换为大写字母
#      然后输出到输出文件

# 处理过程: 1. 打开文件
#        	2. 打开输出文件
# 			3.如果未达到输入文件尾部
#    		  a.将部分文件读入内存缓冲区
# 			  b.读取内存缓冲区的每个字节，如果该字节位小写字母
#  			   ，就将其转换为大写字母
#      		  c. 将内存缓冲区写入输出文件
#

.section .data

.equ SYS_OPEN, 5
.equ SYS_WRITE, 4
.equ SYS_READ, 3
.equ SYS_CLOSE, 6
.equ SYS_EXIT, 1


.equ O_RDONLY, 0
.equ O_CREAT_WRONLY_TRUNC, 03101


.equ STDIN, 0
.equ STDOUT, 1
.equ STDERR, 2

.equ LINUX_SYSCALL, 0X80
.equ END_OF_FILE, 0
.equ NUMBER_ARGUMENTS, 2

.section .bss





