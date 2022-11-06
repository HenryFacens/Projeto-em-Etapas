/*
typedef struct  aluno{
	char nome[80];
	char RA[7];
	int emprestado;           // qtde de livros emprestados – Max=3
	int reservado;              // qtde de livros reservados – Max =1
struct info_livro tabela[4];                  //Obs.: (p->tabela+i)->sigla
}aluno;//Obs.: (p->tabela+i)->reg

struct info_livro{
    char sigla; // [L]ivre, [E]mprestado, [R]eservado
    int reg;// registro do livro
};

Menu
[1] Cadastro Aluno
[2] Mostra Aluno Total
[3] Mostra Aluno Parcial
[4] Fim 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <conio.h>

struct info_livro{
    char sigla; // [L]ivre, [E]mprestado, [R]eservado
    int reg; // registro do livro
};

typedef struct  aluno{
	
	char nome[80];
	char RA[7];
	int emprestado;           // qtde de livros emprestados – Max=3
	int reservado;              // qtde de livros reservados – Max =1
	struct info_livro tabela[4];  //Obs.: (p->tabela+i)->sigla

}aluno;	//Obs.: (p->tabela+i)->reg



void aloca_aluno(aluno **al,int count);
int verifica();
void grava_aluno(aluno *al);
void cadastra_aluno(aluno *al,int count);
void mostra_cadastros(aluno *al,int count);
void mostra_individual(aluno *al,int count);
void cadastra_info_livro(aluno *al,int count);
int verifica_ra(aluno *al,int count);

//void mostra_tabelas(aluno *al,int count); // teste

void cadastra_aluno(aluno *al,int count)
{
	char ra[7];
	int verifica;
	
	printf("\nNome :");
	gets(al->nome);
	printf("\nRA: ");
	gets(al->RA);
	al->emprestado = 0;
	al->reservado = 0;
	grava_aluno(al);
}

main()
{
	char op;
	int sw;
	int count = 0;
	
	aluno *al = NULL;
	FILE *f = NULL;
	
	aloca_aluno(&al,1);
	count = verifica();
	
	cadastra_info_livro(al,4);
	
	
	do
	{
		printf("\n\tMenu \n[1] Cadastro Aluno \n[2] Mostra Aluno Total \n[3] Mostra Aluno Parcial \n[4] Fim\nResposta:");
		scanf("%i",&sw);
		fflush(stdin);
		
		switch(sw)
		{
			case 1:
				cadastra_aluno(al,count+1);
				count++;
				break;
			case 2:
				mostra_cadastros(al,count);
				break;
			case 3:
				mostra_individual(al,count);
				break;
			case 4:
				exit(1);
				break;
			case 5:
				//mostra_tabelas(al,4); // teste secreto
				break;
		}
		printf("\nDESEJA CONTINUAR (S/N)\nResposta: ");
		scanf("%c",&op);
		fflush(stdin);
		
	}while(op != 'N' && op != 'n');
	
}

void cadastra_info_livro(aluno *al,int count)
{
	int aux;
	
	for(aux=0;aux<count;aux++,al++) // para testar coloque 3 e no for abaixo coloque 1
	{
			(al->tabela)->sigla = 'L';
			// printf("%c",(al->tabela)->sigla); // verificar se esta cadastrando 
	}
	
	/*for(aux=0;aux<1;aux++,al++) // TESTE para ver se printa o E na tabela hehe
	{
		(al->tabela)->sigla = 'E';
		printf("%c",(al->tabela)->sigla);
	}*/
	
}

void mostra_individual(aluno *al,int count)
{
	char ra[7];
	int aux;
	char op;
	int i;
	
	aux = count;
	
	FILE *f = fopen("aluno.bin","rb");
		if(f==NULL)
			printf("\nErro\n");
		else
		{	
			printf("\nColoque o RA do Aluno \n");
			printf("RA:");
			scanf("%s",&ra);
			fflush(stdin);
			
			for(aux=0;aux<count;aux++)
			{
				
			fseek(f,aux*sizeof(aluno),0);
			fread(al,sizeof(aluno),1,f);
			
				if(strcasecmp(al->RA,ra)==0)
				{
					printf("\nNome: [%s]",al->nome);
					printf("\t|RA: [%s]",al->RA);
					printf("\t|Livros Emprestados: [%i]",al->emprestado);
					printf("\t|Livros Reservados [%i]",al->reservado);
					for(i=0;i<4;i++,al++)
					{
						printf("\nTABELA %i [%c - ]",i,(al->tabela)->sigla);
					}
				}	
			}
			return;
		}
	printf("\nAluno nao cadastrado :p\n");
}



void mostra_cadastros(aluno *al,int count)
{
	int i;
	
	FILE *f = fopen("aluno.bin","rb");
	

	
	if(f==NULL)
		printf("\nErro\n");
	else
	{
		for(i=0;i<count;i++)
		{
			fseek(f,i*sizeof(aluno),0);
			fread(al,sizeof(aluno),1,f);
			printf("\nNome: [%s]",al->nome);
			printf("\nRA: [%s]",al->RA);
			printf("\nLivros Emprestados: [%i]",al->emprestado);
			printf("\nLivros Reservados [%i]\n\n",al->reservado);
		}
	fclose(f);
	}
	system("pause");
}


void grava_aluno(aluno *al)
{
	FILE *f = fopen("aluno.bin","ab");
	fseek(f,sizeof(aluno),2);
	if(f==NULL)
	{
		printf("\n\nErro");
	}
	else
		fwrite(al,sizeof(aluno),1,f);
	fclose(f);
}

int verifica()
{
	long int count = 0;
	FILE *f = fopen("aluno.bin","rb");
	
	if(f == NULL)
		return count;
	else
	{
		fseek(f,0,2);
		count = ftell(f)/sizeof(aluno);
		fclose(f);
		return count;
	}
}

void aloca_aluno(aluno **al,int count)
{
	if((*al=(aluno*)realloc(*al,count*sizeof(aluno)))==NULL)
		exit(1);
}

/*void mostra_tabelas(aluno *al,int count)
{
	int i;
	for(i=0;i<count;i++,al++)
	{
		printf("%c",(al->tabela)->sigla);
	}
}*/

//BY HENRY SANTURIAO ALMEIDA
