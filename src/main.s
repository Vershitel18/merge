	.file	"main.cpp"
	.text
	.section	.rodata
.LC0:
	.string	"failed to read line if file"
	.text
	.globl	_Z8readLineP13DynamicStringP8_IO_FILE
	.type	_Z8readLineP13DynamicStringP8_IO_FILE, @function
_Z8readLineP13DynamicStringP8_IO_FILE:
.LFB29:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L5:
	movl	-4(%rbp), %eax
	movsbl	%al, %edx
	movq	-24(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_Z16string_push_backP13DynamicStringc@PLT
	xorl	$1, %eax
	testb	%al, %al
	je	.L2
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %edi
	call	exit@PLT
.L2:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	fgetc@PLT
	movl	%eax, -4(%rbp)
	cmpl	$-1, -4(%rbp)
	je	.L3
	cmpl	$10, -4(%rbp)
	je	.L3
	movl	$1, %eax
	jmp	.L4
.L3:
	movl	$0, %eax
.L4:
	testb	%al, %al
	jne	.L5
	cmpl	$-1, -4(%rbp)
	jne	.L6
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	testq	%rax, %rax
	je	.L7
.L6:
	movl	$1, %eax
	jmp	.L8
.L7:
	movl	$0, %eax
.L8:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE29:
	.size	_Z8readLineP13DynamicStringP8_IO_FILE, .-_Z8readLineP13DynamicStringP8_IO_FILE
	.section	.rodata
.LC1:
	.string	"provide exactly one file\n"
.LC2:
	.string	"r"
.LC3:
	.string	"failed to open file"
.LC4:
	.string	"failed to initialize versh"
.LC5:
	.string	"failed to insert into heap"
	.align 8
.LC6:
	.string	"failed to extract min from heap"
.LC7:
	.string	"failed to get file from versh"
	.text
	.globl	main
	.type	main, @function
main:
.LFB30:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$144, %rsp
	movl	%edi, -132(%rbp)
	movq	%rsi, -144(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	cmpl	$1, -132(%rbp)
	jg	.L11
	movq	stderr(%rip), %rax
	leaq	.LC1(%rip), %rdi
	movq	%rax, %rcx
	movl	$25, %edx
	movl	$1, %esi
	call	fwrite@PLT
	movl	$1, %eax
	jmp	.L25
.L11:
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_Z8heapInitP4heap@PLT
	movb	%al, -114(%rbp)
	movq	$1, -112(%rbp)
	jmp	.L13
.L18:
	movq	-112(%rbp), %rax
	leaq	0(,%rax,8), %rdx
	movq	-144(%rbp), %rax
	addq	%rdx, %rax
	movq	(%rax), %rax
	leaq	.LC2(%rip), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fopen@PLT
	movq	%rax, -88(%rbp)
	cmpq	$0, -88(%rbp)
	jne	.L14
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %eax
	jmp	.L25
.L14:
	movq	-88(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z10versh_initP5vershP8_IO_FILE@PLT
	xorl	$1, %eax
	testb	%al, %al
	je	.L16
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %eax
	jmp	.L25
.L16:
	movq	-88(%rbp), %rdx
	leaq	-48(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z8readLineP13DynamicStringP8_IO_FILE
	leaq	-48(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z10insertHeapP4heapP5versh@PLT
	xorl	$1, %eax
	testb	%al, %al
	je	.L17
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %eax
	jmp	.L25
.L17:
	addq	$1, -112(%rbp)
.L13:
	movl	-132(%rbp), %eax
	cltq
	cmpq	%rax, -112(%rbp)
	jb	.L18
	jmp	.L19
.L24:
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_Z14extractHeapMinP4heap@PLT
	movq	%rax, -104(%rbp)
	cmpq	$0, -104(%rbp)
	jne	.L20
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %eax
	jmp	.L25
.L20:
	movq	-104(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movq	-104(%rbp), %rax
	movq	24(%rax), %rax
	movq	%rax, -96(%rbp)
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	_Z12string_clearP13DynamicString@PLT
	cmpq	$0, -96(%rbp)
	jne	.L21
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %eax
	jmp	.L25
.L21:
	movq	-104(%rbp), %rax
	movq	-96(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z8readLineP13DynamicStringP8_IO_FILE
	testb	%al, %al
	je	.L22
	movq	-104(%rbp), %rdx
	leaq	-80(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_Z10insertHeapP4heapP5versh@PLT
	xorl	$1, %eax
	testb	%al, %al
	je	.L23
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
	movl	$1, %eax
	jmp	.L25
.L22:
	movq	-96(%rbp), %rax
	movq	%rax, %rdi
	call	fclose@PLT
.L23:
	movq	-104(%rbp), %rax
	movq	%rax, %rdi
	call	_Z10versh_freeP5versh@PLT
.L19:
	movq	-72(%rbp), %rax
	testq	%rax, %rax
	jne	.L24
	leaq	-80(%rbp), %rax
	movq	%rax, %rdi
	call	_Z10heapDeinitP4heap@PLT
	movb	%al, -113(%rbp)
	movl	$0, %eax
.L25:
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L26
	call	__stack_chk_fail@PLT
.L26:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE30:
	.size	main, .-main
	.ident	"GCC: (GNU) 15.2.1 20260103"
	.section	.note.GNU-stack,"",@progbits
