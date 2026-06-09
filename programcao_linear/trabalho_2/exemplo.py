import highspy

# Inicializa o solver
h = highspy.Highs()

# Define as variáveis de decisão e seus limites (lb = limite inferior, ub = limite superior)
x0 = h.addVariable(lb=0, ub=4)
x1 = h.addVariable(lb=1, ub=7)

# Adiciona as restrições matemáticas do problema
h.addConstr(5 <= x0 + 2 * x1 <= 15)
h.addConstr(3 * x0 + 2 * x1 >= 6)

# Define o objetivo (minimizar a soma das duas variáveis)
h.minimize(x0 + x1)

# Roda o otimizador
h.run()

# Obtém as informações do resultado
info = h.getInfo()
status_do_modelo = h.getModelStatus()

print("Status do modelo:", h.modelStatusToString(status_do_modelo))
print("Valor ótimo encontrado:", info.objective_function_value)
