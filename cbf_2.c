#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_CIDADE 120
#define MAX_JOGOS 450
#define MAX_PRE 50

struct tjogo{
    int id;
    float valor;
    char cidade[TAM_CIDADE];
};

void recebep (char presi[], int *tam);
void menu(char escolha, struct tjogo jogos[], int num_jogos, char presi[], int tamcidade);
void recebeid(int *num_jogos, struct tjogo jogos[]);
void recebevalor(int *num_jogos, struct tjogo jogos[]);
void consultajogo(int *num_jogos, struct tjogo jogos[]);
void recebecidade(int *num_jogos, struct tjogo jogos[], int tamcidade);
void tabelajogos(int *num_jogos, struct tjogo jogos[], char presi[]);
void ordenajogos(int *num_jogos, struct tjogo jogos[]);

int main(){
    struct tjogo jogos[MAX_JOGOS];
    char presi[MAX_PRE];
    int i = 0, tam = 0, espaco_id = 0, num_jogos=0, tamcidade=0;
    char  escolha=0;
    
    recebep (presi, &tam);
 
    for ( i = tam-1; i >= 0; i--){
        if (presi[i]==' ') {
            espaco_id=i;
        } 
    }
    
    for ( i = 0; i < tam; i++) {
        if (i==0 || i==(espaco_id+1)) {
            presi[i]=toupper(presi[i]);
        }else{
            presi[i]=tolower(presi[i]);
        }
        printf("%c",presi[i]);
    }    

    menu(escolha, jogos, num_jogos, presi, tamcidade);

   FILE *pont_arq;
   pont_arq = fopen("nomepresidente.txt", "w+");
    fputs("Presidente da CBF:\n", pont_arq);
    fputs(presi, pont_arq);
   
   fclose(pont_arq);
   return 0;
}

void recebep (char presi[], int *tam){
    do{
        printf("\nDigite o nome do Presidente da CBF: ");
        fflush(stdin);
        gets(presi);

        *tam = strlen (presi);
        if (*tam<=1){
            printf("\nO nome do presidente nao pode ser vazio.");
        }
        if (*tam>MAX_PRE){
            printf("\nO nome do presidente nao pode ter mais de 50 caracteres.");
        }
    } while (*tam<=1 || *tam>50);
}

void menu(char escolha, struct tjogo jogos[], int num_jogos, char presi[], int tamcidade){
    do{
    	
    	system("cls");
    	
        printf("\n\t\tBem vindo ao menu\n\n"); 

        printf("Selecione uma operacao:\n"); 
        printf("\ta-cadastro de um jogo\n");
        printf("\tb-tabela dos jogos  \n");
        printf("\tc- consulta jogo\n");
        printf("\td- sair do menu\n");
        printf("Operacao: "); 
        
        fflush(stdin);
       scanf ("%c", &escolha);
        switch (escolha){
        case 'a':
            //printf("a");
            if(num_jogos == MAX_JOGOS){
                printf("\nVoce ja atingiu o maximo de jogos.");
            }else{
             recebeid(&num_jogos, jogos);
             recebevalor(&num_jogos, jogos);
             recebecidade(&num_jogos, jogos, tamcidade);
            // printf("\n%d %.2f\n ", jogos[num_jogos].id, jogos[num_jogos].valor);
            //puts(jogos[num_jogos].cidade);
             num_jogos+=1;
            }
            break;
        case 'b':
            //printf("b");
            ordenajogos(&num_jogos, jogos);
            tabelajogos(&num_jogos, jogos, presi);
            break;
        case 'c':
            //printf("c");
            consultajogo(&num_jogos, jogos);
            break;
        case 'd':
            printf("\nSaindo...");
            break;       
        default:
        printf("\n Informe uma opcao valida...");
            break;
        }
    } while (escolha!='d');
}

void recebeid(int *num_jogos, struct tjogo jogos[]){
    int i=0, j=0;
    jogos[*num_jogos].id=0;
    do{
        i=0;
        printf("\nInforme a indetificacao do jogo: ");
        fflush(stdin);
        scanf("%d", &jogos[*num_jogos].id);
        if (*num_jogos>0){
            
        for ( j = 0; j < *num_jogos; j++){
            if (jogos[*num_jogos].id==jogos[j].id){
              printf("\n Ja existe um jogo com essa identificacao. ");
              i=500;  
            }
        }
        }
         if (jogos[*num_jogos].id< 300){
                    printf("\nA identificacao de um jogo nao pode ser inferior a 300. ");
                    i=500;
                }else{
                    if (jogos[*num_jogos].id> 10000){
                        printf("\nA identificacao de um jogo nao pode ser superior a 10.000. ");
                        i=500;
                    }
                } 
    } while (i ==500 );
}

