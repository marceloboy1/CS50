from cs50 import get_float

def getPositiveFloat():
    n = get_float("Change:")
    if n < 0:
        n =getPositiveFloat()
    return(n)

value = int(getPositiveFloat()*100)
change = 0

while value > 0:
    if value >= 25:
        change += int(value / 25)
        value = value % 25
        # print("Moedas:", change)
        # print("Valor apos moedas de 25", value)

    elif value >= 10:
        change += int(value / 10)
        value = value % 10
        # print("Moedas:", change)
        # print("Valor apos moedas de 10", value)

    elif value >= 5:
        change += int(value / 5)
        value = value % 5
        # print("Moedas:", change)
        # print("Valor apos moedas de 5", value)

    elif value >= 1:
        change += int(value / 1)
        value = value % 1
        # print("Moedas:", change)
        # print("Valor apos moedas de 1", value)

    else:
        break

print(change)
