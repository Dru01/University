import sympy

class RealFunction:

    def __call__(self, x):
        a = self._evaluate(x)
        return a

    def __init__(self,  expression = "", function = None):
        self._my_symbols = {'x': sympy.Symbol('x', real=True)}
        if expression != "":
            self._expression = expression
            self._my_func = sympy.parsing.sympy_parser.parse_expr(expression, self._my_symbols)
        else:
            self._my_func = function
        self._evaluate = sympy.utilities.lambdify(self._my_symbols['x'], self._my_func, modules=["numpy"])
        self._der = dict()
    
    def der(self, ord):
        if(ord not in self._der):
            _derk = self._my_func
            for _ in range(ord):
                _derk = sympy.diff(self._my_func, self._my_symbols['x'])
            self._der[ord] = self.__class__(function = _derk)
        return self._der[ord]