void consultajogo(int *num_jogos, struct tjogo jogos[]){
    int i=0, j=0, tamcidade=0;
    char cidade[TAM_CIDADE];
        
        if (*num_jogos>=1){
            printf("\nInforme a cidade do jogo que deseja consultar: ");
        
        fflush(stdin);
        gets(cidade);
        tamcidade = strlen (cidade);
        for ( i = 0; i < tamcidade; i++) {
            cidade[i]=tolower(cidade[i]);
        }
        for ( j = 0; j < *num_jogos; j++){
            if (strcmp(jogos[j].cidade, cidade)==0){
              printf("\nIdentificacao: %d.\nValor arrecadado: %.2f \nCidade:%s\n ",jogos[j].id, jogos[j].valor, jogos[j].cidade);
              i=500;  
            }
        }

        if (i!=500){
            printf("\nNao ocorreu jogo na cidade.............. ");
        }
        }else{
            printf("\nNao ha jogos cadastrados ainda para consultar, favor cadastre ao menos um jogo");
        }
}

void recebevalor(int *num_jogos, struct tjogo jogos[]){
    int i=0, j=0;
    jogos[*num_jogos].valor=0;
    do{
        i=0;
        printf("\nInforme o valor arrecadado do jogo: ");
        fflush(stdin);
        scanf("%f", &jogos[*num_jogos].valor);
         if (jogos[*num_jogos].valor< 1000){
                    printf("\nO valor arrecadado de um jogo nao pode ser inferior a 1.000,00. ");
                    i=500;
                }else{
                    if (jogos[*num_jogos].valor> 1000000){
                        printf("\nO valor arrecadado de um jogo nao pode ser superior a 1.000.000,00.  ");
                        i=500;
                    }
                } 
    } while (i ==500 );
}

void recebecidade(int *num_jogos, struct tjogo jogos[], int tamcidade){
    int  i=0;
        do{
        printf("\nDigite o nome da cidade: ");
        fflush(stdin);
        gets(jogos[*num_jogos].cidade);
        tamcidade = strlen (jogos[*num_jogos].cidade);
        for ( i = 0; i < tamcidade; i++) {
            jogos[*num_jogos].cidade[i]=tolower(jogos[*num_jogos].cidade[i]);
        }
        if(tamcidade>TAM_CIDADE){
            printf("\nO nome da cidade nao pode ser superior a 120 caracteres.");
        }
        }while(tamcidade>TAM_CIDADE); 
}

void ordenajogos(int *num_jogos, struct tjogo jogos[]){
 char auxcidade[120];
 int auxid;
 float auxvalor;
 int i=0, j=0, min;
 for(j=0;j<(*num_jogos-1);j++){
  min=j;
  for(i=(j+1);i<*num_jogos;i++){
   if(strcmp(jogos[i].cidade,jogos[min].cidade)<0){
    min = i;
   }
  }
  if(j != min){
   strcpy(auxcidade,jogos[j].cidade);
   strcpy(jogos[j].cidade, jogos[min].cidade);
   strcpy(jogos[min].cidade, auxcidade);
   
   auxid=jogos[j].id;
   jogos[j].id = jogos[min].id;
   jogos[min].id = auxid;

   auxvalor=jogos[j].valor;
   jogos[j].valor = jogos[min].valor;
   jogos[min].valor = auxvalor;
  }
 }
}

void tabelajogos(int *num_jogos, struct tjogo jogos[], char presi[]){
 if(*num_jogos >1){ 
  printf("\nPresidente: %s", presi);
  printf("\nCidade - Identificacao - Valor Arrecadado");
  int i=0;
  for(i=0;i<*num_jogos;i++){
   printf("\n%s - %i - %.2f", jogos[i].cidade, jogos[i].id, jogos[i].valor);
  }
 }else{
  printf("Cadastre ao menos um jogo para visualizar a tabela.");
 }
}
