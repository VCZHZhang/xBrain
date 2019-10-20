#目的：　展示函数如何工作的程序
#   本程序将计算
#　　　２＾３＋５＾２
#
#

#主程序中的所有内容都存储在寄存器中
#　因此数据段不含任何内容
.code32
.section .data

.section .text

.globl _start
_start:
#　压入第二个参数
pushl $3
#　压入第一个参数
pushl $2

call power 		#　函数调用
#　这里为啥要移动
addl $8, %esp   #　将栈指针向后移动
pushl %eax      #　在调用下一个函数之前保存第一个答案


pushl $2
pushl $5
call power
addl $8, %esp
popl %ebx

addl %eax, %ebx 	#　见过在　%ebx
movl $1, %eax
int $0x80

.type power, @function


#
#  参数２
#  参数１
#  返回地址　４(%ebp)
#　旧%ebp    %esp   %ebp
#

power:
pushl %ebp   	#保留旧基址指针
movl %esp, %ebp   

#　相当于栈顶部开辟空间
subl $4, %esp   #　为本地存储保留空间


#　在栈中取出参数
movl 8(%ebp), %ebx
movl 12(%ebp), %ecx

#　放到开辟的空间中
movl %ebx, -4(%ebp)

power_loop_start:
cmpl $1, %ecx
je end_power
movl -4(%ebp), %eax
imull %ebx, %eax
movl %eax, -4(%ebp)

decl %ecx
jmp power_loop_start


end_power:
movl -4(%ebp), %eax
movl %ebp, %esp
popl %ebp
ret


