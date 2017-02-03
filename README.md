#Problema da Mochila com Restrições de Conflito
##Definição do problema
Um leiloeiro tem n objetos para leiloar, onde os objetos sao dados pelo conjunto N = {0, ..., n − 1}. Há m
pessoas interessadas nos objetos, onde as pessoas são dadas pelo conjunto M = {0, ..., m − 1}. Cada pessoa
está interessada em exatamente um subconjunto de objetos. A pessoa i está interessada no conjunto S i ⊆ N
e dá um lance de valor p i pelo conjunto todo. Neste leilão a pessoa está interessada em apenas este conjunto e
não tem interesse em pegar menos objetos que os de interesse. Naturalmente um objeto não pode ser vendido
para duas pessoas diferentes. Além disso, pode ser que alguns objetos não sejam vendidos para ninguém.
O problema consiste em definir as pessoas que vencem o leilão. Uma pessoa i é um vencedor do leilão, se
ela obtém todos os objetos em S i e com isso paga p i ao leiloeiro por todos os objetos que está levando. Os
perdedores não levam nada nem pagam nada.
O leiloeiro recebe todos os lances e só depois escolhe os vencedores. Como ele quer maximizar o valor da
venda, ele deve escolher os vencedores de maneira que o valor total pago a ele seja máximo.
##Referências
- [Enunciado do projeto](https://github.com/HaraldoFilho/Problema-da-Mochila-com-Restricoes-de-Conflito/blob/master/enunciado.pdf)
- [Relatório do projeto](https://github.com/HaraldoFilho/Problema-da-Mochila-com-Restricoes-de-Conflito/blob/master/relatorio.pdf)
- [Página do GLPK](https://www.gnu.org/software/glpk/)
