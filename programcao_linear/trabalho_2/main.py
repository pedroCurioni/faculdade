import highspy

h = highspy.Highs()

# Estacas de 6 metros
S18 = h.addVariable(lb=0)
S20 = h.addVariable(lb=0)
S23 = h.addVariable(lb=0)
S26 = h.addVariable(lb=0)
S30 = h.addVariable(lb=0)
# Estacas de 8 metros
Y18 = h.addVariable(lb=0)
Y20 = h.addVariable(lb=0)
Y23 = h.addVariable(lb=0)
Y26 = h.addVariable(lb=0)
Y30 = h.addVariable(lb=0)
# Estacas de 10 metros
D18 = h.addVariable(lb=0)
D20 = h.addVariable(lb=0)
D23 = h.addVariable(lb=0)
D26 = h.addVariable(lb=0)
D30 = h.addVariable(lb=0)
# Estacas de 12 metros
X18 = h.addVariable(lb=0)
X20 = h.addVariable(lb=0)
X23 = h.addVariable(lb=0)
X26 = h.addVariable(lb=0)
X30 = h.addVariable(lb=0)

objetivo = (
    # Estacas de 6 metros
    200.35 * S18
    + 271.96 * S20
    + 246.70 * S23
    + 299.80 * S26
    + 400.46 * S30
    # Estacas de 8 metros
    + 242.51 * Y18
    + 389.22 * Y20
    + 336.18 * Y23
    + 427.24 * Y26
    + 560.73 * Y30
    # Estacas de 10 metros
    + 304.38 * D18
    + 392.45 * D20
    + 344.23 * D23
    + 376.95 * D26
    + 295.86 * D30
    # Estacas de 12 metros
    + 367.21 * X18
    + 475.68 * X20
    + 310.21 * X23
    + 383.95 * X26
    + 372.02 * X30
)

h.maximize(objetivo)

# R1: Mão de obra
h.addConstr(
    31.93 * S18
    + 39.53 * S20
    + 52.37 * S23
    + 67.23 * S26
    + 89.70 * S30
    + 42.57 * Y18
    + 52.71 * Y20
    + 69.94 * Y23
    + 89.53 * Y26
    + 119.60 * Y30
    + 53.21 * D18
    + 65.88 * D20
    + 87.51 * D23
    + 112.00 * D26
    + 149.50 * D30
    + 63.86 * X18
    + 79.06 * X20
    + 104.91 * X23
    + 134.30 * X26
    + 179.40 * X30
    <= 66000,
)

# R2: Espaço estoque
h.addConstr(
    0.25 * S18
    + 0.27 * S20
    + 0.31 * S23
    + 0.43 * S26
    + 0.49 * S30
    + 0.32 * Y18
    + 0.35 * Y20
    + 0.40 * Y23
    + 0.56 * Y26
    + 0.64 * Y30
    + 0.39 * D18
    + 0.43 * D20
    + 0.49 * D23
    + 0.69 * D26
    + 0.79 * D30
    + 0.46 * X18
    + 0.51 * X20
    + 0.58 * X23
    + 0.82 * X26
    + 0.94 * X30
    <= 2710,
)

# R3: Equipamento
h.addConstr(
    2.17 * S18
    + 2.60 * S20
    + 2.60 * S23
    + 3.25 * S26
    + 4.33 * S30
    + 2.89 * Y18
    + 3.47 * Y20
    + 3.47 * Y23
    + 4.33 * Y26
    + 5.78 * Y30
    + 2.71 * D18
    + 3.25 * D20
    + 3.25 * D23
    + 4.06 * D26
    + 5.42 * D30
    + 4.33 * X18
    + 5.20 * X20
    + 5.20 * X23
    + 6.50 * X26
    + 8.67 * X30
    <= 8400,
)

# R4: Matéria-prima, Cimento
h.addConstr(
    56.70 * S18
    + 70.20 * S20
    + 93.00 * S23
    + 127.36 * S26
    + 159.30 * S30
    + 75.60 * Y18
    + 93.60 * Y20
    + 124.20 * Y23
    + 159.00 * Y26
    + 212.40 * Y30
    + 94.50 * D18
    + 117.00 * D20
    + 155.40 * D23
    + 198.90 * D26
    + 265.50 * D30
    + 113.40 * X18
    + 140.40 * X20
    + 186.30 * X23
    + 238.50 * X26
    + 318.60 * X30
    <= 115000,
)

