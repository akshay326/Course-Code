import math


# First Order ODE (y' = f(x, y)) Solver using Euler method
# xa: initial value of independent variable
# xb: final value of independent variable
# ya: initial value of dependent variable
# n : number of steps (higher the better)
# Returns value of y at xb. 
def Euler(f, xa, xb, ya, n):
    h = (xb - xa) / float(n)
    x = xa
    y = ya
    for i in range(n):
        y += h * f(x, y)
        x += h
    return y


def EulerModified(f, xa, xb, ya, n):
    h = (xb - xa) / float(n)
    x = xa
    y = ya
    for i in range(n):
        k1 = h * f(x, y)
        k2 = h * f(x + h, y + k1)
        y += (k2 + k1) / 2
        x += h
    return y


def f(x, y):
    # return math.cos(2*x) + math.sin(3*x)
    return x**2 + y**2


print(Euler(f,1,2,0,4))
# print(EulerModified(f,1,2,0,4))