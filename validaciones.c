#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "validaciones.h"

#define TAM_BUF 100

static void leer_linea(char *buf, int tam)
{
    int c;

    if (fgets(buf, tam, stdin) == NULL) {
        printf("\nEntrada cerrada. Saliendo del programa.\n");
        exit(0);
    }
    if (strchr(buf, '\n') == NULL) {
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

int leer_int(const char *msg, int min, int max)
{
      char buf[TAM_BUF], *fin;
    long v;

    while (1) {
        printf("%s", msg);
        leer_linea(buf, TAM_BUF);
        v = strtol(buf, &fin, 10);
        if (fin == buf || (*fin != '\n' && *fin != '\0'))
            printf("  [Error] Ingrese un numero entero valido.\n");
        else if (v < min || v > max)
            printf("  [Error] El valor debe estar entre %d y %d.\n", min, max);
        else
            return (int)v;
    }
}

double leer_double(const char *msg, double min, double max)
{
    char buf[TAM_BUF], *fin;
    double v;

    while (1) {
        printf("%s", msg);
        leer_linea(buf, TAM_BUF);
        v = strtod(buf, &fin);
        if (fin == buf || (*fin != '\n' && *fin != '\0') || !isfinite(v))
            printf("  [Error] Ingrese un numero valido (use punto decimal, ej: 12.5).\n");
        else if (v < min || v > max)
            printf("  [Error] El valor debe estar entre %.2f y %.2f.\n", min, max);
        else
            return v;
    }
}

char leer_char(const char *msg, const char *permitidos)
{
    char buf[TAM_BUF], c;

    while (1) {
        printf("%s", msg);
        leer_linea(buf, TAM_BUF);
        if (buf[0] != '\0' && buf[1] == '\n') {
c = (char)tolower((unsigned char)buf[0]);
            if (strchr(permitidos, c) != NULL)
                return c;
        }
        printf("  [Error] Opcion invalida. Opciones permitidas: %s\n", permitidos);
    }
}
