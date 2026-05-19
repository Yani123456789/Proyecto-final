#include <stdio.h>
#include <stdlib.h> 
#define MAX_OYENTES 100
#define NUM_CANCIONES 10

int registrarVotos(int votos[MAX_OYENTES][3]);
void calcularResultados(int votos[MAX_OYENTES][3], int numOyentes, int *primera, int *segunda);
void repartirPremios(int votos[MAX_OYENTES][3], int numOyentes, int primera, int segunda);

int main() {
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

int registrarVotos(int votos[MAX_OYENTES][3]) {
    int i = 0;
    char linea[100]; 
    int v1, v2, v3;

    while (i < MAX_OYENTES) {
        printf("Oyente %d: ", i);
        
        if (fgets(linea, sizeof(linea), stdin) == NULL) {
            break;
        }

       
        int extraidos = sscanf(linea, "%d %d %d", &v1, &v2, &v3);

        
        if (extraidos >= 1 && v1 == -1) {
            break;
        }

       
        if (extraidos < 3) {
            printf("Error: Debes introducir 3 numeros de canciones o -1 para terminar. Intenta de nuevo.\n");
            continue; 
        }

        
        votos[i][0] = v1;
        votos[i][1] = v2;
        votos[i][2] = v3;
        i++;
    }
    return i; 
}


void calcularResultados(int votos[MAX_OYENTES][3], int numOyentes, int *primera, int *segunda) {
    int puntajesCanciones[NUM_CANCIONES] = {0}; 

    for (int i = 0; i < numOyentes; i++) {
        puntajesCanciones[votos[i][0]] += 3; 
        puntajesCanciones[votos[i][1]] += 2; 
        puntajesCanciones[votos[i][2]] += 1; 
    }

    for (int c = 0; c < NUM_CANCIONES; c++) {
        printf("Cancion %d: %d votos\n", c, puntajesCanciones[c]);
    }

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


void repartirPremios(int votos[MAX_OYENTES][3], int numOyentes, int primera, int segunda) {
    int maxPuntosOyente = -1;
    int oyenteGanador = -1;

    for (int i = 0; i < numOyentes; i++) {
        int puntosEsteOyente = 0;
        int acertoPrimera = 0;
        int acertoSegunda = 0;

        for (int j = 0; j < 3; j++) {
            if (votos[i][j] == primera) {
                acertoPrimera = 1;
            }
            if (votos[i][j] == segunda) {
                acertoSegunda = 1;
            }
        }

        if (acertoPrimera) {
            puntosEsteOyente += 30;
        }
        if (acertoSegunda) {
            puntosEsteOyente += 20;
        }
        if (acertoPrimera && acertoSegunda) {
            puntosEsteOyente += 10; 
        }

        printf("Oyente %d: %d puntos\n", i, puntosEsteOyente);

        if (puntosEsteOyente > maxPuntosOyente) {
            maxPuntosOyente = puntosEsteOyente;
            oyenteGanador = i;
        }
    }

    printf("Ganador: el oyente numero %d\n", oyenteGanador);
}
