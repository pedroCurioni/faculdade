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

EnemyLine		STR		'#                   \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/                    #', FIM_TEXTO
EmptyLine		STR		'#                                                                              #', FIM_TEXTO

Bullet				STR		'|'
Enemy				STR		'\W/'

ScreenCentenaPointsPosition		WORD	014Bh		; Posição do ultimo caracter da pontuação na tela
ScreenDezenaPointsPosition		WORD	014Ch		; Posição do ultimo caracter da pontuação na tela
PointsDezena					WORD	0030h		; Numero decimal de pontos
PointsCentena					WORD	0030h		; Numero das centenas de pontos

ScreenLivesPosition				WORD	010Bh		; Posição dos vidas na tela
LivesCounter					WORD	0033h		; Contador de vidas

ShipLine						WORD	21d			; Linha da nave
ShipColumn						WORD	39d			; Coluna atual da nave

ShipBulletExists				WORD	0h			; Guarda a informação se o tiro está ou não na tela
ShipBulletLine					WORD	0h			; Linha do tiro da nave
ShipBulletPosition				WORD	0h			; Posição do tiro da nave

MapColumnLeftBorder				WORD	1d 			; Borda esquerda da linha da nave
MapColumnRightBorder			WORD	80d			; Borda direita da linha da nave

EnemyLastLineStart				WORD	8285h		; Final da ultima linha de inimigos
EnemyLowerLine					WORD	7d			; Número da linha da ultima fileira de inimigos

EnemyMoveCounter				WORD	0000h		; Timer para mover o inimigo

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
; Rotina PrintString
;------------------------------------------------------------------------------
PrintString:	PUSH R1
				PUSH R2
				PUSH R3
	
	MOV R3, R1												; Posiciona o cursor na linha correta
	SHL R3, ROW_SHIFT
	MOV M [ CURSOR ], R3
	
	MOV R2, 81												; Posiciona o R1 no inicio da linha recebida
	MUL R2, R1
	ADD R1, 8000h

	CyclePrintString:	MOV	R2, M [ R1 ]					; Passa para R2 o caracter na posição de R1

						CMP 	R2, FIM_TEXTO				; Verefica se R2 e o fim do texto
						JMP.Z 	EndPrintString

						MOV		M[ IO_WRITE ], R2			; Escreve R2						
						INC 	R1							; Anda a string uma posição para frente

						INC		M[ ColumnIndex ]			; Anda uma linha para frente
						MOV		R2, M[ ColumnIndex ]; 		; R3 = Coluna atual
						OR		R2, R3						; Concatena R2 e R3, R3 = Linha atual movida para os bites da esquerda
						MOV		M[ CURSOR ], R2				; Move o cursor para a posição de R2

						JMP CyclePrintString

	EndPrintString:	MOV R1, 0
					MOV M[ ColumnIndex ], R1
					MOV M [RowIndex ], R1

					POP R3
					POP R2
					POP R1

					RET

;------------------------------------------------------------------------------
; Rotina PrintScreen
;------------------------------------------------------------------------------
PrintScreen:	PUSH R1

				MOV R1, 0

				PrintScreenCycle:	CMP R1, 24
									JMP.Z	EndprintScreen

									CALL PrintString

									INC R1
				
									JMP PrintScreenCycle

				EndprintScreen:	POP R1

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
			PUSH R3

			MOV R2, 0
			MOV R3, ' '

			EraseEnemyLoop:	CMP R2, 3
							JMP.Z EnemyEraseEnd
							MOV M [ R1 ], R3
							
							INC R1					; Anda uma posição na RAM
							INC R2
							JMP EraseEnemyLoop

			EnemyEraseEnd:	POP R3
							POP R2
							POP R1

							RET

