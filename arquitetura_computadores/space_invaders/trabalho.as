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

RAM_POSITION		EQU		8000h
LINE_MEMORY			EQU		81d
LOWEST_ENEMY_LINE 	EQU 21d

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
Line08      	STR    	'#                                                                             |#', FIM_TEXTO
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

GameEnded				WORD	0d

YouWin					STR		'YOU WIN', FIM_TEXTO
GameOver				STR		'GAME OVER', FIM_TEXTO

ScreenCentenaPointsPosition		WORD	014Bh		; Posição do ultimo caracter da pontuação na tela
ScreenDezenaPointsPosition		WORD	014Ch		; Posição do ultimo caracter da pontuação na tela
PointsDezena					WORD	0030h		; Numero decimal de pontos
PointsCentena					WORD	0030h		; Numero das centenas de pontos

ScreenLivesPosition				WORD	010Bh		; Posição dos vidas na tela
LivesCounter					WORD	0033h		; Contador de vidas
LivesAmount						WORD	3d			; Qnt de vidas do jogador

ShipLine						WORD	21d			; Linha da nave
ShipColumn						WORD	39d			; Coluna atual da nave

ShipBulletExists				WORD	0h			; Guarda a informação se o tiro está ou não na tela
ShipBulletLine					WORD	0h			; Linha do tiro da nave
ShipBulletPosition				WORD	0h			; Posição do tiro da nave

MapColumnLeftBorder				WORD	1d 			; Borda esquerda da linha da nave
MapColumnRightBorder			WORD	80d			; Borda direita da linha da nave

EnemyUpperLine					WORD	2h			; Número da linha acima da ultima linha de inimigos
EnemyLowerLine					WORD	7d			; Número da linha da ultima fileira de inimigos

EnemyDirectionFlag				WORD	0d			; Sé for 0 para direita se for 1 para a esquerda, alterado por um XOR com 1
EnemyDefeated					WORD	0d			; Qnt inimigos derrotados

EnemyMoveCounter				WORD	0000h		; Timer para mover o inimigo

DamageDealt						WORD	0d			; Marca se o dado foi causado no jogador ou não

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
	
	MOV R2, LINE_MEMORY												; Posiciona o R1 no inicio da linha recebida
	MUL R2, R1
	ADD R1, RAM_POSITION

	CyclePrintString:	MOV	R2, M [ R1 ]					; Passa para R2 o carácter na posição de R1

						CMP 	R2, FIM_TEXTO				; Verifica se R2 e o fim do texto
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
									JMP.Z	EndPrintScreen

									CALL PrintString

									INC R1
				
									JMP PrintScreenCycle

				EndPrintScreen:	POP R1

								RET

;------------------------------------------------------------------------------
; Rotina Print character on memory
;------------------------------------------------------------------------------
AlterMemory:	PUSH R1		; Posição do cursor
				PUSH R2		; Carácter
				PUSH R3
				PUSH R4

				MOV R3, R1

				AND R1, FFh				; Coluna
				AND R3, FF00h			; Linha
				SHR R3, ROW_SHIFT

				MOV R4, LINE_MEMORY
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

			SUB R1, 2								; Posiciona o cursor para escrever a nave então deletar o ultimo carácter
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
EraseEnemyHandler:	PUSH R1				; Parâmetro: Posição na RAM
					PUSH R2				

					MOV		R2, M [ R1 ]	; Carácter da posição
		
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
					CMP R1, ':'									; Valor da tabela ASCII que fica depois do 9

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

					INC M [ EnemyDefeated ]

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
				PUSH 	R5

				MOV	R5, M [ ShipBulletExists ]		; Verifica se o tiro ja esta na tela
				CMP	R5, 0
				JMP.Z EndMoveBulletUp

				MOV	R1, M [ ShipBulletLine ]
				MOV	R2, M [ ShipBulletPosition ]

				MOV R4, R2
				SUB R4, LINE_MEMORY							; Posição do tiro na linha acima da RAM

				CMP R1, 3								; Verifica colisão do tiro com O teto
				JMP.NZ EndCellingCollision
				MOV R5, 0
				MOV M [ ShipBulletExists ], R5
				JMP EraseBullet

				EndCellingCollision: 	CMP R1, LOWEST_ENEMY_LINE
										JMP.Z EndEnemyInsideBulletCollision
										MOV R5, M [ R2 ]						; Verifica se o inimigo se moveu para o tiro
										CMP R5, '|'
										JMP.Z EndEnemyInsideBulletCollision

										CALL IncreasePoints
										MOV R5, R1
										MOV R1, R2
										CALL EraseEnemyHandler
										MOV R1, R5

										MOV R5, 0
										MOV M [ ShipBulletExists ], R5
										JMP EraseBullet
				

				EndEnemyInsideBulletCollision:	MOV R5, M [ R4 ]
												CMP R5, ' '                       		; Verifica colisão do tiro com inimigo
												JMP.Z EndEnemyMoveCondition

												CALL IncreasePoints
												MOV R5, R1
												MOV R1, R4
												CALL EraseEnemyHandler
												MOV R1, R5

												MOV R5, 0
												MOV M [ ShipBulletExists ], R5
												JMP EraseBullet
				
				EndEnemyMoveCondition:	MOV R5, '|'			; Escreve o tiro na linha de cima
										MOV M [ R4 ], R5		

				EraseBullet:	DEC R1
								CALL PrintString
								INC R1
								CMP R1, LOWEST_ENEMY_LINE
								JMP.Z EndEraseBullet
								
								MOV R5, M [ R2 ]
								CMP R5, '^'
								JMP.Z EndEraseBullet
								CMP R5, '/'
								JMP.Z EndEraseBullet
								CMP R5, '\'
								JMP.Z EndEraseBullet

								MOV R5, ' '
								MOV M [ R2 ], R5
								CALL PrintString

				EndEraseBullet:	DEC M [ ShipBulletLine ]
								MOV M [ ShipBulletPosition ], R4
				
				EndMoveBulletUp:	POP	R5	
									POP	R4
									POP	R3
									POP	R2
									POP	R1

				RET

