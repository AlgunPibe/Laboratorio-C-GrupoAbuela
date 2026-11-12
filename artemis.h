#ifndef ARTEMIS_H
#define ARTEMIS_H

#define G            9.80
#define LIMITE_G     4.0
#define MAX_MISIONES 20

#define A1_DEF  20.0
#define T1_DEF  120.0
#define A2_DEF  12.5
#define H_DEF   160000.0

typedef struct {
    double a1;
    double t1;
    double a2;
    double h;
} Parametros;

typedef struct {
    double v1;
    double y1;
    double v2;        
    double t2;       
    double t_total;   
    double hmax;      
    double g_aceler;  
    double g_sentida; 
    int    puntaje;   
    int    exito;     
} Resultados;

typedef struct {
    Parametros p;
    Resultados r;
} Mision;

int  calcular_mision(const Parametros *p, Resultados *r);
void estado_en_tiempo(const Parametros *p, const Resultados *r, double t,
                      double *y, double *v, double *a, int *fase);
void simular_ascenso(const Parametros *p, const Resultados *r, double paso);
void mostrar_analisis(const Parametros *p, const Resultados *r);
void mostrar_reporte(const Mision historial[], int cantidad);

#endif
