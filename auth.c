#include "auth.h"
//AUTH_EXITO si la autenticacion es correcta 
//AUTH_FALLO si falla, o codigo de error negativo

int mostrar_menu_fallback(void) {
    int opcion;
    printf("\n---- OPCIONES ----\n");
    printf("1. Iniciar Sesion\n");
    printf("2. Registrar nuevo usuario\n");	
    printf("3. Salir\n");
    printf("Seleccione una opcion: ");
    
    if (scanf("%d", &opcion) != 1) {
        limpiar_buffer();
        return 0; // Opcion invalida
    }
    limpiar_buffer();
    
    return opcion;
}

int autenticar_usuario(void) {
    char usuario[MAX_USUARIO];
    char pin[MAX_PIN];
    int resultado;
    int opcion_menu;
    
    while (1) {
        // Directamente pedir cedula y PIN
        limpiarPantalla();
        printf("\n=== INICIAR SESION ===\n");
        
        // Leer y validar usuario
        do {
            leer_usuario(usuario);
            resultado = validar_usuario(usuario);
            if (resultado != AUTH_EXITO) {
                mostrar_error_usuario(resultado);
            }
        } while (resultado != AUTH_EXITO);
        
        // Leer y validar PIN
        do {
            leer_pin(pin);
            resultado = validar_pin(pin);
            if (resultado != AUTH_EXITO) {
                mostrar_error_pin(resultado);
            }
        } while (resultado != AUTH_EXITO);
        
        // Verificar credenciales
        resultado = verificar_credenciales(usuario, pin);
        
        if (resultado == AUTH_EXITO) {
            printf("\nAcceso permitido.\n");
            return AUTH_EXITO;
        } else if (resultado == AUTH_ERROR_ARCHIVO) {
            printf("\nError: No se pudo acceder al archivo de usuarios.\n");
            printf("Presione Enter para continuar...");
            getchar();
        } else {
            // Usuario o PIN incorrecto - mostrar menu de opciones
            printf("\nUsuario o PIN incorrecto.\n");
            
            while (1) {
                opcion_menu = mostrar_menu_fallback();
                
                switch (opcion_menu) {
                    case 1: // Intentar de nuevo
                        break; // Sale del while interno y vuelve al bucle principal
                        
                    case 2: // Registrar usuario
                        limpiarPantalla();
                        printf("\n=== REGISTRAR NUEVO USUARIO ===\n");
                        resultado = registrar_usuario();
                        
                        if (resultado == AUTH_EXITO) {
                            printf("\nUsuario registrado exitosamente.\n");
                            printf("Ahora puede iniciar sesion.\n");
                        } else {
                            mostrar_error_registro(resultado);
                        }
                        printf("Presione Enter para continuar...");
                        getchar();
                        break; // Sale del while interno y vuelve al bucle principal
                        
                    case 3: // Salir
                        printf("\nSaliendo del sistema...\n");
                        return AUTH_FALLO;
                        
                    default:
                        printf("\nOpcion invalida. Intente nuevamente.\n");
                        printf("Presione Enter para continuar...");
                        getchar();
                        continue; // Continua en el while interno
                }
                break; // Sale del while interno
            }
        }
    }
}

// Nueva funcion para registrar usuarios
int registrar_usuario(void) {
    char usuario[MAX_USUARIO];
    char pin[MAX_PIN];
    char pin_confirmacion[MAX_PIN];
    int resultado;
    
    // Leer y validar usuario
    do {
        leer_usuario(usuario);
        resultado = validar_usuario(usuario);
        if (resultado != AUTH_EXITO) {
            mostrar_error_usuario(resultado);
        }
    } while (resultado != AUTH_EXITO);
    
    // Verificar si el usuario ya existe
    resultado = verificar_usuario_existe(usuario);
    if (resultado == AUTH_EXITO) {
        return AUTH_ERROR_USUARIO_EXISTE;
    } else if (resultado == AUTH_ERROR_ARCHIVO) {
        // Si no existe el archivo, se creara
        printf("Nota: Se creara un nuevo archivo de usuarios.\n");
    }
    
    // Leer y validar PIN
    do {
        leer_pin(pin);
        resultado = validar_pin(pin);
        if (resultado != AUTH_EXITO) {
            mostrar_error_pin(resultado);
        }
    } while (resultado != AUTH_EXITO);
    
    // Confirmar PIN
    do {
        printf("Confirme PIN (6 digitos): ");
        
        if (fgets(pin_confirmacion, MAX_PIN, stdin) != NULL) {
            pin_confirmacion[strcspn(pin_confirmacion, "\n")] = '\0';
        } else {
            pin_confirmacion[0] = '\0';
        }
        
        if (strlen(pin_confirmacion) == MAX_PIN - 1 && pin_confirmacion[MAX_PIN - 2] != '\n') {
            limpiar_buffer();
        }
        
        if (strcmp(pin, pin_confirmacion) != 0) {
            printf("Error: Los PINs no coinciden. Intente nuevamente.\n");
        }
    } while (strcmp(pin, pin_confirmacion) != 0);
    
    // Guardar usuario
    resultado = guardar_usuario(usuario, pin);
    
    return resultado;
}

