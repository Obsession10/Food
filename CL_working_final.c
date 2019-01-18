#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <arpa/inet.h>

int port;
int coasa=0;
int timp;

int main(int argc, char *argv[])
{
    int sd;		//descriptorul de socket aka numele lui

    srand((unsigned int)time(NULL));	//initializare rand
    int r ;     		//numar random intre 1-5

    struct sockaddr_in server ;

    char msg[100];	//mesajul trimis
    char new_msg[100]="";
    char raspuns[100]="";

    port = atoi(argv[2]);	//stabilim portul pe care l-am dat in linia de comand

    sd = socket(AF_INET,SOCK_STREAM,0);	//creare socket


    // bagam umplerea
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(port);

    //TENTATIVA DE STABILIRE A CONEXIUNII
    connect(sd , (struct sockaddr *) &server , sizeof(struct sockaddr));

    //trimitem acum mesaj la server
    int cereri_refuzate  = 0;	// numarul de cereri refuzate,la 3 de acst gen clientul pleaca
    int ok=0;
//    char mm[10]="";
    int xs;
    read(sd,&xs,sizeof(xs));
     printf("Sunt CLIENTUL %d\n\n",xs);
     fflush(stdout);
     
     read(sd,&timp,4);

    while (1)
    {  
        
          r = rand() % ( 5 + 1 - 1) + 1;	//numar random 1-5

          //alegeri[r]++;
          write(sd,&r,sizeof(r));	//trimitem serverului alegerea facuta
          sleep(timp/2+2);
	        printf("Am ales felul cu numarul %d\n",r);
	        fflush(stdout);
	  //citim raspunsul dat de server

	//sleep(20);
	         int rr;

           read(sd,&rr,sizeof(rr));// xxx-ul


	        if(rr==1)	// felul de mancare ales e cel mai dorit
	         {
	            read(sd,raspuns,sizeof(raspuns));
	            sleep(timp);
	            printf(raspuns);
	            fflush(stdout);
	           
	            strcat(new_msg,"\nSunt Satul!!!\n");
	            //write(sd,new_msg,100);
	            //sleep(timp);
	             printf(new_msg);
	             fflush(stdout);
	        
	             close(sd);
	            
                     return;
	            
	          }
	        else
            {
                    bzero(raspuns,100);
                    read(sd,raspuns,sizeof(raspuns));
                    sleep(timp);
                    
                    printf(raspuns);
                    fflush(stdout);
                    sleep(5);
		                read(sd,&coasa,sizeof(coasa));

	            if(coasa == 3)  //clientul nu a primit niciodata ce a vrut
	             {
	                 bzero(new_msg,100);
		                strcat(new_msg,"Schimb cantina! Aici mor de foame!\n");
  		           //write(sd,new_msg,100);
  		              sleep(timp);
		              printf(new_msg);
		               fflush(stdout);
		              
		                close(sd);
		            
		                      return;
	              }
            }
            //sleep(timp);
//	}
    }
    close(sd);


}
