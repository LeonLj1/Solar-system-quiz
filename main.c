#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Igrac{

    char ime[50];
    int poeni;
};

void pobednik(struct Igrac Igrac[],int brigr){
    int maxp;

    maxp=0;

    for(int i=1;i<brigr;i++){
        maxp=Igrac[i].poeni>Igrac[maxp].poeni?i:maxp;
    }

    printf("Pobednik je %s sa %d poena.\n",Igrac[maxp].ime,Igrac[maxp].poeni);
}

int main(void){
    int brigr,igr=0,np=0,bc,bn=0,bt=0,i=0,j=0,k=0,l=0;//igr==trenutni igrac, bc==broj karaktera u file-u,bn==broj netacnih reci, bt==broj tacnih reci
    char odgovor[20]="",**tod,**nod,*text,todg[50],nodg[50];//tod==tacni odgovori, nod==netacni odgovori;
    FILE *to,*no;//to==file sa tacnim odgovorima, no==file sa netacnim odgovorima

    memset(todg,0,sizeof(todg));
    memset(nodg,0,sizeof(todg));
    srand(time(NULL));

    to=fopen("TacniOdgovori.txt","r");
    fseek(to,0,SEEK_END);
    bc=ftell(to);
    rewind(to);

    text=malloc(bc*sizeof(char));
    fgets(text,bc,to);

    for(int temp=0;temp<bc;temp++){
        if(text[temp]=='.'){
            bt++;
        }
    }
    tod=malloc(bt*sizeof(char*));
    for(int temp=0;temp<bt;temp++){
        tod[temp]=malloc(85*sizeof(char));//50 je duzina odgovora
    }
    if(tod==NULL){
        printf("Imposible to allocate memory!!!\n");
    }

    for(int temp=0;temp<bc;temp++){

        todg[i]=text[temp];
        
        if(todg[i]=='.'){
            strcpy(tod[j],todg);
            memset(todg,0,sizeof(todg));
            j++;
            temp++;
            i=-1;
        }
        i++;
    }

    free(text);
    text=NULL;
    fclose(to);
    
    printf(" Koliko ima igraca: ");
    scanf("%d",&brigr);
    printf("\n");

    struct Igrac Igrac[brigr];

    for(int i=0;i<brigr;i++){
        printf(" Ime %d. igraca: ",i+1);
        scanf("%49s",Igrac[i].ime);

        Igrac[i].poeni=0;

        
    }

    printf("\n");

    while(1){
        if(igr>=brigr){
            igr=0;
        }

        if(np==3||(np-3)%5==0){
            printf(" Na %d. pitanje odgovara %s.\n",np+1,Igrac[igr].ime);
            printf(" Tacno\n Netacno\n (Odgovor se mora uneti sa . na kraju reci)\n ");
            scanf("%s",&odgovor);
            printf("----------------------------\n");
            if(strcmp(odgovor,tod[np])==0){
                Igrac[igr].poeni+=5;
            }
            igr++;
            np++;
        }

        if(igr>=brigr){
            igr=0;
        }
        
        printf(" Na %d. pitanje odgovara %s.\n",np+1,Igrac[igr].ime);

        int r=0,p=-1,A,B,C;
        char pod[3][85];//pod==ponudjeni odgovori;

        memset(pod,0,sizeof(pod));

        strcpy(pod[0],tod[np]);
        for(int temp=1;temp<3;temp++){
            do{
                r=rand()%230;
            }while(r==np||r==p||strcmp(tod[r],"Tacno.")==0||strcmp(tod[r],"Netacno.")==0);
            strcpy(pod[temp],tod[r]);
            p=r;
        }

        A=rand()%3;
        do{
            B=rand()%3;
        }while(A==B);
        do{
            C=rand()%3;
        }while(C==A||C==B);
        
        printf(" Ponudjeni odgovori su:\n A:%s\n B:%s\n C:%s\n ",pod[A],pod[B],pod[C]);
        
        scanf("%s",&odgovor);

        if(strcmp(odgovor,"A")==0||strcmp(odgovor,"a")==0){
            if(strcmp(pod[A],tod[np])==0){
                Igrac[igr].poeni+=5;
                printf("Tacno.\n");
            }else{
                printf("Netacno.\n");
            }
        }
        if(strcmp(odgovor,"B")==0||strcmp(odgovor,"b")==0){
            if(strcmp(pod[B],tod[np])==0){
                Igrac[igr].poeni+=5;
                printf("Tacno.\n");
            }else{
                printf("Netacno.\n");
            }
        }
        if(strcmp(odgovor,"C")==0||strcmp(odgovor,"c")==0){
            if(strcmp(pod[C],tod[np])==0){
                Igrac[igr].poeni+=5;
                printf("Tacno.\n");
            }else{
                printf("Netacno.");
            }
        }
        
        if(strcmp(odgovor,"Kraj")==0||(np+1)==230){
            printf("----------------------------\n");
            for(int temp=0;temp<brigr;temp++){
                printf(" %s ima:      %d poena\n ",Igrac[temp].ime,Igrac[temp].poeni);
            }
            printf("----------------------------\n");
            break;
        }

        if(strcmp(odgovor,"Trenutnostanje")==0){

            printf("----------------------------\n");
            for(int temp=0;temp<brigr;temp++){
                printf("%s ima:      %d poena\n",Igrac[temp].ime,Igrac[temp].poeni);
            }
            igr--;
            np--;
        }

        printf("----------------------------\n");

        igr++;
        np++;
    }

    pobednik(Igrac,brigr);

    printf("Hvala na ucescu!!!\n");

    getchar();
    printf("Press any key continue.");
    getchar();

    return 0;
}
