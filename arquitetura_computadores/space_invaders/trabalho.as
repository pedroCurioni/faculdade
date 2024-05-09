;------------------------------------------------------------------------------
; ZONA I: Definicao de constantes
;         Pseudo-instrucao : EQU
;------------------------------------------------------------------------------
CR              EQU     0Ah
FIM_TEXTO       EQU     '@'
IO_READ         EQU     FFFFh
IO_WRITE        EQU     FFFEh
IO_STATUS       EQU     FFFDh
INITIAL_SP      EQU     FDFFh
CURSOR		    EQU     FFFCh
CURSOR_INIT		EQU		FFFFh
TIMER_INTERVAL	EQU		FFF6h
TIMER_CONTROL	EQU		FFF7h
INTERRUPT_MASK	EQU		FFFAh
ROW_POSITION	EQU		0d
COL_POSITION	EQU		0d
ROW_SHIFT		EQU		8d
COLUMN_SHIFT	EQU		8d

RAM_POSITION	EQU		8000h
LINE_MEMMORY	EQU		81d

;------------------------------------------------------------------------------
; ZONA II: definicao de variaveis
;          Pseudo-instrucoes : WORD - palavra (16 bits)
;                              STR  - sequencia de caracteres (cada ocupa 1 palavra: 16 bits).
;          Cada caracter ocupa 1 palavra
;------------------------------------------------------------------------------

                	ORIG    8000h
Line00      	STR    	'################################################################################', FIM_TEXTO
Line01			STR		'#   lives: 3                                                       points: 000 #', FIM_TEXTO
Line02      	STR    	'#                                                                              #', FIM_TEXTO
Line03			STR		'#                   \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/                    #', FIM_TEXTO
Line04			STR		'#                   \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/                    #', FIM_TEXTO
Line05			STR		'#                   \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/                    #', FIM_TEXTO
Line06			STR		'#                   \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/                    #', FIM_TEXTO
Line07			STR		'#                   \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/                    #', FIM_TEXTO
Line08      	STR    	'#                                                                              #', FIM_TEXTO
Line09      	STR    	'#                                                                              #', FIM_TEXTO
Line10      	STR    	'#                                                                              #', FIM_TEXTO
Line11      	STR    	'#                                                                              #', FIM_TEXTO
Line12      	STR    	'#                                                                              #', FIM_TEXTO
Line13      	STR    	'#                                                                              #', FIM_TEXTO
Line14      	STR    	'#                                                                              #', FIM_TEXTO
Line15      	STR    	'#                                                                              #', FIM_TEXTO
Line16      	STR    	'#                                                                              #', FIM_TEXTO
Line17      	STR    	'#                                                                              #', FIM_TEXTO
Line18      	STR    	'#                                                                              #', FIM_TEXTO
Line19      	STR    	'#                                                                              #', FIM_TEXTO
Line20      	STR    	'#                                                                              #', FIM_TEXTO
Line21			STR		'#                                     /-\                                      #', FIM_TEXTO
Line22      	STR    	'#                                                                              #', FIM_TEXTO
Line23      	STR    	'################################################################################', FIM_TEXTO

Bullet				STR		'|'
Enemy				STR		'\W/'

ScreenCentenaPointsPosition		WORD	014Bh		; Posição do ultimo caracter da pontuação na tela
ScreenDezenaPointsPosition		WORD	014Ch		; Posição do ultimo caracter da pontuação na tela
PointsDezena				WORD	0030h		; Numero decimal de pontos
PointsCentena				WORD	0030h		; Numero das centenas de pontos

ShipLine			WORD	21d			; Linha da nave
ShipColumn			WORD	39d			; Coluna atual da nave

ShipBulletExists		WORD	0h		; Guarda a informação se o tiro está ou não na tela
ShipBulletPosition		WORD	0h		; Posição do tiro da nave

MapColumnLeftBorder		WORD	1d 		; Borda esquerda da linha da nave
MapColumnRightBorder	WORD	80d		; Borda direita da linha da nave

RowIndex		WORD	0d
ColumnIndex		WORD	0d
TextIndex		WORD	0d


;------------------------------------------------------------------------------
; ZONA III: definicao de tabela de interrupções
;------------------------------------------------------------------------------
                ORIG    FE00h
