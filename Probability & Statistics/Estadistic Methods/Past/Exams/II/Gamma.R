rm(list=ls())

# FUNCIONES PARA GRÁFICAS PP Y QQ PARA LA GAMMA

# Gráfica PP Gamma
pp_plot = function(Y, param, confidence){
  bg <- param[1]
  sg <- 1/param[2]
  Y = pgamma(sort(Y), bg, sg)
  X = c(1:n)/(n+1)
  plot(X, Y,
       main = "Gráfica PP (Gamma)",
       xlab = "Probabilidades empíricas",
       ylab = "Probabilidades teóricas",
       pch = 19, cex=0.3)
  abline(a = 0, b = 1, col = "red", lwd = 2)
  points(X, qbeta((1 - confidence)/2, 1:n, n + 1 - 1:n),
         type = "l",
         lty = 2)
  points(X, qbeta((1 + confidence)/2, 1:n, n + 1 - 1:n),
         type = "l",
         lty = 2)
}

# Gráfica QQ Gamma
qq_plot = function(X, param, confidence) {
  bg <- param[1]
  sg <- 1/param[2]
  Y = sort(X)
  X = qgamma(c(1:n)/(n+1), bg, sg)
  plot(X, Y,
       main = "Gráfica QQ (Gamma)",
       xlab = "Probabilidades teóricas",
       ylab = "Probabilidades empíricas",
       pch = 19, cex=0.3)
  abline(a = 0, b = 1, col = "red", lwd = 2)
  points(X, qgamma(qbeta((1 - confidence)/2, 1:n, n + 1 - 1:n),
                     bg, sg),
         type = "l",
         lty = 2)
  points(X, qgamma(qbeta((1 + confidence)/2, 1:n, n + 1 - 1:n),
                     bg, sg),
         type = "l",
         lty = 2)
}

# PARA LA GAMMA

emv_Gamma <- function(vec, mat_y){
  # lv estima la logver en parámetros específicos cuando hay censura
  lv <- function(params){
    a <- params[1]
    b <- 1/params[2]
    if(b > 0 && a > 0){
      # Diferencias de distribuciones Gamma
      difvec <- pgamma(mat_y[,2],a,b) - pgamma(mat_y[,1],a,b)
      k <- 0.000001
      Zvec <- ((difvec < k)*(k - difvec)) + difvec
      lnZ <- log(Zvec)
      lv <- sum(lnZ)
    }
    else{
      lv = -9999999999999999;
    }
    lv = -lv
    return(lv)
  }
  emv <- optim(vec, lv)$par
  return(emv)
}

# MUESTRAS SIMULADAS FINAS

set.seed(1000000)

datosFinos <- function(params, mat_y, n){
  a <- params[1]
  b <- 1/params[2]
  ancho <- pgamma(mat_y[,2], a, b) - pgamma(mat_y[,1], a, b)
  U <- runif(n)
  Z <- pgamma(mat_y[,1], a, b) + (U * ancho)
  X_ast <- qgamma(Z, a, b)
  return(X_ast)
}

simular_cia <- function(param_emv) {
  simulacion <- datosFinos(param_emv, mat_y, n)
  w <- lv_Y_usual(param_emv, simulacion)
  return(-2*w + 2*k)
}

f_Y <- function(y, param) {
  alpha  <- param[1]
  beta <- param[2]
  return(dgamma(y, alpha, 1/beta))
}

lv_Y_usual <- function(param, y) {
  return(sum(log(f_Y(y, param))))
}

# PROGRAMA PRINCIPAL

# Datos originales
y <- scan("datos.txt")

# Matrices de intervalos de censura para datos y logdatos
mat_y <- cbind(y-1, y)
mat_x <- log(mat_y)

# Cálculo de estimadores de momentos para los datos censurados
x <- y
n <- length(x)
xb <- sum(x)/n
S2 <- sum((x-xb)^2)/n

alpha_t <- xb^2/S2
beta_t <- S2/xb
c(alpha_t, beta_t)

# Cálculo de estimadores de máxima verosimilitud para los datos censurados

emv<- emv_Gamma(c(alpha_t,beta_t), mat_y)
alpha_emv <- emv[1]
beta_emv <- emv[2]
c(alpha_emv, beta_emv)

#_______________________________________________________________________________
# GRÁFICAS PP Y QQ, Y CIA ######################################################

# Gráficas PP y QQ -------------------------------------------------------------
X_ast <- datosFinos(c(alpha_emv, beta_emv), mat_y, n)

pp_plot(X_ast, c(alpha_emv, beta_emv), 0.95)
qq_plot(X_ast, c(alpha_emv, beta_emv), 0.95)

# Criterio de Información de Akaike ________________________________________

no_sim <- 1000 # no. de simulaciones
k <- 2         # no. de parámetros

simulaciones <- replicate(no_sim, simular_cia(c(alpha_emv, beta_emv)))
cia <- mean(simulaciones)
cia
