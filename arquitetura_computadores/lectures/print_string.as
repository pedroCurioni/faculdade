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
Text			STR     'Arquitetura de Computadores', FIM_TEXTO
RowIndex		WORD	0d
ColumnIndex		WORD	0d
TextIndex		WORD	0d


;------------------------------------------------------------------------------
; ZONA II: definicao de tabela de interrupções
;------------------------------------------------------------------------------
                ORIG    FE00h
INT0            WORD    WriteCharacter

;------------------------------------------------------------------------------
; ZONA IV: codigo
;        conjunto de instrucoes Assembly, ordenadas de forma a realizar
;        as funcoes pretendidas
;------------------------------------------------------------------------------
                ORIG    0000h
                JMP     Main

;------------------------------------------------------------------------------
; Rotina de Interrupção WriteCharacter
;------------------------------------------------------------------------------
WriteCharacter: PUSH	R1
				PUSH	R2

				MOV		R1, M[ TextIndex ]
				MOV		R1, M[ R1 ]
				CMP 	R1, FIM_TEXTO
				JMP.Z	Halt
				MOV     M[ IO_WRITE ], R1
				INC		M[ RowIndex ]
				INC		M[ ColumnIndex ]
				INC		M[ TextIndex ]
				MOV		R1, M[ RowIndex ]
				MOV		R2, M[ ColumnIndex ]
				SHL		R1, ROW_SHIFT
				OR		R1, R2
				MOV		M[ CURSOR ], R1

				POP		R2
				POP		R1
				RTI

;------------------------------------------------------------------------------
; Função Main
;------------------------------------------------------------------------------
Main:			ENI

				MOV		R1, INITIAL_SP
				MOV		SP, R1		 		; We need to initialize the stack
				MOV		R1, CURSOR_INIT		; We need to initialize the cursor 
				MOV		M[ CURSOR ], R1		; with value CURSOR_INIT

				MOV 	R1, Text 			; Passa para R1 a memoria do inicio de text
				PrintString:	MOV	R2, M [ R1 ]	; Passa para R2 o caracter na posição de R1

				CMP 	R2, FIM_TEXTO		; Verefica se R2 e o fim do texto
				JMP.Z Halt

				MOV		M[ IO_WRITE ], R2	; Escreve R2
				INC 	R1					; Anda a string uma posição para frente

				INC		M[ ColumnIndex ]		; Anda uma linha para frente
				MOV		R2, M[ RowIndex ]		; R2 = Linha atual
				MOV		R3, M[ ColumnIndex ]; 	; R3 = Coluna atual
				SHL		R2, ROW_SHIFT			; R2 = Linha atual movida para os bites da esquerda
				OR		R2, R3					; Concatena R2 e R3
				MOV		M[ CURSOR ], R2			; Move o cursor para a posição de R2

				JMP PrintString


Cycle: 			BR		Cycle	
Halt:           BR		Halt