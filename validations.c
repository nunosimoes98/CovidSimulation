#include "functions.h"

int verificaNumerosLidos(pessoa *p) {

	if (p->idade < 0 || p->nrDiasInfetado < 0) {
		return -1;
	}

	return 0;
}

void validacoesSalasId(local* salas, int  nSalas) {
	local* aux;

	aux = salas;

	for (int i = 0; i < nSalas; i++) {
		for (int j = i; j < nSalas; j++) {
			if (salas[i].id == aux[j].id && j != i) {
				printf("\n\n\t[erro] existem IDs iguais nos espacos para as populacoes!!\n");
				exit(EXIT_FAILURE);
			}
		}
	}

}

void validacoesSalasLigacoes(local *salas, int nSalas){
	local *aux;
	int flag;
	
	aux = salas;

	for (int i = 0; i < nSalas; i++) {
		for (int j = 0; j < 3; j++) {
			flag = 0;
			for (int k = 0; k < nSalas; k++) {

				if (salas[i].liga[j] == aux[k].id && salas[i].liga[j]!= -1) {
					for (int z = 0; z < 3; z++) {

						if (salas[i].id == aux[k].liga[z]) {
						   
							flag = 1;
							
						}	
					}
				}

				if (flag == 1) {
					break;
				}

			}
			if (salas[i].liga[j] == -1) {
				flag = 1;
			}

			 if(flag == 0) {
				printf("\n\n\t[erro] nao existem ligacoes corretas\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

void validacoesSalas(local  *salas, int nSalas) {

	validacoesSalasId(salas,nSalas);

	validacoesSalasLigacoes(salas, nSalas);

}

void validacaoPessoasID(pessoa *pessoas,int  nPessoas) {

	pessoa *aux;

	aux = pessoas;

	for (int i = 0; i < nPessoas; i++) {
		for (int j = i; j < nPessoas; j++) {
			if (strcmp(pessoas[i].id,aux[j].id)==0 && j != i) {
				printf("\n\n\t[erro] existem IDs iguais na populacao\n");
				exit(EXIT_FAILURE);
			}
		}
	}

}

espaco*  verificarSeFicaImune(espaco *eLista,pessoa *pessoas, int nPessoas) {
	int res;

	for (int i = 0; i < nPessoas; i++) {
	
		if (pessoas[i].Curada==SIM && pessoas[i].curadaNoDiaAtual == NAO && pessoas[i].localOndeSeEncontra != NULL && pessoas[i].estado=='S') {
		
			res=intUniformRnd(1, 100);

			if (res <= 20 && res > 0) {
				pessoas[i].estado = 'I';
				pessoas[i].nrDiasInfetado = 0;
				pessoas[i].ficouImune = SIM;
				eLista=atualizaImunidadeNaLista(eLista,&(pessoas[i]));
			
			}

		}
	
	}
	
	return eLista;
}

void pedirEverificarIdLocal(local* salas, int nSalas, int *idLocal, espaco *eLista) {
	int flag;
	int capacidade;
	espaco *aux;

	do {
		aux = NULL;
		aux = eLista;
		flag = NAO_ULTRAPASSOU_CAPACIDADE;

		printf("\n\t\tSalas Disponiveis:");
		for (int i = 0; i < nSalas; i++) {
			printf("\n\t\tSala numero:%d", salas[i].id);
		}
		printf("\n\n\t\tIntroduza o numero da sala:");
		scanf("%d", idLocal);
		limpaStdin();

		while (aux != NULL && aux->local->id != *idLocal){

			aux = aux->prox;
		}

		if (aux == NULL) {
			printf("\n\n\t\t[erro]Numero de sala introduzido Invalido!!\n");
		}
		else {
			capacidade = ((aux->local->capacidade - aux->nPessoas)-1);

			if (capacidade < 0) {
				flag = ULTRAPASSOU_CAPCIDADE;
				printf("\n\n\t\t[erro]Ultrapassou a capacidade da sala!!\n");
			}
		}
	   
	} while (aux == NULL || flag!=NAO_ULTRAPASSOU_CAPACIDADE);



}

void pedirEverificarIdPessoa(char *idPessoa, pessoa *pessoas, int nPessoas) {

	int flag;

	do {
		flag = NAO_ENCONTROU;
		printf("\n\n\t\tIntroduza o id da pessoa:");
		scanf(" %99[^\n]", idPessoa);
		limpaStdin();

		for (int i = 0; i < nPessoas; i++) {
			if (strcmp(idPessoa,pessoas[i].id)==0) {
				flag = ENCONTROU;
				break;
			}

		}
		if (flag == ENCONTROU) {

			printf("\n\n\t\t[erro]Numero de id introduzido e Invalido pois ja existe esse id!!\n");
		}

	} while (flag != NAO_ENCONTROU);

}

void pedirEverificarIdade(int *idade) {

	do {
		printf("\n\n\t\tIntroduza a sua idade:");
		scanf("%d", idade);
		limpaStdin();

		if (*idade<=0) {

			printf("\n\n\t\t[erro]Numero de idade introduzido Invalido!!\n");
		}

	} while(*idade<=0);

}

void pedirEverificarNumeroDiaDeInfecao(int *nrDiasInf,int idade) {
	int res;
	int nrDiasInfAux;
	
	do {
		printf("\n\n\t\tIntroduza o numero de dias de infecao:");
		scanf("%d", nrDiasInf);
		limpaStdin();

		res = idade / 10;
		nrDiasInfAux= 5 + res;

		if (*nrDiasInf <= 0 || *nrDiasInf > nrDiasInfAux) {

			printf("\n\n\t\t[erro]Numero introduzido invalido, tem que ser positivo ou menor do que o introduziu!!\n");
		}

	} while (*nrDiasInf <= 0 || *nrDiasInf > nrDiasInfAux);


}

void pedirEverificarIdsEnPessoasAmover(espaco* eLista,int *idOrigem, int *idDestino,int *nPessoasMover,local *salas,int nSalas) {
	espaco* aux,*aux1;
	int flag,capacidade,flag1;


	do {
		aux = NULL;
		aux = eLista;
		
		printf("\n\t\tSalas Disponiveis:");
		for (int i = 0; i < nSalas; i++) {
			printf("\n\t\tSala numero:%d",salas[i].id);
		}
		
		printf("\n\n\t\tIntroduza o numero da sala de origem:");
		scanf("%d", idOrigem);
		limpaStdin();

		while (aux != NULL && aux->local->id != *idOrigem) {

			aux = aux->prox;
		}

		if (aux == NULL) {
			printf("\n\n\t\t[erro]Numero de sala introduzido Invalido!!\n");
		}
		
	} while (aux == NULL);

	if (aux->nPessoas > 0) {

		do {
			printf("\n\t\tA sala %d tem ligacao com a(s) sala(s):", *idOrigem);
			for (int j = 0; j < 3; j++) {

				if (aux->local->liga[j] != -1) {
					printf("\n\t\tSala numero:%d", aux->local->liga[j]);
				}

			}

			flag = NAO_ENCONTROU;
			printf("\n\n\t\tIntroduza o numero da sala de destino:");
			scanf("%d", idDestino);
			limpaStdin();

			for (int k = 0; k < 3; k++) {
				if (aux->local->liga[k] == *idDestino && aux->local->liga[k] >= 0) {
					flag = ENCONTROU;
				}

			}

			if (flag == NAO_ENCONTROU) {
				printf("\n\n\t\t[erro]A sala numero %d nao tem ligacao com a sala numero %d!!\n", aux->local->id, *idDestino);
			}


		} while (flag == NAO_ENCONTROU);

		aux1 = NULL;
		aux1 = eLista;

		while (aux1->local->id != *idDestino) {
			aux1 = aux1->prox;
		}

		if ((aux1->local->capacidade - aux1->nPessoas) <= 0) {

			printf("\n\n\t\t[erro]A sala numero %d esta completa nao e possivel mover pessoas!!\n", *idDestino);
		}
		else {
			do {
				flag1 = NAO_ULTRAPASSOU_CAPACIDADE;


				printf("\n\t\t E possivel mover ate %d pessoas", (aux1->local->capacidade - aux1->nPessoas));
				printf("\n\n\t\tIntroduza o numero de pessoas a mover:");
				scanf("%d", nPessoasMover);
				limpaStdin();

				if (*nPessoasMover > (aux1->local->capacidade - aux1->nPessoas) || *nPessoasMover <= 0) {
					printf("\n\n\t\t[erro]Numero de pessoas a mover e superior ao da sala ou numeros de pessoas tem quer ser positivo!!\n");

				}
				else {


					capacidade = ((aux1->local->capacidade - aux1->nPessoas) - *nPessoasMover);

					if (capacidade < 0) {

						printf("\n\n\t\t[erro]Nao e possivel adicionar no destino %d, pois ultrapassa a capacidade!!\n", *idDestino);
					}
				}


			} while (*nPessoasMover > (aux1->local->capacidade - aux1->nPessoas) || *nPessoasMover <= 0 || *nPessoasMover > aux->nPessoas);

		}
		
	}
	else {
		printf("\n\n\t\t[erro]Nao existem pessoas no local %d para poder mover!!\n",*idOrigem);
	
	}
}