INT0            WORD    MoveLeft
INT1            WORD    MoveRight
INT2            WORD    StartShipBullet
INT3            WORD    Main
INT4            WORD    Main
INT5            WORD    Main
INT6            WORD    Main
INT7            WORD    Main
INT8            WORD    Main
INT9            WORD    Main
INT10           WORD    Main
INT11           WORD    Main
INT12           WORD    Main
INT13           WORD    Main
INT14           WORD    Main
INT15           WORD    TimerRoutine

;------------------------------------------------------------------------------
; ZONA IV: codigo
;        conjunto de instrucoes Assembly, ordenadas de forma a realizar
;        as funcoes pretendidas
;------------------------------------------------------------------------------
                ORIG    0000h
                JMP     Main

;------------------------------------------------------------------------------
; Rotina Esqueleto
;------------------------------------------------------------------------------
Esqueleto: 	PUSH R1
			PUSH R2
			PUSH R3

			POP R3
			POP R2
			POP R1

			RET


;------------------------------------------------------------------------------
; Rotina PringString
;------------------------------------------------------------------------------
PringString:	PUSH R1
				PUSH R2
				PUSH R3

	CyclePrintString:	MOV	R2, M [ R1 ]					; Passa para R2 o caracter na posição de R1

						CMP 	R2, FIM_TEXTO				; Verefica se R2 e o fim do texto
						JMP.Z 	EndPrintString

						MOV		M[ IO_WRITE ], R2			; Escreve R2						
						INC 	R1							; Anda a string uma posição para frente

						INC		M[ ColumnIndex ]			; Anda uma linha para frente
						MOV		R2, M[ RowIndex ]			; R2 = Linha atual
						MOV		R3, M[ ColumnIndex ]; 		; R3 = Coluna atual
						SHL		R2, ROW_SHIFT				; R2 = Linha atual movida para os bites da esquerda
						OR		R2, R3						; Concatena R2 e R3
						MOV		M[ CURSOR ], R2				; Move o cursor para a posição de R2

						JMP CyclePrintString

	EndPrintString:	INC M[ RowIndex ]
					MOV R1, COL_POSITION
					MOV M[ ColumnIndex ], R1
					MOV R2, M[ RowIndex ]
					SHL	R2, ROW_SHIFT						; R2 = Linha atual movida para os bites da esquerda
					OR	R2, R1								; Concatena R2 e R3
					MOV	M[ CURSOR ], R2						; Move o cursor para a posição de R2

					POP R3
					POP R2
					POP R1

					RET

;------------------------------------------------------------------------------
; Rotina PrintScreen
;------------------------------------------------------------------------------
PrintScreen:	PUSH R1
				PUSH R2

				MOV R1, RAM_POSITION
				MOV R2, 0

				PrintScreenCycle:	CMP R2, 24
									JMP.Z	EndprintScreen

									CALL PringString

									ADD R1, 81
									INC R2

									JMP PrintScreenCycle

				EndprintScreen:	POP R2
								POP R1

								RET

;------------------------------------------------------------------------------
; Rotina Print character on memory
;------------------------------------------------------------------------------
AlterMemory:	PUSH R1		; Posição do cursor
				PUSH R2		; Caracter
				PUSH R3
				PUSH R4

				MOV R3, R1

				AND R1, FFh				; Coluna
				AND R3, FF00h			; Linha
				SHR R3, ROW_SHIFT

				MOV R4, LINE_MEMMORY
				MUL R3, R4				; Move uma linha inteira na memoria

				ADD R1, R4

				MOV R3, RAM_POSITION
				ADD R1, R3

				MOV M [ R1 ], R2		; Altera o dado na RAM

				POP R4
				POP R3
				POP R2
				POP R1
				
				RET

;------------------------------------------------------------------------------
; Rotina Print Ship
;------------------------------------------------------------------------------
PrintShip:	PUSH R1
			PUSH R2

			MOV R2, '/'
			MOV M [ IO_WRITE ], R2
			CALL AlterMemory

			INC R1
			MOV M [ CURSOR ], R1

			MOV R2, '-'
			MOV M [ IO_WRITE ], R2
			CALL AlterMemory

			INC R1
			MOV M [ CURSOR ], R1

			MOV R2, '\'
			MOV M [ IO_WRITE ], R2
			CALL AlterMemory

			POP R2
			POP R1

			RET