;------------------------------------------------------------------------------
; Interrupção StartShipBullet
;------------------------------------------------------------------------------
StartShipBullet:	PUSH R1
					PUSH R2
					PUSH R3

					MOV R1, M [ GameEnded ]				; Verifica se o jogo ja acabou
					CMP R1, 1
					JMP.Z EndStartShipBullet

					MOV R1, M [ ShipBulletExists ]			; Verifica se o tiro ja esta na tela
					CMP R1, 1
					JMP.Z EndStartShipBullet

					MOV R1, 1
					MOV M [ ShipBulletExists ], R1

					MOV R1, M [ ShipLine ]
					MOV R2, M [ ShipColumn ]

					MOV R3, LINE_MEMORY

					MUL R3, R1
					ADD R1, R2
					ADD R1, RAM_POSITION

					MOV R3, LOWEST_ENEMY_LINE
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

					MOV R3, LINE_MEMORY
					MOV R4, R1
					MUL R4, R3
					ADD R3, RAM_POSITION							; Guarda a posição da linha na RAM

					CopyEnemyMemoryLoop:	MOV R4, M [R3]
					CMP R4, FIM_TEXTO
					JMP.Z EndCopyEnemyMemory
					MOV R4, M [ R2 ]
					MOV M [ R3 ], R4

					INC R2
					INC R3
					JMP CopyEnemyMemoryLoop

					EndCopyEnemyMemory: CALL PrintString

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

					MOV R3, LINE_MEMORY
					MOV R4, R1
					MUL R4, R3
					ADD R3, RAM_POSITION							; Guarda a posição da linha na RAM

					CopyEmptyMemoryLoop:	MOV R4, M [R3]
					CMP R4, FIM_TEXTO
					JMP.Z EndCopyEmptyMemory
					MOV R4, M [ R2 ]
					MOV M [ R3 ], R4

					INC R2
					INC R3
					JMP CopyEmptyMemoryLoop

					EndCopyEmptyMemory: CALL PrintString

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

				DEC M [ LivesAmount ]

				POP R2
				POP R1

				RET

;------------------------------------------------------------------------------
; Rotina Zerar Pontos
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

				MOV R1, 0
				MOV M [ EnemyDefeated ], R1

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

					MOV R1, 3								 				;	 Inicio das linhas de inimigos
					StartPrintEnemyLoop: CMP R1, 8
										JMP.Z StartCleanMapLoop

										CALL PrintEnemyLine

										INC R1
										JMP StartPrintEnemyLoop

					StartCleanMapLoop:	CMP R1, LOWEST_ENEMY_LINE
										JMP.Z EndEnemyDamageHandler

										CALL PrintEmptyLine

										INC R1
										JMP StartCleanMapLoop

					EndEnemyDamageHandler:	CALL DecreaseLives
											CALL ResetPoints

											MOV R4, 0
											MOV M [ EnemyDirectionFlag ], R4
											MOV R4, 2
											MOV M [ EnemyUpperLine ], R4
											MOV R4, 7
											MOV M [ EnemyLowerLine], R4

					POP R4
					POP R3
					POP R2
					POP R1

					RET

