// [CAP.7] utilidades.h - Funciones genericas de proposito general
#pragma once

// [CAP.7] "template<typename T>" declara que esta funcion esta
// [CAP.7] parametrizada por un tipo T, que se determina automaticamente
// [CAP.7] a partir de los argumentos con los que se llame.
template<typename T>
T restringir(T valor, T minimo, T maximo) {
    if (valor < minimo) {
        return minimo;
    }
    if (valor > maximo) {
        return maximo;
    }
    return valor;
}

template<typename T>
T maximo(T a, T b) {
    return (a < b) ? b : a;
}
