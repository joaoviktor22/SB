%include "io64.inc"
section .data

msg db 'Qual seu nome?',0xa
len equ $ - msg
bemvindo db 'Hola, '
lenbv equ $ - bemvindo
bemvindo2 db ', bem vindo ao programa de CALC IA-32.',0xa
lenbv2 equ $ - bemvindo2

menu0 db 'ESCOLHA UMA OPCAO!',0xa
lenmenu equ $ - menu0
menu1 db '1)SOMA',0xa
lenmenu1 equ $ - menu1
menu2 db '2)SUBTRACAO',0xa
lenmenu2 equ $ - menu2
menu3 db '3)MULTIPLICACAO',0xa
lenmenu3 equ $ - menu3
menu4 db '4)DIVISAO',0xa
lenmenu4 equ $ - menu4
menu5 db '5)MODULO',0xa
lenmenu5 equ $ - menu5
menu6 db '6)SAIR',0xa
lenmenu6 equ $ - menu6
pularlinha db 0xa

valor1m db 'Qual seu primeiro valor?',0xa
lenvalor1 equ $ - valor1m
valor2m db 'Qual seu segundo valor?',0xa
lenvalor2 equ $ - valor2m
resultadom db 'Resultado : '
lenresultado equ $ - resultadom

tamanho dd 0
tamnome dd 0
aux dd 0
valor dd 0
valor1 dd 0
valor2 dd 0
resultado dd 0
nega db '-'

section .bss

MAX equ 20
nome resb MAX


section .text
	global _start
