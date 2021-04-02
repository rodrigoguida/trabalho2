# include <stdio.h>
# include <stdlib.h>
# include <conio.h>
# include <time.h>
# define TAM_MAX 100000


typedef struct NO{
    int info;
    int altura;
    struct NO *esq;
    struct NO *dir;
}NO;

typedef struct NO* ArvAVL;


ArvAVL* cria_ArvAVL(){
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);
    free(raiz);
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}

void preOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("No %d: %d\n",(*raiz)->info,altura_NO(*raiz));
        preOrdem_ArvAVL(&((*raiz)->esq));
        preOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        printf("No %d: H(%d) fb(%d)\n",(*raiz)->info,altura_NO(*raiz),fatorBalanceamento_NO(*raiz));
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void posOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        posOrdem_ArvAVL(&((*raiz)->esq));
        posOrdem_ArvAVL(&((*raiz)->dir));
        printf("%d\n",(*raiz)->info);
    }
}

int consulta_ArvAVL(ArvAVL *raiz, int valor){
    if(raiz == NULL)
        return 0;
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info){
            return 1;
        }
        if(valor > atual->info)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

//=================================
void RotacaoLL(ArvAVL *A){
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A){
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A){
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}

int insere_ArvAVL(ArvAVL *raiz, int valor){
    int res;
    if(*raiz == NULL){
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        novo->info = valor;
        novo->altura = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;
    if(valor < atual->info){
        if((res = insere_ArvAVL(&(atual->esq), valor)) == 1){
            if(fatorBalanceamento_NO(atual) >= 2){
                if(valor < (*raiz)->esq->info ){
                    RotacaoLL(raiz);
                }else{
                    RotacaoLR(raiz);
                }
            }
        }
    }else{
        if(valor > atual->info){
            if((res = insere_ArvAVL(&(atual->dir), valor)) == 1){
                if(fatorBalanceamento_NO(atual) >= 2){
                    if((*raiz)->dir->info < valor){
                        RotacaoRR(raiz);
                    }else{
                        RotacaoRL(raiz);
                    }
                }
            }
        }else{
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}

struct NO* procuraMenor(struct NO* atual){
    struct NO *no1 = atual;
    struct NO *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int remove_ArvAVL(ArvAVL *raiz, int valor){
	if(*raiz == NULL){
	    return 0;
	}

    int res;
	if(valor < (*raiz)->info){
	    if((res = remove_ArvAVL(&(*raiz)->esq,valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->dir->esq) <= altura_NO((*raiz)->dir->dir))
                    RotacaoRR(raiz);
                else
                    RotacaoRL(raiz);
            }
	    }
	}

	if((*raiz)->info < valor){
	    if((res = remove_ArvAVL(&(*raiz)->dir, valor)) == 1){
            if(fatorBalanceamento_NO(*raiz) >= 2){
                if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq) )
                    RotacaoLL(raiz);
                else
                    RotacaoLR(raiz);
            }
	    }
	}

	if((*raiz)->info == valor){
	    if(((*raiz)->esq == NULL || (*raiz)->dir == NULL)){// nó tem 1 filho ou nenhum
			struct NO *oldNode = (*raiz);
			if((*raiz)->esq != NULL)
                *raiz = (*raiz)->esq;
            else
                *raiz = (*raiz)->dir;
			free(oldNode);
		}else { // nó tem 2 filhos
			struct NO* temp = procuraMenor((*raiz)->dir);
			(*raiz)->info = temp->info;
			remove_ArvAVL(&(*raiz)->dir, (*raiz)->info);
            if(fatorBalanceamento_NO(*raiz) >= 2){
				if(altura_NO((*raiz)->esq->dir) <= altura_NO((*raiz)->esq->esq))
					RotacaoLL(raiz);
				else
					RotacaoLR(raiz);
			}
		}
		if (*raiz != NULL)
            (*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;
		return 1;
	}

	(*raiz)->altura = maior(altura_NO((*raiz)->esq),altura_NO((*raiz)->dir)) + 1;

	return res;
}

int buscar(NO* p, int x)
{
    if(p == NULL)
    {
        return 0;
    }
    else if(p->info == x)
    {
        return 1;
    }
    else if(x < p->info)
    {
        return buscar(p->esq, x);
    }
    else
    {
        return buscar(p->dir, x);
    }
}

NO* inserir(NO* p, int x)
{
    if (p == NULL)
    {
        p = malloc(sizeof(NO));
        p->info = x;
        p->esq = NULL;
        p->dir = NULL;
    }
    else if(x < p->info)
    {
        p->esq = inserir(p->esq, x);
    }
    else if(x > p->info)
    {
        p->dir = inserir(p->dir, x);
    }

    return p;
}

NO *removeFolha(NO *p)
{
    free(p);
    return NULL;
}

NO *removeUmFilho(NO *p)
{
    NO *aux;

    if(p->esq == NULL)
    {
        aux = p->dir;
    }
    else
    {
        aux = p->esq;
    }

    free(p);
    return aux;
}

NO *menorDaSubArvoreDireita(NO *p)
{
    NO *aux = p->dir;
    while(aux->esq != NULL)
    {
        aux = aux->esq;
    }
    return aux;
}

NO *remover(NO *p, int x)
{
    if(p == NULL)
    {
        return NULL;

    }
    else if(x < p->info)
    {
        p->esq = remover(p->esq, x);
    }
    else if(x > p->info)
    {
        p->dir = remover(p->dir, x);
    }
    else
    {
        if(p->esq == NULL && p->dir == NULL)
        {
            p = removeFolha(p);
        }
        else if(p->esq == NULL || p->dir == NULL)
        {
            p = removeUmFilho(p);
        }
        else
        {
            NO *aux = menorDaSubArvoreDireita(p);
            int tmp = p->info;
            p->info = aux->info;
            aux->info = tmp;

            p->dir = remover(p->dir, x);
        }
    }
    return p;
}



int main(){
	ArvAVL* avl;
	NO *abb = NULL;
	avl = cria_ArvAVL();
	int i;

	double start, stop, elapsed;
    srand(time(NULL));
	int vetorAleatorio[TAM_MAX-1];

	printf("Arvores: Tempo de insercao\n");

    srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM_MAX-1; i++){
        vetorAleatorio[i] = (rand() % 100);
    }

    for (i = 0; i < TAM_MAX-1; i++){
        inserir(abb,vetorAleatorio[i]);
    }
	stop = (double) clock() / CLOCKS_PER_SEC;
  	elapsed = stop - start;
    printf("ABB: %f\n", elapsed);

    srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM_MAX-1; i++){
        vetorAleatorio[i] = (rand() % 100);
        insere_ArvAVL(avl,vetorAleatorio[i]);
    }
	stop = (double) clock() / CLOCKS_PER_SEC;
  	elapsed = stop - start;
    printf("AVL: %f\n", elapsed);


    printf("Arvores: Tempo de Busca\n");

    srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM_MAX-1; i++){
        consulta_ArvAVL((abb),vetorAleatorio[i]);
    }
	stop = (double) clock() / CLOCKS_PER_SEC;
  	elapsed = stop - start;
    printf("ABB: %f\n", elapsed );

    srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM_MAX-1; i++){
        consulta_ArvAVL(avl,vetorAleatorio[i]);
    }
	stop = (double) clock() / CLOCKS_PER_SEC;
  	elapsed = stop - start;
    printf("AVL: %f\n", (elapsed ));


    printf("Arvores: Tempo de Exclusao\n");

    srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM_MAX-1; i++){
		remover(abb,vetorAleatorio[i]);
    }
	stop = (double) clock() / CLOCKS_PER_SEC;
  	elapsed = stop - start;
    printf("ABB: %f\n", elapsed);


    srand((unsigned)time(NULL));
	start = (double) clock() / CLOCKS_PER_SEC;
	for (i = 0; i < TAM_MAX-1; i++){
		remove_ArvAVL(avl,vetorAleatorio[i]);
    }
	stop = (double) clock() / CLOCKS_PER_SEC;
  	elapsed = stop - start;
    printf("AVL: %f\n", elapsed);
    }
