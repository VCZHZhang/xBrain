.386
.model flat, stdcall
.stack 4096
ExitProcess PROTO, dwExitCode:DWORD
.code 
main PROC
	mov ebx, 10
	add eax, 68888
	add ebx, 9
	add ebx, 9
	INVOKE ExitProcess, 0

main ENDP
END main