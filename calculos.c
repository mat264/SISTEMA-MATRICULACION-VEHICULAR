#include "calculos.h"

// Calcula la matricula con las distintas consideraciones
float calcularMatricula(Vehiculo* vehiculo) {
    // Calcular valor base (1% del avaluo)
    vehiculo->valorBase = vehiculo->avaluo * 0.01;
    
    // Calcular recargo por revisiones
    if (vehiculo->revisiones < 3) {
        vehiculo->recargo = vehiculo->valorBase * 0.15; // 15% del valor base
    } else {
        vehiculo->recargo = 0.0;
    }
    
    // Calcular descuento por antiguedad (mas de 10 años)
    int anioActual = 2025;
    int antiguedad = anioActual - vehiculo->anio;
    if (antiguedad > 10) {
        vehiculo->descuento = vehiculo->valorBase * 0.10; // 10% del valor base
    } else {
        vehiculo->descuento = 0.0;
    }
    
    // Calcular multas totales ($50 por cada multa)
    vehiculo->multasTotales = vehiculo->multas * 50.0;
    
    // Calcular valor total de la matricula
    vehiculo->matricula = vehiculo->valorBase + vehiculo->multasTotales + vehiculo->recargo - vehiculo->descuento;
    
    return vehiculo->matricula;
}
