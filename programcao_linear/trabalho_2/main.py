from typing import Dict, Any

import highspy


def get_model_data() -> dict[str, Any]:
    return {
        "var_names": [
            "S18", "S20", "S23", "S26", "S30",  # 6 metros
            "Y18", "Y20", "Y23", "Y26", "Y30",  # 8 metros
            "D18", "D20", "D23", "D26", "D30",  # 10 metros
            "X18", "X20", "X23", "X26", "X30",  # 12 metros
        ],
        "obj_coefs": [
            200.35, 271.96, 246.70, 299.80, 400.46,
            242.51, 389.22, 336.18, 427.24, 560.73,
            304.38, 392.45, 344.23, 376.95, 295.86,
            367.21, 475.68, 310.21, 383.95, 372.02,
        ],
        "constraints": [
            {
                "name": "R1: Mão de obra",
                "limit": 66000,
                "coefs": [
                    31.93, 39.53, 52.37, 67.23, 89.70,
                    42.57, 52.71, 69.94, 89.53, 119.60,
                    53.21, 65.88, 87.51, 112.00, 149.50,
                    63.86, 79.06, 104.91, 134.30, 179.40
                ]
            },
            {
                "name": "R2: Espaço estoque",
                "limit": 2710,
                "coefs": [
                    0.25, 0.27, 0.31, 0.43, 0.49,
                    0.32, 0.35, 0.40, 0.56, 0.64,
                    0.39, 0.43, 0.49, 0.69, 0.79,
                    0.46, 0.51, 0.58, 0.82, 0.94
                ]
            },
            {
                "name": "R3: Equipamento",
                "limit": 8400,
                "coefs": [
                    2.17, 2.60, 2.60, 3.25, 4.33,
                    2.89, 3.47, 3.47, 4.33, 5.78,
                    2.71, 3.25, 3.25, 4.06, 5.42,
                    4.33, 5.20, 5.20, 6.50, 8.67
                ]
            },
            {
                "name": "R4: Cimento",
                "limit": 115000,
                "coefs": [
                    56.70, 70.20, 93.00, 127.36, 159.30,
                    75.60, 93.60, 124.20, 159.00, 212.40,
                    94.50, 117.00, 155.40, 198.90, 265.50,
                    113.40, 140.40, 186.30, 238.50, 318.60
                ]
            },
            {
                "name": "R5: Press mix",
                "limit": 300,
                "coefs": [
                    0.14, 0.18, 0.23, 0.32, 0.40,
                    0.19, 0.23, 0.31, 0.40, 0.53,
                    0.24, 0.29, 0.39, 0.50, 0.66,
                    0.28, 0.35, 0.47, 0.60, 0.80
                ]
            },
            {
                "name": "R6: Areia",
                "limit": 250,
                "coefs": [
                    0.16, 0.17, 0.18, 0.19, 0.22,
                    0.21, 0.22, 0.24, 0.26, 0.29,
                    0.27, 0.28, 0.30, 0.33, 0.36,
                    0.32, 0.33, 0.36, 0.39, 0.44
                ]
            },
            {
                "name": "R7: Fio de protensão",
                "limit": 7900,
                "coefs": [
                    4.00, 5.77, 5.77, 5.77, 5.77,
                    7.55, 7.55, 7.55, 7.33, 7.55,
                    9.32, 9.32, 9.32, 12.68, 12.68,
                    11.10, 11.10, 15.10, 15.10, 15.10
                ]
            },
            {
                "name": "R8: Brita nº 1",
                "limit": 170,
                "coefs": [
                    0.08, 0.11, 0.14, 0.18, 0.24,
                    0.11, 0.14, 0.19, 0.24, 0.32,
                    0.14, 0.18, 0.23, 0.30, 0.40,
                    0.17, 0.21, 0.28, 0.36, 0.48
                ]
            },
            {
                "name": "R9: Aço CA60",
                "limit": 3600,
                "coefs": [
                    2.85, 2.92, 3.46, 3.31, 4.49,
                    3.59, 2.91, 3.95, 4.57, 6.16,
                    4.49, 4.35, 4.80, 5.55, 7.82,
                    5.29, 5.07, 8.02, 6.98, 9.49
                ]
            },
            {
                "name": "R10: Brita nº 0",
                "limit": 260,
                "coefs": [
                    0.13, 0.16, 0.21, 0.27, 0.35,
                    0.17, 0.21, 0.28, 0.35, 0.47,
                    0.21, 0.26, 0.34, 0.44, 0.59,
                    0.25, 0.31, 0.41, 0.53, 0.71
                ]
            }
        ]
    }


def solve_optimization_model(data: Dict[str, Any]) -> highspy.Highs:
    h = highspy.Highs()

    # Silencia os logs
    h.setOptionValue("output_flag", False)

    var_names = data["var_names"]

    variables = {name: h.addVariable(lb=0) for name in var_names}

    objetivo = sum(
        coef * variables[name]
        for coef, name in zip(data["obj_coefs"], var_names, strict=True)
    )
    h.maximize(objetivo)

    for c in data["constraints"]:
        expr = sum(
            coef * variables[name]
            for coef, name in zip(c["coefs"], var_names, strict=True)
        )
        h.addConstr(expr <= c["limit"])

    h.run()

    return h


def print_report(h: highspy.Highs, data: Dict[str, Any]) -> None:
    if h.getModelStatus() != highspy.HighsModelStatus.kOptimal:
        print("O modelo não encontrou uma solução ótima.")
        return

    info = h.getInfo()
    solution = h.getSolution()
    var_names = data["var_names"]
    constraints = data["constraints"]

    print(f"Valor ótimo de Z = {info.objective_function_value:.2f}\n")

    print("--- Variáveis ---")
    print(f"{'Variável':<10} | {'Valor Ótimo':<15} | {'Custo Reduzido':<15}")
    print("-" * 45)
    for nome, valor, custo_reduzido in zip(var_names, solution.col_value, solution.col_dual, strict=True):
        print(f"{nome:<10} | {valor:<15.4f} | {custo_reduzido:<15.4f}")

    print("\n--- Restrições e Folgas ---")
    print(f"{'Recurso':<25} | {'Uso Real':<12} | {'Limite':<10} | {'Folga':<10} | {'Preço Sombra'}")
    print("-" * 80)

    for c, uso_real, preco_sombra in zip(constraints, solution.row_value, solution.row_dual, strict=True):
        limite = c['limit']
        folga = limite - uso_real

        nome_recurso = c['name'].replace("R", "").replace(":", "").strip()
        nome_recurso = nome_recurso[:23]

        print(f"{nome_recurso:<25} | {uso_real:<12.2f} | {limite:<10.2f} | {folga:<10.2f} | {preco_sombra:.4f}")


def main():
    data = get_model_data()

    model = solve_optimization_model(data)

    print_report(model, data)


if __name__ == "__main__":
    main()
