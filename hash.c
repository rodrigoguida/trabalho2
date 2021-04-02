# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
# include <time.h>
# define TAM_MAX 100000

struct dados
{
  int info;
  struct dados *prox;
};

typedef struct dados Dados;
typedef Dados* Hash[TAM_MAX];


int funcaoHash(int num)
{
  return(num%TAM_MAX);
}

void inicializaHash(Hash tab)
{
 int i;
 for(i = 0; i < TAM_MAX; i++)
 {
  tab[i] = NULL;
 }
}

void insereHash(Hash tab, int num)
{
 int i = 0;
 int chave = funcaoHash(num);
 Dados* aux = tab[chave];
 while(aux != NULL)
 {
  if(aux->info == num)
  {
   break;
  }
  aux = aux->prox;
 }
 if(aux == NULL)
 {
  aux = (Dados*) malloc (sizeof(Dados));
  aux->info = num;
  aux->prox = tab[chave];
  tab[chave] = aux;
 }
}


void buscaHash(Hash tab,int num)
{
 int pos = num;
 if(num > TAM_MAX || num < 0)
 {
  printf("\nPosicao nao encontrada!");
  return;
 }else
 {

}
}

void imprimeColisao(Hash tab, int pos)
{
 Dados* aux = tab[pos];
 if(aux == NULL)
 {
  printf("Esta posicao esta vazia!");
  return;
 }else
 {
  if(aux != NULL)
  {
   printf("%3d",aux->info);
   while(aux->prox != NULL)
   {
    printf(" -> %d",aux->prox->info);
    aux = aux->prox;
   }
  }
 }
}

void imprimeHash(Hash tab)
{
 int  i = 0,cont = 0;
 printf("Posicoes\tTabela");
 for(i = 0; i < TAM_MAX; i++)
 {
  if(tab[i] != NULL)
  {
   printf("\n  %d\t\t%d",i,tab[i]->info);
   Dados* aux =tab[i]->prox;
   while(aux!=NULL)
   {
    printf(" -> %3d",aux->info);
     aux=aux->prox;
   }
  }
 }
}

void removeHash(Hash tab, int num)
{
 int pos = num;
 int ex ;
 if(num > TAM_MAX)
 {
  printf("\nEsta posicao nao existe na tabela!");
 }else{
  if(tab[pos] == NULL)
  {
   printf("Esta chave esta vazia!");
  }else
  {
   printf("\n\n\n");
   imprimeColisao(tab,pos);
   printf("\n\nQual registro deseja apagar =  ");
   scanf("%d",&ex);
   if(tab[pos]->info == ex)
   {
    if(tab[pos]->prox == NULL)
    {
     tab[pos] = NULL;
     return;
    }
    if(tab[pos]->prox != NULL)
    {
     tab[pos]->info = tab[pos]->prox->info;
     tab[pos]->prox = tab[pos]->prox->prox;
     return;
    }
   }else{
   if(tab[pos]->info != ex)
   {

    if(tab[pos]->prox == NULL)
    {
     printf("\nRegistro nao encontrado!");
     getch();
     return;
    }else{
    Dados* ant = NULL;
    Dados* aux = tab[pos]->prox;
    while(aux->prox != NULL  && aux->info != ex)
    {
     ant = aux;
     aux = aux->prox;
    }
    if(aux->info != ex)
    {
     printf("\nRegistro nao encontrado!\n");
     return;
    }else
    {
    if(ant == NULL)
    {
     tab[pos]->prox = aux->prox;
    }else{
         ant->prox = aux->prox;
        }
        aux = NULL;
        free(aux);
        }
      }
     }
    }
   }
  }
}


typedef struct reg {
	int  item;
	int ocupado;
}HASH2;


int funcaohash(int  chave) {
	return (chave % TAM_MAX);
}

void inicializa(HASH2 tabHash[]) {
	int i;
	for(i=0; i<TAM_MAX; i++)
		tabHash[i].ocupado = 0;
}

void insere(HASH2 tabHash[], int  e) {

	if (cheia(tabHash)) {
		return;
	}

	int pos = funcaohash(e);


	if (tabHash[pos].ocupado == 1) {
		if (e==tabHash[pos].item) {
			return;
		}

		while (pos < TAM_MAX) {
			if (pos==TAM_MAX-1) pos=-1;
			pos++;
			if (tabHash[pos].ocupado == 0)
				break;
		}
	}


	tabHash[pos].item=e;
	tabHash[pos].ocupado = 1;

}

int busca(HASH2 tabHash[], int  chave) {
	int pos = funcaohash(chave);
	int iniciobusca = pos;
	if (tabHash[pos].ocupado == 1) {

		if (tabHash[pos].item == chave)
			return pos;

		while (pos < TAM_MAX) {
			if (pos==TAM_MAX-1) pos=-1;
			pos++;
			if (tabHash[pos].ocupado == 1 && tabHash[pos].item == chave)
				return pos;
			if (pos==iniciobusca) return -1;
		}


	}
	return -1;
}

void apaga(HASH2 tabHash[], int  chave) {
    int pos = busca(tabHash,chave);
	if (pos!=-1) {
		tabHash[pos].ocupado=0;
		printf("-> Dados HASH[%d] apagados",pos);
	}
	else printf("Item nao encontrado");
}

void imprime(HASH2 tabHash[]) {
	int i;
	for (i=0; i<TAM_MAX; i++)
		if( tabHash[i].ocupado == 1)
			printf("\nCampo [%d] = %d",i,tabHash[i].item);
}

int cheia(HASH2 tabHash[]) {
	int i, qtde=0;
	for (i=0; i<TAM_MAX; i++)
		if( tabHash[i].ocupado == 1)
			qtde++;
	if (qtde == TAM_MAX) return 1;
	else return 0;
}

main() {
	int i, pos;
	HASH2 tab[TAM_MAX];
	Hash tabela;
	inicializa(tab);
	inicializaHash(tabela);
	double start, stop, elapsed;
    srand(time(NULL));
	int vetorAleatorio[TAM_MAX-1];

	printf("Tabela Hash: Tempo de insercao\n");

    srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM_MAX-1; i++){
        vetorAleatorio[i] = (rand() % 100);
    insere(tab,vetorAleatorio[i]);
  }
	stop = (double) clock() / CLOCKS_PER_SEC;
  	elapsed = stop - start;
    printf("Hash sem Lista: %f\n", elapsed);

    srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM_MAX-1; i++){
        insereHash(tabela,vetorAleatorio[i]);
    }
	stop = (double) clock() / CLOCKS_PER_SEC;
  	elapsed = stop - start;
    printf("Hash com Lista: %f\n", elapsed);

    printf("Tabela Hash: Tempo de Busca\n");

    srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM_MAX-1; i++){
        busca(tab, vetorAleatorio[i]);
    }
	stop = (double) clock() / CLOCKS_PER_SEC;
  	elapsed = stop - start;
    printf("Hash sem Lista: %f\n", elapsed);

    srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM_MAX-1; i++){
        buscaHash(tabela,vetorAleatorio[i]);
    }
	stop = (double) clock() / CLOCKS_PER_SEC;
  	elapsed = stop - start;
    printf("Hash com Lista: %f\n", elapsed);

}
