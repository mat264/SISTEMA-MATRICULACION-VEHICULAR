#include <stdio.h>
#include "libreriaValidaciones.h"

void mostrarMenu(){
	int opcionMenu;
	printf("---SISTEMA MATRICULACI�N---\n");
	printf("Elija una opci�n: \n");
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
		printf("M�DULO DE REGISTRO\n");
		Vehiculo nuevo = registrarVehiculo();
		printf("\n----Datos Registrados----\n");
		printf("Placa: %s\n",  nuevo.placa);
		printf("N�mero de c�dula del propietario: %s\n", nuevo.cedula);
		printf("A�o: %d\n", nuevo.anio);
		printf("Aval�o: %.2f\n", nuevo.avaluo);
		
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
		printf("Opci�n invalida.\n");
		printf("Ingrese una de las opciones del Menu (1-4)\n");
		do {
		mostrarMenu();
		scanf("%d", &opcionMenu);
		}while(opcionMenu == 4);
					
				}
	}
	
	
	
	
	return 0;
}