;------------------------------------------------------------------------------
; Rotina Handler Erase Enemy
;------------------------------------------------------------------------------
EraseEnemyHandler:	PUSH R1				; Parametro: Posição na RAM
					PUSH R2				

					MOV		R2, M [ R1 ]	; Caracter da posição
		
					CMP 	R2, '\'
					JMP.NZ 	EndFirstEnemyPosition
					CALL 	EraseEnemy
					JMP 	EndEraseEnemy

					EndFirstEnemyPosition:  CMP 	R2, 'W'
											JMP.NZ 	EndSecondEnemyPosition
											DEC 	R1
											CALL 	EraseEnemy
											JMP 	EndEraseEnemy

					EndSecondEnemyPosition: 	CMP	 	R2, '/'
												SUB 	R1, 2
												CALL 	EraseEnemy

					EndEraseEnemy:	POP R2
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
MoveBulletUp:	PUSH 	R1								; Contem a posição da linha anterior
				PUSH 	R2								; Calculado, Contem a posição da proxima linha
				PUSH 	R3
				PUSH	R4

				MOV 	R3, M [ ShipBulletExists ]		; Verifica se o tiro ja esta na tela
				CMP 	R3, 0
				JMP.Z 	BulletNotExists

				MOV 	R3, M [ ShipBulletLine ]
				DEC 	R3
				CMP		R3, 1
				JMP.Z	BulletInLastRow
				
				MOV 	R2, R1
				SUB 	R2, 81

				; Inicio colisão
				MOV 	R3, M [ R2 ]
				CMP 	R3, ' '

				JMP.Z	EndColisionCheck
				CALL 	IncreasePoints
				MOV		R4, R1
				MOV		R1, R2
				CALL 	EraseEnemyHandler
				MOV		R1, R4
				JMP		BulletInLastRow

				EndColisionCheck:		MOV 	R3, M [ Bullet ]				; Coloca o tiro na linha seguinte
										MOV		M [ R2 ], R3

										CMP 	R1, 86A5h						; Se o valor de R1 for menor que o especifica significa que a posição anterior não corresponde a linha da nave
										JMP.N	ErasePreviousBullet
										JMP		EndMoveBulletUp

				BulletInLastRow:		MOV 	R4, 0
										MOV 	M [ ShipBulletExists ], R4

				ErasePreviousBullet:	MOV 	R3, ' '
										MOV		M [ R1 ], R3

										MOV		R1, M [ShipBulletLine]
										CALL 	PrintString

				EndMoveBulletUp: 		DEC 	M [ ShipBulletLine ]
										MOV		R1, M [ ShipBulletLine ]
										CALL 	PrintString
				
										MOV 	M [ ShipBulletPosition ], R2
				
				BulletNotExists:		POP	 	R4
										POP 	R3
										POP 	R2
										POP 	R1

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
					MOV R2, M [ ShipColumn ]

					MOV R3, 81

					MUL R3, R1
					ADD R1, R2
					ADD R1, 8000h

					MOV R3, 21
					MOV M [ ShipBulletLine ], R3

					MOV M [ ShipBulletPosition ], R1

					CALL MoveBulletUp

					EndStartShipBullet: POP R3
										POP R2
										POP R1

										RTI

;------------------------------------------------------------------------------
; Rotina Printar Inimigos
;------------------------------------------------------------------------------
PrintEnemyLine:		PUSH R1									; Contem a linha que sera printada
					PUSH R2									; Linha de inimigos na ram
					PUSH R3									; Posição da linha na RAM
					PUSH R4

					MOV R2, EnemyLine

					MOV R3, 81
					MOV R4, R1
					MUL R4, R3
					ADD R3, 8000h							; Guarda a posição da linha na RAM

					CopyEnemyMemmoryLoop:	MOV R4, M [R3]
					CMP R4, FIM_TEXTO
					JMP.Z EndCopyEnemyMemmory
					MOV R4, M [ R2 ]
					MOV M [ R3 ], R4

					INC R2
					INC R3
					JMP CopyEnemyMemmoryLoop

					EndCopyEnemyMemmory: CALL PrintString

					POP R4
					POP R3
					POP R2
					POP R1

					RET

