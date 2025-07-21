#include "validaciones.h"
#include "calculos.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Funcion para limpiar consola ("cls" para windows, "clear" para linux)
void limpiarPantalla() {
	system("cls");
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
	printf("Anio: %d\n", v.anio);
	printf("Avaluo: $%.2f\n", v.avaluo);
	printf("Matricula: $%.2f\n", v.matricula);
	printf("-------------------------\n");
}

// Función para guardar un vehículo en el archivo
void guardarVehiculoEnArchivo(Vehiculo v) {
	FILE* archivo = fopen(ARCHIVO_VEHICULOS, "a");
	if (archivo == NULL) {
		printf("Error: No se pudo abrir el archivo para guardar.\n");
		return;
	}
	
	// Formato: placa:cedula:anio:avaluo:matricula
	fprintf(archivo, "%s:%s:%d:%.2f:%.2f\n", 
		v.placa, v.cedula, v.anio, v.avaluo, v.matricula);
	
	fclose(archivo);
}

// Función para cargar vehículos desde el archivo
int cargarVehiculosDesdeArchivo(Vehiculo vehiculos[]) {
	FILE* archivo = fopen(ARCHIVO_VEHICULOS, "r");
	if (archivo == NULL) {
		// Si no existe el archivo, no es error, solo no hay vehículos guardados
		return 0;
	}
	
	int totalVehiculos = 0;
	char linea[200];
	
	while (fgets(linea, sizeof(linea), archivo) && totalVehiculos < MAX_VEHICULOS) {
		// Remover el salto de línea al final
		linea[strcspn(linea, "\n")] = 0;
		
		// Lee la línea usando strtok para leer hasta encontrar :
		char* token = strtok(linea, ":");
		if (token != NULL) {
			strcpy(vehiculos[totalVehiculos].placa, token);
			
			token = strtok(NULL, ":");
			if (token != NULL) {
				strcpy(vehiculos[totalVehiculos].cedula, token);
				
				token = strtok(NULL, ":");
				if (token != NULL) {
					vehiculos[totalVehiculos].anio = atoi(token);
					
					token = strtok(NULL, ":");
					if (token != NULL) {
						vehiculos[totalVehiculos].avaluo = atof(token);
						
						token = strtok(NULL, ":");
						if (token != NULL) {
							vehiculos[totalVehiculos].matricula = atof(token);
							totalVehiculos++;
						}
					}
				}
			}
		}
	}
	
	fclose(archivo);
	return totalVehiculos;
}

