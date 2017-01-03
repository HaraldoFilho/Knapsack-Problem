/// MC548 - PROJETO E ANALISE DE ALGORITMOS II - 1s2010
/// Prof. Flavio Keidi Miyazawa
/// ---------------------------------------------------------------
/// PROJETO PRATICO: PROBLEMA DA MOCHILA COM RESTRICOES DE CONFLITO
/// Haraldo Sergio A. Pereira Filho (003059)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "qsort.h"
#include "heuristics.h"

data_out_str star_greedy_heuristic(data_in_str d, float fator, time_t tstart, int tmax, int info, int modo) {

	int i, k, l;												// variaveis para iteracoes de loops
	int c;														// variavel binaria de controle

	int q;														// variavel para armazenar numero de vencedores ate' o momento
	float s;													// variavel para armazenar total pago ao leiloeiro ate' o momento

	data_out_str r;												// estrutura para armazenar dados da melhor solucao

	float* w = malloc(d.m*sizeof(float));						// vetor para armazenar valor w = p(i)/k(i) para cada comprador
	int* z = malloc(d.m*sizeof(int));							// vetor para ordenar indices dos compradores por valor decrescente de w
	int* o = malloc(d.n*sizeof(int));							// vetor para armazenar indice dos objetos ja selecionados
	int* v = malloc(d.m*sizeof(int));							// vetor para armazenar indice dos vencedores do leilao (solucao temporaria)
	r.v = malloc(d.m*sizeof(r.v));								// vetor para armazenar indice dos vencedores do leilao (melhor solucao)

	for (i = 0; i < d.m; i++) {
		r.v[i] = 0;												// inicializa vetor de vencedores (melhor solucao)
		z[i] = i;												// inicializa vetor de indices dos compradores
		w[i] = d.p[i]/d.k[i];									// calcula w para cada comprador
	}

	switch (modo) {
	
	case 1:
		quickSort(z, 0, d.m-1, w);								// ordena z por valor decrescente de w
		break;
	
	case 2:
		quickSort(z, 0, d.m-1, d.p);							// ordena z por valor decrescente de p
		break;

	}
	
	r.q = 0;													// nenhum vencedor ate' agora
	r.s = 0;													// valor total pago ao leiloeiro ate' agora = 0

	for (l = 0; l < d.m; l++) {									// para cada participante do leilao...

		if ((tmax > NO_LIMIT)&&(time_over(tstart,tmax) == YES)) break;
		
		q = 0;
		s = 0;
		for (i = 0; i < d.m; i++) v[i] = 0;						// inicializa vetor de vencedores (solucao temporaria)
		for (i = 0; i < d.n; i++) o[i] = 0;						// inicializa vetor de objetos selecionados
		
		for (k = 0; k < d.n; k++) {
			if (d.s[k][z[l]] == 1) o[k] = 1;					// ...coloca cada objeto de S(z[l]) na solucao
		}
		v[z[l]] = 1;											// coloca z[l] no vetor de vencedores
		q++;													// incrementa numero de vencedores
		s = d.p[z[l]];											// adiciona valor de p(z[l]) ao total pago ao leiloeiro
	
		for (i = 0; i < l; i++) {								// para cada participante i com indice z[i] menor do que z[l]...

			c = 0;
			for (k = 0; k < d.n; k++) {								
				if ((d.s[k][z[i]] == 1)&&(o[k] == 1)) {			// ...verifica se algum objeto de S(z[i]) ja esta na solucao
					c = 1;											
					break;											
				}
			}
			if (c == 0) {										// se nenhum objeto de S(z[i]) esta na solucao...
				for (k = 0; k < d.n; k++) {
					if (d.s[k][z[i]] == 1) o[k] = 1;			// ...coloca cada objeto de S(z[i]) na solucao
				}
				v[z[i]] = 1;									// coloca z[i] no vetor de vencedores
				q++;											// incrementa numero de vencedores
				s += d.p[z[i]];									// adiciona valor de p(z[i]) ao total pago ao leiloeiro
			}
		}
		for (i = l+1; i < d.m; i++) {							// para cada participante i com indice z[i] maior do que z[l]...
			
			c = 0;
			for (k = 0; k < d.n; k++) {								
				if ((d.s[k][z[i]] == 1)&&(o[k] == 1)) {			// ...verifica se algum objeto de S(z[i]) ja esta na solucao
					c = 1;											
					break;											
				}
			}
			if (c == 0) {										// se nenhum objeto de S(z[i]) esta na solucao...
				for (k = 0; k < d.n; k++) {
					if (d.s[k][z[i]] == 1) o[k] = 1;			// ...coloca cada objeto de S(z[i]) na solucao
				}
				v[z[i]] = 1;									// coloca z[i] no vetor de vencedores
				q++;											// incrementa numero de vencedores
				s += d.p[z[i]];				 					// adiciona valor de p(z[i]) ao total pago ao leiloeiro
			}
		
		}
		
		if (info == INFO_ON) printf("\npivot = %d: solucao = %.1f, melhor = %.1f", l, s, r.s);
		
		if (s > r.s) {											// solucao para z[i] e' a melhor encontrada ?
			r.s = s;
			r.q = q;
			for (i = 0; i < d.m; i++) {
				r.v[i] = v[i];
			}

		}
		
		if (s < fator*r.s) break;								// se solucao encontrada esta longe da melhor solucao por um fator (%), interrompe a busca

	}

	r.t = (int) difftime(time(NULL), tstart);					// calcula tempo de execucao do algoritmo

	free(v);
	free(o);
	free(z);
	free(w);

	return r;													// retorna melhor solucao encontrada

}

