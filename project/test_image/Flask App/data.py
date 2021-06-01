# Entonces así funciona :D
# Le dices al usuario
# Ingrese el valor en el eje x, la variable en este ejemplo es var1

from sympy import *
from sympy.parsing.sympy_parser import parse_expr
import numpy as np  # Permite manejar datos, añade funciones trigonometricas
import matplotlib.pyplot as pyplot  # Permite graficar

x = Symbol('x')

ecuacion = str(input('ecuación'))
ecuacionParseada = parse_expr(ecuacion)
derivada = diff(ecuacionParseada, x)
derivadaNumpy = lambdify(x, derivada, 'numpy')
ecuacionNumpy = lambdify(x, ecuacionParseada, 'numpy')
x1 = int(input('ingrese el valor en el eje x'))
# y1 = input('ingrese el valor en el eje y')

print('La derivada es:', derivada)

def graph(x):
    return ecuacionNumpy(x)


def tang(x):
    return derivadaNumpy(x1) * (x - x1) + ecuacionNumpy(x1)


x = np.linspace(-2,2)

pyplot.plot(x, graph(x))
pyplot.plot(x, tang(x))
pyplot.title('Función f(x) = sen(x) + cos(2x)')
pyplot.show()