clc, clearvars;

% Ordem das variáveis no vetor x:
% x = [xA1, xA2, xA3, xA4, xZ1, xZ2, xZ3, xZ4, xS1, xS2, xS3, xS4]
% 1. Coeficientes (Receita - Custo)
f_max = [3, -2, 2, -5, 9, 4, 8, 1, 16, 11, 15, 8];
% Como o linprog do MATLAB minimiza, invertemos o sinal:
f = -f_max;

% Restrições (Ax <= b)
A = zeros(10, 12); % 10 Restrições e 12 variaveis
b = zeros(10, 1);

% Restrições de quantidade disponível (Petróleo 1, 2, 3 e 4)
% Tipo 1: xA1 + xZ1 + xS1 <= 3500 (Índices: 1, 5, 9)
A(1, [1, 5, 9]) = 1;
b(1) = 3500;
% Tipo 2: xA2 + xZ2 + xS2 <= 2200 (Índices: 2, 6, 10)
A(2, [2, 6, 10]) = 1;
b(2) = 2200;
% Tipo 3: xA3 + xZ3 + xS3 <= 4200 (Índices: 3, 7, 11)
A(3, [3, 7, 11]) = 1;
b(3) = 4200;
% Tipo 4: xA4 + xZ4 + xS4 <= 1800 (Índices: 4, 8, 12)
A(4, [4, 8, 12]) = 1;
b(4) = 1800;

% Restrições de proporção da mistura (Rearranjadas para <= 0)

% Gasolina Superazul (Variáveis S: índices 9 a 12)
% 1. 0.7xS1 - 0.3xS2 - 0.3xS3 - 0.3xS4 <= 0
A(5, 9:12) = [0.7, -0.3, -0.3, -0.3];
% 2. 0.4xS1 - 0.6xS2 + 0.4xS3 + 0.4xS4 <= 0 (invertida da eq. original >=)
A(6, 9:12) = [0.4, -0.6,  0.4,  0.4];
% 3. -0.5xS1 - 0.5xS2 + 0.5xS3 - 0.5xS4 <= 0
A(7, 9:12) = [-0.5, -0.5,  0.5, -0.5];

% Gasolina Azul (Variáveis Z: índices 5 a 8)
% 4. 0.7xZ1 - 0.3xZ2 - 0.3xZ3 - 0.3xZ4 <= 0
A(8, 5:8) = [0.7, -0.3, -0.3, -0.3];
% 5. -0.9xZ1 + 0.1xZ2 + 0.1xZ3 + 0.1xZ4 <= 0 (invertida da eq. original >=)
A(9, 5:8) = [0.1, -0.9, 0.1, 0.1];

% Gasolina Amarela (Variáveis A: índices 1 a 4)
% 6. 0.3xA1 - 0.7xA2 - 0.7xA3 - 0.7xA4 <= 0
A(10, 1:4) = [0.3, -0.7, -0.7, -0.7];

% Limites
lb = zeros(12, 1); % Todas as 12 variáveis devem ser >= 0
ub = [];           % Sem limite superior

[x, fval] = linprog(f, A, b, [], [], lb, ub);
lucro_maximo = -fval; % Inverte a minimização

fprintf('Lucro Máximo: R$ %.2f\n\n', lucro_maximo);
fprintf('Distribuição de Barris:\n');
fprintf('G. Amarela: P1=%.1f, P2=%.1f, P3=%.1f, P4=%.1f\n', x(1:4));
fprintf('G. Azul:    P1=%.1f, P2=%.1f, P3=%.1f, P4=%.1f\n', x(5:8));
fprintf('G. Super:   P1=%.1f, P2=%.1f, P3=%.1f, P4=%.1f\n', x(9:12));