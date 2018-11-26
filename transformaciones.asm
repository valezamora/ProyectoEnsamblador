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
	mov rsi, Ch		; guarda un 12 (no estoy segura si se pone c)
	mul rsi, rdx
	mov rax, [rdi+rsi]	;el tipo de transformacion se guarda en el espacio (dirTransformaciones+ 4 + i*12)
	
	;incrementa contador
	inc rdx
	
	; obtiene parametros
	
	;primer parametro (r8)
	; se guarda en i+4
	mov r12, 4
	add r12, rdx
	mov r8, [rdi+r12]
	
	;segundo parametro (r9)
	; se guarga en i+8
	mov r12, 8
	add r12, rdx
	mov r9, [rdi+r12]
	
	; inicio de la imagen (r10)
	mov r15, dirImagen
	mov r10, [r15+8]	; mas 8 porque primero estan dos enteros de las dimensiones 
	
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
	jmp fin			; salta al fin de la funcion
	
; ---------------- Transformaciones de imagenes vectoriales -----------------------------
; 
; Registros ocupados:
;	- rax = tipo de transformacion
;	- rdi = vector de transformaciones 
;	- rcx = cantidad de transformaciones
;	- rdx = i
;	- r8 = primer parametro
;	- r9 = segundo parametro
;	- r10 = inicio de la imagen

;id = 0
reflexion:		

		
	jmp testFor1

; ----------------------------------------------------------------------------------------
;id = 1
escalacion:		


	vzeroupper
	jmp testFor1

;--------------------------------------------------------------------------------------------
; id = 2
traslacion:
	; Se utiliza AVX, se procesan 256 bits a la vez, de 64 en 64 puntos.
	
	;get inicio de puntos y (r11)
	mov r14, cantX
	mov r11, [r15+r14]
	
	; crea vector de x y vector de para poder hacer las operaciones en paquetes
	
	; parametro x: poner el valor de r8 64 veces (ymm0)
	
	; parametro y: poner el valor de r9 64 veces (ymm1)
	
	
	
	;calcular cantidad de operaciones requeridas 
	mov r14, cantX
	mov r13, 40h
	div r14, r13	; (total de puntos en un eje/64)
	
	
	; contador (r12)
	mov r12, 0
	mov r13, 0
	
	;inicia ciclo
	jmp testForTraslacion
	
	;ciclo para leer los valores y sumarles el parametro en x y y
	forTraslacion:
		; mueve parte del vector de datos x a ymm2
		vmovaps ymm2, ymmword ptr [r10+r13] 
		
		;suma
		vaddps ymm4,ymm0,ymm2
		
		; guarda resultado de vuelta al vector
		vmovaps ymmword ptr [r10+r13], ymm4
		
		; mueve parte del vector de datos y a ymm3
		vmovaps ymm2, ymmword ptr [r11+r13] 

		; suma 
		vaddps ymm4,ymm1,ymm3
	
		; guarda resultado de vuelta al vector
		vmovaps ymmword ptr [r11+r13],ymm4
		
		; aumentar contador
		inc r12
		add r13, 100h		; aumenta la cantidad de bits que ya se utilizaron (256)
		
	testForTraslacion:
		; compara contador (r12) con cantidad de puntos (r14)
		cmp r12, r14
		; continua el ciclo si el contador es menor
		jl forTraslacion 
		
	
	vzeroupper
	jmp testFor1


; ---------------- Transformaciones de mapas de bits --------------------
; Para estas se utilizan instrucciones AVX de enteros. 
; Se procesan de 64 en 64 

; id = 3
brillo:
	; Se le suma el nivel del cambio de brillo a todas las entradas, verificando que no sean mayores a 255.
		
	; Se genera vector que contiene 64 veces el valor contenido en r8 (se guarda en ymm0)
	
	
	; Ciclo para sumar el vector a todas las entradas 
	mov r11, 0		;contador
	mov r12, 0 		;traslacion dentro del vector de pixeles
	mov r13, cantX
	mov r14, cantY
	mul r13, r14	; cantidad total de puntos (cada uno de 24 bits)
	div r13, 40h 	;total de operaciones requeridas (total puntos/64)
	
	jmp tesForBrillo
	
	forBrillo:
		; Se guarda imagen en ymm0
		vmovdqa ymm1,ymmword ptr [r10+r12]
		
		; Se le suma el nivel del cambio (ymm0 + ymm0)
		
		; PREGUNTA AL PROFE, COMO ERA LO DE MAXIMO 256, PUEDE HACERSE USANDO ENTEROS DE 4 BYTES
		
		
		; aumentar contador
		inc r11
		add r12, 100h 	;(sumar 256)
	
	tesForBrillo:
		cmp r11, r13
		jl forBrillo
	
	vzeroupper
	jmp testFor1

;--------------------------------------------------------------------------------------------

; id = 4
negativo:
	; Se genera vector que contiene 255 (64 255's)
	
	; Ciclo para negativo
	
	; contador
	mov r11, 0		;contador
	mov r12, 0 		;traslacion dentro del vector de pixeles
	mov r13, cantX
	mov r14, cantY
	mul r13, r14	; cantidad total de puntos (cada uno de 24 bits)
	div r13, 40h 	;total de operaciones requeridas (total puntos/64)
	
	
	jmp testForNegativo
	
	forNegativo:
		; Se guarda imagen en ymm0
		vmovdqa ymm1,ymmword ptr [r10+r12]
		
		; Se le suma el vector de 255 
		; PREGUNTA AL PROFE DE COMO HACER LO DE OVERFLOW QUE SE MANTENGA ENTRE 0 Y 255
		
		; aumentar contador
		inc r11
		add r12, 100h 	;(sumar 256)
	
	testForNegativo:
		cmp r11, r13
		jl forNegativo
	
	vzeroupper
	jmp testFor1

;--------------------------------------------------------------------------------------------
	
; id = 5
contraste:

	vzeroupper
	jmp testFor1
	
fin: 
	; devolver espacio de la pila
	
	pop ebp
	ret