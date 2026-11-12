#include <stdio.h>
#include <math.h>
#include "artemis.h"


int calcular_mision(const Parametros *p, Resultados *r)
{
    double dy, a_max;

    r->v1 = p->a1 * p->t1;
    r->y1 = 0.5 * p->a1 * p->t1 * p->t1;

    if (r->y1 >= p->h)
        return 0;

    dy     = p->h - r->y1;
    r->v2  = sqrt(r->v1 * r->v1 + 2.0 * p->a2 * dy);
    r->t2  = (r->v2 - r->v1) / p->a2;
    r->t_total = p->t1 + r->t2;

    r->hmax = p->h + (r->v2 * r->v2) / (2.0 * G);

    a_max = (p->a1 > p->a2) ? p->a1 : p->a2;
    r->g_aceler  = a_max / G;
    r->g_sentida = (a_max + G) / G;

    if (r->g_sentida > LIMITE_G) {
        r->exito   = 0;
        r->puntaje = 0;
    } else {
        r->exito   = 1;
        r->puntaje = (int)(100.0 * (1.0 - r->g_sentida / LIMITE_G));
    }
    return 1;
}

void estado_en_tiempo(const Parametros *p, const Resultados *r, double t,
                      double *y, double *v, double *a, int *fase)
{
    double dt;

    if (t <= p->t1) {
        *fase = 1;
        *a = p->a1;
        *v = p->a1 * t;
        *y = 0.5 * p->a1 * t * t;
    } else if (t < r->t_total) {
        dt = t - p->t1;
        *fase = 2;
        *a = p->a2;
        *v = r->v1 + p->a2 * dt;
        *y = r->y1 + r->v1 * dt + 0.5 * p->a2 * dt * dt;
    } else {
        *fase = 3;
        *a = 0.0;
        *v = r->v2;
        *y = p->h;
    }
}

void simular_ascenso(const Parametros *p, const Resultados *r, double paso)
{
    double t = 0.0, y, v, a;
    int fase, fase_ant = 0;

    printf("\n=== SIMULACION DE ASCENSO SLS / ORION ===\n");
    printf("%10s %14s %12s %10s  %s\n",
           "t (s)", "altitud (m)", "v (m/s)", "a (m/s2)", "evento");

    while (t < r->t_total) {
        estado_en_tiempo(p, r, t, &y, &v, &a, &fase);
        printf("%10.1f %14.1f %12.1f %10.2f  ", t, y, v, a);
        if (fase != fase_ant && fase == 1)      printf("Despegue");
        else if (fase != fase_ant && fase == 2) printf("Desacople de SRB");
        printf("\n");
        fase_ant = fase;
        t += paso;
    }
   
    estado_en_tiempo(p, r, r->t_total, &y, &v, &a, &fase);
    printf("%10.1f %14.1f %12.1f %10.2f  Apagado de motores\n",
           r->t_total, y, v, a);
}

void mostrar_analisis(const Parametros *p, const Resultados *r)
{
    printf("\n=== ANALISIS DE LA MISION ===\n");
    printf("1) Al desacople (t = %.1f s):\n", p->t1);
    printf("     rapidez v1 = %.2f m/s\n", r->v1);
    printf("     altitud y1 = %.2f m\n", r->y1);
    printf("2) Rapidez maxima al apagar motores (h = %.1f m):\n", p->h);
    printf("     v2 = %.2f m/s  (fase 2 dura %.2f s)\n", r->v2, r->t2);
    printf("3) Si los motores fallan en h = %.1f m (caida libre, g = %.2f):\n",
           p->h, G);
    printf("     altitud maxima hmax = %.2f m\n", r->hmax);
    printf("4) Aceleracion maxima: %.2f g (solo a/g)\n", r->g_aceler);
    printf("     Tripulacion siente: %.2f g (a + g, incluye la gravedad)\n",
           r->g_sentida);
    printf("\nEvaluacion: %s | Puntaje: %d/100 (limite %.1f g)\n",
           r->exito ? "MISION EXITOSA" : "MISION FALLIDA, tripulacion en riesgo",
           r->puntaje, LIMITE_G);
}

void mostrar_reporte(const Mision historial[], int cantidad)
{
    const Mision *m;
    int i;

    printf("\n=== REPORTE FINAL DE DESEMPENO ===\n");
    if (cantidad == 0) {
        printf("Todavia no se realizo ninguna mision.\n");
        return;
    }
    printf("%3s %7s %7s %7s %10s %10s %8s %8s\n",
           "N", "a1", "t1", "a2", "v2 (m/s)", "hmax (km)", "g sent.", "puntos");
    for (i = 0, m = historial; i < cantidad; i++, m++) {
        printf("%3d %7.2f %7.1f %7.2f %10.1f %10.1f %8.2f %8d  %s\n",
               i + 1, m->p.a1, m->p.t1, m->p.a2, m->r.v2,
               m->r.hmax / 1000.0, m->r.g_sentida, m->r.puntaje,
               m->r.exito ? "OK" : "FALLO");
    }
}
