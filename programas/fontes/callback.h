/// MC548 - PROJETO E ANALISE DE ALGORITMOS II - 1s2010
/// Prof. Flavio Keidi Miyazawa
/// ---------------------------------------------------------------
/// PROJETO PRATICO: PROBLEMA DA MOCHILA COM RESTRICOES DE CONFLITO
/// Haraldo Sergio A. Pereira Filho (003059)


// Header da biblioteca callback.c       
// Funcao de callback do otimizador inteiro do GLPK

typedef struct cb_info_str { int ctrl;			// variavel de controle de execucao das heuristicas: 0 = nao executadas, 1 = ja executadas
							 int tmax;			// tempo maximo de execucao das heuristicas
							 data_in_str d; 	// dados de entrada do problema
						   } cb_info_str ;

void usr_callback(glp_tree *tree, void *info);
/* Rotina chamada pelo GLPK no processo de branch and cut do otimizador inteiro	*/
