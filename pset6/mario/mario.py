from cs50 import get_int

def getPositiveInt():
    n = get_int("Height:")
    if n < 1 or n > 8:
        n =getPositiveInt()
    return(n)


h = getPositiveInt()
for i in range(1, h+1):
    print(' '*(h-i) + '#'*i + '  ' + '#'*i)
