#include <stdio.h>
#include "libreriaValidaciones.h"

void mostrarMenu(){
	int opcionMenu;
	printf("---SISTEMA MATRICULACIÓN---\n");
	printf("Elija una opción: \n");
	printf("1.-Registrar vehiculo\n");
	printf("2.-Listar vehiculos\n");
	printf("3.-Buscar vehiculos por placa\n");
	printf("4.-Salir\n");
}
	
	

	

int main() {
	//Muestra el menu hasta que el usuario elija salir
	
	int opcionMenu;
	do {
		mostrarMenu();
		scanf("%d", &opcionMenu);
		
	} while(opcionMenu == 4);
	limpiarPantalla();
	
	
	
	//Segun la opcion ingresada por el usuario ejecuta un caso
	switch(opcionMenu){
		
	case 1:{
		printf("MÓDULO DE REGISTRO\n");
		Vehiculo nuevo = registrarVehiculo();
		printf("\n----Datos Registrados----\n");
		printf("Placa: %s\n",  nuevo.placa);
		printf("Número de cédula del propietario: %s\n", nuevo.cedula);
		printf("Año: %d\n", nuevo.anio);
		printf("Avalúo: %.2f\n", nuevo.avaluo);
		
		break;
	}
		
	case 2:{
			printf("Proximo");
			break;
		}
			
	case 3:{
			printf("Proximo");	
			break;
			}
	
	default:{
		printf("Opción invalida.\n");
		printf("Ingrese una de las opciones del Menu (1-4)\n");
		do {
		mostrarMenu();
		scanf("%d", &opcionMenu);
		}while(opcionMenu == 4);
					
				}
	}
	
	
	
	
	return 0;
}

