#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

/* portul folosit */
#define PORT 2909
int alegeri[5];
char raspuns[100];
int alegere;
int ok;
int contor=0;
int flag=0;
int xxx;
int copie=0;
char append[2];
int ramasi=0;
int coasa=0;
int flagulet=0;
int stf;
int qa=0;
int copie_nclienti;
int ss=0;

/* codul de eroare returnat de anumite apeluri */
extern int errno;

static void *treat(void *); /* functia executata de fiecare thread ce realizeaza comunicarea cu clientii */
//void raspunde(void *);

typedef struct {
	pthread_t idThread; //id-ul thread-ului
	int thCount; //nr de conexiuni servite
}Thread;

Thread *threadsPool; //un array de structuri Thread


int sd; //descriptorul de socket de ascultare
int nclienti;//numarul de clienti
int timp;
pthread_mutex_t mlock=PTHREAD_MUTEX_INITIALIZER;              // variabila mutex ce va fi partajata de threaduri

int raspunde(int cl,int idThread);
int maxim_m();




int main (int argc, char *argv[])
{
  struct sockaddr_in server;	// structura folosita de server
  void threadCreate(int);

   if(argc<3)
   {
        fprintf(stderr,"Eroare: Primul argument este numarul de clienti\nAl doilea este numarul de secunde\n");
		exit(1);
   }

   nclienti=atoi(argv[1]);
   timp=atoi(argv[2]);
   copie_nclienti=nclienti;

   if(nclienti <=0)
	{
        fprintf(stderr,"Eroare: Numar de clienti invalid...");
		exit(1);
	}
    threadsPool = calloc(sizeof(Thread),nclienti);

   /* crearea unui socket */
     //		socket( DOMENIU, TIP, PROTOCOL - 0 pt nivelul de TRANSPORT)
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server]Eroare la socket().\n");
      return errno;
    }
  /* utilizarea optiunii SO_REUSEADDR */
  int on=1;
  setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

  /* pregatirea structurilor de date */
  bzero (&server, sizeof (server));

  /* umplem structura folosita de server */
  /* stabilirea familiei de socket-uri */
   //FAMILY - FAMILIA DE ADRESE
    server.sin_family = AF_INET;

  /* acceptam orice adresa IP*/
    server.sin_addr.s_addr = htonl (INADDR_ANY);

  /* utilizam un port dat de utilizator */
    //HTONS 0 CONVERSIE A UNUI SHORT DE LA GAZDA LA RETEA
    server.sin_port = htons (PORT);

  /* atasam socketului o adresa */
  if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[server]Eroare la bind().\n");
      return errno;
    }

  /* punem serverul sa asculte daca vin clienti sa se conecteze 
  	 listen-permite unui socket sa accpte conexiuni,backlog-nr conexiuni coada*/
  if (listen (sd, nclienti) == -1)
    {
      perror ("[server]Eroare la listen().\n");
      return errno;
    }


   int i;
   for(i=0; i<nclienti;i++) threadCreate(i);


  /* servim in mod concurent clientii...folosind thread-uri */
  for ( ; ; )
  {
		printf ("[server]Asteptam la portul %d...\n\n",PORT);
        pause();
  }
  return 0;

  /* servim in mod concurent clientii...folosind thread-uri */
  for ( ; ; )
  {
		printf ("[server]Asteptam la portul %d...\n\n",PORT);
        pause();
  }
  return 0;
};

