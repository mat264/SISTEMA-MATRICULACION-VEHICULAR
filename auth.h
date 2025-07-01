#ifndef AUTH_H
#define AUTH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Constantes para el módulo de autenticación
#define MAX_USUARIO 11      // 10 dígitos + terminador nulo
#define MAX_PIN 7           // 6 dí­gitos + terminador nulo
#define MAX_LINEA 256       // Tamaño máximo de línea en archivo
#define ARCHIVO_USUARIOS "usuarios.txt"

// Codigos de retorno para las funciones
#define AUTH_EXITO 1
#define AUTH_FALLO 0
#define AUTH_ERROR_ARCHIVO -1
#define AUTH_ERROR_FORMATO -2
#define AUTH_ERROR_ENTRADA -3

// Estructura para almacenar credenciales
typedef struct {
    char usuario[MAX_USUARIO];
    char pin[MAX_PIN];
} Credencial;

//Funciones 
int autenticar_usuario(void);
int validar_usuario(const char* usuario);
int validar_pin(const char* pin);
int verificar_credenciales(const char* usuario, const char* pin);
void leer_usuario(char* usuario);
void leer_pin(char* pin);
void limpiar_buffer(void);
void mostrar_error_usuario(int codigo_error);
void mostrar_error_pin(int codigo_error);

#endif // AUTH_H