;------------------------------------------------------------------------------
; Rotina Mover Inimigo Direita
;------------------------------------------------------------------------------
MoveEnemyRight:	PUSH R1							
				PUSH R2
				PUSH R3
				PUSH R4
				PUSH R5

				MOV R3, M [ EnemyLowerLine ]
				MOV R2, LINE_MEMORY
				MUL R2, R3
				ADD R3, 78													; Final da ultima linha de inimigos
				ADD R3, RAM_POSITION												; Inicio da RAM

				MOV R2, R3			
				DEC R2														; Posição anterior ao R3

				MOV R1, M [ EnemyLowerLine ]

				MOV R4, ' '													; Verifica se o inimigo está na parede
				CMP M [ R3 ], R4
				JMP.Z LoopMoveEnemyRight									; Se a posição ao lado da parede estiver vazia continue
				CALL MoveEnemyDown
				JMP EndMoveEnemyRight

				LoopMoveEnemyRight:		MOV R4, M [ EnemyUpperLine ]
										CMP R1, R4						; Verifica se já acabou as linhas de inimigos
										JMP.Z EndMoveEnemyRight

				LoopMoveEnemyRightLine:	MOV R4, '#'
										CMP M[R2], R4
										JMP.NZ MoveEnemyRightStart
										CALL PrintString
										DEC R1							; Sobe uma linha
										SUB R2, 4						; Sobe para cima na RAM
										SUB R3, 4						; Sobe para cima na RAM

										MOV R4, ' '						; Verifica se o inimigo está na parede sempre que inicia uma nova linha
										CMP M [ R3 ], R4
										JMP.Z LoopMoveEnemyRight		; Se a posição ao lado da parede estiver vazia continue
										CALL MoveEnemyDown
										JMP EndMoveEnemyRight

				MoveEnemyRightStart:	MOV R4, M [ R2 ]
										CMP R4, '|'
										JMP.Z DoNotMoveBulletRight				; Se a posição atual for o tiro passe para proxima posição

										MOV R5, M [ R3 ]
										CMP R5, '|'
										JMP.NZ ContinueMoveRight					; Sé a proxima posição não for o tiro prossiga

										CMP R4, '/'								; Sé a posição anterior for a ponta de uma nave mova para cima do tiro
										JMP.NZ DoNotMoveBulletRight
										
										ContinueMoveRight: 	MOV M [ R3 ], R4
															MOV R4, ' '
															MOV M[ R2 ], R4
										
				DoNotMoveBulletRight:	DEC R2
										DEC R3
										JMP LoopMoveEnemyRightLine


				EndMoveEnemyRight:		POP R5
										POP R4	
										POP R3
										POP R2
										POP R1

				RET

;------------------------------------------------------------------------------
; Rotina Mover Inimigo Esquerda
;------------------------------------------------------------------------------
MoveEnemyLeft:	PUSH R1							
				PUSH R2
				PUSH R3
				PUSH R4
				PUSH R5

				MOV R3, M [ EnemyLowerLine ]
				MOV R2, LINE_MEMORY
				MUL R2, R3
				ADD R3, RAM_POSITION												; Inicio da RAM
				INC R3

				MOV R2, R3			
				INC R2														; Posição posterior ao R3

				MOV R1, M [ EnemyLowerLine ]

				MOV R4, ' '													; Verifica se o inimigo está na parede
				CMP M [ R3 ], R4
				JMP.Z LoopMoveEnemyLeft									; Se a posição ao lado da parede estiver vazia continue
				CALL MoveEnemyDown
				JMP EndMoveEnemyLeft

				LoopMoveEnemyLeft:		MOV R4, M [ EnemyUpperLine ]
										CMP R1, R4						; Verifica se já acabou as linhas de inimigos
										JMP.Z EndMoveEnemyLeft

				LoopMoveEnemyLeftLine:	MOV R4, '#'
										CMP M[R2], R4
										JMP.NZ MoveEnemyLeftStart
										CALL PrintString
										DEC R1							; Sobe uma linha
										SUB R2, 158						; Sobe para cima na RAM
										SUB R3, 158						; Sobe para cima na RAM

										MOV R4, ' '						; Verifica se o inimigo está na parede sempre que inicia uma nova linha
										CMP M [ R3 ], R4
										JMP.Z LoopMoveEnemyLeft			; Se a posição ao lado da parede estiver vazia continue
										CALL MoveEnemyDown
										JMP EndMoveEnemyLeft

				MoveEnemyLeftStart:	 	MOV R4, M [ R2 ]
										CMP R4, '|'
										JMP.Z DoNotMoveBulletLeft				; Se a posição atual for o tiro passe para proxima posição

										MOV R5, M [ R3 ]
										CMP R5, '|'
										JMP.NZ ContinueMoveLeft					; Sé a proxima posição não for o tiro prossiga

										CMP R4, '\'								; Sé a posição anterior for a ponta de uma nave mova para cima do tiro
										JMP.NZ DoNotMoveBulletLeft

										ContinueMoveLeft:	MOV M [ R3 ], R4
															MOV R4, ' '
															MOV M[ R2 ], R4
										
				DoNotMoveBulletLeft:	INC R2
										INC R3
										JMP LoopMoveEnemyLeftLine


				EndMoveEnemyLeft:		POP R5
										POP R4	
										POP R3
										POP R2
										POP R1

				RET