void threadCreate(int i)
{
	void *treat(void *);

	pthread_create(&threadsPool[i].idThread,NULL,&treat,(void*)i);
	return; /* threadul principal returneaza */
}
//int ss=0;
void *treat(void * arg)
{
		int client;

		struct sockaddr_in from;
 	        bzero (&from, sizeof (from));



		for( ; ; )
		{
			int length = sizeof (from);

			pthread_mutex_lock(&mlock);
			//int(arg) e numarul threadului curent
			//BLOCHEAZA APELANTUL PANA LA SOSIREA UNEI CERERI DE CONECTARE
			if ( (client = accept (sd, (struct sockaddr *) &from, &length)) < 0)
				{
	 			 perror ("[thread]Eroare la accept().\n");
				}

			pthread_mutex_unlock(&mlock);

			threadsPool[(int)arg].thCount++;

				while( raspunde(client,(int)arg)!=0 )
				    {}
		//	ss++;
		copie_nclienti--;
		int i;

		if(flag == 3 && copie_nclienti==0)
		{
		    for(i=0;i<5;i++)
		    {
		      printf("\nFelul %d are %d cereri per total",i+1,alegeri[i]);
		      fflush(stdout);
		    }
		    qa=1;
		}
	//	copie_nclienti--;
			/* am terminat cu acest client, inchidem/ELIBERAM conexiunea */
			close (client);
		}
//	printf("here\n");
}


int raspunde(int cl,int idThread)
{
	 int nr, i,maxim=0,c=0;
	 int xs=idThread+1;

	 printf("Clientul numarul %d conectat,asteptam...\n",xs);
	 fflush(stdout);

        if(xs==copie_nclienti)
    {
    	 printf("\n");
   	    fflush(stdout);
    }

         ok=0;
        write(cl,&xs,sizeof(xs));
        write(cl,&timp,4);

  while (1)
	{//	sleep(10);
	  	int z=1;
    	maxim=0;
		int joc=0;

		read (cl, &nr,sizeof(nr)); //felul ales,alegere
		sleep(timp);
		printf("Clientul %d a ales felul numarul %d\n",xs,nr);
		fflush(stdout);

	    alegeri[nr-1]++;

		sleep(timp-2);


		for(i=0;i<5;i++)	//vedem cel mai dorit fel de mancare
		 if(alegeri[i]>=maxim)
			 maxim = alegeri[i];

	         if(nclienti==xs && flagulet==0)
	         {
	            for(i=1;i<=5;i++)
	            {
	        		printf("\nFelul %d are %d cereri per total ",i,alegeri[i-1]);
	        		fflush(stdout);
	        		if(i==5)
	        		{
	        	 	   printf("\n\n");
	        	   	   fflush(stdout);
	        		}
	        	
	            }
	           		 flagulet=10;

	         }



	         if(copie_nclienti==ramasi && coasa==0)
	         {

	            for(i=1;i<=5;i++)
	            {
	        		printf("\nFelul %d are %d cereri per total ",i,alegeri[i-1]);
	        		fflush(stdout);
	        		if(i==5)
	        		{
	        	  	  printf("\n\n");
	        	   	 fflush(stdout);
	        		}
	            }

	            coasa=10;
	         }


		xxx=0;
		
	    if(maxim == alegeri[nr-1])
		{
			xxx=1;
			ok=1;
			c=0;
			copie=0;
	        }
	    else
				xxx=0;


	    write(cl,&xxx,sizeof(nr));

	    if(xxx==1)
	    {
	              //copie_nclienti--;
	         if(c==2)
	             flag=3;
			bzero(raspuns,100);	// curatenie in raspuns
			strcat(raspuns,"Masa e servita\n");

			write(cl,raspuns,sizeof(raspuns));

				//close (cl);
				return 0;
			//copie_nclienti--;
	   }
	   else
		{
		        c++;
		    //    copie++;
			bzero(raspuns,100);

			bzero(append,2);
			strcat(raspuns,"Indisponibil - primit de ");
			sprintf(append,"%d",c);
			strcat(raspuns,append);
			strcat(raspuns," ori\n\n");

			write(cl,raspuns,sizeof(raspuns));

	        write(cl,&c,sizeof(c));

			if(c==3)
			{
			//    copie_nclienti--;
			    flag=3;
			    //close(cl);
			    return 0;

			}

	//	write(cl,raspuns,sizeof(raspuns));
		//write(cl,&c,sizeof(c));

		}
       ramasi++;
	}

  close(cl);
  return;
}
