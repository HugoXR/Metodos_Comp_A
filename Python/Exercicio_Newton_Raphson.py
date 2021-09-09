def Func(x):
    F = [0 for i in range(2)]
    F[0] = x[0]*x[0] + x[1];
    F[1] = 2*(x[0]*x[0])-x[1];

    return F

def Jac(x):
    J = [[0 for i in range(2)] for j in range(2)]
    
    J[0][0] = 2*x[0]
    J[0][1] = 1
    J[1][0] = 4*x[0]
    J[1][1] = -1
    return J

def Newton_Raphson(x, erro, solucao):
    i = 0
    delta_x = [0 for j in range(2)]
    x_i = x
    
    F = [0 for j in range(2)]
    J = [[0 for k in range(2)] for j in range(2)]

    F = Func(x)
    while(max(F) > erro):
        i += 1
        print(f"Iteracao {i:d}", file=solucao)
        
        F = Func(x_i)
        f1 = F[0]
        f2 = F[1]
        print(f"F_1(x) = {f1:.6f}   F_2(x) = {f2:.6f}", file=solucao)
        
        J = Jac(x_i)
        J_11 = J[0][0]
        J_12 = J[0][1]
        J_21 = J[1][0]
        J_22 = J[1][1]
        print(f"J_11 = {J_11:.6f}, J_12 = {J_12:.6f}, J_21 = {J_21:.6f}, J_22 = {J_22:.6f}", file=solucao)
        
        delta_x1 = (J_22*f1 - f2*J_12) / (J_21*J_12 - J[0][0]*J[1][1])
        delta_x2 = (-f1 - J_11*delta_x1)/J_12
        print(f"delta_x1 = {delta_x1:.6f}, delta_x2 = {delta_x2:.6f}\n", file=solucao)

        x_i[0] += delta_x1
        x_i[1] += delta_x2
        x1 = x_i[0]
        x2 = x_i[1]
        print(f"x1 = {x1:.6f}, x2 = {x2:.6f}\n\n", file=solucao)

x = [1,2] #Entradas
erro = 1E-12;
x_inicial = [1, 2]
with open("solucao_sistema_nao_linear_newton_raphson.txt", "w") as solucao:
    print(f"Objetivo do Programa: Calcular o zero de um sistema nao linear",file=solucao)
    print(f"Nome: Hugo Xavier Rodrigues",file=solucao)
    print(f"Matricula: 190108622", file=solucao)
    print(f"Data: 09-09-2021\n", file=solucao)

    Newton_Raphson(x, erro, solucao)

    print(f"Seja x1_inicial = {x_inicial[0]:d} e x2_inicial = {x_inicial[1]:d}; erro = 10^-12\n", file=solucao)
    print(f"Solucao do sistema nao linear\n", file=solucao)
    print(f"x1 = {x[0]:.6f}, x2 = {x[1]:.6f}", file=solucao)

print(f"Solucao do sistema nao linear\n")
print(f"x1 = {x[0]:.6f}, x2 = {x[1]:.6f}")
