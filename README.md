# RcppSplines

## 簡介
`RcppSplines` 是一個基於 `Rcpp` 實作的 R 套件，提供高效能的 **M-spline**, **B-spline**, 和 **I-spline** 計算方法。本專案的目標是為 R 用戶提供更快、更靈活的樣條函數運算，適用於統計建模、數據擬合與機器學習。

## 特色
- **高效能**：透過 C++ 搭配動態規劃（Dynamic programming）實作，提高計算速度。
- **多樣性**：支援 M-spline、B-spline、I-spline。

## 安裝
- **For MacOS User:**  
事先安裝Xcode套件   

- **For Ｗindow User:**  
事先安裝Xcode套件 devtools
```r
if (!requireNamespace("devtools", quietly = TRUE)) install.packages("devtools")
```
## 使用方法

### 加載套件
```r
# 事先使用 source 編譯 cpp 檔
library(RcppSplines)
```

### 生成 spline basis fuction
```r
### B-spline 
t = seq(0.1, 10, 0.1)
order = 50
knots = c(rep(min(t) - 1e-3, order), 2, 5, 7, rep(max(t) + 1e-3, order))
X = bSpline(p = order, k = knots, x = t)

par(mar = c(0.8, 1, -1, -1) + 4, family = "Palatino")
plot(NA, main = paste('order = ', order), xlab = expression(x), ylab =      
expression(f(x)), xlim = c(min(t), max(t)), ylim = c(0, 1))
for (i in 1:dim(X)[2]) {
  lines(t, X[, i], ty = 'l')
}
abline(v = knots, col = 4, lty = 3)
```

