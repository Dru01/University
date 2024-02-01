# En esta celda puede poner el código de la función pedida
# o poner la instrucción para importarlas de un archivo .py
import sympy
import numpy as np
import plotly as py
import plotly.graph_objs as go

# Clase Funciones de R -> R, con derivadas
class RealFunction:

    #Para que se pueda evaluar la funcion como f(x0), x0\in R
    def __call__(self, x):
        return self._evaluate(x)

    #Inicialización de función
    def __init__(self, parameters = [],  expression = "", function = None):
        self._paramaters = parameters
        self._my_symbols = {'x': sympy.Symbol('x', real=True)}
        if expression != "":
            self._expression = expression
            self._my_func = sympy.parsing.sympy_parser.parse_expr(expression, self._my_symbols)
        else:
            self._my_func = function
        self._evaluate = sympy.utilities.lambdify(self._my_symbols['x'], self._my_func, "sympy")
        self._der = dict()
    
    #Derivadas de la función
    def der(self, ord):
        if(ord not in self._der):
            _derk = self._my_func
            for _ in range(ord):
                _derk = sympy.diff(_derk, self._my_symbols['x'])
            self._der[ord] = self.__class__(parameters = self._paramaters, function = _derk)
        return self._der[ord]

# Clase Polinomios de R -> R, con derivadas
class Polynomial(RealFunction):
    
    def __init__(self, coeficients = [],):
        x = sympy.symbols('x')
        self._degree = len(coeficients)
        self._my_func = sum([c*x**(self._degree-1-i) for i, c in enumerate(coeficients)])
        super().__init__(parameters = coeficients, function = self._my_func)
        self._roots = np.roots(coeficients)
    
    def graph(self):
        real_roots = self._roots.real[abs(self._roots.imag)<1e-5]
        real_roots.sort()
        x = np.linspace(real_roots[0]-1,real_roots[-1]+1,100)
        fig = go.Figure()
        fig.add_trace(
            go.Scatter(
                x=x,
                y=[self.__call__(x) for x in x],
                mode="lines",
                name=r'$P(x)$'
            )
        )
        x = real_roots
        fig.add_trace(
            go.Scatter(
                x=x,
                y=[self.__call__(x) for x in x],
                mode="markers",
                marker = dict(size=10),
                name='Roots'
            )
        )
        fig.update_layout(
            template = "simple_white",
            title = dict(
                text = r"$Raices del polinomio P(x) = "+ sympy.printing.latex(f_1._my_func) + "$",
                x = 0.5,
                xanchor = "center"
            ),
            hovermode="x unified"
        )
        fig.show()

f_1 = Polynomial([-4,33,97,-840])
f_1.graph()