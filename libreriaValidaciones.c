#include "libreriaValidaciones.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

void limpiarPantalla() {
	system("cls");
}






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

Vehiculo registrarVehiculo() {
	Vehiculo v;
	int valido = 0, intentos = 0;
	
	valido = 0; intentos = 0;
	while (!valido) {
		printf("Ingrese la placa vehicular (EJEMPLO: ABC1234): ");
		scanf("%19s", v.placa);
		if (validarPlaca(v.placa)) {
			valido = 1;
		} else {
			printf("Placa inv�lida. Debe tener 3 letras may�sculas seguidas y de 3-4 d�gitos.\n");
			
		}
	}
	
	limpiarPantalla();
	
	valido = 0; 
	while (!valido) {
		printf("Ingrese el n�mero de c�dula del Propietario: ");
		scanf("%14s", v.cedula);
		if (strlen(v.cedula) != 10) {
			printf("C�dula inv�lida!!!. Debe tener exactamente 10 d�gitos.\n");
			continue; 
			
		}
		
		
		valido = 1;
		for (int i = 0; i < 10; i++) {
			if (!isdigit(v.cedula[i])) {
				printf("C�dula inv�lida!!!. Debe contener solo d�gitos.\n");
				valido = 0;
				break; 
				
			}
		}
		
	}
	
	limpiarPantalla();
	
	valido = 0;
	while (!valido) {
		printf("Ingrese el a�o del vehiculo:");
		
		// Verificar si scanf pudo leer un entero correctamente
		
		if (scanf("%d", &v.anio) == 1) {
			// scanf exitoso, verificar rango
			if (v.anio >= 1995 && v.anio <= 2025) {
				valido = 1;
			} else {
				printf("A�o inv�lido. Ingrese uno entre 1995 y 2025");
			}
		} else {
			// scanf falla (entrada no numerica)
			printf("Error: Debe ingresar solo n�meros. No se permiten letras o caracteres especiales.\n");
			
			// Limpiar el buffer de entrada
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
		
	}
	
	limpiarPantalla();
	
	valido = 0; 
	while (!valido) {
		printf("Ingrese el aval�o del veh�culo: ");
		scanf("%f", &v.avaluo);
		if (v.avaluo > 0) {
			valido = 1;
		} else {
			printf("Aval�o inv�lido!!!. Debe ser un n�mero positivo.\n");
		}
		
	}
	
	limpiarPantalla();
	
	
	
	return v;
	
}

