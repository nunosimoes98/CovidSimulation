#include "functions.h"


local* leFicheiroSalas(char * nomeFich, local *salas, int *nSalas) {
	local sala;
	int s;
	local *aux=NULL;
	int i = 0;
	FILE* fSalas;
	int flag = 0;

	fSalas = fopen(nomeFich, "rb");

	if (fSalas == NULL) {

		printf("\n\n\t[erro] ao abrir o ficheiro do espaco para leitura!!\n");

		exit(EXIT_FAILURE);
	}

	while (fread(&s, sizeof(int), 1, fSalas) == 1) {
		flag = 1;
		sala.id = s;

		if (sala.id < 0) {
			fclose(fSalas);
			free(salas);
			printf("\n\n\t[erro] o ID nao e positivo!!\n");
			exit(EXIT_FAILURE);
		}

		if (fread(&s, sizeof(int), 1, fSalas) != 1) {
			fclose(fSalas);
			free(salas);
			printf("\n\n\t[erro] a ler a capacidade das salas!!");
			exit(EXIT_FAILURE);
		}

		sala.capacidade = s;

		if (sala.capacidade < 0) {
			fclose(fSalas);
			free(salas);
			printf("\n\n\t[erro] a capacidade nao e positiva!!\n");
			exit(EXIT_FAILURE);
		}

		for (int j = 0; j < 3; j++) {
			if (fread(&s, sizeof(int), 1, fSalas) != 1) {
				fclose(fSalas);
				free(salas);
				printf("\n\n\t[erro] a ler a ligacao das salas!!\n");
				exit(EXIT_FAILURE);
			}
			sala.liga[j] = s;
		}

		aux= realloc(salas, sizeof(local) * (i + 1));
		
		if (aux == NULL) {
			free(salas);
			fclose(fSalas);
			printf("\n\n\t[erro] sem memoria para realocar os locais!!\n");
			exit(EXIT_FAILURE);

		}

		salas = aux;

		salas[i] = sala;

		i++;

	}
    
	if (flag == 0) {
		fclose(fSalas);
		printf("\n\n\t[erro] a ler o id das salas!!");
		exit(EXIT_FAILURE);

	}

	*nSalas = i;

	fclose(fSalas);

	return salas;

}

int ficheiroPessoa(pessoa *p, FILE *fPessoa) {

	int res;
	

	res = fscanf(fPessoa, " %99[^' ']", p->id);

	if (res == EOF) {
		return 0;
	}

	res = fscanf(fPessoa," %d", &(p->idade));
	if (res != 1) {
		printf("\n\n\t[erro] na leitura da idade!!\n");
		return -1;
	}


	res = fscanf(fPessoa, " %c",&(p->estado));
	if (res != 1) {
		printf("\n\n\t[erro] na leitura do estado!!\n");
		return -1;
	}

	if (p->estado == 'D') {
	
		res = fscanf(fPessoa, " %d",&(p->nrDiasInfetado));
		p->Curada = NAO;
	
	}
	else if (p->estado== 'S'){
		p->nrDiasInfetado = 0;
		p->Curada = NAO;
	}
	else {
		p->Curada = SIM;
		p->nrDiasInfetado = 0;
	}

	res = verificaNumerosLidos(p);
	if (res == -1) {
		printf("\n\n\t[erro]Existe numeros invalidos no ficheiro da populacao!\n");
		return -1;
	}

	p->pessoaA = NAO;
	p->ficouImune = NAO;

	return 1;
}

pessoa* leFicheiroPessoas(char *nomeFich, pessoa *pessoas, int *nPessoas) {
	FILE *fPessoa;
	int i = 0, res;
	pessoa p;
	pessoa *aux;


	fPessoa = fopen(nomeFich, "rt");

	if (fPessoa == NULL) {

		printf("Erro ao abrir o ficheiro da populacao ara leitura!!\n");

		exit(EXIT_FAILURE);
	}

	while ((res = ficheiroPessoa(&p, fPessoa)) == 1) {

		aux = realloc(pessoas, sizeof(pessoa) * (i + 1));

		if (aux == NULL) {
			free(pessoas);
			fclose(fPessoa);
			printf("[Erro] sem memoria para as pessoas!!\n");
			exit(EXIT_FAILURE);

		}

		pessoas = aux;

		pessoas[i] = p;
		pessoas[i].localOndeSeEncontra = NULL;

		i++;

	}

	if (res == -1) {
		free(pessoas);
		fclose(fPessoa);
		exit(EXIT_FAILURE);

	}

	*nPessoas = i;

	fclose(fPessoa);

	return pessoas;

}

void escrevePessoasFich(char *nomeFich,pessoa *pessoas,int nPessoas) {
	FILE *fp;

	fp= fopen(nomeFich, "wt");

	if (fp == NULL) {
		printf("Erro ao abrir/criar o ficheiro %s para escrita!!\n",nomeFich);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < nPessoas; i++) {
		fprintf(fp, "%s", pessoas[i].id);
		fprintf(fp, "  ");
		fprintf(fp, "%d", pessoas[i].idade);
		fprintf(fp, "  ");
		fprintf(fp, "%c", pessoas[i].estado);

		if (pessoas[i].estado == 'D') {
			fprintf(fp, "  ");
			fprintf(fp, "%d\n", pessoas[i].nrDiasInfetado);
		
		}
		else {
			fputc('\n', fp);
		}
	
	}

	fclose(fp);
}

void escreveFichPessoas(pessoa* pessoas, int nPessoas) {
	char nomeFich[TAM_TEXTO];
	int tam;
	char nomeFichAux[TAM_TEXTO] = ".txt";
	int c,cAux;
	
	
	do {

		printf("\n\n\tInsira o nome do ficheiro onde quer guardar as pessoas:");
		scanf(" %99[^\n]", nomeFich);
		limpaStdin();

		tam = strlen(nomeFich);

		c = 0;
		cAux = 3;
		for (int i = tam-1; i >= 0; i--) {
			if (nomeFich[i] == nomeFichAux[cAux]) {
				c++;
				cAux--;
			}
			if (c == 4) {

				break;
			}
		}

		if (c != 4) {
			printf("\n\n\tO ficheiro tem que terminar com a extensao .txt");
		
		}

	} while (c != 4);


	escrevePessoasFich(nomeFich, pessoas, nPessoas);

}