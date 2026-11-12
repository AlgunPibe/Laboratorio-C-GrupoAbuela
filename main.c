#include <stdio.h>
#include "artemis.h"
#include "validaciones.h"

static void mostrar_menu(void)
{
    printf("\n==============================================\n");
    printf("   ARTEMIS - ASCENSO Y PROPULSION CON EL SLS\n");
    printf("==============================================\n");
    printf(" 1. Nueva mision\n");
    printf(" 2. Simular ascenso paso a paso\n");
    printf(" 3. Ver analisis de la ultima mision\n");
    printf(" 4. Reporte final (historial)\n");
    printf(" 5. Salir\n");
}

static void pedir_parametros(Parametros *p)
{
    char usar_def = leer_char("Usar valores del enunciado? (s/n): ", "sn");

    if (usar_def == 's') {
        p->a1 = A1_DEF;  p->t1 = T1_DEF;
        p->a2 = A2_DEF;  p->h  = H_DEF;
        return;
    }
    p->a1 = leer_double("Aceleracion fase 1 a1 (m/s2) [1 - 100]: ", 1.0, 100.0);
    p->t1 = leer_double("Tiempo de desacople t1 (s) [1 - 1000]: ", 1.0, 1000.0);
    p->a2 = leer_double("Aceleracion fase 2 a2 (m/s2) [1 - 100]: ", 1.0, 100.0);
    p->h  = leer_double("Altitud de apagado h (m) [1000 - 1000000]: ", 1000.0, 1000000.0);
}

int main(void)
{
    Mision historial[MAX_MISIONES];
    int cantidad = 0;
    int hay_ultima = 0;
    Mision *ultima = NULL;
    int opcion;
    double paso;

    do {
        mostrar_menu();
        opcion = leer_int("Opcion: ", 1, 5);

        switch (opcion) {
        case 1:
            if (cantidad == MAX_MISIONES) {
                printf("  [Error] Historial lleno (%d misiones).\n", MAX_MISIONES);
                break;
            }
            pedir_parametros(&historial[cantidad].p);
            if (!calcular_mision(&historial[cantidad].p, &historial[cantidad].r)) {
                printf("  [Error] Con esos datos los SRB se desacoplan DESPUES de\n");
                printf("          alcanzar la altitud objetivo (y1 >= h). Pruebe otros valores.\n");
                break;
            }
            ultima = &historial[cantidad];
            cantidad++;
            hay_ultima = 1;
            printf("\nMision #%d calculada correctamente.\n", cantidad);
            mostrar_analisis(&ultima->p, &ultima->r);
            break;

        case 2:
            if (!hay_ultima) {
                printf("  [Aviso] Primero cree una mision (opcion 1).\n");
                break;
            }
            paso = leer_double("Paso de tiempo de la tabla (s) [1 - 60]: ", 1.0, 60.0);
            simular_ascenso(&ultima->p, &ultima->r, paso);
            break;

        case 3:
            if (!hay_ultima) {
                printf("  [Aviso] Primero cree una mision (opcion 1).\n");
                break;
            }
            mostrar_analisis(&ultima->p, &ultima->r);
            break;

        case 4:
            mostrar_reporte(historial, cantidad);
            break;

        case 5:
            printf("\nFin de la simulacion. Misiones realizadas: %d\n", cantidad);
            break;
        }
    } while (opcion != 5);

    return 0;
}