;------------------------------------------------------------------------------
; Rotina CheckEnemyDamage
;------------------------------------------------------------------------------
CheckEnemyDamage:	PUSH R1														; Contador de caracteres não vazios encontrados na linha, indicando que existem inimigos
					PUSH R2														; Aux
					PUSH R3														; Parâmetro: Linha que sera verificada no caso inicio da linha 20

					MOV R1, 0

					LoopEnemyDamageCheck:	MOV R2, M [ R3 ]
											CMP R2, '#'							; A linha inteira foi analisada
											JMP.Z EndEnemyDamageCheckLoop

											CMP R2, ' '
											JMP.Z EndEnemyDamageCheck
											INC R1

											EndEnemyDamageCheck:	INC R3
																	JMP LoopEnemyDamageCheck

					EndEnemyDamageCheckLoop:	CMP R1, 0
												JMP.Z SkipDamage
												CALL EnemyDamageHandler			; Se foram encontrados inimigos na linha de o dano
												MOV R2, 1
												MOV M [ DamageDealt ], R1		; Indica que o dano foi dado
												JMP EndDamageCheck

					SkipDamage: DEC M [ EnemyLowerLine ] 
					
					EndDamageCheck:	POP R3
									POP R2
									POP R1

					RET

;------------------------------------------------------------------------------
; Rotina Mover inimigo Baixo
;------------------------------------------------------------------------------
MoveEnemyDown:	PUSH R1	
				PUSH R2						
				PUSH R3
				PUSH R4
				PUSH R5
				PUSH R6

				MOV R3, M [ EnemyLowerLine ]
				MOV R2, LINE_MEMORY
				MUL R2, R3
				ADD R3, RAM_POSITION													; Inicio da RAM
				INC R3

				MOV R2, R3			
				ADD R2, LINE_MEMORY													; Posição posterior na linha de baixo do R3

				MOV R1, M [ EnemyLowerLine ]
				MOV R5, R1
				INC R1																	; Posição da linha para o print

				CMP R1, LOWEST_ENEMY_LINE
				JMP.NZ LoopMoveEnemyDown
				CALL CheckEnemyDamage
				MOV R4, M [ DamageDealt ]
				CMP R4, 1
				JMP.NZ EndMoveEnemyDownNoAction

				JMP EndMoveEnemyDownNoAction

				LoopMoveEnemyDown:		MOV R4, M [ EnemyUpperLine ]
										CMP R5, R4						; Verifica se já acabou as linhas de inimigos
										JMP.Z EndMoveEnemyDown

				LoopMoveEnemyDownLine:	MOV R4, '#'
										CMP M[R2], R4
										JMP.NZ MoveEnemyDownStart
										CALL PrintString
										DEC R1							; Sobe uma linha
										DEC R5
										SUB R2, 159						; Sobe para cima na RAM
										SUB R3, 159						; Sobe para cima na RAM
										JMP LoopMoveEnemyDown

				MoveEnemyDownStart:	 	MOV R4, M [ R3 ]
										CMP R4, '|'								; Verifica para não mover o tiro para baixo
										JMP.Z	DoNotMoveBulletDown

										MOV R6, M [ R2 ]
										CMP R6, '|'
										JMP.NZ ContinueMoveDown					; Sé a proxima posição não for o tiro prossiga
										
										; Se a proxima posição for um tiro e a posição atual for vazia não mova o vazio para o tiro, não quebra o programa o tiro so pisca quando ocorre
										CMP R4, '\'								; Sé a posição anterior for a ponta de uma nave mova para cima do tiro
										JMP.Z ContinueMoveDown
										CMP R4, 'W'								; Sé a posição anterior for o meio de uma nave mova para cima do tiro
										JMP.Z ContinueMoveDown
										CMP R4, '/'								; Sé a posição anterior for a ponta de uma nave mova para cima do tiro
										JMP.Z ContinueMoveDown
										
										JMP DoNotMoveBulletDown					; Se a posição na linha de cima do tiro não for uma nave não mova o espaço vazio para o tiro

										ContinueMoveDown: 	MOV M [ R2 ], R4
															MOV R4, ' '
															MOV M[ R3 ], R4
										
										DoNotMoveBulletDown:	INC R2
																INC R3
																JMP LoopMoveEnemyDownLine

				EndMoveEnemyDown:		CALL PrintString
										INC M [ EnemyUpperLine ]
										INC M [ EnemyLowerLine ]
										
										MOV R4, 1
										XOR M [ EnemyDirectionFlag ], R4

				EndMoveEnemyDownNoAction:	MOV R4, 0
											MOV M [ DamageDealt ], R4
											
				POP R6
				POP R5
				POP R4	
				POP R3
				POP R2
				POP R1

				RET

