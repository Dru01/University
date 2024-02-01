import math
import sympy
import numpy as np
from realfunction import RealFunction
import plotly.graph_objects as go

def NewtonRaphson(x0, f, iterMax, tol, tmin = None, tmax = None):
    xk  = x0
    res = 0
    for k in range(iterMax):
        fk = float(f(xk))
        if fk<tol and fk>-tol:
            res = 1
            break
        else:
            dfk = float(f.der(1)(xk))
            if dfk!=0:
                xk = xk - fk/dfk
                if(tmin != None):
                    xk = max(xk, tmin)
                if(tmax != None):
                    xk = min(xk, tmax)
            else:
                res = -1
                break
    return xk,k,res

def c_1(frec):
    return sum((frec[0][j]+1)*frec[1][j] for j in range(len(frec[0])))
def c_2(frec):
    return sum(frec[1][j] for j in range(len(frec[0])))

def main():
    
    frec = np.array([[0,1,2,3,4],[147,36,13,4,0]])
    f = RealFunction(expression = "-{}".format(c_1(frec)) + "/(exp(x)-1) + " + "{}".format(c_2(frec))+"/x")
    iterMax = int(1e6)
    tol = 1e-5
    x0 = 0.1
    xk,k,res = NewtonRaphson(x0 = x0, iterMax = iterMax, f = f, tol = tol)
    
    print("Para la funcion real f(x) = {}\nCon punto inicial x0 = {}, donde f(x0) = {}".format(f._my_func, x0, f(x0)))

    print("\tEl metodo de Newton, obtuvo res = {}, es decir:\n".format(res))
    if res==1:
        print('\t\tEncontro una raiz cerca de xk = {}\n\t\tdonde f(xk) = {},\n\t\ten {} iteraciones'.format(xk,f(xk), k))
    elif res==0:
        print('\t\tNo converje.')
        return
    else:
        print('\t\tSe cancelo la derivada en algun momento')
        return
    print("")
    
    emv_lambda = xk
    n = sum(frec[1])
    print("Las frecuencias esperados son:")
    print("No. defectuosos", frec[0])
    print("frec. obs.", frec[1])
    print("frec. esp.", np.concatenate((np.round([(1-math.exp(-xk))**(j+1)/((j+1)*xk)*n for j in range(4)], 1), np.round([(1-sum((1-math.exp(-xk))**(j+1)/((j+1)*xk) for j in range(4)))*n],1))))
    print("")

    p = 0.1
    f = RealFunction(expression = "{}".format(c_1(frec)) + "*log(1-exp(-x)) - " + "{}".format(c_2(frec)) + "*log(x)")
    g = RealFunction(function = f._my_func - f(emv_lambda) - math.log(p))
    xk,k,res = NewtonRaphson(emv_lambda + 0.001, g, iterMax, tol, tmin = emv_lambda, tmax = 1)
    R_lambda_tmax = xk
    xk,k,res = NewtonRaphson(emv_lambda - 0.001, g, iterMax, tol, tmin = 0.000001, tmax = emv_lambda)
    R_lambda_tmin = xk
    print("El intervalo de verosimilitud del {}% es: [{},{}]".format(p*100, R_lambda_tmin, R_lambda_tmax))

if __name__ == "__main__":
    main()