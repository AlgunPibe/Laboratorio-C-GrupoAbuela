#include "artemis.h"
#include <math.h>
#include "artemis.h"

int calcular_mision(const Parametros *p, Resultados *r) {
  double dy, a_max;

  r->v1 = p->a1 * p->t1;
  r->y1 = 0.5 * p->a1 * p->t1 * p->t1;
  if (r->y1 >= p->h)
    return 0;
  dy = p->h - r->y1;
  r->v2 = sqrt(r->v1 * r->v1 + 2.0 * p->a2 * dy);
  r->t2 = (r->v2 - r->v1) / p->a2;
  r->t_total = p->t1 + r->t2;

  r->hmax = p->h + (r->v2 * r->v2) / (2.0 * G);

  a_max = (p->a1 > p->a2) ? p->a1 : p->a2;
  r->g_aceler = a_max / G;
  r->g_sentida = (a_max + G) / G;

if (r->g_sentida > LIMITE_G) {
  r->exito = 0;
  r->puntaje = 0;
} else {
  r->exito = 1;
  r->puntaje = (int) (100.0 * (1.0 - r->g_sentida / LIMITE_G));
}
return 1;
}
