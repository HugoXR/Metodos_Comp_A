#Abrindo arquivo para ler sistema linear com cada linha uma linha da matriz A, e a última a do vetor b
with open("sistema.txt", 'r') as entrada:
    matriz_vetor = [linha.split() for linha in entrada if(linha != '\n')]

#inicializando o vetor b
for i in range(len(matriz_vetor)):
    if(i == (len(matriz_vetor) - 1)):
        vetor = [0 for j in range(len(matriz_vetor[i]))]
#inicializando a matriz A
matriz = [[0 for j in range(len(matriz_vetor[i]))] for i in range(len(matriz_vetor) - 1)]

#populando a matriz A e vetor b
for i in range(len(matriz_vetor)):
    for j in range(len(matriz_vetor[i])):
        if(i == (len(matriz_vetor) - 1)):
            vetor[j] = float(matriz_vetor[i][j])
        else:
            matriz[i][j] = float(matriz_vetor[i][j])

def swap(matriz, x):
    if(x == (len(matriz) - 1)):
        matrix.pop(x)
        return
    
    for i in range(len(matriz)):
        value = matriz[x][i]
        matriz[x][i] = matriz[x+1][i]
        matriz[x+1][i] = value

#Encontrando a solução do sistema linear
for i in range(len(matriz)):
    a_ii = matriz[i][i]
    
    if(a_ii == 0):
        swap(matriz, i)

    for j in range(len(matriz[i])):
        if(i != j):
            multiplicador = matriz[j][i] / a_ii
            for k in range(len(matriz[i])):
                matriz[j][k] = round(((multiplicador*matriz[i][k] - matriz[j][k])), 2)
            vetor[j] = (multiplicador*vetor[i]) - vetor[j]

def find_values(value):
    if(matriz[vetor.index(value)][vetor.index(value)] == 0):
        raise ValueError("Divisão por 0")
    value = round(value/matriz[vetor.index(value)][vetor.index(value)], 2)
    return value

vetor_resultado = list(map(find_values, vetor))
print(vetor_resultado)
