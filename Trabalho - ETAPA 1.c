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

 
struct  info_aluno{ 
 char   sigla;
 char   RA[7]; 
 int   dia_ret;   // dia – máx=31 
 int   mes_ret;   // mes: fev=28 dias 
 int   dia_dev;   // mes: abril=jun=set=nov=30 dias 
 int   mes_dev;   // os demais = 31 dias
 };

typedef struct    livro{ 
 int   reg_livro;    // gerado automaticamente 
 char   titulo[80]; 
 char   autor[80]; 
struct info_aluno status[2];   //Obs.: (p->status+i)->sigla
} livro; 

struct  info_livro{ 
 char  sigla;    // [L]ivre, [E]mprestado, [R]eservado 
 int  reg;   // registro do livro 
}; 

typedef struct  aluno{
	
	char nome[80];
	char RA[7];
	int emprestado;           // qtde de livros emprestados – Max=3
	int reservado;              // qtde de livros reservados – Max =1
	struct info_livro tabela[4];  //Obs.: (p->tabela+i)->sigla

}aluno;	//Obs.: (p->tabela+i)->reg

void consulta_livros(aluno *al,livro *lv,int count);
int escolha_livro(aluno *al,livro *lv,int count);
int verifica_livro();
void cadastra_livro(livro *lv,int count);
void aloca_aluno(aluno **al,int count);
void aloca_livro(livro **lv, int count);
int verifica();
void grava_aluno(aluno *al);
void cadastra_aluno(aluno *al,livro *lv,int count);
void mostra_cadastros(aluno *al,livro *lv,int count);
void mostra_individual(aluno *al,livro *lv,int count, int contdr);
void cadastra_info_livro(aluno *al,int count);
int verifica_ra(aluno *al,int count);
void grava_livro(livro *lv);
void mostra_cadastra_livro(livro *lv,int count);
void emprestar_livro(aluno *al,livro *lv,int count, int contdr);



	/*for(i=0;i<count;i++,al++)
	{
		if(strcasecmp((lv->status)->RA,ra) == 0 && strcasecmp(al->RA,ra) == 0)
		{
			al->
			(lv->status)->
		}
	}*/
	//printf("\nAluno nao cadastrado");
//void mostra_tabelas(aluno *al,int count); // teste
//void mostra_cadastra_livro(livro *lv,int count); // teste
int verifica_vazio(aluno *al,livro *lv,int count, int contdr);

int main()
{
	char op;
	int sw;
	int count = 0;
	int contdr = 0;

	livro *lv = NULL;
	aluno *al = NULL;
	FILE *f = NULL;
	
	aloca_aluno(&al,1);
	aloca_livro(&lv,4);

	count = verifica();
	contdr = verifica_livro();
	
	cadastra_info_livro(al,4);
	cadastra_livro(lv,4);
	
	do
	{
		printf("\n\tMenu \n[1] Cadastro Aluno \n[2] Emprestar LIVRO \n[3] Mostra Aluno Total\n[4] Mostra Aluno Parcial \n[5] Consulta de LIVROS \n[6] Fim\nResposta:");
		scanf("%i",&sw);
		fflush(stdin);
		
		switch(sw)
		{
			case 1:
				cadastra_aluno(al,lv,count+1);
				break;
			case 2:
				emprestar_livro(al,lv,count,contdr);
				break;
			case 3:
				mostra_cadastros(al,lv,count);
				break;
			case 4:
				mostra_individual(al,lv,count,contdr);
				break;
			case 5:
				consulta_livros(al,lv,contdr);
				break;
			case 6:
				exit(1);
				break;
			case 7:
				//mostra_tabelas(al,4); // teste secreto
				break;
		}

		printf("\nDESEJA SAIR DO PROGRAMA (S/N)\nResposta: ");
		scanf("%c",&op);
		fflush(stdin);
		
	}while(op != 'q' && op != 'Q');
	
}

void cadastra_aluno(aluno *al,livro *lv,int count)
{
	char ra[7];
	
	printf("\nNome :");
	gets(al->nome);
	printf("\nRA: ");
	scanf("%s",&ra);
	fflush(stdin);

	strcpy((lv->status)->RA,ra);
	strcpy(al->RA,ra);

	al->emprestado = 0;
	al->reservado = 0;
	
	printf("\nCadastrado com Sucesso !");

	grava_aluno(al);
	grava_livro(lv);
}

void mostra_livros(aluno *al,livro *lv,int count)
{
	int i;

	for (i=0; i < count; ++i, lv++)
	{
		printf("\n\tTitulo : %s\n",lv->titulo);
		printf("\tAutor : %s\n",lv->autor);
		printf("\tREGISTRO DO LIVRO : %i\n",lv->reg_livro);
		printf("\tStatus do Livro: %c\n",(lv->status)->sigla);
	}	
}

int escolha_livro(aluno *al,livro *lv,int count)
{
	int i;
	char titulo2[80];

	mostra_livros(al,lv,4);

	printf("\nEscolha o Livro:");
	gets(titulo2);
	printf("\n\nEscolha feita %s",titulo2);

	for(i=0;i<count;i++,lv++)
	{
		if(strcasecmp(titulo2,lv->titulo) == 0)
		{
			(lv->status)->sigla = 'E';
			return i;
		}
	}
	return -1;	
}

