#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#define MAX_VEHICULOS 100

typedef struct {
	char placa[20];     
	char cedula[15];    
	int anio;
	char tipo[20];      
	float avaluo;
	float matricula;    // Valor total de la mat�cula
	int revisiones;     // Numero de revisiones realizadas
	int multas;         // Numero de multas
	float valorBase;    // 1% del avaluo
	float recargo;      // 15% si no cumple 3 revisiones
	float descuento;    // 10% si el veh�culo tiene m�s de 10 a�os
	float multasTotales; // 50$ por cada multa
} Vehiculo;

// Funciones de validacion y utilidades
int validarPlaca(const char* placa);
void limpiarPantalla();
Vehiculo registrarVehiculo();

// Funciones de gestion de veh�culos
void agregarVehiculo(Vehiculo vehiculos[], int* totalVehiculos, Vehiculo nuevoVehiculo);
void listarVehiculos(Vehiculo vehiculos[], int totalVehiculos);
int buscarVehiculoPorPlaca(Vehiculo vehiculos[], int totalVehiculos, const char* placa);

#endif