;------------------------------------------------------------------------------
; Interrupção Move left
;------------------------------------------------------------------------------
MoveLeft:	PUSH R1
			PUSH R2

			MOV R1, M [ ShipLine ]
			SHl	R1, ROW_SHIFT

			MOV R2, M [ ShipColumn ]
			OR R1, R2

			DEC R2			
			CMP R2, M [ MapColumnLeftBorder ]		; Verifica se a ponta esquerda da nave esta na borda do mapa
			JMP.Z EndMoveLeft

			SUB R1, 2								; Posiciona o cursor para escrever a nave então deletar o ultimo caracter
			MOV M [ CURSOR ], R1

			CALL PrintShip

			ADD R1, 3
			MOV M [ CURSOR ], R1
			MOV R2, ' '
			MOV M [ IO_WRITE ], R2

			DEC M [ ShipColumn ]

			EndMoveLeft:	POP R2	
							POP R1

							RTI

;------------------------------------------------------------------------------
; Interrupção Move right
;------------------------------------------------------------------------------
MoveRight:	PUSH R1
			PUSH R2

			MOV R1, M [ ShipLine ]
			SHl	R1, ROW_SHIFT

			MOV R2, M [ ShipColumn ]
			OR R1, R2

			ADD R2, 3			
			CMP R2, M [ MapColumnRightBorder ]		; Verifica se a ponta direita da nave esta na borda do mapa
			JMP.Z EndMoveRight

			SUB R1, 1
			MOV M [ CURSOR ], R1

			MOV R2, ' '
			MOV M [ IO_WRITE ], R2
			INC R1
			MOV M [ CURSOR ], R1

			CALL PrintShip

			INC M [ ShipColumn ]

			EndMoveRight:	POP R2
							POP R1

							RTI


;------------------------------------------------------------------------------
; Rotina Erase Enemy
;------------------------------------------------------------------------------
EraseEnemy:	PUSH R1 ; Posição na RAM
			PUSH R2	; Contador
			PUSH R3	; Posição da nave na tela
			PUSH R4

			MOV R2, 0
			MOV R4, ' '

			EraseEnemyLoop:	CMP R2, 3
							JMP.Z EnemyEraseEnd
							MOV M[ CURSOR ], R3
							MOV M[ IO_WRITE ], R4
							MOV M [ R1 ], R4
							
							INC R3					; Anda uma posição na tela
							INC R1					; Anda uma posição na RAM
							INC R2
							JMP EraseEnemyLoop

			EnemyEraseEnd:  POP R4
							POP R3
							POP R2
							POP R1

							RET

;------------------------------------------------------------------------------
; Rotina Handler Erase Enemy
;------------------------------------------------------------------------------
EraseEnemyHandler:	PUSH R1				; Posição na RAM
					PUSH R2				; Caracter da posição
					PUSH R3				; Posição da nave na tela
		
					CMP R2, '\'
					JMP.NZ EndFirstEnemyPosition
					CALL EraseEnemy
					JMP EndEraseEnemy

					EndFirstEnemyPosition:  CMP R2, 'W'
											JMP.NZ EndSecondEnemyPosition
											DEC R1
											DEC R3
											CALL EraseEnemy
											JMP EndEraseEnemy

					EndSecondEnemyPosition: 	CMP R2, '/'
												SUB R1, 2
												SUB R3, 2
												CALL EraseEnemy

					EndEraseEnemy:	POP R3
									POP R2
									POP R1

									RET

;------------------------------------------------------------------------------
; Rotina Increase Points
;------------------------------------------------------------------------------
IncreasePoints:		PUSH R1
					PUSH R2
					PUSH R3

					

					MOV R1, M [ PointsDezena ]
					INC R1
					CMP R1, ':'									; Valor da tabela ascii que fica depois do 9

					JMP.NZ PrintDezena

					IncreaseCentena:	MOV R1, '0'
										MOV R2, M [ PointsCentena ]
										INC R2
										
										MOV R3, M [ScreenCentenaPointsPosition]
										MOV M [ CURSOR ], R3

										MOV M [ IO_WRITE ], R2
										MOV M [ PointsCentena ], R2

					PrintDezena:		MOV R3, M [ ScreenDezenaPointsPosition ]
										MOV M [ CURSOR ], R3

										MOV M [ IO_WRITE ], R1
										MOV M [ PointsDezena ], R1

					POP R3
					POP R2
					POP R1

					RET

