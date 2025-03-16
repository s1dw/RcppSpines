degree <- 4
order = 50
t = seq(0.1, 10, 0.1)
knots = c(rep(min(t) - 1e-3, order), 2, 5, 7, rep(max(t) + 1e-3, order))
X = bSpline(p = order, k = knots, x = t)
par(mar = c(0.8, 1, -1, -1) + 4, family = "Palatino")
plot(NA, main = paste('order = ', order), xlab = expression(x), ylab = expression(f(x)),
     xlim = c(min(t), max(t)), ylim = c(0, 1))
for (i in 1:dim(X)[2]) {
  lines(t, X[, i], ty = 'l')
}
abline(v = knots, col = 4, lty = 3)