Vehiculo registrarVehiculo() {
	Vehiculo v;
	int valido = 0;
	
	// Validar placa
	valido = 0;
	while (!valido) {
		printf("Ingrese la placa vehicular (EJEMPLO: XYZ567): \n");
		scanf("%19s", v.placa);
	
		// Conversión a mayúsculas para validar correctamente 
		for (int i = 0; v.placa[i]; i++) {
			v.placa[i] = toupper(v.placa[i]);
		}
		if (validarPlaca(v.placa)) {
			valido = 1;
		} else {
			printf("Placa invalida. Debe tener 3 letras mayusculas seguidas y de 3-4 digitos.\n");
			printf("Presione enter para continuar\n");
			getchar(); getchar();
			limpiarPantalla();
		}
	}
	
	limpiarPantalla();
	
	// Validar cedula
	valido = 0; 
	while (!valido) {
		printf("Ingrese el numero de cedula del Propietario: \n");
		scanf("%14s", v.cedula);
		if (strlen(v.cedula) != 10) {
			printf("Cedula invalida. Debe tener exactamente 10 digitos.\n");
			printf("Presione enter para continuar\n");
			getchar(); getchar(); 
			limpiarPantalla();	
			continue; 
		}
		
		valido = 1;
		for (int i = 0; i < 10; i++) {
			if (!isdigit(v.cedula[i])) {
				printf("Cedula invalida. Debe contener solo digitos.\n");
				valido = 0;
				printf("Presione enter para continuar\n");
				getchar(); getchar(); 
				limpiarPantalla();
				break; 
			}
			
		}
	}
	
	limpiarPantalla();
	
	// Validar anio
	valido = 0;
	while (!valido) {
		printf("Ingrese el anio del vehiculo: \n");
		
		if (scanf("%d", &v.anio) == 1) {
			if (v.anio >= 1995 && v.anio <= 2025) {
				valido = 1;
			} else {
				printf("Anio invalido. Ingrese uno entre 1995 y 2025\n");
				printf("Presione enter para continuar\n");
				getchar(); getchar(); 
				limpiarPantalla();
			}
		} else {
			printf("Error: Debe ingresar solo numeros. No se permiten letras o caracteres especiales.\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Presione enter para continuar\n");
			getchar();
			limpiarPantalla();
		}
	}
	
	limpiarPantalla();
	
	// Validar avaluo
	valido = 0; 
	while (!valido) {
		printf("Ingrese el avaluo del vehiculo: $\n");
		if (scanf("%f", &v.avaluo) == 1) {
			if (v.avaluo > 1000 && v.avaluo <= 1000000) {
				valido = 1;
			} else {
				printf("Avaluo invalido. Debe ser un numero entre 1000 y 1000000.\n");
				printf("Presione enter para continuar\n");
				getchar(); getchar(); 
				limpiarPantalla();
			}
		} else {
			printf("Error: Debe ingresar un numero valido.\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			printf("Presione enter para continuar\n");
			getchar(); getchar(); 
			limpiarPantalla();
		}
	}
	
	limpiarPantalla();
	
	// Validar numero de revisiones
	valido = 0;
	while (!valido) {
		printf("Ingrese el numero de revisiones (0-3): \n");
		if (scanf("%d", &v.revisiones) == 1) {
			// Verificación especial si es 0 (corrección solicitada)
			if (v.revisiones == 0) {
				printf("Debe cumplir al menos una revision para matricularse.\n");
				getchar(); getchar(); // limpiar buffer y esperar ENTER
				v.anio = -1; // marcamos inválido para que el main lo descarte
				return v;
			} else if (v.revisiones >= 1 && v.revisiones <= 3) {
				valido = 1;
			} else {
				printf("Numero de revisiones invalido. Debe ser un numero entero entre 0 y 3.\n");
				printf("Presione enter para continuar\n");
				getchar(); 
				limpiarPantalla();
			}
		} else {
			printf("Error: Debe ingresar un numero valido.\n");
			printf("Presione enter para continuar\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			getchar();
			limpiarPantalla();
		}
	}
	
	limpiarPantalla();
	
	// Validar multas
	valido = 0;
	while (!valido) {
		printf("Ingrese el numero de multas pendientes: \n ");
		if (scanf("%d", &v.multas) == 1) {
			
			int c = getchar();
			if (c == '.') {
				// Si encontramos un punto decimal, es un numero decimal
				printf("Error: Las multas deben ser un numero entero. No se permiten decimales.\n");
				printf("Presione enter para continuar\n");
				// Limpiar el resto de la entrada
				while ((c = getchar()) != '\n' && c != EOF);
				getchar();
				limpiarPantalla();
				continue; //Salta la iteracion actual y continua con la siguiente iteracion del mismo bucle.
				
			} else {
				// Devolver el caracter al buffer si no es un punto
				ungetc(c, stdin);
			}
			
			if (v.multas >= 0 && v.multas <= 10) {
				valido = 1;
			} else {
				printf("Numero de multas invalido. Debe ser un numero entre 0 y 10\n");
				printf("Presione enter para continuar\n");
				getchar(); getchar();
				limpiarPantalla();
			}
		} else {
			printf("Error: Debe ingresar un numero valido.\n");
			int c;
			while ((c = getchar()) != '\n' && c != EOF);
			getchar();
			limpiarPantalla();
			
		}
	}
	
	// Calcular matricula
	calcularMatricula(&v);
	limpiarPantalla();
	
	return v;
}

// Agrega vehiculos, maximo 100
void agregarVehiculo(Vehiculo vehiculos[], int* totalVehiculos, Vehiculo nuevoVehiculo) {
	if (*totalVehiculos < MAX_VEHICULOS) {
		vehiculos[*totalVehiculos] = nuevoVehiculo;
		(*totalVehiculos)++;
		
		// Guardar el vehiculo en el archivo
		guardarVehiculoEnArchivo(nuevoVehiculo);
		
		printf("Vehiculo registrado exitosamente!\n");
	} else {
		printf("Error: No se pueden registrar mas vehiculos. Limite alcanzado.\n");
		printf("Presione enter para continuar\n");
		getchar(); getchar(); 
		limpiarPantalla();
	}
}

// Imprime en consola la lista de todos los vehiculos registrados hasta el momento
void listarVehiculos(Vehiculo vehiculos[], int totalVehiculos) {
	if (totalVehiculos == 0) {
		printf("No hay vehiculos registrados.\n");
		return;
	}
	
	printf("\n=== LISTA DE VEHICULOS MATRICULADOS ===\n");
	printf("Total de vehiculos: %d\n\n", totalVehiculos);
	
	for (int i = 0; i < totalVehiculos; i++) {
		printf("Vehiculo #%d:\n", i + 1);
		mostrarVehiculo(vehiculos[i]);
		printf("\n");
	}
}

// Busca vehiculos segun la placa exacta
int buscarVehiculoPorPlaca(Vehiculo vehiculos[], int totalVehiculos, const char* placa) {
	for (int i = 0; i < totalVehiculos; i++) {
		if (strcmp(vehiculos[i].placa, placa) == 0) {
			return i;
		}
	}
	return -1;
}
