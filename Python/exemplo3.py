
def fatorial(value):
    if value >= 1:
        return value*fatorial(value-1)

    return 1


value = int(input("Digite o valor do input:\n"))
f_value = fatorial(value)
print(f_value)

