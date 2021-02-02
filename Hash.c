#include <openssl/crypto.h>
#include <openssl/sha.h>
#include <stdio.h>                       
#include <stdlib.h>
#include <string.h>
void adcbloco(int);
void verefica();
void alteraBlocos(int,int);
void chain();
int comparaHash(unsigned char*, unsigned char*);
void mostraHash();

int count;

// p -lcrypto

struct blocos{
unsigned char proximohash[SHA256_DIGEST_LENGTH];
int blocodata;
struct blocos *point;
}*var;

    unsigned char* toString(struct blocos b){
    unsigned char *str=malloc(sizeof(unsigned char)*sizeof(b));
    memcpy(str,&b,sizeof(b));
    return str;
}
  void mostraHash(unsigned char hash[], int lenght){
        int i;
                for(i=0; i < lenght;i++)
                    printf("%02x",hash[i]);
}
  int comparaHash(unsigned char *str1 , unsigned char *str2){
    int z;
    for(z=0; z< SHA256_DIGEST_LENGTH;z++)
            if(str1[z]!= str2[z])
                return 1;
    }


  void mostraBloco(struct blocos *b){
    printf("\033[1;35m %p]t",b);
    mostraHash(b->proximohash,sizeof(b->proximohash));
    printf("\033[1;36m\t [%d] \t",b->blocodata);
    printf("\033[1;31m %p\n",b->point);
}

  void mostraTodos(){
    struct blocos *atual=var;
        int count=0;
        while(atual){
            mostraBloco(atual);
                atual=atual->point;
        }
}
  void adcbloco(int data){                                  
    if(var==NULL){                                                
        var=malloc(sizeof(struct blocos));
            SHA256("",sizeof(""),var->proximohash);
            var->blocodata=data;
            return;
    }                                       
            struct blocos *blocoatual=var;
            while(blocoatual->point)
                    blocoatual=blocoatual->point;
                        struct blocos *novobloco=malloc(sizeof(struct blocos));
                        blocoatual->point=novobloco;
                          novobloco->blocodata=data;
                            SHA256(toString(*blocoatual),sizeof(*blocoatual),novobloco->proximohash);
                        
    }
    void verefica(){                 
        if(var==NULL){              
            printf("\n \033[1;31m Blockchain Vazia \n");
                return;
        }
           struct blocos *atual=var->point,*prox=var;
             count =1;
           while(atual){
               printf(" \033[1;36m %d \t [%d] \t",count++,atual->blocodata);
               mostraHash(SHA256(toString(*prox),sizeof(*prox),NULL),SHA256_DIGEST_LENGTH); 
               printf("\033[1;31m -");
               mostraHash(atual->proximohash,SHA256_DIGEST_LENGTH);
                        if(comparaHash(SHA256(toString(*prox),sizeof(*prox),NULL),atual->proximohash))
                                printf("VEREFICADO\n");
                        else
                            printf("FALHA AO VEREFICAR \n");
                            prox=atual;
                            atual=atual->point;                                                                                                                                               
       }    
       }

void alteraBlocos(int n, int newdata){
        //int count;
        struct blocos *atual=var;
            if(atual==NULL){
                 printf("\n \033[1;31m Bloco inexistente \n");
                 return;
            }while(count!=n){
               if(atual->point==NULL && count!=n){
                   printf("Bloco inexistente");
                        return;
            }       else if(count==n)
                    break;
                    atual=atual->point;
                    count++;
            }
                    printf("antes->");
                        mostraBloco(atual);
                        atual->blocodata=newdata;
                        printf("Depois->");
                            mostraBloco(atual);
                                printf("\n");
            }

    void chain(){
        struct blocos *atual=var,*prox;
        if(atual==NULL){
            printf("---Blockchain Vazia---\n");
                return;
        }
        while(1){
            prox=atual;
                atual=atual->point;
                    if(atual==NULL){
                        return;
                    }else{
                        mostraHash(SHA256(toString(*prox),sizeof(*prox),atual->proximohash),SHA256_DIGEST_LENGTH);
                        printf("\n");
                    }
                      
                        


                        }
    
    
                        }    
int main(void){
    int c,n,r;
    printf("=============================================");
    printf("\033[1;32m\n1->Adicionar bloco Manualmente\n");
    printf("\033[1;32m\n2->Adicionar blocos Automaticamente\n");
    printf("\033[1;32m\n3->Mostrar Todos os blocos\n");
    printf("\033[1;32m\n4->Vereficar Blocos\n");

    while(1){
        printf("\033[1;33m\nescolha->\n");
        scanf("%d", &c);
        switch(c){
            case 1:
              printf("\033[1;31m\nInsira o bloco\n");
              scanf("%d", &n);
              adcbloco(n);
                return main();
                break;

            case 2:
                printf("\033[1;33m\n---Quantos blocos deseja adicionar---\n");
                scanf("%d",&n);
                for(int i=0; i<n;i++){
                    r=rand()%(n*10);
                    printf("\033[1;31m\n---Adicionando bloco--- [%d]\n",r);
                    adcbloco(r);
                }   
                    return main();
                    break;

            case 3:
                printf("\033[1;32m\n[Blocos Atuais]\n");
                mostraTodos();
                return main();
                break;
                

            case 4:
                printf("\033[1;32m\n[---Vereficando---]\n");
                verefica();
                return main();
                break;

           
                


        }
    }
    

}
