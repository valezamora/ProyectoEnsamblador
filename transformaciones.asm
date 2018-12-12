;---------------------------------------------------------------
;
;	Dispositivo
; 	Grupo 1 - Proyecto integrador
;
;----------------------------------------------------------------

global transformarImagen


section .data
	
section .bss


section .text

transformarImagen:
	;pila

	mov ebp, esp
	
	; registros callee saved
	push rbx
	push r12
	push r13
	push r14
		
	; -------parametros---------------------------------------------------
	; cantidad de transformaciones, vector de transformaciones, cantidad puntos x o filas, cantidad de puntos y o columnas y puntero a imagen
	; guardar direcciones de variables globales
	; se pasan como parametro (direccionTransformaciones, direccionImagen)
	;mov [cantTransformaciones], rdi
	;mov [dirTransformaciones], rsi
	;mov [cantX], rdx
	;mov [cantY], rcx
	;mov [dirImagen], r8
	
	mov r10, rdx
	
	; for por cantidad de transformaciones
	mov rbx, 0  ;contador
	jmp testFor1

for1:
	; obtiene tipo de transformacion 

	mov rax, 12		; guarda un 12 
	mul rbx			; guarda un 12*i en rax
	mov r12, rax
	mov r13, rsi
	add r13, r12
	mov rax, [r13]	;el tipo de transformacion se guarda en el espacio (dirTransformaciones+ i*12)
	
	;incrementa contador
	inc rbx
	
	; obtiene parametros
	
	;primer parametro (r15)
	; se guarda en i+4
	mov r12, 4
	add r12, rbx
	mov r15, [rsi+r12]
	
	;segundo parametro (r9)
	; se guarga en i+8
	mov r12, 8
	add r12, rbx
	mov r9, [rsi+r12]
	
	; inicio de la imagen (r8)
	
	;compara rax para saltar a la ejecucion de la transformacion
	cmp rax, 0
	je reflexion
	cmp rax, 1
	;je escalacion
	cmp rax, 2
	;je traslacion
	cmp rax, 3
	;je brillo
	cmp rax, 4
	;je negativo
	cmp rax, 5
	;je contraste
	
;test para ver si faltan mas transformaciones	
testFor1:
	cmp rbx, rdi	;compara contador con la cantidad de transformaciones
	jl for1			; salta al contenido del for si el contador es menor que la cantidad de transformaciones
	jmp fin			; salta al fin de la funcion
	
; ---------------- REGISTROS OCUPADOS -----------------------------
; 
; Registros ocupados:
;	- rax = tipo de transformacion
;	- rsi = vector de transformaciones 
;	- rdi = cantidad de transformaciones
;	- rdx = transformaciones
;	- rbx = i
;	- r8 = imagen
;	- r15 = primer parametro
;	- r9 = segundo parametro



; ---------------- Transformaciones de imagenes vectoriales -----------------------------

;id = 0
reflexion:		
	
	;get inicio de puntos y (r11)
	mov r11, r10	; cantidad de puntos
	mov rax, 4
	mul r11
	mov r11, rax	;distania del inicio del vector
	mov r13, r8
	add r11, r13		; posicion inicial de puntos y

	
	;calcular cantidad de operaciones requeridas 
	mov rax, r10
	mov r13, 8
	div r13			; (total de puntos en un eje/8)
	mov r14, rax

	
	; contador (r12)
	mov r12, 0
	mov r13, 0
	
	;inicia ciclo
	jmp testForReflexion
	
	
	forReflexion:
		; mueve parte del vector de datos x a ymm0
		vmovaps ymm0, [r8+r13] 
		;mueve parte del vector de ddatos y a ymm1
		vmovaps ymm1, [r11+r13]
		
		; guarda invertidos los puntos
		vmovaps  [r8+r13], ymm1
		vmovaps  [r11+r13], ymm0
	
		; aumentar contador
		inc r12
		add r13, 100h		; aumenta la cantidad de bits que ya se utilizaron (256 bits = 8 puntos)
	
	testForReflexion:
	; compara contador (r12) con cantidad de puntos (rax)
		cmp r12, r14
		; continua el ciclo si el contador es menor
		jl forReflexion
		
	vzeroupper	
	jmp testFor1

; ----------------------------------------------------------------------------------------

;id = 1
escalacion:
	; Se utiliza AVX, se procesan 256 bits a la vez, de 8 en 8 puntos en formato punto flotante de 32 bits.
	
	;get inicio de puntos y (r11)
	mov r14, rdx
	mov r11, [r15+r14]
	
	; crea vector de x y vector de y para poder hacer las operaciones en paquetes
	
	; parametro x: poner el valor de r15  (ymm0)
	vpbroadcastd ymm0, [r15]
	
	; parametro y: poner el valor de r9 64 veces (ymm1)
	vpbroadcastd ymm1, [r9]
	
	;calcular cantidad de operaciones requeridas 
	mov rax, rdx
	mov r13, 8
	div r13			; (total de puntos en un eje/8)
	mov r14, rax
	
	; contador (r12)
	mov r12, 0
	mov r13, 0
	
	;inicia ciclo
	
	jmp testForEscalacion
	
	;ciclo para leer los valores y sumarles el parametro en x y y
	forEscalacion:
		; mueve parte del vector de datos x a ymm2
		vmovaps ymm2,  [r8+r13] 
		
		; multiplicacion
		vmulps ymm4,ymm0,ymm2
		
		; guarda resultado de vuelta al vector
		vmovaps  [r8+r13], ymm4
		
		; mueve parte del vector de datos y a ymm3
		vmovaps ymm2, [r11+r13] 

		; multiplicacion 
		vmulps ymm4,ymm1,ymm3
	
		; guarda resultado de vuelta al vector
		vmovaps [r11+r13],ymm4
		
		; aumentar contador
		inc r12
		add r13, 100h		; aumenta la cantidad de bits que ya se utilizaron (256)
		
	testForEscalacion:
		; compara contador (r12) con cantidad de puntos (r14)
		cmp r12, r14
		; continua el ciclo si el contador es menor
		jl forEscalacion
		
	
	vzeroupper
	jmp testFor1