data_out_str greedy_heuristic(data_in_str d, time_t tstart, int tmax, int modo) {

	int i, k;													// variaveis para iteracoes de loops
	int c;														// variavel binaria de controle

	data_out_str r;
	float* w = malloc(d.m*sizeof(int));							// vetor para armazenar valor w = p(i)/k(i) para cada comprador
	int* z = malloc(d.m*sizeof(int));							// vetor para ordenar indices dos compradores por valor decrescente de w
	int* o = malloc(d.n*sizeof(int));							// vetor para armazenar indice dos objetos ja selecionados
	r.v = malloc(d.m*sizeof(r.v));								// vetor para armazenar indice dos vencedores do leilao

	for (i = 0; i < d.m; i++) {
		r.v[i] = 0;												// inicializa vetor de vencedores
		z[i] = i;												// inicializa vetor de indices dos compradores
		w[i] = d.p[i]/(float)d.k[i];							// calcula w para cada comprador
	}
	for (i = 0; i < d.n; i++) o[i] = 0;							// inicializa vetor de objetos selecionados

	switch (modo) {
	
	case 1:
		quickSort(z, 0, d.m-1, w);								// ordena z por valor decrescente de w
		break;
	
	case 2:
		quickSort(z, 0, d.m-1, d.p);							// ordena z por valor decrescente de p
		break;
	
	}

	r.q = 0;													// nenhum vencedor ate' agora
	r.s = 0;													// valor total pago ao leiloeiro ate' agora = 0

	for (i = 0; i < d.m; i++) {									// para cada participante do leilao...

		if ((tmax > NO_LIMIT)&&(time_over(tstart,tmax) == YES)) break;

		c = 0;
		for (k = 0; k < d.n; k++) {								
			if ((d.s[k][z[i]] == 1)&&(o[k] == 1)) {				// ...verifica se algum objeto de S(z[i]) ja esta na solucao
				c = 1;											
				break;											
			}
		}
		if (c == 0) {											// se nenhum objeto de S(z[i]) esta na solucao...
			for (k = 0; k < d.n; k++)
				if (d.s[k][z[i]] == 1) o[k] = 1;				// ...coloca cada objeto de S(z[i]) na solucao
			r.v[z[i]] = 1;										// coloca z[i] no vetor de vencedores
			r.q++;												// incrementa numero de vencedores
			r.s += d.p[z[i]];									// adiciona valor de p(z[i]) ao total pago ao leiloeiro
		}
	}

	r.t = (int) difftime(time(NULL), tstart);					// calcula tempo de execucao do algoritmo

	free(o);
	free(z);
	free(w);

	return r;

}

int time_over(time_t tstart, int tmax) {

	if ((tmax > NO_LIMIT)&&(time(NULL)-tstart >= tmax)) return YES;
	return NO;
}


