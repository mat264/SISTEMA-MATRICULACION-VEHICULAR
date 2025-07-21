#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#define MAX_VEHICULOS 100
#define ARCHIVO_VEHICULOS "vehiculos.txt"

typedef struct {
	char placa[20];     
	char cedula[15];    
	int anio;
	char tipo[20];      
	float avaluo;
	float matricula;    // Valor total de la matrícula
	int revisiones;     // Numero de revisiones realizadas
	int multas;         // Numero de multas
	float valorBase;    // 1% del avaluo
	float recargo;      // 15% si no cumple 3 revisiones
	float descuento;    // 10% si el vehículo tiene más de 10 años
	float multasTotales; // 50$ por cada multa
} Vehiculo;

// Funciones de validacion y utilidades
int validarPlaca(const char* placa);
void limpiarPantalla();
Vehiculo registrarVehiculo();

// Funciones de gestion de vehículos
void agregarVehiculo(Vehiculo vehiculos[], int* totalVehiculos, Vehiculo nuevoVehiculo);
void listarVehiculos(Vehiculo vehiculos[], int totalVehiculos);
int buscarVehiculoPorPlaca(Vehiculo vehiculos[], int totalVehiculos, const char* placa);

// Funciones de manejo de archivos
void guardarVehiculoEnArchivo(Vehiculo v);
int cargarVehiculosDesdeArchivo(Vehiculo vehiculos[]);
void mostrarVehiculo(Vehiculo v);

#endif