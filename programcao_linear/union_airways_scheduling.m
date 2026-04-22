clc, clearvars;
% 1. Função objetivo (Custo a minimizar)
% f(x1,x2,x3,x4,x5) = 170x1 + 160x2 + 175x3 + 180x4 + 195x5
f = [170; 160; 175; 180; 195];

% 2. Matriz de restrições (A * x <= b)
% Como as restrições originais são >=, multiplicamos os coeficientes por -1
A = [
    -1,  0,  0,  0,  0; % x1 >= 48
    -1, -1,  0,  0,  0; % x1 + x2 >= 79
    -1, -1,  0,  0,  0; % x1 + x2 >= 65 (redundante, mas mantida)
    -1, -1, -1,  0,  0; % x1 + x2 + x3 >= 87
     0, -1, -1,  0,  0; % x2 + x3 >= 64
     0,  0, -1, -1,  0; % x3 + x4 >= 73 (redundante, mas mantida)
     0,  0, -1, -1,  0; % x3 + x4 >= 82
     0,  0,  0, -1,  0; % x4 >= 43
     0,  0,  0, -1, -1; % x4 + x5 >= 52
     0,  0,  0,  0, -1  % x5 >= 15
];

% 3. Vetor de termos independentes (b)
% Como as restrições originais são >=, multiplicamos os termos por -1
b = [-48; -79; -65; -87; -64; -73; -82; -43; -52; -15];

% 4. Limites inferiores (x >= 0 para todas as variáveis)
lb = zeros(5, 1);

% 5. Limites superiores (não existem neste problema)
ub = []; 

[x, fval] = linprog(f, A, b, [], [], lb, ub);

%intcon = 1:5; % Indica que as variáveis de 1 a 5 devem ser números inteiros
%[x, fval] = intlinprog(f, A, b, [], [], lb, ub);

disp('Número de agentes atribuídos por turno (x1 a x5):');
disp(x); % Arredondado por questões de formatação de exibição
disp(['Custo total diário (Z): $', num2str(fval)]);
fprintf('\n');