void emprestar_livro(aluno *al,livro *lv,int count, int contdr)
{
	int i;
	int verfica_livro2;

	char ra[7];
	printf("\nRA: ");
	scanf("%s",&ra);
	fflush(stdin);

	do
	{
		verfica_livro2 = escolha_livro(al,lv,4);

	}while(verfica_livro2 == -1);



}
void consulta_livros(aluno *al,livro *lv,int count)
{
	int i;
	FILE *f = fopen("livro.bin","rb");

	if(f == NULL)
	{
		printf("Erro\n");
	}
	else{	

		for(i=0;i<4;i++,lv++)
		{
		printf("\n\tTitulo : %s\n",lv->titulo);
		printf("\tAutor : %s\n",lv->autor);
		printf("\tREGISTRO DO LIVRO : %i\n",lv->reg_livro);
		printf("\tStatus do Livro: %c\n",(lv->status)->sigla);
		}
	fclose(f);
	}
}
void cadastra_livro(livro *lv,int count)
{
	int i;
	int j = 1;


	for(i=0;i<1;i++,lv++)
	{

		lv->reg_livro = j+i;
		(lv->status)->sigla = 'L';
		strcpy(lv->titulo,"Diario-de-um-banana");
		strcpy(lv->autor,"Eu");
		printf("\n%s",lv->titulo);
		printf("\n%s",lv->autor);
		printf("\n%i\n\n",lv->reg_livro);
		j++;

	}
	for(i=0;i<1;i++,lv++)
	{
		lv->reg_livro = j+i;
		(lv->status)->sigla = 'L';
		strcpy(lv->titulo,"Moao");
		strcpy(lv->autor,"VC");
		printf("\n%s",lv->titulo);
		printf("\n%s",lv->autor);
		printf("\n%i\n\n",lv->reg_livro);
		j++;
	}
	for(i=0;i<1;i++,lv++)
	{
		lv->reg_livro = j+i;
		(lv->status)->sigla = 'L';
		strcpy(lv->titulo,"Artick-monkei");
		strcpy(lv->autor,"Lv");
		printf("\n%s",lv->titulo);
		printf("\n%s",lv->autor);
		printf("\n%i\n\n",lv->reg_livro);
		j++;
	}
	for(i=0;i<1;i++,lv++)
	{
		lv->reg_livro = j+i;
		(lv->status)->sigla = 'L';
		strcpy(lv->titulo,"Noite");
		strcpy(lv->autor,"Friends");
		printf("\n%s",lv->titulo);
		printf("\n%s",lv->autor);
		printf("\n%i\n\n",lv->reg_livro);
		j++;
	}
	grava_livro(lv);
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

void mostra_individual(aluno *al,livro *lv,int count,int contdr)
{
	char ra[7];
	int aux;
	int aux2;
	char op;
	int i;
	
	aux = count;
	aux2 = contdr;
	
	FILE *f = fopen("aluno.bin","rb");
	FILE *f2 = fopen("livro.bin","rb");

		if(f==NULL && f2 == NULL)
			printf("\nErro\n");
		else
		{	
			printf("\nColoque o RA do Aluno \n");
			printf("RA:");
			scanf("%s",&ra);
			fflush(stdin);
			
			for(aux=0;aux<count;aux++,aux2++)
			{
				
			fseek(f,aux*sizeof(aluno),0);
			fread(al,sizeof(aluno),1,f);

			fseek(f2,aux2*sizeof(livro),0);
			fread(lv,sizeof(livro),1,f2);

			
				if(strcasecmp(al->RA,ra)==0 && strcasecmp((lv->status)->RA,ra) == 0)
				{
					printf("\nNome: [%s]",al->nome);
					printf("\t|RA: [%s]",al->RA);
					printf("\t|Livros Emprestados: [%i]",al->emprestado);
					printf("\t|Livros Reservados [%i]",al->reservado);
					for(i=0;i<4;i++,al++)
					{
						printf("\nTABELA %i [%c - %s]",i,(al->tabela)->sigla,lv->titulo);
					}
				}	
			}
			return;
		}
	printf("\nAluno nao cadastrado :p\n");
}



void mostra_cadastros(aluno *al,livro *lv,int count)
{
	int i;
	
	FILE *f = fopen("aluno.bin","rb");
	FILE *f2 = fopen("livro.bin","rb");

	if(f==NULL && f2 == NULL)
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
			printf("\nRA livros [%s]\n\n",(lv->status)->RA);
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
void grava_livro(livro *lv)
{
	FILE *f = fopen("livro.bin","ab");
	fseek(f,sizeof(livro),2);
	if(f==NULL)
	{
		printf("\n\nErro");
	}
	else
		fwrite(lv,sizeof(livro),1,f);
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
}//verifica

int verifica_livro()
{
	long int count = 0;

	FILE *f = fopen("livros.bin","rb");

	if(f == NULL)
	{
		return count;
	}
		else
	{
		fseek(f,0,2);
		count = ftell(f)/sizeof(livro);
		fclose(f);
		return count;
	}
}//verifica

void aloca_aluno(aluno **al,int count)
{
	if((*al=(aluno*)realloc(*al,count*sizeof(aluno)))==NULL)
		exit(1);
}
void aloca_livro(livro **lv, int count)
{
	if((*lv=(livro*)realloc(*lv,count*sizeof(livro)))==NULL)
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
void mostra_cadastra_livro(livro *lv,int count)
{
	int i;
	for(i=0;i<count;i++,lv++)
	{
		printf("%s",lv->titulo);
		printf("%s",lv->autor);
	}
}

//BY HENRY SANTURIAO ALMEIDA
