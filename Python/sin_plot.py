from math import sin
import matplotlib.pyplot as plt

def function(x):
    value = sin(1/x)
    return value

num_pontos = 100
eixo_x = []
x_i = -10.0
x_f = 10.0
dx = (x_f - x_i) / (num_pontos - 1.0)
i = -10.0

while(i < num_pontos):
    eixo_x.append(i)
    i += dx

eixo_y = [function(x) for x in eixo_x]

plt.plot(eixo_x, eixo_y, marker='o')
plt.title('Function sin(1/x)')
plt.xlabel('x')
plt.ylabel('sin(1/x)')
plt.show()
