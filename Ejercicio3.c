#include <stdio.h>
#include <string.h>

//Dado una cadena C con un programa en un lenguaje L, donde en la cadena E se encuentra
//las palabras reservadas de L, muestre un resumen indicando la cantidad de palabras reservadas
//de L en C.

#define MAX_PALABRAS 7
#define MAX_LARGO 1000

int contarPalabrasReservadas(const char *codigo, const char *palabrasReservadas[], int numPalabras) {
    int contador = 0;
    const char *delimitadores = " \n\t;(){}[],."; // Definimos los delimitadores que habrán en el código a evaluar

    const char *coincidencia = codigo;

    while (*coincidencia) {
        size_t longitud = strcspn(coincidencia, delimitadores); // Obtenemos la longitud hasta encontrar el siguiente delimitador

        // Verificamos si el la coincidencia encontrada es una palabra reservada
        for (int i = 0; i < numPalabras; i++) {
            if (strncmp(coincidencia, palabrasReservadas[i], longitud) == 0 && strlen(palabrasReservadas[i]) == longitud) {
                contador++;
                break;
            }
        }

        coincidencia += longitud;
        coincidencia += strspn(coincidencia, delimitadores); // Saltamos los delimitadores porque no se evaluaran a nivel de resultado final
    }

    return contador;
}

int main() {
    const char *palabrasReservadas[MAX_PALABRAS] = {"int", "float", "if", "else", "for", "while", "return"};
    const char *codigo = 
        "int main() {\n"
        "    float x = 5.0;\n"
        "    if (x > 0) {\n"
        "        return 1;\n"
        "    } else {\n"
        "        for (int i = 0; i < 10; i++) {\n"
        "            while (x > 0) {\n"
        "                x--;\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "}\n";

    int cantidad = contarPalabrasReservadas(codigo, palabrasReservadas, MAX_PALABRAS);
    printf("Cantidad de palabras reservadas: %d\n", cantidad);

    return 0;
}