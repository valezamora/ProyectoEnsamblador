;---------------------------------------------------------------
;
;	Dispositivo
; 	Grupo 1 - Proyecto integrador
;
;----------------------------------------------------------------

section .data
	cantX: db 0h		; cantidad en x
	cantY: db 0h		; cantidad en y
	cantTransformaciones: db 0h 	; cantidad de transformaciones a realizar
	
section .bss
	dirTransformaciones: resb 6
	dirImagen: resb 6


section .text
	;pila
	push ebp
	mov ebp, esp
	
	; guardar direcciones de variables globales
	; se pasan como parametro (direccionTransformaciones, direccionImagen)
	mov dirTransformaciones, rdi
	mov dirImagen, rsi
	
	;guardar tamanos
	mov cantX, [rsi]
	mov cantY, [rsi+4]
	mov cantTransformaciones, [rdi]
	
	; for por cantidad de transformaciones
	mov rdx, 0  ;contador
	mov rcx, cantTransformaciones
	jmp testFor1

for1:
	; obtiene tipo de transformacion 
	mov rdi, dirTransformaciones
	add rdi, 4		;no toma en cuenta la cantidad de transformaciones
	mov rsi, Ch		; suma 12 (no estoy segura si se pone c)
	mov rax, [rdi+rsi]	;el tipo de transformacion se guarda en el espacio (dirTransformaciones+ 4 + i*12)
	
	;incrementa contador
	inc rdx
	
	;compara rax para saltar a la ejecucion de la transformacion
	cmp rax, 0
	je reflexion
	cmp rax, 1
	je escalacion
	cmp rax, 2
	je traslacion
	cmp rax, 3
	je brillo
	cmp rax, 4
	je negativo
	cmp rax, 5
	je contraste
	
;test para ver si faltan mas transformaciones	
testFor1:
	cmp rdx, rcx	;compara contador con la cantidad de transformaciones
	jl for1			; salta al contenido del for si el contador es menor que la cantidad de transformaciones
	
; https://localhost:5500/em
; ---------------- Transformaciones de imagenes vectoriales --------------------?
;id = 0
reflexion:		

	jmp testFor1

;id = 1
escalacion:		

	jmp testFor1

; id = 2
traslacion:

	jmp testFor1


; ---------------- Transformaciones de mapas de bits --------------------?
; id = 3
brillo:

	jmp testFor1

; id = 4
negativo:

	jmp testFor1

; id = 5
contraste:

	jmp testFor1
	
fin: 
	; devolver espacio de la pila
	
	pop ebp
	ret