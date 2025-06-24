
#ifndef LIBRERIAVALIDACIONES_H
#define LIBRERIAVALIDACIONES_H

#define MAX_VEHICULOS 100

typedef struct {
	char placa[20];     
	char cedula[15];    
	int anio;
	char tipo[20];      
	float avaluo;
	float matricula;    // Valor total de la matr�cula
	int revisiones;     // N�mero de revisiones realizadas
	int multas;         // N�mero de multas
	float valorBase;    // 1% del aval�o
	float recargo;      // 15% si no cumple 3 revisiones
	float descuento;    // 10% si el veh�culo tiene m�s de 10 a�os
	float multasTotales; // 50$ por cada multa
} Vehiculo;

// Funciones de validaci�n y utilidades
int validarPlaca(const char* placa);
void limpiarPantalla();

// Funciones de registro y c�lculo
Vehiculo registrarVehiculo();
float calcularMatricula(Vehiculo* vehiculo);

// Funciones de gesti�n de veh�culos
void agregarVehiculo(Vehiculo vehiculos[], int* totalVehiculos, Vehiculo nuevoVehiculo);
void listarVehiculos(Vehiculo vehiculos[], int totalVehiculos);
int buscarVehiculoPorPlaca(Vehiculo vehiculos[], int totalVehiculos, const char* placa);

// Funciones de visualizaci�n
void mostrarVehiculo(Vehiculo v);
void mostrarComprobante(Vehiculo v);
void generarComprobanteArchivo(Vehiculo v, const char* nombreArchivo);

#endif
