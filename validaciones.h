#ifndef VALIDACIONES_H
#define VALIDACIONES_H

int    leer_int(const char *msg, int min, int max);
double leer_double(const char *msg, double min, double max);
char   leer_char(const char *msg, const char *permitidos);

#endif