// Verificar si un usuario ya existe
int verificar_usuario_existe(const char* usuario) {
    FILE* archivo;
    char linea[MAX_LINEA];
    char usuario_archivo[MAX_USUARIO];
    
    archivo = fopen(ARCHIVO_USUARIOS, "r");
    if (archivo == NULL) {
        return AUTH_ERROR_ARCHIVO;
    }
    
    while (fgets(linea, sizeof(linea), archivo)) {
        linea[strcspn(linea, "\n")] = '\0';
        
        char* token = strtok(linea, ":");
        if (token != NULL) {
            strcpy(usuario_archivo, token);
            
            if (strcmp(usuario, usuario_archivo) == 0) {
                fclose(archivo);
                return AUTH_EXITO; // Usuario existe
            }
        }
    }
    
    fclose(archivo);
    return AUTH_FALLO; // Usuario no existe
}

// Guardar usuario en archivo
int guardar_usuario(const char* usuario, const char* pin) {
    FILE* archivo;
    
    // Abrir archivo en modo append (agregar al final)
    archivo = fopen(ARCHIVO_USUARIOS, "a");
    if (archivo == NULL) {
        return AUTH_ERROR_ARCHIVO;
    }
    
    // Escribir usuario:pin
    fprintf(archivo, "%s:%s\n", usuario, pin);
    
    fclose(archivo);
    return AUTH_EXITO;
}

// Mostrar errores de registro
void mostrar_error_registro(int codigo_error) {
    switch (codigo_error) {
        case AUTH_ERROR_USUARIO_EXISTE:
            printf("Error: El usuario ya existe en el sistema.\n");
            break;
        case AUTH_ERROR_ARCHIVO:
            printf("Error: No se pudo acceder al archivo de usuarios.\n");
            break;
        case AUTH_ERROR_FORMATO:
            printf("Error: Formato de datos invalido.\n");
            break;
        default:
            printf("Error desconocido durante el registro.\n");
            break;
    }
}

//Valida que el usuario tenga exactamente 10 digitos
int validar_usuario(const char* usuario) {
    int longitud = strlen(usuario);
    
    // Verificar longitud exacta de 10 digitos
    if (longitud != 10) {
        return AUTH_ERROR_FORMATO;
    }
    
    // Verificar que todos los caracteres sean digitos
    for (int i = 0; i < longitud; i++) {
        if (!isdigit(usuario[i])) {
            return AUTH_ERROR_FORMATO;
        }
    }
    
    return AUTH_EXITO;
}

//Valida que el PIN tenga exactamente 6 digitos
int validar_pin(const char* pin) {
    int longitud = strlen(pin);
    
    // Verificar longitud exacta de 6di­gitos
    if (longitud != 6) {
        return AUTH_ERROR_FORMATO;
    }
    
    // Verificar que todos los caracteres sean digitos
    for (int i = 0; i < longitud; i++) {
        if (!isdigit(pin[i])) {
            return AUTH_ERROR_FORMATO;
        }
    }
    
    return AUTH_EXITO;
}

