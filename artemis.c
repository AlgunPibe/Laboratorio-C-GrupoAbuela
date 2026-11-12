#include "artemis.h"

int calcular_mision(const Parametros *p, Resultados *r) {
  r->v1 = p->a1 * p->t1;
  r->y1 = 0.5 *p->a1 * p->t1 * p->t1;
