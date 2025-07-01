#include "auth.h"

//AUTH_EXITO si la autenticacion es correcta 
//AUTH_FALLO si falla, o codigo de error negativo

int autenticar_usuario(void) {
    char usuario[MAX_USUARIO];
    char pin[MAX_PIN];
    int resultado;
    
    printf("\n=== SISTEMA DE AUTENTICACION ===\n");
    
    while (1) {
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
        
        // Verificar datos del archivo txt		
        resultado = verificar_credenciales(usuario, pin);
        
        if (resultado == AUTH_EXITO) {
            printf("\nAutenticacion exitosa. Acceso permitido.\n");
            return AUTH_EXITO;
        } else if (resultado == AUTH_ERROR_ARCHIVO) {
            printf("\nError: No se pudo acceder al archivo de usuarios.\n");
            return AUTH_ERROR_ARCHIVO;
        } else {
            printf("\nUsuario o PIN incorrecto. Intente nuevamente.\n\n");
            // Continua el bucle para permitir otro intento
        }
    }
}

//Valida que el usuario tenga exactamente 10 dígitos
 
int validar_usuario(const char* usuario) {
    int longitud = strlen(usuario);
    
    // Verificar longitud exacta de 10 dígitos
    if (longitud != 10) {
        return AUTH_ERROR_FORMATO;
    }
    
    // Verificar que todos los caracteres sean dígitos
    for (int i = 0; i < longitud; i++) {
        if (!isdigit(usuario[i])) {
            return AUTH_ERROR_FORMATO;
        }
    }
    
    return AUTH_EXITO;
}

//Valida que el PIN tenga exactamente 6 di­gitos
 
int validar_pin(const char* pin) {
    int longitud = strlen(pin);
    
    // Verificar longitud exacta de 6 di­gitos
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
//Formato esperado del archivo: usuario:pin (una línea por usuario)

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
    // Leer línea por línea
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
    printf("Ingrese usuario (10 digitos): ");
    
    if (fgets(usuario, MAX_USUARIO, stdin) != NULL) {
        // Remover salto de lí­nea si existe
        usuario[strcspn(usuario, "\n")] = '\0';
    } else {
        // Si hay error en la lectura, establecer cadena vacía
        usuario[0] = '\0';
    }
    
    // Limpiar buffer si la entrada fue muy larga
    if (strlen(usuario) == MAX_USUARIO - 1 && usuario[MAX_USUARIO - 2] != '\n') {
        limpiar_buffer();
    }
}

//Lee pin
void leer_pin(char* pin) {
    printf("Ingrese PIN (6 digitos): ");
    
    if (fgets(pin, MAX_PIN, stdin) != NULL) {
        // Remover salto de li­nea si existe
        pin[strcspn(pin, "\n")] = '\0';
    } else {
        // Si hay error en la lectura, establecer cadena vacía
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
            printf("Error: El usuario debe tener exactamente 10 digitos numericos.\n");
            break;
        case AUTH_ERROR_ENTRADA:
            printf("Error: Entrada invalida. Intente nuevamente.\n");
            break;
        case AUTH_ERROR_ARCHIVO:
            printf("Error: No se pudo acceder al archivo de usuarios.\n");
            break;
        default:
            printf("Error desconocido en usuario.\n");
            break;
    }
}


 //Muestra mensajes de error especi­ficos para PIN
 
void mostrar_error_pin(int codigo_error) {
    switch (codigo_error) {
        case AUTH_ERROR_FORMATO:
            printf("Error: El PIN debe tener exactamente 6 digitos numericos.\n");
            break;
        case AUTH_ERROR_ENTRADA:
            printf("Error: Entrada invalida. Intente nuevamente.\n");
            break;
        case AUTH_ERROR_ARCHIVO:
            printf("Error: No se pudo acceder al archivo de usuarios.\n");
            break;
        default:
            printf("Error desconocido en PIN.\n");
            break;
    }
}
