
#ifndef LIBRERIAVALIDACIONES_H
#define LIBRERIAVALIDACIONES_H

#define MAX_VEHICULOS 100

typedef struct {
	char placa[20];     
	char cedula[15];    
	int anio;
	char tipo[20];      
	float avaluo;
	float matricula;    // Valor total de la matrícula
	int revisiones;     // Número de revisiones realizadas
	int multas;         // Número de multas
	float valorBase;    // 1% del avalúo
	float recargo;      // 15% si no cumple 3 revisiones
	float descuento;    // 10% si el vehí­culo tiene más de 10 años
	float multasTotales; // 50$ por cada multa
} Vehiculo;

// Funciones de validación y utilidades
int validarPlaca(const char* placa);
void limpiarPantalla();

// Funciones de registro y cálculo
Vehiculo registrarVehiculo();
float calcularMatricula(Vehiculo* vehiculo);

// Funciones de gestión de vehí­culos
void agregarVehiculo(Vehiculo vehiculos[], int* totalVehiculos, Vehiculo nuevoVehiculo);
void listarVehiculos(Vehiculo vehiculos[], int totalVehiculos);
int buscarVehiculoPorPlaca(Vehiculo vehiculos[], int totalVehiculos, const char* placa);

// Funciones de visualización
void mostrarVehiculo(Vehiculo v);
void mostrarComprobante(Vehiculo v);
void generarComprobanteArchivo(Vehiculo v, const char* nombreArchivo);

#endif
