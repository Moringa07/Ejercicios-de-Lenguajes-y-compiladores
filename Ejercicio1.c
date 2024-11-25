#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// 1) Dado una cadena M, cuente los números reales de la forma: a) a.bbbb, donde a: es un
//número entre 1 y 999, y b: entre 0 y 9. 

//declaracion de funciones 
int validacion_numero(const char *numero);
int cont_numeros(const char *cadena);

int validacion_numero(const char *numero) {
    // Verificamos que el número se encuentre con el formato a.bbbb
    int punto_encontrado = 0;
    int i = 0;

    // Verificamos los parámetros del numero antes del punto (esté entre 1 y 999)
    while (isdigit(numero[i])) {
        i++;
    }

    // Nos aseguramos de que 'a' no sea vacío y que no tenga más de 3 dígitos
    if (i == 0 || i > 3) 
    return 0;

    // Verificamos el punto decimal del numero a evaluar en la cadena
    if (numero[i] == '.') {
        punto_encontrado = 1;
        i++;
    } else {
        return 0; // No hay punto decimal
    }

    // Ahora verificamos que 'b' tenga exactamente los 4 dígitos después del punto 
    for (int j = 0; j < 4; j++) {
        if (!isdigit(numero[i + j])) {
            return 0; // No es un dígito válido
        }
    }

    // Nos aseguramos de que no haya más caracteres después de 'bbbb'
    if (numero[i + 4] != '\0') {
        return 0;
    }

    return 1; // El número es válido
}

int cont_numeros(const char *cadena) {
    int contador = 0;
    char *coincidencia;
    char cadena_copia[1000];

    // Hacemos una copia de la cadena para dividir en identificadores 
    strcpy(cadena_copia, cadena);

    // Usar strtok para separar la cadena en identificadores
    coincidencia = strtok(cadena_copia, " ,;"); // Separar por espacios, comas y punto y coma

    while (coincidencia != NULL) {
        if (validacion_numero(coincidencia)) {
            contador++; // Incrementar contador por cada coincidencia
        }
        coincidencia = strtok(NULL, " ,;"); // Obtener el siguiente token
    }

    return contador;
}

int main() {
    char cadena[1000];

    // Leer la cadena de entrada
    printf("Introduce la cadena: ");
    fgets(cadena, sizeof(cadena), stdin);
    
    // Eliminar el salto de línea al final de la cadena
    cadena[strcspn(cadena, "\n")] = 0;

    // Contar los números en la cadena
    int cantidad = cont_numeros(cadena);
    
    printf("Total de numeros con el formato a.bbbb: %d\n", cantidad);

    return 0;
}