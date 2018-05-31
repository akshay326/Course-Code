"""
    Akshay Sharma
    16123004
    Maths And Computing
    Date of submission - 31 March 2018

    Numerical Techniques
    Assignment 1
"""

from math import sin, cos, exp


# This is a function for calculating derivative of a function
def derivative(f, x, h=0.001):
    return (f(x + h) - f(x - h)) / (2.0 * h)


# This a function for Bisection Method
def bisection(f, a, b, decimals=2):
    """

    :param f: The function whose roots are to be evaluated
    :param a: initial lower bound
    :param b: initial upper bound. f(a)*f(b) should be negative
    :param decimals: The decimal precision wanted. By default 2
    :return: List of possible roots
    """

    a = a * 1.0
    b = b * 1.0

    if f(a) * f(b) > 0:
        return "Bounds are same valued"

    if decimals < 1:
        return "Wrong decimal value"

    while 10 ** (-decimals) < 2 * abs(b - a):
        if f(a) == 0.0:
            return str("given function has root %.{0}f".format(decimals) % a)

        if f(b) == 0.0:
            return str("given function has root %.{0}f".format(decimals) % b)

        m = (a + b) / 2.0
        if f(m) * f(a) > 0:
            a = m
        else:
            b = m

    return str("given function has root in [%.{0}f,%.{0}f] with error %.2E".format(decimals+1) % (a, b, f(b)))


# This a function for Iteration Method
def iteration(f, i, max_iterations=10, decimals=2):
    """

    :param f:  The function
    :param i: Initial point
    :param max_iterations: Max Number of iterations permissible. By default 10
    :param decimals: The decimal precision wanted. By default 2
    :return:
    """

    if max_iterations < 1:
        return "Wrong iteration value value"

    # check whether |f(x)| < 1 or not
    if abs(derivative(f,i)) >= 1:
        return "Initial Point is diverging. |f(x)| >= 1"

    for j in range(max_iterations):
        i = f(i) - i
        if f(i) < 10**(-decimals):
            return str("given function has root %.{0}f with error %.2E".format(decimals) % (i,f(i)))

    return str("Failed to converge after %d iterations, value is %s" % (max_iterations,i))


# This a function for Newton Raphson Method
def newton_raphson(f, x, decimals=2):
    """
    :param f:  The function
    :param x: Initial point
    :param decimals: Decimal Precision wanted. By default 2
    :return:
    """

    if decimals < 1:
        return "Wrong decimal value"

    while 10 ** (-decimals) < abs(f(x)):
        x -= f(x) / derivative(f, x)

    return str("given function has root %.{0}f with error %.2E".format(decimals) % (x,f(x)))


# This a function for Regula Falsi
def regula_falsi(f, a, b, decimals=2):
    """
    :param f:  The function
    :params a,b: initial bounds
    :param decimals: Decimal Precision wanted. By default 2
    :return:
    """

    if decimals < 1:
        return "Wrong decimal value"

    val = 100000 # any large value
    while 10 ** (-decimals) < abs(val):
        if a == b:
            break
        val = (a * f(b) - b * f(a)) / (f(b) - f(a))
        a = b
        b = val

    return str("given function has root in [%.{0}f,%.{0}f] with error %.2E".format(decimals) % (a, b, f(b)))


def f1(x):
    return x ** 5 - 25 * x ** 4 + 184 * x ** 3 - 640 * x ** 2 - 2223 * x - 4095


def f2(x):
    return x ** 3 + x**2 - 1


def f3(x):
    return x * sin(x) + cos(x)


def f4(x):
    return x * sin(x) + cos(x)


def f(x):
    return x**4 - 2*x - 1

'''
    Sample input and output(functions f1,f2,f3,.. are defined above):
    
    Command:    print bisection(f1, 0, 17, decimals=5)
    Output:     given function has root in [16.849605,16.849609] with error 1.77E-01
    
    Command:    print iteration(f2, -0.5, max_iterations=5, decimals=3)
    Output:     given function has root -0.375 with error -9.12E-01
    
    Command:    print regula_falsi(f3, -3,1, decimals=10)
    Output:     given function has root in [-25.0929104121,-25.0929104121] with error -4.88E-15
    
    Command:    print newton_raphson(f4, 3,14)
    Output:     given function has root 2.79838604578389 with error -1.11E-16
'''
# print(bisection(f, 0, 2, decimals=4))
# print(regula_falsi(f, 0, 2, decimals=4))
# print(iteration(f, 0, 2, decimals=4))
# print(newton_raphson(f, 0, decimals=4))