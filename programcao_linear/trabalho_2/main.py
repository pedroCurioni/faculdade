import highspy


def main():
    h = highspy.Highs()

    # Variáveis de decisão (Estacas de 6m, 8m, 10m e 12m)
    var_names = [
        "S18",
        "S20",
        "S23",
        "S26",
        "S30",  # Estacas de 6 metros
        "Y18",
        "Y20",
        "Y23",
        "Y26",
        "Y30",  # Estacas de 8 metros
        "D18",
        "D20",
        "D23",
        "D26",
        "D30",  # Estacas de 10 metros
        "X18",
        "X20",
        "X23",
        "X26",
        "X30",  # Estacas de 12 metros
    ]

    # Criação das variáveis no modelo (todas com limite inferior = 0)
    variables = {name: h.addVariable(lb=0) for name in var_names}

    # Coeficientes da função objetivo
    obj_coefs = [
        200.35,
        271.96,
        246.70,
        299.80,
        400.46,  # Estacas de 6 metros
        242.51,
        389.22,
        336.18,
        427.24,
        560.73,  # Estacas de 8 metros
        304.38,
        392.45,
        344.23,
        376.95,
        295.86,  # Estacas de 10 metros
        367.21,
        475.68,
        310.21,
        383.95,
        372.02,  # Estacas de 12 metros
    ]

    # Maximização do lucro
    objetivo = sum(coef * variables[name] for coef, name in zip(obj_coefs, var_names, strict=True))
    h.maximize(objetivo)

    # Definição das restrições: [Nome, Limite, Coeficientes]
    constraints = [
        {
            "name": "R1: Mão de obra",
            "limit": 66000,
            "coefs": [
                31.93,
                39.53,
                52.37,
                67.23,
                89.70,
                42.57,
                52.71,
                69.94,
                89.53,
                119.60,
                53.21,
                65.88,
                87.51,
                112.00,
                149.50,
                63.86,
                79.06,
                104.91,
                134.30,
                179.40,
            ],
        },
        {
            "name": "R2: Espaço estoque",
            "limit": 2710,
            "coefs": [
                0.25,
                0.27,
                0.31,
                0.43,
                0.49,
                0.32,
                0.35,
                0.40,
                0.56,
                0.64,
                0.39,
                0.43,
                0.49,
                0.69,
                0.79,
                0.46,
                0.51,
                0.58,
                0.82,
                0.94,
            ],
        },
        {
            "name": "R3: Equipamento",
            "limit": 8400,
            "coefs": [
                2.17,
                2.60,
                2.60,
                3.25,
                4.33,
                2.89,
                3.47,
                3.47,
                4.33,
                5.78,
                2.71,
                3.25,
                3.25,
                4.06,
                5.42,
                4.33,
                5.20,
                5.20,
                6.50,
                8.67,
            ],
        },
        {
            "name": "R4: Matéria-prima, Cimento",
            "limit": 115000,
            "coefs": [
                56.70,
                70.20,
                93.00,
                127.36,
                159.30,
                75.60,
                93.60,
                124.20,
                159.00,
                212.40,
                94.50,
                117.00,
                155.40,
                198.90,
                265.50,
                113.40,
                140.40,
                186.30,
                238.50,
                318.60,
            ],
        },
        {
            "name": "R5: Matéria-prima, Press mix",
            "limit": 300,
            "coefs": [
                0.14,
                0.18,
                0.23,
                0.32,
                0.40,
                0.19,
                0.23,
                0.31,
                0.40,
                0.53,
                0.24,
                0.29,
                0.39,
                0.50,
                0.66,
                0.28,
                0.35,
                0.47,
                0.60,
                0.80,
            ],
        },
        {
            "name": "R6: Matéria-prima, Areia",
            "limit": 250,
            "coefs": [
                0.16,
                0.17,
                0.18,
                0.19,
                0.22,
                0.21,
                0.22,
                0.24,
                0.26,
                0.29,
                0.27,
                0.28,
                0.30,
                0.33,
                0.36,
                0.32,
                0.33,
                0.36,
                0.39,
                0.44,
            ],
        },
        {
            "name": "R7: Matéria-prima, Fio de protensão",
            "limit": 7900,
            "coefs": [
                4.00,
                5.77,
                5.77,
                5.77,
                5.77,
                7.55,
                7.55,
                7.55,
                7.33,
                7.55,
                9.32,
                9.32,
                9.32,
                12.68,
                12.68,
                11.10,
                11.10,
                15.10,
                15.10,
                15.10,
            ],
        },
        {
            "name": "R8: Matéria-prima, Brita nº 1",
            "limit": 170,
            "coefs": [
                0.08,
                0.11,
                0.14,
                0.18,
                0.24,
                0.11,
                0.14,
                0.19,
                0.24,
                0.32,
                0.14,
                0.18,
                0.23,
                0.30,
                0.40,
                0.17,
                0.21,
                0.28,
                0.36,
                0.48,
            ],
        },
        {
            "name": "R9: Matéria-prima, Aço CA60",
            "limit": 3600,
            "coefs": [
                2.85,
                2.92,
                3.46,
                3.31,
                4.49,
                3.59,
                2.91,
                3.95,
                4.57,
                6.16,
                4.49,
                4.35,
                4.80,
                5.55,
                7.82,
                5.29,
                5.07,
                8.02,
                6.98,
                9.49,
            ],
        },
        {
            "name": "R10: Matéria-prima, Brita nº 0",
            "limit": 260,
            "coefs": [
                0.13,
                0.16,
                0.21,
                0.27,
                0.35,
                0.17,
                0.21,
                0.28,
                0.35,
                0.47,
                0.21,
                0.26,
                0.34,
                0.44,
                0.59,
                0.25,
                0.31,
                0.41,
                0.53,
                0.71,
            ],
        },
    ]

    # Adiciona as restrições ao modelo
    for c in constraints:
        expr = sum(coef * variables[name] for coef, name in zip(c["coefs"], var_names, strict=True))
        h.addConstr(expr <= c["limit"])

    # Roda o modelo
    h.run()

    # Resultados
    print("Status do modelo:", h.getModelStatus())

    info = h.getInfo()
    print(f"Valor ótimo de Z = {info.objective_function_value:.2f}\n")

    solution = h.getSolution()

    print("--- ANÁLISE DAS VARIÁVEIS (Produção e Custos Reduzidos) ---")
    print(f"{'Variável':<10} | {'Valor Ótimo':<15} | {'Custo Reduzido':<15}")
    print("-" * 45)
    for nome, valor, custo_reduzido in zip(var_names, solution.col_value, solution.col_dual, strict=True):
        print(f"{nome:<10} | {valor:<15.4f} | {custo_reduzido:<15.4f}")

    print("\n--- ANÁLISE DAS RESTRIÇÕES (Preços Sombra dos Recursos) ---")
    print(f"{'Restrição':<35} | {'Preço Sombra':<15}")
    print("-" * 55)
    # Como as restrições foram adicionadas na ordem da lista, podemos pareá-las diretamente
    for c, preco_sombra in zip(constraints, solution.row_dual, strict=True):
        print(f"{c['name']:<35} | {preco_sombra:<15.4f}")


if __name__ == "__main__":
    main()