;--------------------------------------------------------------------------------------------
; id = 2
traslacion:
	; Se utiliza AVX, se procesan 256 bits a la vez, de 64 en 64 puntos en formato punto flotante de 32 bits.
	
	;get inicio de puntos y (r11)
	mov r14, rdx
	mov r11, [r15+r14]
	
	; crea vector de x y vector de y para poder hacer las operaciones en paquetes
	
	; parametro x: poner el valor de r15 (ymm0)
	vpbroadcastd ymm0, [r15]
	
	; parametro y: poner el valor de r9 64 veces (ymm1)
	vpbroadcastd ymm1, [r9]
	
	;calcular cantidad de operaciones requeridas 
	mov rax, rdx
	mov r13, 8
	div r13			; (total de puntos en un eje/8)
	mov r14, rax

	
	; contador (r12)
	mov r12, 0
	mov r13, 0
	
	;inicia ciclo
	
	jmp testForTraslacion
	
	;ciclo para leer los valores y sumarles el parametro en x y y
	forTraslacion:
		; mueve parte del vector de datos x a ymm2
		vmovaps ymm2, [r8+r13] 
		
		;suma
		vaddps ymm4,ymm0,ymm2
		
		; guarda resultado de vuelta al vector
		vmovaps [r8+r13], ymm4
		
		; mueve parte del vector de datos y a ymm3
		vmovaps ymm2, [r11+r13] 

		; suma 
		vaddps ymm4,ymm1,ymm3
	
		; guarda resultado de vuelta al vector
		vmovaps [r11+r13],ymm4
		
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
; Se procesan de 256 en 256 porque se utilizan enteros de 1 byte 

; id = 3
brillo:
	; Se le suma el nivel del cambio de brillo a todas las entradas, verificando que no sean mayores a 255.
		
	; Se genera vector que contiene 64 veces el valor contenido en r15 (se guarda en ymm0)
	vpbroadcastb ymm0, [r15]
	
	; Ciclo para sumar el vector a todas las entradas 
	mov r11, 0		;contador
	mov r12, 0 		;traslacion dentro del vector de pixeles
	mov rax, rdx
	mov r14, rcx
	mul r14		; cantidad total de puntos (cada uno de 24 bits)
	mov r13, 32
	div r13 	; total de operaciones requeridas (total puntos/256)
	mov r13, rax
	
	jmp tesForBrillo
	
	forBrillo:
		; Se guarda imagen en ymm1
		vmovdqa ymm1, [r8+r12]
		
		; Se le suma el nivel del cambio en ymm2 (ymm0 + ymm1) (instruccion para 1 byte)
		vpaddb ymm2, ymm0, ymm1	
		
		; Se guarda imagen nuevamente
		vmovdqa [r8+r12], ymm1
		
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
	; Se genera vector que contiene 255 (64 255's) se guarda en ymm0
	mov r15, 255
	vpbroadcastb ymm0, [r15]
	
	; Ciclo para negativo
	
	; contador
	mov r11, 0		;contador
	mov r12, 0 		;traslacion dentro del vector de pixeles
	mov rax, rdx
	mov r14, rcx
	mul r14			; cantidad total de puntos (cada uno de 24 bits)
	mov r13, 32 	;total de operaciones requeridas (total puntos/32)
	div r13
	mov r13, rax
	
	jmp testForNegativo
	
	forNegativo:
		; Se guarda imagen en ymm1
		vmovdqa ymm1, [r8+r12]
		
		; Se le resta el vector de 255 
		vpsubb ymm2, ymm0, ymm1
		
		; Se guarda imagen nuevamente
		vmovdqa [r8+r12], ymm2
		
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
; Se genera vector que contiene el parametro  (64 255's) se guarda en ymm0
	vpbroadcastb ymm0, [r15]
	
	; Ciclo para contraste
	
	; contador
	mov r11, 0		; contador
	mov r12, 0 		; traslacion dentro del vector de pixeles
	mov rax, rdx
	mov r14, rcx
	mul r14			; cantidad total de puntos (cada uno de 24 bits)
	mov r13, 32 	; total de operaciones requeridas (total puntos/32)
	div r13
	mov r13, rax
	
	jmp testForContraste
	
	forContraste:
		; Se guarda imagen en ymm1
		vmovdqa ymm1, [r8+r12]
		
		; Se le suma el vector de parametro 
		vpaddb ymm2, ymm0, ymm1
		
		; Se guarda imagen nuevamente
		vmovdqa  [r8+r12], ymm2
		
		; aumentar contador
		inc r11
		add r12, 100h 	;(sumar 256)
	
	testForContraste:
		cmp r11, r13
		jl forContraste
	
	vzeroupper
	jmp testFor1

;------------------------------------------------------------------------------------------------
fin:
	pop r14
	pop r13
	pop r12
	pop rbx
	
	ret
