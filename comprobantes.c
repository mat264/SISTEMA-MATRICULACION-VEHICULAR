#include "comprobantes.h"
#include <stdio.h>

// FUNCION MOSTRAR COMPROBANTES
void mostrarComprobante(Vehiculo v) {
    int anioActual = 2025;
    int antiguedad = anioActual - v.anio;
    
    printf("\n");
    printf("================================================\n");
    printf("           COMPROBANTE DE MATRICULA\n");
    printf("================================================\n");
    printf("Placa: %s\n", v.placa);
    printf("Cedula del propietario: %s\n", v.cedula);
    printf("Año del vehiculo: %d (Antiguedad: %d años)\n", v.anio, antiguedad);
    printf("Avaluo: $%.2f\n", v.avaluo);
    printf("================================================\n");
    printf("           DETALLE DE COSTOS\n");
    printf("================================================\n");
    printf("Valor Base (1%% del avaluo):      $%8.2f\n", v.valorBase);
    
    if (v.revisiones < 3) {
        printf("Revisiones realizadas: %d/3\n", v.revisiones);
        printf("Recargo por revisiones (15%%):    $%8.2f\n", v.recargo);
    } else {
        printf("Revisiones realizadas: %d/3\n", v.revisiones);
        printf("Recargo por revisiones:          $%8.2f\n", v.recargo);
    }
    
    if (antiguedad > 10) {
        printf("Descuento por antiguedad (10%%):  $%8.2f\n", v.descuento);
    } else {
        printf("Descuento por antiguedad:        $%8.2f\n", v.descuento);
    }
    
    if (v.multas > 0) {
        printf("Multas pendientes: %d\n", v.multas);
        printf("Costo de multas ($50 c/u):       $%8.2f\n", v.multasTotales);
    } else {
        printf("Multas pendientes: 0 \n");
        printf("Costo de multas:                 $%8.2f\n", v.multasTotales);
    }
    
    printf("------------------------------------------------\n");
    printf("TOTAL A PAGAR:                   $%8.2f\n", v.matricula);
    printf("================================================\n");
}

// Comprobante en archivo
void generarComprobanteArchivo(Vehiculo v, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error: No se pudo crear el archivo %s\n", nombreArchivo);
        return;
    }
    
    int anioActual = 2025;
    int antiguedad = anioActual - v.anio;
    
    // Escribir el comprobante en el archivo
    fprintf(archivo, "\n");
    fprintf(archivo, "================================================\n");
    fprintf(archivo, "           COMPROBANTE DE MATRICULA\n");
    fprintf(archivo, "================================================\n");
    fprintf(archivo, "Placa: %s\n", v.placa);
    fprintf(archivo, "Cedula del propietario: %s\n", v.cedula);
    fprintf(archivo, "AÃ±o del vehiculo: %d (Antiguedad: %d años)\n", v.anio, antiguedad);
    fprintf(archivo, "AvalÃºo: $%.2f\n", v.avaluo);
    fprintf(archivo, "================================================\n");
    fprintf(archivo, "           DETALLE DE COSTOS\n");
    fprintf(archivo, "================================================\n");
    fprintf(archivo, "Valor Base (1%% del avaluo):      $%8.2f\n", v.valorBase);
    
    if (v.revisiones < 3) {
        fprintf(archivo, "Revisiones realizadas: %d/3\n", v.revisiones);
        fprintf(archivo, "Recargo por revisiones (15%%):    $%8.2f\n", v.recargo);
    } else {
        fprintf(archivo, "Revisiones realizadas: %d/3 OK\n", v.revisiones);
        fprintf(archivo, "Recargo por revisiones:          $%8.2f\n", v.recargo);
    }
    
    if (antiguedad > 10) {
        fprintf(archivo, "Descuento por antiguedad (10%%):  $%8.2f\n", v.descuento);
    } else {
        fprintf(archivo, "Descuento por antiguedad:        $%8.2f\n", v.descuento);
    }
    
    if (v.multas > 0) {
        fprintf(archivo, "Multas pendientes: %d\n", v.multas);
        fprintf(archivo, "Costo de multas ($50 c/u):       $%8.2f\n", v.multasTotales);
    } else {
        fprintf(archivo, "Multas pendientes: 0 0K\n");
        fprintf(archivo, "Costo de multas:                 $%8.2f\n", v.multasTotales);
    }
    
    fprintf(archivo, "------------------------------------------------\n");
    fprintf(archivo, "TOTAL A PAGAR:                   $%8.2f\n", v.matricula);
    fprintf(archivo, "================================================\n");
    fprintf(archivo, "\nComprobante generado automaticamente\n");
    fprintf(archivo, "Sistema de Matriculacion Vehicular\n");
    fprintf(archivo, "================================================\n");
    
    fclose(archivo);
    printf("Â¡Comprobante guardado exitosamente en: %s!\n", nombreArchivo);
}
