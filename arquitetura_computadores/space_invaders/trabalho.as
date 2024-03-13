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
ROW_POSITION	EQU		0d
COL_POSITION	EQU		0d
ROW_SHIFT		EQU		8d
COLUMN_SHIFT	EQU		8d

;------------------------------------------------------------------------------
; ZONA II: definicao de variaveis
;          Pseudo-instrucoes : WORD - palavra (16 bits)
;                              STR  - sequencia de caracteres (cada ocupa 1 palavra: 16 bits).
;          Cada caracter ocupa 1 palavra
;------------------------------------------------------------------------------

                	ORIG    8000h
BorderLine      	STR    	'################################################################################', FIM_TEXTO
InformationLine		STR		'#  lives: 3                                                         points: 0  #', FIM_TEXTO
EnemySpaceShipLine	STR		'#                   \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/ \W/                    #', FIM_TEXTO
PlayerShipLine		STR		'#                                     /-\                                      #', FIM_TEXTO
GenericLine      	STR    	'#                                                                              #', FIM_TEXTO

ShipPosition	WORD	1627h	; Posição atual da nave
ShipLeftBorder	WORD	1601h 	; Borda esquerda da linha da nave
ShipRightBorder	WORD	164Fh	; Borda direita da linha da nave

RowIndex		WORD	0d
ColumnIndex		WORD	0d
TextIndex		WORD	0d


;------------------------------------------------------------------------------
; ZONA III: definicao de tabela de interrupções
;------------------------------------------------------------------------------
                ORIG    FE00h
INT0            WORD    MoveLeft
INT1            WORD    MoveRight

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

	CyclePrintString:	MOV	R2, M [ R1 ]	; Passa para R2 o caracter na posição de R1

						CMP 	R2, FIM_TEXTO		; Verefica se R2 e o fim do texto
						JMP.Z 	EndPrintString

						MOV		M[ IO_WRITE ], R2	; Escreve R2
						INC 	R1					; Anda a string uma posição para frente

						INC		M[ ColumnIndex ]		; Anda uma linha para frente
						MOV		R2, M[ RowIndex ]		; R2 = Linha atual
						MOV		R3, M[ ColumnIndex ]; 	; R3 = Coluna atual
						SHL		R2, ROW_SHIFT			; R2 = Linha atual movida para os bites da esquerda
						OR		R2, R3					; Concatena R2 e R3
						MOV		M[ CURSOR ], R2			; Move o cursor para a posição de R2

						JMP CyclePrintString

	EndPrintString:	INC M[ RowIndex ]
					MOV R1, COL_POSITION
					MOV M[ ColumnIndex ], R1
					MOV R2, M[ RowIndex ]
					SHL	R2, ROW_SHIFT			; R2 = Linha atual movida para os bites da esquerda
					OR	R2, R1					; Concatena R2 e R3
					MOV	M[ CURSOR ], R2			; Move o cursor para a posição de R2

					POP R3
					POP R2
					POP R1

					RET

;------------------------------------------------------------------------------
; Rotina PrintScreen
;------------------------------------------------------------------------------
PrintScreen:	PUSH R1
				PUSH R2

				MOV R1, BorderLine
				CALL PringString

				MOV R1, InformationLine
				CALL PringString

				MOV R2, 0
				CyclePrintEnemy: 	CMP R2, 5
									JMP.Z CycleEndPrintEnemy
									INC R2
									MOV R1, EnemySpaceShipLine
									CALL PringString
									JMP CyclePrintEnemy
				
				CycleEndPrintEnemy:	MOV R2, 0
					
				CyclePrintScreen: 	CMP R2, 15
									JMP.Z CycleEndPrintScreen
									INC R2
									MOV R1, GenericLine
									CALL PringString
									JMP CyclePrintScreen
				
				CycleEndPrintScreen:	MOV R1, PlayerShipLine
										CALL PringString
										MOV R1, BorderLine
										CALL PringString

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
			INC R1
			MOV M [ CURSOR ], R1

			MOV M [ ShipPosition ], R1		; Posição do meio da nave

			MOV R2, '-'
			MOV M [ IO_WRITE ], R2
			INC R1
			MOV M [ CURSOR ], R1

			MOV R2, '\'
			MOV M [ IO_WRITE ], R2

			POP R2
			POP R1

			RET

;------------------------------------------------------------------------------
; Interrupção Move left
;------------------------------------------------------------------------------
MoveLeft:	PUSH R1
			PUSH R2

			MOV R1, M [ ShipPosition ]

			MOV R2, R1
			DEC R2			
			CMP R2, M [ ShipLeftBorder ]		; Verifica se a ponta esquerda da nave esta na borda do mapa
			JMP.Z EndMoveLeft

			SUB R1, 2							; Posiciona o cursor para escrever a nave então deletar o ultimo caracter
			MOV M [ CURSOR ], R1

			CALL PrintShip

			ADD R1, 3
			MOV M [ CURSOR ], R1
			MOV R2, ' '
			MOV M [ IO_WRITE ], R2

			EndMoveLeft:	POP R2	
							POP R1

							RTI

;------------------------------------------------------------------------------
; Interrupção Move right
;------------------------------------------------------------------------------
MoveRight:	PUSH R1
			PUSH R2

			MOV R1, M [ ShipPosition ]

			MOV R2, R1
			ADD R2, 2			
			CMP R2, M [ ShipRightBorder ]		; Verifica se a ponta direita da nave esta na borda do mapa
			JMP.Z EndMoveRight

			SUB R1, 1
			MOV M [ CURSOR ], R1

			MOV R2, ' '
			MOV M [ IO_WRITE ], R2
			INC R1
			MOV M [ CURSOR ], R1

			CALL PrintShip

			EndMoveRight:	POP R2
							POP R1

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




Cycle: 			BR		Cycle	
Halt:           BR		Halt