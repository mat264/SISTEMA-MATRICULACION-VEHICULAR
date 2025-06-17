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
			printf("Placa inválida. Debe tener 3 letras mayúsculas seguidas y de 3-4 dígitos.\n");
			
		}
	}
	
	limpiarPantalla();
	
	valido = 0; 
	while (!valido) {
		printf("Ingrese el número de cédula del Propietario: ");
		scanf("%14s", v.cedula);
		if (strlen(v.cedula) != 10) {
			printf("Cédula inválida!!!. Debe tener exactamente 10 dígitos.\n");
			continue; 
			
		}
		
		
		valido = 1;
		for (int i = 0; i < 10; i++) {
			if (!isdigit(v.cedula[i])) {
				printf("Cédula inválida!!!. Debe contener solo dígitos.\n");
				valido = 0;
				break; 
				
			}
		}
		
	}
	
	limpiarPantalla();
	
	valido = 0;
	while (!valido) {
		printf("Ingrese el año del vehiculo:");
		
		// Verificar si scanf pudo leer un entero correctamente
		
		if (scanf("%d", &v.anio) == 1) {
			// scanf exitoso, verificar rango
			if (v.anio >= 1995 && v.anio <= 2025) {
				valido = 1;
			} else {
				printf("Año inválido. Ingrese uno entre 1995 y 2025");
			}
		} else {
			// scanf falla (entrada no numerica)
			printf("Error: Debe ingresar solo números. No se permiten letras o caracteres especiales.\n");
			
			// Limpiar el buffer de entrada
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
		}
		
	}
	
	limpiarPantalla();
	
	valido = 0; 
	while (!valido) {
		printf("Ingrese el avalúo del vehículo: ");
		scanf("%f", &v.avaluo);
		if (v.avaluo > 0) {
			valido = 1;
		} else {
			printf("Avalúo inválido!!!. Debe ser un número positivo.\n");
		}
		
	}
	
	limpiarPantalla();
	
	
	
	return v;
	
}