_start:

	call cabeca

	loop:
	call menu
	call pegarvalor

	mov ebx, dword[aux]
	sub ebx, 0x30
	mov dword[valor], ebx

	call soma
	call subtracao
	call multiplicacao
	call divisao
	call modulo

	cmp byte[valor], 6
	jne loop

	fim:
	mov eax, 1
	int 0x80

	cabeca:

	mov edx, len
	mov ecx, msg
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, MAX
	mov ecx, nome
	mov ebx, 0
	mov eax, 3
	int 0x80

	dec eax
	mov dword[tamnome],eax

	mov edx, 1
	mov ecx, tamanho
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, lenbv
	mov ecx, bemvindo
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, [tamnome]
	mov ecx, nome
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, lenbv2
	mov ecx, bemvindo2
	mov ebx, 1
	mov eax, 4
	int 0x80

	ret

	menu:

	mov edx, lenmenu
	mov ecx, menu0
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, lenmenu1
	mov ecx, menu1
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, lenmenu2
	mov ecx, menu2
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, lenmenu3
	mov ecx, menu3
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, lenmenu4
	mov ecx, menu4
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, lenmenu5
	mov ecx, menu5
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, lenmenu6
	mov ecx, menu6
	mov ebx, 1
	mov eax, 4
	int 0x80

	ret

	pegarvalor:

	mov edx, MAX
	mov ecx, aux
	mov ebx, 0
	mov eax, 3
	int 0x80

	ret

	soma:
	cmp byte[valor], 1
	jne return

	mov edx, lenvalor1
	mov ecx, valor1m
	mov ebx, 1
	mov eax, 4
	int 0x80

	call pegarvalor
	mov edx, aux
	call convertestrint
	call negar
	mov dword[valor1], eax

	mov edx, lenvalor2
	mov ecx, valor2m
	mov ebx, 1
	mov eax, 4
	int 0x80

	call pegarvalor
	mov edx, aux
	call convertestrint
	call negar
	mov dword[valor2], eax

	mov edx, lenresultado
	mov ecx, resultadom
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov eax, dword[valor1]
	add eax, dword[valor2]
	mov edi,resultado
	call converteintstr

	mov edx, [tamanho]
	mov ecx, resultado
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, 1
	mov ecx, pularlinha
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, 1
	mov ecx, pularlinha
	mov ebx, 0
	mov eax, 3
	int 0x80

	ret

	subtracao:
	cmp byte[valor], 2
	jne return

	mov edx, lenvalor1
	mov ecx, valor1m
	mov ebx, 1
	mov eax, 4
	int 0x80

	call pegarvalor
	mov edx, aux
	call convertestrint
	call negar
	mov dword[valor1], eax

	mov edx, lenvalor2
	mov ecx, valor2m
	mov ebx, 1
	mov eax, 4
	int 0x80

	call pegarvalor
	mov edx, aux
	call convertestrint
	call negar
	mov dword[valor2], eax

	mov edx, lenresultado
	mov ecx, resultadom
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov eax, dword[valor1]
	sub eax, dword[valor2]
	mov edi,resultado
	call converteintstr

	mov edx, [tamanho]
	mov ecx, resultado
	mov ebx, 1
	mov eax, 4
	int 0x80


	mov edx, 1
	mov ecx, pularlinha
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, 1
	mov ecx, pularlinha
	mov ebx, 0
	mov eax, 3
	int 0x80

	ret

	multiplicacao:
	cmp byte[valor], 3
	jne return

	mov edx, lenvalor1
	mov ecx, valor1m
	mov ebx, 1
	mov eax, 4
	int 0x80

	call pegarvalor
	mov edx, aux
	call convertestrint
	call negar
	mov dword[valor1], eax

	mov edx, lenvalor2
	mov ecx, valor2m
	mov ebx, 1
	mov eax, 4
	int 0x80

	call pegarvalor
	mov edx, aux
	call convertestrint
	call negar
	mov dword[valor2], eax

	mov edx, lenresultado
	mov ecx, resultadom
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov eax, dword[valor1]
	mov ebx, dword[valor2]
	imul ebx
	mov edi,resultado
	call converteintstr

	mov edx, [tamanho]
	mov ecx, resultado
	mov ebx, 1
	mov eax, 4
	int 0x80


	mov edx, 1
	mov ecx, pularlinha
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, 1
	mov ecx, pularlinha
	mov ebx, 0
	mov eax, 3
	int 0x80

	ret

	divisao:
	cmp byte[valor], 4
	jne return

	mov edx, lenvalor1
	mov ecx, valor1m
	mov ebx, 1
	mov eax, 4
	int 0x80

	call pegarvalor
	mov edx, aux
	call convertestrint
	call negar
	mov dword[valor1], eax

	mov edx, lenvalor2
	mov ecx, valor2m
	mov ebx, 1
	mov eax, 4
	int 0x80

	call pegarvalor
	mov edx, aux
	call convertestrint
	call negar
	mov dword[valor2], eax

	mov edx, lenresultado
	mov ecx, resultadom
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov eax, dword[valor1]
	cdq
	mov ebx, dword[valor2]
	idiv ebx
	mov edi,resultado
	call converteintstr

	mov edx, [tamanho]
	mov ecx, resultado
	mov ebx, 1
	mov eax, 4
	int 0x80


	mov edx, 1
	mov ecx, pularlinha
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, 1
	mov ecx, pularlinha
	mov ebx, 0
	mov eax, 3
	int 0x80

	ret

	modulo:
	cmp byte[valor], 5
	jne return

	mov edx, lenvalor1
	mov ecx, valor1m
	mov ebx, 1
	mov eax, 4
	int 0x80

	call pegarvalor
	mov edx, aux
	call convertestrint

	mov dword[valor1], eax

	mov edx, lenresultado
	mov ecx, resultadom
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov eax, dword[valor1]
	mov edi,resultado
	call converteintstr

	mov edx, [tamanho]
	mov ecx, resultado
	mov ebx, 1
	mov eax, 4
	int 0x80


	mov edx, 1
	mov ecx, pularlinha
	mov ebx, 1
	mov eax, 4
	int 0x80

	mov edx, 1
	mov ecx, pularlinha
	mov ebx, 0
	mov eax, 3
	int 0x80

	ret

	convertestrint:
	xor eax,eax
	movzx ebx,byte[edx]
	cmp ebx, '-'
	je negativo2
	conv:
	movzx ecx,byte[edx]
	inc edx
	cmp ecx,'0'
	jb return
	cmp ecx,'9'
	ja return
	sub ecx, 0x30
	imul eax,10
	add eax, ecx
	jmp conv

	negativo2:
	inc edx
	jmp conv

	negar:
	cmp ebx, '-'
	jne return
	NEG eax
	ret

	converteintstr:
	xor ebx, ebx
	cmp eax, 0
	jge put
	neg eax
	push eax
	mov edx, 1
	mov ecx, nega
	mov ebx, 1
	mov eax, 4
	int 0x80
	pop eax
	xor ebx, ebx
	put:
	xor edx, edx
	mov ecx, 10
	div ecx
	add edx, 0x30
	push edx
	inc ebx
	test eax, eax
	jnz put
	mov [tamanho],ebx
	out:
	pop eax
	stosb
	dec ebx
	cmp ebx, 0
	jg out
	mov eax, 0x0a
	stosb
	ret

	return:

	ret