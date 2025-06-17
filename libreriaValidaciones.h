#ifndef LIBRERIAVALIDACIONES_H
#define LIBRERIAVALIDACIONES_H


typedef struct {
	char placa[20];     
	char cedula[15];    
	int anio;
	char tipo[20];      
	float avaluo;
} Vehiculo;

int validarPlaca(const char* placa);

Vehiculo registrarVehiculo();

void limpiarPantalla();





#endif
