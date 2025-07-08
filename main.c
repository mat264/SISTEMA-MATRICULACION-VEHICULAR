#include <stdio.h>
#include <string.h>
#include "validaciones.h"
#include "calculos.h"
#include "comprobantes.h"
#include "auth.h"

//FUNCION MENU INICIAL
void mostrarMenu(){
    printf("\n----SISTEMA MATRICULACION----\n");
    printf("Elija una opcion: \n");
    printf("1.-Registrar y matricular vehiculo\n");
    printf("2.-Listar veiculos\n");
    printf("3.-Buscar vehiculo por placa (Comprobantes)\n");
    printf("4.-Salir\n");
    printf("Opcion: ");
} 
//CUERPO DEL PROGRAMA
int main() {
    //PROCESO DE AUTENTICACION ===
    limpiarPantalla();
    printf("----BIENVENIDO AL SISTEMA DE MATRICULACION VEHICULAR----\n");
    // Intentar autenticacion
    int resultado_auth = autenticar_usuario();
    
    if (resultado_auth != AUTH_EXITO) {
        printf("\nAcceso denegado. El programa se cerrara.\n");
        printf("Presione Enter para salir");
        getchar();
        return 1; // Salir con código de error
    }
    
    // Autenticación correcta
    limpiarPantalla();
    printf("ACCESO AUTORIZADO!\n");
    printf("Presione Enter para continuar al sistema");
    getchar();
    limpiarPantalla();
     
    //INICIO DEL SISTEMA PRINCIPAL
    Vehiculo vehiculos[MAX_VEHICULOS];
    int totalVehiculos = 0;
    int opcionMenu;
    
    //Bucle hasta que el usuario elija una opción
    do {
        mostrarMenu();
        
        // Validar entrada del menu
        if (scanf("%d", &opcionMenu) != 1) {
            printf("Error: Ingrese un numero valido.\n");
            // Limpiar buffer completamente
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcionMenu = 0; // Forzar a un valor invalido para continuar el bucle
            continue;
        }
        // Limpiar buffer despues de leer el numero
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
		
        //Switch para evaluar la opcion ingresada por el usuario
        switch(opcionMenu){
            case 1: {
                limpiarPantalla();
                printf("=== MODULO DE REGISTRO ===\n");
                Vehiculo nuevo = registrarVehiculo();
                agregarVehiculo(vehiculos, &totalVehiculos, nuevo);
                printf("\n---VEHICULO REGISTRADO EXITOSAMENTE---\n");
                printf("\nPresione Enter para continuar");
                getchar();
				limpiarPantalla();
				break;
            }
            
            case 2: {
                limpiarPantalla();
                printf("=== MODULO DE LISTADO ===\n");
                listarVehiculos(vehiculos, totalVehiculos);
                printf("\nPresione Enter para continuar");
                getchar();
                limpiarPantalla();
                break;
            }
            
            case 3: {
                limpiarPantalla();
                printf("=== MODULO DE BUSQUEDA ===\n");
                if (totalVehiculos == 0) {
                    printf("No hay vehiculos registrados para buscar.\n");
					getchar();
					limpiarPantalla();
                } else {
                    char placaBuscar[20];
                    int valido = 0;
                    printf("Vehiculos registrados: %d\n", totalVehiculos);
                    printf("Ingrese la placa a buscar (formato XYZ567): ");
                    
                    //Bucle que se repite hasta que ingrese un valor valido (valido=1)
                    while (!valido) {
                        // Leer la placa con fgets para mejor control
                        if (fgets(placaBuscar, sizeof(placaBuscar), stdin) != NULL) {
                            // Remover el salto de linea si existe
                            size_t len = strlen(placaBuscar);
                            if (len > 0 && placaBuscar[len-1] == '\n') {
                                placaBuscar[len-1] = '\0';
                            }
                            
                            if (validarPlaca(placaBuscar)) {
                                valido = 1;
                            } else {
                                printf("Formato de placa invalido. Use 3 letras mayusculas seguidas de 3-4 digitos.(XYZ567)");
                                printf("Ingrese la placa nuevamente: ");
								limpiarPantalla();
                            }
                        } else {
                            printf("Error al leer la placa. Intente nuevamente: ");
                        }
                    }
                    
                    int indice = buscarVehiculoPorPlaca(vehiculos, totalVehiculos, placaBuscar);
                    
                    if (indice != -1) {
                        printf("\nVehículo encontrado!\n");
                        mostrarComprobante(vehiculos[indice]);
                        
                        // Preguntar si desea generar archivo TXT
                        printf("\nDesea generar un archivo TXT con este comprobante? (s/n): ");
                        char respuesta;
                        scanf(" %c", &respuesta);
                        
                        if (respuesta == 's' || respuesta == 'S') {
                            char nombreArchivo[100];
                            printf("Ingrese el nombre del archivo (sin extension): ");
                            scanf("%99s", nombreArchivo);
                            
                            // Agregar extension .txt si no la tiene
                            if (strstr(nombreArchivo, ".txt") == NULL) {
                                strcat(nombreArchivo, ".txt");
                            }
                            
                            generarComprobanteArchivo(vehiculos[indice], nombreArchivo);
                            
                            printf("\nDesea abrir la ubicacion del archivo? (s/n): ");
                            char abrirUbicacion;
                            scanf(" %c", &abrirUbicacion);
                            
                            if (abrirUbicacion == 's' || abrirUbicacion == 'S') {
                                printf("El archivo se encuentra en la misma carpeta del programa:\n");
                                printf("Nombre del archivo: %s\n", nombreArchivo);
#ifdef _WIN32
                                system("explorer .");
#elif __linux__
                                system("xdg-open .");
#endif
                            }
                        }
                    } else {
                        printf("\nVehiculo con placa %s no encontrado.\n", placaBuscar);
                    }
                }
                
                printf("\nPresione Enter para continuar...");
                getchar();
                limpiarPantalla();
                break;
            }
            
            case 4: {
                printf("\nGracias por usar el Sistema de Matriculacion\n");
                printf("Cerrando sesion...\n");
                printf("Saliendo del programa...\n");
                break;
            }
            
            default: {
                printf("\nOpcion invalida. Ingrese una opcion del 1 al 4.\n");
                printf("Presione Enter para continuar...");
                getchar();
                limpiarPantalla();
                break;
            }
        }
        
    } while(opcionMenu != 4);
    
    return 0;
}
