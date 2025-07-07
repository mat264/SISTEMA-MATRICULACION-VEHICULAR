#include "validaciones.h"
#include "calculos.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Funci?n para limpiar consola ("cls" para windows, "clear" para linux)
void limpiarPantalla() {
    system("clear");
}

// Valida el formato de la placa
int validarPlaca(const char* placa) {
    int len = strlen(placa);
    if (len < 6 || len > 7) return 0;
    for (int i = 0; i < 3; i++) {
        if (!isupper(placa[i])) return 0;
    }
    for (int i = 3; i < len; i++) {
        if (!isdigit(placa[i])) return 0;
    }
    return 1;
}

void mostrarVehiculo(Vehiculo v) {
    printf("----Datos del Vehiculo----\n");
    printf("Placa: %s\n", v.placa);
    printf("Numero de cedula del propietario: %s\n", v.cedula);
    printf("Año: %d\n", v.anio);
    printf("Avaluo: $%.2f\n", v.avaluo);
    printf("Matricula: $%.2f\n", v.matricula);
    printf("-------------------------\n");
}

Vehiculo registrarVehiculo() {
    Vehiculo v;
    int valido = 0;
    
    // Validar placa
    valido = 0;
    while (!valido) {
        printf("Ingrese la placa vehicular (EJEMPLO: XYZ567): ");
        scanf("%19s", v.placa);
        if (validarPlaca(v.placa)) {
            valido = 1;
        } else {
            printf("Placa invalida. Debe tener 3 letras mayusculas seguidas y de 3-4 digitos.\n");
        }
    }
    
    limpiarPantalla();
    
    // Validar cedula
    valido = 0; 
    while (!valido) {
        printf("Ingrese el numero de cedula del Propietario: ");
        scanf("%14s", v.cedula);
        if (strlen(v.cedula) != 10) {
            printf("Cedula invalida!!!. Debe tener exactamente 10 digitos.\n");
            continue; 
        }
        
        valido = 1;
        for (int i = 0; i < 10; i++) {
            if (!isdigit(v.cedula[i])) {
                printf("Cedula invalida!!!. Debe contener solo digitos.\n");
                valido = 0;
                break; 
            }
        }
    }
    
    limpiarPantalla();
    
    // Validar año
    valido = 0;
    while (!valido) {
        printf("Ingrese el año del vehiculo: ");
        
        if (scanf("%d", &v.anio) == 1) {
            if (v.anio >= 1995 && v.anio <= 2025) {
                valido = 1;
            } else {
                printf("Año invalido. Ingrese uno entre 1995 y 2025\n");
            }
        } else {
            printf("Error: Debe ingresar solo numeros. No se permiten letras o caracteres especiales.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    
    limpiarPantalla();
    
    // Validar avaluo
    valido = 0; 
    while (!valido) {
        printf("Ingrese el avaluo del vehiculo: $");
        if (scanf("%f", &v.avaluo) == 1) {
            if (v.avaluo > 0 && v.avaluo <= 1000000) {
                valido = 1;
            } else {
                printf("Avaluo invalido!!!. Debe ser un numero entre 0 y 1000000.\n");
            }
        } else {
            printf("Error: Debe ingresar un numero valido.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    
    limpiarPantalla();
    
    // Preguntar numero de revisiones
    valido = 0;
    while (!valido) {
        printf("Ingrese el numero de revisiones realizadas (0-3): ");
        if (scanf("%d", &v.revisiones) == 1) {
            if (v.revisiones >= 0 && v.revisiones <= 3) {
                valido = 1;
            } else {
                printf("Numero de revisiones invalido. Debe ser entre 0 y 3.\n");
            }
        } else {
            printf("Error: Debe ingresar un numero valido.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    
    limpiarPantalla();
    
    // Preguntar numero de multas
    valido = 0;
    while (!valido) {
        printf("Ingrese el numero de multas pendientes: ");
        if (scanf("%d", &v.multas) == 1) {
            if (v.multas >= 0 && v.multas <= 10) {
                valido = 1;
            } else {
                printf("Numero de multas invalido. Debe ser un numero entre 0 y 10\n");
            }
        } else {
            printf("Error: Debe ingresar un numero valido.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    
    // Calcular la matricula 
    calcularMatricula(&v);
    limpiarPantalla();
    
    return v;
}

// Agrega vehiculos, maximo 100
void agregarVehiculo(Vehiculo vehiculos[], int* totalVehiculos, Vehiculo nuevoVehiculo) {
    if (*totalVehiculos < MAX_VEHICULOS) {
        vehiculos[*totalVehiculos] = nuevoVehiculo;
        (*totalVehiculos)++;
        printf("Vehiculo registrado exitosamente!\n");
    } else {
        printf("Error: No se pueden registrar mas vehiculos. Limite alcanzado.\n");
    }
}

// Imprime en consola la lista de todos los vehiculos registrados hasta el momento
void listarVehiculos(Vehiculo vehiculos[], int totalVehiculos) {
    if (totalVehiculos == 0) {
        printf("No hay vehiculos registrados.\n");
        return;
    }
    
    printf("\n=== LISTA DE VEHICULOS MATRICULADOS ===\n");
    printf("Total de vehículos: %d\n\n", totalVehiculos);
    
    for (int i = 0; i < totalVehiculos; i++) {
        printf("Vehículo #%d:\n", i + 1);
        mostrarVehiculo(vehiculos[i]);
        printf("\n");
    }
}

// Busca vehiculos segun la placa exacta
int buscarVehiculoPorPlaca(Vehiculo vehiculos[], int totalVehiculos, const char* placa) {
    for (int i = 0; i < totalVehiculos; i++) {
        if (strcmp(vehiculos[i].placa, placa) == 0) {
            return i; // Retorna el del veh?culo encontrado
        }
    }
    return -1; // No encontrado
}
