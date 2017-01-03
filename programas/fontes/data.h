/// MC548 - PROJETO E ANALISE DE ALGORITMOS II - 1s2010
/// Prof. Flavio Keidi Miyazawa
/// ---------------------------------------------------------------
/// PROJETO PRATICO: PROBLEMA DA MOCHILA COM RESTRICOES DE CONFLITO
/// Haraldo Sergio A. Pereira Filho (003059)


// Header da biblioteca data.c       
// Funcoes para entrada e saida de dados 

typedef	struct data_in_str { int     n;					// quantidade de objetos no conjunto N
				  	         int     m;					// quantidade de pessoas no conjunto M
				             int**   s;	   				// conjuntos S(i) de objetos: s[k][i] = 1 -> pessoa i quer objeto k				  
				             int*    k;					// quantidade de objetos k(i) no conjunto S(i)
				             float*  p;					// valor p(i) que a pessoa i paga pelo conjunto S(i) de objetos
				           } data_in_str ;

typedef	struct data_out_str { char  a;					// algoritmo utilizado
							  int   t;					// tempo em segundos da execucao do programa
							  int   m;					// quantidade de pessoas no conjunto M
							  int   q;					// quantidade de vencedores do leilao
							  int*  v;				    // conjunto de vencedores do leilao: v[i] = 1 -> pessoa i venceu leilao
							  float s;					// total pago ao leiloeiro (solucao)
				            } data_out_str ;

data_in_str read_input_file(char* file);
/* le o arquivo de entrada e retorna uma estrutura contendo os dados de entrada */       

int write_output_file(char* file, data_out_str r);
/* escreve o arquivo de saida com os resultados obtidos */

data_in_str copy_in_struct(data_in_str d);
/* copia estrutura de entrada */

data_out_str copy_out_struct(data_out_str r);
/* copia estrutura de saida */

void free_in_struct(data_in_str d) ;
/* libera memoria alocada para estrutura de entrada */

void free_out_struct(data_out_str r) ;
/* libera memoria alocada para estrutura de saida */