//Verifica los datos del archivo de usuarios
//Formato esperado del archivo: usuario:pin (una li­nea por usuario)
int verificar_credenciales(const char* usuario, const char* pin) {
    FILE* archivo;
    char linea[MAX_LINEA];
    char usuario_archivo[MAX_USUARIO];
    char pin_archivo[MAX_PIN];
    
    // Abrir archivo de usuarios
    archivo = fopen(ARCHIVO_USUARIOS, "r");
    if (archivo == NULL) {
        return AUTH_ERROR_ARCHIVO;
    }
    // Leer linea por li­nea
    while (fgets(linea, sizeof(linea), archivo)) {
        
        // Remover salto de linea si existe
        linea[strcspn(linea, "\n")] = '\0';
        
        // Separar usuario y pin usando ':' como delimitador
        char* token = strtok(linea, ":");
        if (token != NULL) {
            strcpy(usuario_archivo, token);
            
            token = strtok(NULL, ":");
            if (token != NULL) {
                strcpy(pin_archivo, token);
                
                // Comparar usuario y pin
                if (strcmp(usuario, usuario_archivo) == 0 && 
                    strcmp(pin, pin_archivo) == 0) {
                    fclose(archivo);
                    return AUTH_EXITO;
                }
            }
        }
    }
    
    fclose(archivo);
    return AUTH_FALLO;
}

//Lee usuario
void leer_usuario(char* usuario) {
    printf("Ingrese su cedula (10 digitos): \n");
    
    if (fgets(usuario, MAX_USUARIO, stdin) != NULL) {
        // Remover salto de li­nea si existe
        usuario[strcspn(usuario, "\n")] = '\0';
    } else {
        // Si hay error en la lectura, establecer cadena vaci­a
        usuario[0] = '\0';
    }
    
    // Limpiar buffer si la entrada fue muy larga
    if (strlen(usuario) == MAX_USUARIO - 1 && usuario[MAX_USUARIO - 2] != '\n') {
        limpiar_buffer();
    }
}

//Lee pin
void leer_pin(char* pin) {
    printf("Ingrese PIN (6 digitos): \n");
    
    if (fgets(pin, MAX_PIN, stdin) != NULL) {
        // Remover salto de linea si existe
        pin[strcspn(pin, "\n")] = '\0';
    } else {
        // Si hay error en la lectura, establecer cadena vacia
        pin[0] = '\0';
    }
    
    // Limpiar buffer si la entrada fue muy larga
    if (strlen(pin) == MAX_PIN - 1 && pin[MAX_PIN - 2] != '\n') {
        limpiar_buffer();
    }
}

//Limpia el buffer de entrada para evitar problemas con entradas largas
void limpiar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Muestra mensajes de error segun el caso
void mostrar_error_usuario(int codigo_error) {
    switch (codigo_error) {
        case AUTH_ERROR_FORMATO:
            printf("Error: La cedula debe tener exactamente 10 digitos numericos.\n");
			printf("\nPresione Enter para continuar");
			getchar();
			limpiarPantalla();
            break;
        case AUTH_ERROR_ENTRADA:
            printf("Error: Entrada invalida. Intente nuevamente.\n");
			printf("\nPresione Enter para continuar");
			getchar();
			limpiarPantalla();
            break;
        case AUTH_ERROR_ARCHIVO:
            printf("Error: No se pudo acceder al archivo de usuarios.\n");
			printf("\nPresione Enter para continuar");
			getchar();
			limpiarPantalla();
            break;
        default:
            printf("Error desconocido en la cedula.\n");
			printf("\nPresione Enter para continuar");
			getchar();
			limpiarPantalla();
            break;
    }
}

//Muestra mensajes de error especificos para PIN
void mostrar_error_pin(int codigo_error) {
    switch (codigo_error) {
        case AUTH_ERROR_FORMATO:
            printf("Error: El PIN debe tener exactamente 6 digitos numericos.\n");
			printf("\nPresione Enter para continuar");
			getchar();
			limpiarPantalla();
            break;
        case AUTH_ERROR_ENTRADA:
            printf("Error: Entrada invalida. Intente nuevamente.\n");
			printf("\nPresione Enter para continuar");
			getchar();
			limpiarPantalla();
            break;
        case AUTH_ERROR_ARCHIVO:
            printf("Error: No se pudo acceder al archivo de usuarios.\n");
			printf("\nPresione Enter para continuar");
			getchar();
			limpiarPantalla();
            break;
        default:
            printf("Error desconocido en PIN.\n");
			printf("\nPresione Enter para continuar");
			getchar();
			limpiarPantalla();
            break;
    }
}
