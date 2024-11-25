#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// implemente la evaluación de expresiones aritméticas considerando los operadores +,-,*,/ y
//los operando pueden ser ingresados en notación científica (125e25,5e-8 para denotar 12x1025
//,5x10-8 respectivamente), la entrada al programa será una cadena de caracteres con la expresión,
//ejemplo de expresión a evaluar: (125e10 – 1e15)/5e-85*15.


// Declaración de funciones
double valueFactor(const char **expresion);
double evaluarTermino(const char **expresion);
double evaluar(const char **expresion);


// Función principal para evaluar la expresión matemática
double evaluar(const char **expresion) {
    double resultado = evaluarTermino(expresion); // Llama a evaluarTermino para obtener el primer término de la expresión

    // Procesa los operadores + y - en la expresión
    while (**expresion) {
        char operador = **expresion;

        if (operador != '+' && operador != '-') {
            break;
        }

        (*expresion)++; // Avanza al siguiente carácter

        double siguienteTermino = evaluarTermino(expresion); // Obtiene el siguiente término de la expresión

        // Realiza la operación correspondiente según el operador encontrado
        switch (operador) {
            case '+':
                resultado += siguienteTermino;
                break;
            case '-':
                resultado -= siguienteTermino;
                break;
        }
    }

    return resultado; // Devuelve el resultado de la evaluación de la expresión
}

// Función para evaluar un término de la expresión
double evaluarTermino(const char **expresion) {
    double resultado = valueFactor(expresion); // Obtiene el primer factor del término

    // Procesa los operadores * y / en el término
    while (**expresion) {
        char operador = **expresion;

        if (operador != '*' && operador != '/' && !isspace(operador)) {
            break;
        }

        if (operador == ' ') {
            (*expresion)++;
            continue; // Salta al siguiente carácter si es un espacio en blanco
        }

        (*expresion)++; // Avanza al siguiente carácter

        double siguienteFactor = valueFactor(expresion); // Obtiene el siguiente factor

        // Realiza la operación correspondiente según el operador encontrado
        switch (operador) {
            case '*':
                resultado *= siguienteFactor;
                break;
            case '/':
                if (siguienteFactor != 0) {
                    resultado /= siguienteFactor;
                } else {
                    printf("Error: División por cero.\n");
                    exit(EXIT_FAILURE);
                }
                break;
        }
    }

    return resultado; // Devuelve el resultado del término evaluado
}

// Función para obtener el valor de un factor en la expresión
double valueFactor(const char **expresion) {
    double resultado;

    // Salta los espacios en blanco
    while (isspace(**expresion)) {
        (*expresion)++;
    }

    if (**expresion == '(') {
        (*expresion)++; // Avanza al siguiente carácter
        resultado = evaluar(expresion); // Evalúa la expresión dentro de paréntesis
        (*expresion)++; // Avanza al siguiente carácter después del paréntesis de cierre
    } else {
        char *endptr;
        resultado = strtod(*expresion, &endptr); // Convierte el número en punto flotante
        *expresion = endptr; // Actualiza la posición del puntero en la expresión

    }

    return resultado; // Devuelve el valor del factor
}

// Función principal
int main() {
    const char *expresion = "(125e10 - 1e15) / (5e-85 * 15)";
    double resultado = evaluar(&expresion); // Evalúa la expresión y guarda el resultado
    printf("Resultado de la expresión: %.9e\n", resultado); // Imprime el resultado

    return 0; // Retorna 0 para indicar que el programa se ejecutó correctamente
}