# R5: Matéria-prima, Press mix
h.addConstr(
    0.14 * S18
    + 0.18 * S20
    + 0.23 * S23
    + 0.32 * S26
    + 0.40 * S30
    + 0.19 * Y18
    + 0.23 * Y20
    + 0.31 * Y23
    + 0.40 * Y26
    + 0.53 * Y30
    + 0.24 * D18
    + 0.29 * D20
    + 0.39 * D23
    + 0.50 * D26
    + 0.66 * D30
    + 0.28 * X18
    + 0.35 * X20
    + 0.47 * X23
    + 0.60 * X26
    + 0.80 * X30
    <= 300,
)

# R6: Matéria-prima, Areia
h.addConstr(
    0.16 * S18
    + 0.17 * S20
    + 0.18 * S23
    + 0.19 * S26
    + 0.22 * S30
    + 0.21 * Y18
    + 0.22 * Y20
    + 0.24 * Y23
    + 0.26 * Y26
    + 0.29 * Y30
    + 0.27 * D18
    + 0.28 * D20
    + 0.30 * D23
    + 0.33 * D26
    + 0.36 * D30
    + 0.32 * X18
    + 0.33 * X20
    + 0.36 * X23
    + 0.39 * X26
    + 0.44 * X30
    <= 250,
)

# R7: Matéria-prima, Fio de protensão
h.addConstr(
    4.00 * S18
    + 5.77 * S20
    + 5.77 * S23
    + 5.77 * S26
    + 5.77 * S30
    + 7.55 * Y18
    + 7.55 * Y20
    + 7.55 * Y23
    + 7.33 * Y26
    + 7.55 * Y30
    + 9.32 * D18
    + 9.32 * D20
    + 9.32 * D23
    + 12.68 * D26
    + 12.68 * D30
    + 11.10 * X18
    + 11.10 * X20
    + 15.10 * X23
    + 15.10 * X26
    + 15.10 * X30
    <= 7900,
)

# R8: Matéria-prima, Brita nº 1
h.addConstr(
    0.08 * S18
    + 0.11 * S20
    + 0.14 * S23
    + 0.18 * S26
    + 0.24 * S30
    + 0.11 * Y18
    + 0.14 * Y20
    + 0.19 * Y23
    + 0.24 * Y26
    + 0.32 * Y30
    + 0.14 * D18
    + 0.18 * D20
    + 0.23 * D23
    + 0.30 * D26
    + 0.40 * D30
    + 0.17 * X18
    + 0.21 * X20
    + 0.28 * X23
    + 0.36 * X26
    + 0.48 * X30
    <= 170,
)

# R9: Matéria-prima, Aço CA60
h.addConstr(
    2.85 * S18
    + 2.92 * S20
    + 3.46 * S23
    + 3.31 * S26
    + 4.49 * S30
    + 3.59 * Y18
    + 2.91 * Y20
    + 3.95 * Y23
    + 4.57 * Y26
    + 6.16 * Y30
    + 4.49 * D18
    + 4.35 * D20
    + 4.80 * D23
    + 5.55 * D26
    + 7.82 * D30
    + 5.29 * X18
    + 5.07 * X20
    + 8.02 * X23
    + 6.98 * X26
    + 9.49 * X30
    <= 3600,
)

# R10: Matéria-prima, Brita nº 0
h.addConstr(
    0.13 * S18
    + 0.16 * S20
    + 0.21 * S23
    + 0.27 * S26
    + 0.35 * S30
    + 0.17 * Y18
    + 0.21 * Y20
    + 0.28 * Y23
    + 0.35 * Y26
    + 0.47 * Y30
    + 0.21 * D18
    + 0.26 * D20
    + 0.34 * D23
    + 0.44 * D26
    + 0.59 * D30
    + 0.25 * X18
    + 0.31 * X20
    + 0.41 * X23
    + 0.53 * X26
    + 0.71 * X30
    <= 260,
)
# ---------------------------------------------------------

# 5. Roda o modelo (comentado pois rodar sem restrições dará infinito)
h.run()

# 6. Para obter os resultados (após rodar com restrições):
print("Status do modelo:", h.getModelStatus())
solution = h.getSolution()
basis = h.getBasis()
info = h.getInfo()
print("Valor ótimo de Z =", info.objective_function_value)

variaveis = [
    "S18",
    "S20",
    "S23",
    "S26",
    "S30",
    "Y18",
    "Y20",
    "Y23",
    "Y26",
    "Y30",
    "D18",
    "D20",
    "D23",
    "D26",
    "D30",
    "X18",
    "X20",
    "X23",
    "X26",
    "X30",
]
for nome, valor in zip(variaveis, solution.col_value, strict=True):
    print(f"{nome} = {valor:.4f}")
