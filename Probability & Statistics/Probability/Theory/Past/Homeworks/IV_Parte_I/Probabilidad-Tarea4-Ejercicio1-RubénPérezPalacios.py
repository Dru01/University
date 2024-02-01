#Hecho por: Ricardo Alberto Gloria Picazzo

from scipy import stats 
import math as ma


#función inversa de una normal
a = stats.norm.ppf(0.025) 
b = stats.norm.ppf(0.975)

print("a = ", a, "\nb = ", b)


#Media muestral de los 718 datos    

    #Leer datos del archivo
f = open("tarea4e3.txt", "r")


s = 0 #suma de los 718 datos
for x in f.readlines():
    y1 =  x.split(" ")[1]
    y2 = y1.split("\n")[0]
    s = s + int(y2)
f.close()

d = 718 #No. de datos

med = s/718 #media muestral 

print("Media Muestral =", med)

#Calculemos el intervalo de 95% de confianza (i, f)

i = med - b*( (ma.sqrt(med))/ma.sqrt(d) )
f = med - a*( (ma.sqrt(med))/ma.sqrt(d) )

print("El intervalo de confinaza es: (", i, ",", f, ")")
