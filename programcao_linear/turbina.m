clc, clearvars;
% 1. FUNÇÃO OBJETIVO (f)
% Como queremos MAXIMIZAR o lucro, passamos os coeficientes multiplicados por -1.
% Lucro = 145*x1 + 164*x2 + 228*x3 - Custos de Materiais
% Ordem: [x1..3, EA..ED, PA..PD, RA..RD, yA..yD]
f = [-145, -164, -228, 18, 20, 17, 19, 1, 1.5, 2, 1.7, 1, 0.8, 1.7, 1.6, 0, 0, 0, 0];

% 2. RESTRIÇÕES DE DESIGUALDADE (A * x <= b)
% Vamos construir a matriz A e o vetor b linha por linha para facilitar a leitura.
A = zeros(21, 19);
b = zeros(21, 1);

% --- Balanceamento de Insumos (Demanda - Compras <= 0) ---
% Ejetores: 1x1 + 1x2 + 2x3 - EA - EB - EC - ED <= 0
A(1,:) = [1 1 2  -1 -1 -1 -1  0 0 0 0  0 0 0 0  0 0 0 0]; 
% Pás: 6x1 + 8x2 + 10x3 - PA - PB - PC - PD <= 0
A(2,:) = [6 8 10  0 0 0 0  -1 -1 -1 -1  0 0 0 0  0 0 0 0];
% Rolamentos: 40x1 + 60x2 + 85x3 - RA - RB - RC - RD <= 0
A(3,:) = [40 60 85  0 0 0 0  0 0 0 0  -1 -1 -1 -1  0 0 0 0];

% --- Restrição de Mão de Obra ---
% 500x1 + 600x2 + 1200x3 <= 1800
A(4, 1:3) = [500 600 1200];
b(4) = 1800;

% --- Restrição de Capital de Giro ---
% Custo de Compras <= 1300
A(5, 4:15) = [18 20 17 19  1 1.5 2 1.7  1 0.8 1.7 1.6];
b(5) = 1300;

% --- Capacidade Máxima dos Fornecedores (12 restrições) ---
% Fornecedor A (E_A - 6y_A <= 0, etc.)
A(6, [4, 16]) = [1, -6];    % E_A <= 6y_A
A(7, [8, 16]) = [1, -40];   % P_A <= 40y_A
A(8, [12, 16]) = [1, -280]; % R_A <= 280y_A

% Fornecedor B
A(9, [5, 17]) = [1, -4];    % E_B <= 4y_B
A(10, [9, 17]) = [1, -60];  % P_B <= 60y_B
A(11, [13, 17]) = [1, -150];% R_B <= 150y_B

% Fornecedor C
A(12, [6, 18]) = [1, -6];   % E_C <= 6y_C
A(13, [10, 18]) = [1, -100];% P_C <= 100y_C
A(14, [14, 18]) = [1, -120];% R_C <= 120y_C

% Fornecedor D
A(15, [7, 19]) = [1, -10];  % E_D <= 10y_D
A(16, [11, 19]) = [1, -150];% P_D <= 150y_D
A(17, [15, 19]) = [1, -170];% R_D <= 170y_D

% --- Condição Mínima de Compra (Se y=1, custo >= 400) ---
% Reorganizado como: 400y_A - CustoA <= 0
% A
A(18, [4, 8, 12, 16]) = [-18, -1, -1, 400];
% B
A(19, [5, 9, 13, 17]) = [-20, -1.5, -0.8, 400];
% C
A(20, [6, 10, 14, 18]) = [-17, -2, -1.7, 400];
% D
A(21, [7, 11, 15, 19]) = [-19, -1.7, -1.6, 400];

% 3. LIMITES DAS VARIÁVEIS (Bounds)
% Todas as 19 variáveis devem ser maiores ou iguais a zero
lb = zeros(19, 1);
% As primeiras 15 não têm limite superior prático (além do estabelecido pelas restrições)
% As últimas 4 são binárias, então o limite superior é 1
ub = [inf(15, 1); ones(4, 1)];

% 4. TIPO DAS VARIÁVEIS
% Todas as 19 variáveis devem ser números inteiros (não se produz meia peça)
intcon = 1:19;

% 5. RESOLVER O PROBLEMA COM intlinprog
options = optimoptions('intlinprog', 'Display', 'iter'); % Mostra o progresso no console
[x, fval, exitflag, output] = intlinprog(f, intcon, A, b, [], [], lb, ub, options);

% 6. EXIBIR OS RESULTADOS
if exitflag > 0
    fprintf('\n--- SOLUÇÃO ÓTIMA ENCONTRADA ---\n');
    fprintf('Lucro Máximo = %.2f U.M.\n\n', -fval); % Invertemos o sinal de volta
    
    fprintf('PRODUÇÃO:\n');
    fprintf('Turbina I:   %d\n', round(x(1)));
    fprintf('Turbina II:  %d\n', round(x(2)));
    fprintf('Turbina III: %d\n\n', round(x(3)));
    
    fprintf('COMPRAS E SELEÇÃO DE FORNECEDORES:\n');
    fornos = {'A', 'B', 'C', 'D'};
    for i = 1:4
        idx_E = i + 3;  % Índices 4 a 7
        idx_P = i + 7;  % Índices 8 a 11
        idx_R = i + 11; % Índices 12 a 15
        idx_Y = i + 15; % Índices 16 a 19
        
        if round(x(idx_Y)) == 1
            fprintf('Fornecedor %s: ATIVADO\n', fornos{i});
            fprintf('  - Ejetores:   %d\n', round(x(idx_E)));
            fprintf('  - Pás:        %d\n', round(x(idx_P)));
            fprintf('  - Rolamentos: %d\n', round(x(idx_R)));
        else
            fprintf('Fornecedor %s: INATIVO\n', fornos{i});
        end
    end
else
    disp('O solver não conseguiu encontrar uma solução ótima.');
end