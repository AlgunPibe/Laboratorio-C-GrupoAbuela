#ifndef ARTEMIS_H
#define ARTEMIS_H  

#define G 9.80

typedef struct {
  double a1, t1, a2, h;
} Parametros;

typedef struct {
  double v1, y1, v2, hmax, g_max;
} Resultados;

int calcular_mision(const Parametros *p, Resultados *r);

#endif
