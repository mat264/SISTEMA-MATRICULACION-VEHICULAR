//DEFINICIÓN DE LA ESTRUCTURA VEHÍCULO E IMPLEMENTACION DE FUNCIONES Y VALIDACIONES BÁSICAS//

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_VEHICULOS 100

typedef struct {
	char placa[20];     
	char cedula[15];    
	int anio;
	char tipo[20];      
	float avaluo;
} Vehiculo;

int validarPlaca(const char* placa) {
	int len = strlen(placa);
	if (len < 6 || len > 7) return 0;
	for (int i = 0; i < 3; i++) {
		if (!isalpha(placa[i])) return 0;
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
	while (!valido && intentos < 3) {
		printf("Ingrese la placa vehicular (ej: ABC1234): ");
		scanf("%19s", v.placa);
		if (validarPlaca(v.placa)) {
			valido = 1;
		} else {
			printf("Placa inválida. Debe tener 3 letras seguidas de 3-4 dígitos.\n");
		}
		intentos++;
	}
	
	valido = 0; intentos = 0;
	while (!valido && intentos < 3) {
		printf("Ingrese el número de cédula del Propietario: ");
		scanf("%14s", v.cedula);
		if (strlen(v.cedula) != 10) {
			printf("Cédula inválida!!!. Debe tener exactamente 10 dígitos.\n");
			intentos++;
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
		intentos++;
	}
	
	valido = 0; intentos = 0;
	while (!valido && intentos < 3) {
		printf("Ingrese el tipo de vehículo (M o C): ");
		scanf("%19s", v.tipo);
		if (strcmp(v.tipo, "M") == 0 || strcmp(v.tipo, "C") == 0) {
			valido = 1; 
		} else {
			printf("Tipo de vehículo inválido!!!. Debe ser 'M' para motocicleta o 'C' para carro.\n");
		}
		intentos++;
	}
	
	valido = 0; intentos = 0;
	while (!valido && intentos < 3) {
		printf("Ingrese el año del vehículo: ");
		scanf("%d", &v.anio);
		if (v.anio >= 1995 && v.anio <= 2025){
			valido = 1;
		} else {
			printf("Año inválido!!!. Debe ser un número entre 1995 y 2025.\n");
		}
		intentos++;
	}
	
	valido = 0; intentos = 0;
	while (!valido && intentos < 3) {
		printf("Ingrese el avalúo del vehículo: ");
		scanf("%f", &v.avaluo);
		if (v.avaluo > 0) {
			valido = 1;
		} else {
			printf("Avalúo inválido!!!. Debe ser un número positivo.\n");
		}
		intentos++;
	}
	
	return v;
}

int main() {
	Vehiculo nuevo = registrarVehiculo();
	
	const char* tipoTexto = (strcmp(nuevo.tipo, "M") == 0) ? "motocicleta" : "vehículo";
	const char* articulo = (strcmp(nuevo.tipo, "M") == 0) ? "de la" : "del";
	
	printf("\n----Datos Registrados----\n");
	printf("Placa %s %s: %s\n", articulo, tipoTexto, nuevo.placa);
	printf("Número de cédula del propietario: %s\n", nuevo.cedula);
	printf("Tipo de vehículo: %s\n", nuevo.tipo);
	printf("Año %s %s: %d\n", articulo, tipoTexto, nuevo.anio);
	printf("Avalúo %s %s: %.2f\n", articulo, tipoTexto, nuevo.avaluo);
	
	return 0;
}