;------------------------------------------------------------------------------
; Rotina MoveBulletUp
;------------------------------------------------------------------------------
MoveBulletUp:	PUSH 	R1							; Contem a posição da linha anterior
				PUSH 	R2
				PUSH 	R3
				PUSH	R4

				MOV R2, M [ ShipBulletExists ]		; Verifica se o tiro ja esta na tela
				CMP R2, 0

				JMP.Z EndMoveBulletUp

				MOV 	R2, R1
				MOV		R4, R1

				AND		R1, 255						; Zera os 8 bits da dirita de R1 que representam a linha
				SHR 	R2, ROW_SHIFT				; Coloca os valors da coluna na esquerda para decrementar
				DEC 	R2

				CMP		R2, 1						; Verifica se o tiro esta na posição mais alta possivel
				JMP.Z 	BulletInLastRow

				SHL		R2, ROW_SHIFT
				OR		R1, R2

				MOV		M[ ShipBulletPosition ], R1
				MOV		M[ CURSOR ], R1
				
				; ---------------------------
				; Colisão
				; ---------------------------
				MOV R2, R1
				AND R1, FFh				; Coluna
				AND R2, FF00h			; Linha
				SHR R2, ROW_SHIFT

				MOV R3, LINE_MEMMORY
				MUL R2, R3				; Move uma linha inteira na memoria

				ADD R1, R3

				MOV R2, RAM_POSITION
				ADD R1, R2

				MOV R2, M [ R1 ]		; Recupera o dado da RAM

				CMP R2, ' '
				JMP.Z EndColisionCheck

				CALL IncreasePoints

				MOV R3, M [ ShipBulletPosition ]
				CALL EraseEnemyHandler

				JMP BulletInLastRow
				; ---------------------------

				EndColisionCheck:	MOV		R1, M [ Bullet ]
									MOV		M[ IO_WRITE ], R1

									MOV R1, M [ ShipLine ]
									SHl	R1, ROW_SHIFT
									MOV R2, M [ ShipColumn ]
									OR R1, R2

									CMP R4, R1							; Verifica se a posição anterior e referente a nave
									JMP.Z	EndMoveBulletUp
									
									JMP		ErasePreviousShipBullet

				BulletInLastRow:			MOV		R1, 0
											MOV		M [ ShipBulletExists ], R1

				ErasePreviousShipBullet:	MOV		M [ CURSOR ], R4
											MOV 	R4,	' '
											MOV 	M[ IO_WRITE ], R4

				EndMoveBulletUp:	POP R4
									POP R3
									POP R2
									POP R1

									RET

;------------------------------------------------------------------------------
; Interrupção StartShipBullet
;------------------------------------------------------------------------------
StartShipBullet:	PUSH R1
					PUSH R2
					PUSH R3

					MOV R1, M [ ShipBulletExists ]			; Verifica se o tiro ja esta na tela
					CMP R1, 1
					JMP.Z EndStartShipBullet

					MOV R1, 1
					MOV M [ ShipBulletExists ], R1

					MOV R1, M [ ShipLine ]
					SHl	R1, ROW_SHIFT
					MOV R2, M [ ShipColumn ]
					OR R1, R2
					CALL MoveBulletUp

					EndStartShipBullet: POP R3
										POP R2
										POP R1

										RTI

;------------------------------------------------------------------------------
; Rotina Start Timer
;------------------------------------------------------------------------------
StartTimer:		PUSH R1

				MOV			R1, 1					 ; Reseta o timer
				MOV			M [ TIMER_INTERVAL ], R1
				MOV 		R1, 1
				MOV			M [ TIMER_CONTROL ],  R1

				POP R1

				RET

;------------------------------------------------------------------------------
; Interrupção Timer
;------------------------------------------------------------------------------
TimerRoutine:	PUSH R1
				PUSH R2

				MOV R1, M [ ShipBulletPosition ]
				CALL MoveBulletUp

				CALL StartTimer

				POP R2
				POP	R1

				RTI

;------------------------------------------------------------------------------
; Função Main
;------------------------------------------------------------------------------
Main:	ENI

		MOV		R1, INITIAL_SP
		MOV		SP, R1		 		; We need to initialize the stack
		MOV		R1, CURSOR_INIT		; We need to initialize the cursor 
		MOV		M[ CURSOR ], R1		; with value CURSOR_INIT
		
		CALL PrintScreen
		CALL StartTimer

Cycle:	BR			Cycle
Halt:           BR		Halt