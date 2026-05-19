#include <stdio.h>

#define MAX_OYENTES 100
#define NUM_CANCIONES 10

// Prototipos de las funciones
int registrarVotos(int votos[MAX_OYENTES][3]);
void calcularResultados(int votos[MAX_OYENTES][3], int numOyentes, int *primera, int *segunda);
void repartirPremios(int votos[MAX_OYENTES][3], int numOyentes, int primera, int segunda);

int main() {
    // Matriz para almacenar los 3 votos de cada oyente (máximo 100 oyentes)
    int votos[MAX_OYENTES][3];
    int numOyentes = 0;
    int primeraMasVotada = -1, segundaMasVotada = -1;

    printf("--- INCISO 1: Registro de Concursantes ---\n");
    numOyentes = registrarVotos(votos);

    if (numOyentes == 0) {
        printf("No se registraron oyentes en el concurso.\n");
        return 0;
    }

    printf("\n--- INCISO 2: Calculo de Votos y Ganadores ---\n");
    calcularResultados(votos, numOyentes, &primeraMasVotada, &segundaMasVotada);

    printf("\n--- INCISO 3: Puntuacion de Oyentes y Ganador ---\n");
    repartirPremios(votos, numOyentes, primeraMasVotada, segundaMasVotada);

    return 0;
}

// ==========================================
// INCISO 1: Leer y almacenar los votos
// ==========================================
int registrarVotos(int votos[MAX_OYENTES][3]) {
    int i = 0;
    int v1, v2, v3;

    while (i < MAX_OYENTES) {
        printf("Oyente %d: ", i);
        scanf("%d %d %d", &v1, &v2, &v3);

        // Si el primer dato es -1, detenemos la lectura
        if (v1 == -1) {
            break;
        }

        // Almacenamos los votos en la matriz
        votos[i][0] = v1;
        votos[i][1] = v2;
        votos[i][2] = v3;
        i++;
    }
    return i; // Devuelve la cantidad total de oyentes que participaron
}

// ==========================================
// INCISO 2: Calcular votos por canción y top 2
// ==========================================
void calcularResultados(int votos[MAX_OYENTES][3], int numOyentes, int *primera, int *segunda) {
    int puntajesCanciones[NUM_CANCIONES] = {0}; // Inicializa el conteo de las 10 canciones en 0

    // Acumular los puntos por cada canción
    for (int i = 0; i < numOyentes; i++) {
        puntajesCanciones[votos[i][0]] += 3; // 1er lugar = 3 pts
        puntajesCanciones[votos[i][1]] += 2; // 2do lugar = 2 pts
        puntajesCanciones[votos[i][2]] += 1; // 3er lugar = 1 pt
    }

    // Mostrar los votos obtenidos por cada canción
    for (int c = 0; c < NUM_CANCIONES; c++) {
        printf("Cancion %d: %d votos\n", c, puntajesCanciones[c]);
    }

    // Encontrar la 1ra y 2da canción más votada
    int max1 = -1, max2 = -1;
    *primera = -1;
    *segunda = -1;

    for (int c = 0; c < NUM_CANCIONES; c++) {
        if (puntajesCanciones[c] > max1) {
            max2 = max1;
            *segunda = *primera;

            max1 = puntajesCanciones[c];
            *primera = c;
        } else if (puntajesCanciones[c] > max2) {
            max2 = puntajesCanciones[c];
            *segunda = c;
        }
    }

    printf("1a cancion: %d\n", *primera);
    printf("2a cancion: %d\n", *segunda);
}

// ==========================================
// INCISO 3: Repartir puntos a oyentes y buscar ganador
// ==========================================
void repartirPremios(int votos[MAX_OYENTES][3], int numOyentes, int primera, int segunda) {
    int maxPuntosOyente = -1;
    int oyenteGanador = -1;

    for (int i = 0; i < numOyentes; i++) {
        int puntosEsteOyente = 0;
        int acertoPrimera = 0;
        int acertoSegunda = 0;

        // Revisar las 3 canciones que votó el oyente actual
        for (int j = 0; j < 3; j++) {
            if (votos[i][j] == primera) {
                acertoPrimera = 1;
            }
            if (votos[i][j] == segunda) {
                acertoSegunda = 1;
            }
        }

        // Aplicar reglas de puntuación
        if (acertoPrimera) {
            puntosEsteOyente += 30;
        }
        if (acertoSegunda) {
            puntosEsteOyente += 20;
        }
        if (acertoPrimera && acertoSegunda) {
            puntosEsteOyente += 10; // Bono de 10 puntos suplementarios
        }

        printf("Oyente %d: %d puntos\n", i, puntosEsteOyente);

        // Validar si es el oyente con más puntos hasta ahora
        if (puntosEsteOyente > maxPuntosOyente) {
            maxPuntosOyente = puntosEsteOyente;
            oyenteGanador = i;
        }
    }

    printf("Ganador: el oyente numero %d\n", oyenteGanador);
}
