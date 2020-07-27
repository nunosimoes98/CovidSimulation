#include "functions.h"

void limpaStdin() {

	scanf("%*[^\n]");

}

void pause() {

	int numero;

	do {
		printf("\n\tIntroduza a tecla [0] para continuar!\n");
		scanf(" %d", &numero);

		if (numero != 0) {
			limpaStdin();
		}

	} while (numero != 0);

}

void limpaEcra() {
	int i;
	for (i = 0; i < 15; i++)
		printf("\n");

}

void menuInicial() {
	printf("\n\tBEM-VINDO AO SIMULADOR DE COVID-19!\n\n");
	printf("\n\tAntes de se proceder a sua simulacao vai ser necessario prepapar o ambiente.\n");
}

pessoa* obtemFichPessoas(pessoa *pessoas, int *nPessoas) {

	char nomeFich[TAM_TEXTO];

	printf("\n\tIndique nome da populacao que quer utilizar:");
	scanf(" %99[^\n]", nomeFich);
	limpaStdin();

	pessoas = leFicheiroPessoas(nomeFich, pessoas, nPessoas);

	return pessoas;
}

local* obtemFichSalas(local *salas, int *nSalas) {
	char nomeFich[TAM_TEXTO];

	printf("\n\tIndique o nome do espaco que quer utilizar:");
	scanf(" %99[^\n]", nomeFich);
	limpaStdin();

	salas = leFicheiroSalas(nomeFich, salas, nSalas);

	return salas;
}

void mostraEstatisticas(espaco *eLista) {
	espaco *aux=NULL;
	populacao *auxP;


	 aux = eLista;  

	while (aux != NULL) {
		printf("\n\n\tSala:%d\n\tNumero de pessoas:%d\n\tPessoas Doentes:%d\n\tPessoas Imunes:%d\n\tPessoas Saudaveis:%d\n", aux->local->id, aux->nPessoas, aux->pessoasDoentes,aux->pessoasImunes,aux->pessoasSaudaveis);
		auxP = NULL;
		auxP = aux->listaPessoas;
		while (auxP != NULL) {

			printf("\n\t\tPessoa ID:%s\n\t\tEstado:%c\n", auxP->pessoa->id,auxP->pessoa->estado);
		
			if (auxP->pessoa->estado == 'D') {
				printf("\t\tNumero de dias infetado:%d\n", auxP->pessoa->nrDiasInfetado);
			}

			auxP = auxP->prox;
		}

		aux = aux->prox;

	}



}