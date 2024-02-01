library(stats)

sum_probability <- 0.9

target_probability <- (1-sum_probability)/2

tmin <- -1

while(pt(tmin, 9) > target_probability)
{
  tmin <- tmin * 2
}

tmax <- 0

while((tmax - tmin) > 1e-15)
{
  prom <- (tmax + tmin) / 2
  
  if(pt(prom,9) < target_probability)
  {
    tmin <- prom
  } else
    tmax <- prom
}

b <- tmax

a <- -2

tmin <- 0

tmax <- 1

if(pt(a,9) + sum_probability > 1)
  print("No existe c")

target_probability <- sum_probability+pt(a,9)

while(pt(tmax, 9) < target_probability)
{
  tmax <- tmax * 2
}

while((tmax - tmin) > 1e-15)
{
  prom <- (tmax + tmin) / 2
  
  if(pt(prom,9) < target_probability)
  {
    tmin <- prom
  } else
    tmax <- prom
}

c <- tmax

cat("Los valores de a,b,c respectivamente son respectivamente\n", a, b, c)

if((c-a) > 2*b)
{
  cat("Se cumple que |c-a|>2b")
} else
  cat("No se cumple que |c-a|>2b")

options(digits=10)
