from math import sin, log
import matplotlib.pyplot as plt


num_pontos = 100
x_i = 0.1
x_f = 10.0

dx = (x_f - x_i) / (num_pontos - 1.0)

x = x_i

with open("grafico.dat", "w") as grafico:
	for i in range(num_pontos):
		func = sin(log(x))
		print(f"{x:.6f}  {func:.6f}", file=grafico)
		x += dx



eixo_x = [i+1 for i in range(num_pontos)]
eixo_y = [sin(log(j)) for j in eixo_x]

plt.plot(eixo_x, eixo_y, marker='o')
plt.title('Function sin(log(x))')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.show()