;------------------------------------------------------------------------------
; Rotina Printar Linhas Vazias
;------------------------------------------------------------------------------
PrintEmptyLine:		PUSH R1									; Contem a linha que sera printada
					PUSH R2									; Linha de inimigos na ram
					PUSH R3									; Posição da linha na RAM
					PUSH R4

					MOV R2, EmptyLine

					MOV R3, 81
					MOV R4, R1
					MUL R4, R3
					ADD R3, 8000h							; Guarda a posição da linha na RAM

					CopyEmptyMemmoryLoop:	MOV R4, M [R3]
					CMP R4, FIM_TEXTO
					JMP.Z EndCopyEmptyMemmory
					MOV R4, M [ R2 ]
					MOV M [ R3 ], R4

					INC R2
					INC R3
					JMP CopyEmptyMemmoryLoop

					EndCopyEmptyMemmory: CALL PrintString

					POP R4
					POP R3
					POP R2
					POP R1

					RET

;------------------------------------------------------------------------------
; Rotina Diminuir Vida
;------------------------------------------------------------------------------
DecreaseLives:	PUSH R1
				PUSH R2

				DEC M [LivesCounter]
				MOV R1, M [ LivesCounter ]

				MOV R2, M [ ScreenLivesPosition ]
				MOV M [ CURSOR ], R2

				MOV M [IO_WRITE], R1

				POP R2
				POP R1

				RET

;------------------------------------------------------------------------------
; Rotina Resetar Pontos
;------------------------------------------------------------------------------
ResetPoints:	PUSH R1
				PUSH R2

				MOV R1, 0030h
				MOV M [ PointsCentena ], R1
				MOV M [ PointsDezena ], R1

				MOV R2, M [ ScreenCentenaPointsPosition ]
				MOV M [ CURSOR ], R2
				MOV M [IO_WRITE], R1
	
				MOV R2, M [ ScreenDezenaPointsPosition ]
				MOV M [ CURSOR ], R2
				MOV M [IO_WRITE], R1

				POP R2
				POP R1

				RET

;------------------------------------------------------------------------------
; Rotina Dano do inimigo
;------------------------------------------------------------------------------
EnemyDamageHandler:	PUSH R1
					PUSH R2
					PUSH R3
					PUSH R4

					MOV R1, 3								 ; Inicio das linhas de inimigos
					StartPrintEnemyLoop: CMP R1, 8
										JMP.Z StartCleanMapLoop

										CALL PrintEnemyLine

										INC R1
										JMP StartPrintEnemyLoop

					StartCleanMapLoop:	CMP R1, 21
										JMP.Z EndEnemyDamageHandler

										CALL PrintEmptyLine

										INC R1
										JMP StartCleanMapLoop

					EndEnemyDamageHandler:	CALL DecreaseLives
											CALL ResetPoints
											MOV R4, 8285h						; Reseta os valores
											MOV M [ EnemyLastLineStart ], R4
											MOV R4, 7d
											MOV M [ EnemyLowerLine ], R4

					POP R4
					POP R3
					POP R2
					POP R1

					RET

;------------------------------------------------------------------------------
; Rotina Move Enemy Down
;------------------------------------------------------------------------------
MoveEnemyDown:	PUSH R1			
				PUSH R2			
				PUSH R3
				PUSH R4
				PUSH R5

				MOV		R1, M [ EnemyLowerLine ]				; Posição da ram para o printstring
				INC 	R1
				MOV		R2, M [ EnemyLastLineStart ]			; Posição de fim na ram
				MOV		R3, M [ EnemyLastLineStart ]			; Mesma posição na proxíma linha
				ADD		R3, 42	
				MOV		R4, 0									; Contador de Linhas passadas

				DownLoopEnemyLine:		CMP 	R4, 5					; Verifica se já foi verificada todas as linhas de inimigos
										JMP.Z	DownEndMoveEnemy

				DownLoopEnemyColumn:	MOV 	R5,	'#'
										CMP		M [ R3 ], R5			; Verifica se a linha atual acabou
										JMP.Z	DownGotoNextLine

										MOV 	R5, M [ R2 ]
										MOV		M [ R3 ], R5
										MOV		R5, ' '
										MOV		M [ R2 ], R5

										DEC 	R2
										DEC 	R3
										JMP 	DownLoopEnemyColumn

				DownGotoNextLine:		CALL 	PrintString
										DEC 	R1						; Sobe a linha do print
										SUB 	R2, 42					; Passa para o final da linha acima na RAM
										SUB 	R3, 42					; Passa para o final da linha acima na RAM
										INC 	R4						; Aumenta o contador de linha
										JMP 	DownLoopEnemyLine

				DownEndMoveEnemy:		CALL 	PrintString
										INC 	M [ EnemyLowerLine ]
										MOV 	R5, 81
										ADD		M [ EnemyLastLineStart ], R5
				
				POP R5
				POP R4
				POP R3
				POP R2
				POP R1

				RET


