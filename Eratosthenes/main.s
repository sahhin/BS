;******************** (C) COPYRIGHT HAW-Hamburg ********************************
;* File Name          : main.s
;* Author             : Alfred Lohmann
;* Author             : Tobias Jaehnichen	
;* Version            : V2.0
;* Date               : 23.04.2017
;* Description        : This is a simple main.
;					  : The output is send to UART 1. Open Serial Window when 
;					  : when debugging. Select UART #1 in Serial Window selection.
;					  :
;					  : Replace this main with yours.
;
;*******************************************************************************

	EXTERN Init_TI_Board		; Initialize the serial line
	

;********************************************
; Data section, aligned on 4-byte boundery
;********************************************
		;Make a new block of data
	AREA MyData, DATA, align = 2 ;Align data or code to a particular memory boundary, Typically	2^N
	global prims ;TODO
		
prims SPACE 100 ;Allocate a zeroed block of memory for prims, Platz für 100 byte reserviert wurde , mit nullen initialisiert 
outpu DCD 0 ;Allocate words (32 bits) of data
	

;********************************************
; Code section, aligned on 8-byte boundery
;********************************************
	;Make a new block of code
	AREA |.text|, CODE, READONLY, ALIGN = 3
	
	extern CountPrimNum ; C-Programm

;--------------------------------------------
; main subroutine     
;--------------------------------------------
		EXPORT main [CODE]
	
main	PROC ;Declare the start of a procedure
	
		mov r0,#6
		mov r1,#4
		adds r1,r1,r0
		movcc r3,#0xD
		movcs r4,#0xC
	
		LDR r2,=prims
		mov r1,#1
		mov r0,#0
		strb r0,[r2]
		strb r0,[r2,#1]

		;Forschleife zur Initialisierung Primzahlenarray
		mov r3,#2
lini 	cmp r3,#100
		beq liniend
		strb r1,[r2,r3] ; Inhalt der r1 wurde unter adresse (berechnet r2 + r3) gespeichert, x20000008 + x00000002 = x2000000A
 		add r3,r3,#1 ;i++
	b lini
liniend ;ende Forschleife zur Initialisierung
	
		;aeussere Forschleife zur Besetzung Primzahlenarray
		mov r3,#2
lallez cmp r3,#10
		bpl lallezend
		;if untersuchte Zahl == Primzahl
		ldrb r4,[r2,r3]
		cmp r4,r1 ;if prim
		bne endifp
			;Forschleife zum Loeschen von Vielfachen
			add r5, r3,r3
lallep cmp r5,#100
			bpl lallepend
 				strb r0,[r2,r5]
			add r5,r5,r3 ;j=j+i
			b lallep
lallepend ;ende Forschleife zu Loeschen
endifp ;ende if untersuchte Zahl == Primzahl
		add r3,r3,#1 ;i++
	b lallez
lallezend ; ende aeussere Forschleife zur Besetzung Primzahlenarray

;#####################################################################

	; START PRIMZAHLEN ZAEHLEN
	
	;C-Unterprogramm
	mov r0, #20
	mov r1, #30
	ldr r2, =prims
	BL CountPrimNum; rufen Unterprogramm auf
	
	mov r0, #50
	mov r1, #80
	ldr r2, =prims
	BL CountPrimNum; rufen Unterprogramm auf
	
	;ASM-Unterprogramm
	mov r0, #20 ;Parameter Anfang
	mov r1, #30 ;Parameter Ende
	ldr r2, =prims ;Prim-Array
	bl CountPrimNumAsm; rufe Unterprogramm auf
	
	mov r0, #50 ;Parameter Anfang
	mov r1, #80 ;Parameter Ende
	ldr r2, =prims ;Prim-Array
	bl CountPrimNumAsm; rufe Unterprogramm auf
	
forever b forever ; nowhere to retun if main ends
	ENDP ; Designate the end of a procedure
		
CountPrimNumAsm ;Unterprogramm
	mov r3, #0 ; Prim-Counter zuruecksetzen
	add r0, r2, r0 ; Start
	add r1, r2, r1 ;Ende
loop
	cmp r0,r1 ;Vergleiche Start- und Endadresse
	
	beq endProgramm1 ;Wenn letzter Vergleich equal, Programm beenden
	
	ldrb r2, [r0] ;Lade 1 Byte aus Primzahl-Array nach r7
	
	cmp r2, #1 ;Ist r7 eine Primzahl?
	
	addeq r3, r3, #1 ;Wenn ja, erhoehe Counter +1
	
	add r0, r0, #1 ;Erhoehe Start-Adresse +1
	b loop ;Zurueck zum Schleifenanfang
	
endProgramm1 ;Marker für Ende erstes ASM Unterprogramm

	bx lr		
 
	ALIGN
	END ;Designate the end of a source file