import math

print()

with open("exemplo1.txt", 'r') as arquivo:
    a, b, c, d = tuple([float(value) for value in arquivo])

M = [[a, b], [c, d]]
sum1 = sum([M[i][i] for i in range(len(M))])
pw1 = sum1**2

print(sum1)

discriminante_eq_segundo_grau = pw1 - 4*(M[0][0]*M[1][1] - M[0][1]*M[1][0])

if(discriminante_eq_segundo_grau < 1):
	raise ValueError("Discriminante negativo")

lambda1 = (sum1 + math.sqrt(discriminante_eq_segundo_grau)) / 2.0
lambda2 = (sum1 - math.sqrt(discriminante_eq_segundo_grau)) / 2.0

print(f"Autovalores lambda1 = {lambda1:.2f}, lambda2 = {lambda2:.2f}")

lambda1_menos_a = lambda1 - M[0][0]

v1 = [0 for i in range(2)]

v1[0] = math.sqrt((1/(1 + ((lambda1_menos_a**2)/M[0][1]**2))))
v1[1] = (((lambda1_menos_a)*v1[0])/M[0][1])

lambda2_menos_a = lambda2 - M[0][0]

v2 = [0 for i in range(2)]

v2[0] = math.sqrt(1.0/(1.0 + ((lambda2_menos_a**2)/(M[0][1]**2))))
v2[1] = (((lambda2_menos_a)*v2[0])/M[0][1])

print("Autovetores\n")

print(f"v1[0] = {v1[0]:.2f}   v1[1] = {v1[1]:.2f}\n")
print(f"v2[0] = {v2[0]:.2f}   v2[1] = {v2[1]:.2f}\n")

prod_escalar = (v1[0]*v2[0] + v1[1]*v2[1])

print(f"produto interno = {prod_escalar:.2f}")

if(round(prod_escalar,2) != 0):
	print("Não é uma matriz hermetiana(Autovetores não perpendiculares)")


with open("exemplo1_saida.txt", 'a') as saida:
	print(f"Autovalores lambda1 = {lambda1:.2f}, lambda2 = {lambda2:.2f}", file=saida)
	print("Autovetores\n", file=saida)
	print(f"v1[0] = {v1[0]:.2f}   v1[1] = {v1[1]:.2f}\n", file=saida)
	print(f"v2[0] = {v2[0]:.2f}   v2[1] = {v2[1]:.2f}\n", file=saida)
	print(f"produto interno = {prod_escalar:.2f}", file=saida)