;------------------------------------------------------------------------------
; Rotina ClearScreen
;------------------------------------------------------------------------------
ClearScreen:	PUSH R1

				MOV R1, 3								 				; Inicio das linhas de inimigos
				StartCleanScreenLoop:	CMP R1, LOWEST_ENEMY_LINE						; Limpa a tela
										JMP.Z EndClearScreen

										CALL PrintEmptyLine

										INC R1
										JMP StartCleanScreenLoop

				EndClearScreen:			POP R1
										RET

;------------------------------------------------------------------------------
; Rotina GameLoss
;------------------------------------------------------------------------------
GameLoss:		PUSH R1
				PUSH R2
				PUSH R3
				PUSH R4

				CALL ClearScreen

				MOV R1, 1												; Desativa o timer
				MOV	M [ TIMER_CONTROL ],  R1

				MOV R1, 197d											; 2 linhas para baixo e centraliza
				MOV R3, RAM_POSITION
				ADD R3, R1
				
				MOV R1, GameOver
				MOV R2, FIM_TEXTO

				StarMoveGameOver: 	CMP M[ R1 ], R2
								 	JMP.Z EndMoveGameOver

									MOV R4, M [R1]
									MOV M [ R3 ], R4
									INC R1
									INC R3
									JMP StarMoveGameOver

				EndMoveGameOver:	MOV R1, 2
									CALL PrintString

				MOV R1, 1
				MOV M [ GameEnded ], R1

				POP R4
				POP R3
				POP R2
				POP R1
				RET

;------------------------------------------------------------------------------
; Rotina Game Won
;------------------------------------------------------------------------------
GameWon:		PUSH R1
				PUSH R2
				PUSH R3
				PUSH R4

				CALL ClearScreen

				MOV R1, 1												; Desativa o timer
				MOV	M [ TIMER_CONTROL ],  R1

				MOV R1, 197d											; 2 linhas para baixo e centraliza
				MOV R3, RAM_POSITION
				ADD R3, R1
				
				MOV R1, YouWin
				MOV R2, FIM_TEXTO

				StarMoveGameWon: 	CMP M[ R1 ], R2
								 	JMP.Z EndMoveGameWon

									MOV R4, M [R1]
									MOV M [ R3 ], R4
									INC R1
									INC R3
									JMP StarMoveGameWon

				EndMoveGameWon:		MOV R1, 2
									CALL PrintString

				MOV R1, 1
				MOV M [ GameEnded ], R1

				POP R4
				POP R3
				POP R2
				POP R1
				RET

;------------------------------------------------------------------------------
; Rotina Start Timer
;------------------------------------------------------------------------------
StartTimer:		PUSH R1

				MOV			R1, 1					 ; Reinicia o timer
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

				MOV R1, M [ LivesAmount ]				; Se acabaram as vidas
				CMP R1, 0
				CALL.Z GameLoss
				CMP R1, 0
				JMP.Z EndTimer

				MOV R1, M [ EnemyDefeated ]				; Se todos os inimigos foram derrotados
				CMP R1, 50
				CALL.Z GameWon
				CMP R1, 50
				JMP.Z EndTimer

				MOV R2, M [ EnemyMoveCounter ]	
				CMP R2, 2
				JMP.NZ EndMove

				MOV R2, M [ EnemyDirectionFlag ]
				CMP R2, 0
				JMP.Z MoveRightFlagActivation
				CALL MoveEnemyLeft
				JMP	EndMovement
				MoveRightFlagActivation: CALL MoveEnemyRight

				EndMovement: MOV R2, 0
				MOV M [ EnemyMoveCounter ], R2

				EndMove: INC M[ EnemyMoveCounter ]

				CALL MoveBulletUp
				
				CALL StartTimer

				EndTimer:	POP R2
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

Cycle:			BR			Cycle
Halt:           BR		Halt