;------------------------------------------------------------------------------
; Rotina Move Enemy
;------------------------------------------------------------------------------
MoveEnemy:		PUSH R1			
				PUSH R2			
				PUSH R3
				PUSH R4
				PUSH R5
				PUSH R6

				MOV		R1, M [ EnemyLowerLine ]				; Posição da ram para o printstring
				MOV		R2, M [ EnemyLastLineStart ]			; Posição de fim na ram
				MOV		R3, M [ EnemyLastLineStart ]			; Uma posição antes da ultima posição da ultima linha de inimigos
				DEC 	R3
				MOV		R4, 0									; Contador de Linhas passadas
				MOV		R6, 0									; Contador de espaços entre o inicio da linha e o primeiro caracter

				MOV		R5, R1
				INC 	R5
				CMP		R5, 21
				JMP.NZ	LoopEnemyLine
				CALL	EnemyDamageHandler
				JMP		EndMoveEnemy

				LoopEnemyLine:		CMP 	R4, 5					; Verifica se já foi verificada todas as linhas de inimigos
									JMP.Z	EndMoveEnemy

				LoopEnemyColumn:	MOV 	R5,	'#'
									CMP		M [ R3 ], R5			; Verifica se a linha atual acabou
									JMP.Z	GotoNextLine

									MOV		R5, '/'					; Verificação de colisão
									CMP		M [ R2 ], R5
									JMP.NZ	MoveCharacterRight
									CMP		R6, 0
									JMP.NZ	MoveCharacterRight
									CALL 	MoveEnemyDown
									JMP		EndMoveEnemy

									MOV		R5, '|'					; Não mova o tiro
									CMP		M [ R2 ], R5
									JMP.Z  EndBulletCheck
									CMP		M [ R3 ], R5
									JMP.Z  EndBulletCheck

				MoveCharacterRight:	MOV 	R5, M [ R3 ]
									MOV		M [ R2 ], R5
									MOV		R5, ' '
									MOV		M [ R3 ], R5

				EndBulletCheck:		DEC 	R2
									DEC 	R3
									INC 	R6
									JMP 	LoopEnemyColumn

				GotoNextLine:		CALL 	PrintString
									DEC 	R1						; Sobe a linha do print
									SUB 	R2, 4					; Passa para o final da linha acima na RAM
									SUB 	R3, 4					; Passa para o final da linha acima na RAM
									INC 	R4						; Aumenta o contador de linha
									MOV		R6, 0
									JMP 	LoopEnemyLine

				EndMoveEnemy:		POP R6
									POP R5
									POP R4
									POP R3
									POP R2
									POP R1

				RET

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

				MOV R2, M [ EnemyMoveCounter ]	
				CMP R2, 7
				JMP.NZ EndMove

				CALL MoveEnemy
				MOV R2, 0
				MOV M [ EnemyMoveCounter ], R2

				EndMove: INC M[ EnemyMoveCounter ]
				
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
		
		CALL 	PrintScreen
		CALL 	StartTimer

Cycle:	BR			Cycle
Halt:           BR		Halt