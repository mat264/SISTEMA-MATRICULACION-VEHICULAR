#include <stdio.h>
#include <stdbool.h>
void registro_vehicular(char placa[], char cedula[], char *tipo, int *ano, float *costo){
	printf("----Registro Vehicular----\n");
	printf("1. Ingrese la placa vehicular: ");
	scanf("%s", placa);
	printf("2. Ingrese su número de cédula: ");
	scanf("%s", cedula);
	printf("3. Ingrese el tipo de vehículo(M o C): ");
	scanf(" %c", tipo);  
	printf("4. Ingrese el año del vehículo: ");
	scanf("%d", ano);
	printf("5. Ingrese el costo del vehículo: ");
	scanf("%f", costo);
}
float calcularValorMatricula(float avaluo, int anioVehiculo, bool tieneMulta, bool revisionesCompletas) {
	int anioActual = 2025;
	float valorBase, descuento = 0, recargo = 0, multa = 0, valorTotal;
	// Valor base: 1% del avalúo
	valorBase = avaluo * 0.01;
	// Descuento por antigüedad (más de 10 años = 10% descuento)
	if ((anioActual - anioVehiculo) > 10) {
		descuento = valorBase * 0.10;
	}
	// Multa fija si tiene multas
	if (tieneMulta) {
		multa = 50.0;
	}
	// Recargo si no completó revisiones técnicas
	if (!revisionesCompletas) {
		recargo = valorBase * 0.15;
	}
	// Cálculo final
	valorTotal = valorBase + multa + recargo - descuento;
	
	return valorTotal;
}

int main() {
	char placa[8];
	char cedula[15];
	char tipo;
	int ano;
	float costo;	
	registro_vehicular(placa, cedula, &tipo, &ano, &costo);
	printf("----Datos Registrados----\n");
	printf("Placa del vehículo: %s\n", placa);
	printf("Número de cédula: %s\n", cedula);
	printf("Tipo de vehículo: %c\n", tipo);
	printf("Año del vehículo: %d\n", ano);
	printf("Costo del vehículo: %.2f\n", costo);
	return 0;
}
