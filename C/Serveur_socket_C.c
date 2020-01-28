#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h> 
#include <strings.h>
#include <string.h> 
#include <stdlib.h>

int countVoyelle(char phrase[])
{
	int toSender = 0, nbchar = strlen(phrase);

	char voyelles[12] = "aeiouyAEIOUY";
	 
    for(int i = 0; i < nbchar; i++)
    {
        if(strchr(voyelles,phrase[i]))
        {
            toSender++;
        }
    }

    return toSender;
}


int countWord(char phrase[])
{
	int toSender = 0, nbchar = strlen(phrase);
    int inWord = 0;

    for (int i = 0; i < nbchar; ++i)
    {
    	switch(phrase[i]) 
    	{
        	case '\0': 
        	case ' ': 
        	case '\t': 
        	case '\n': 
        	case '\r':
            	if (inWord) 
            	{ 
            		inWord = 0; 
            		toSender++; 
            	}
            	break;
        	default: inWord = 1;
        }
    }
    if (inWord) 
    { 
    	inWord = 0; 
    	toSender++; 
    }
    return toSender;
}

int main(int argc, char const *argv[])
{
	// VAR
	int socketnb, scom, lg_app, i, j, erreur, fin;
	struct sockaddr_in adr; 
	struct sockaddr_storage recep;
	char buf[1500], renvoi[1500], host[1024],service[20];

	// Init Socket
	socketnb = socket(AF_INET,SOCK_STREAM,0);
	printf("%s => %d\n","Socket creer",socketnb );

	adr.sin_family=AF_INET;
	adr.sin_port=htons(7500);
	adr.sin_addr.s_addr=INADDR_ANY;
	
	if (bind(socketnb,(struct sockaddr *)&adr,sizeof(struct sockaddr_in)) !=0) 
	{  
	    printf("probleme de bind sur v4\n");      
	    exit(1); 
	}

	if (listen(socketnb,5) != 0)      
	{        
		printf("pb ecoute\n"); exit(1);
	}     

	// Boucle infinit
	while(1)
	{
		fin = 0;
		printf("en attente de connexion\n");
		scom = accept(socketnb,(struct sockaddr *)&recep ,&lg_app);
		getnameinfo((struct sockaddr *)&recep,sizeof (recep), host, sizeof(host),service, sizeof(service),0); 
		printf("recu de %s venant du port %s\n",host, service);
		while (1)     
		{ 
			recv(scom,buf,sizeof(buf),0);
			printf("buf recu %s\n",buf);
			bzero(renvoi,sizeof(renvoi)); 
			erreur = 0;
			switch(buf[0])
		    {
		      case '1':
		        printf("Fonction 1 => OK\n");
		      	send(scom,"ARK\n",4,0);      
		        bzero(buf,sizeof(buf));
		        recv(scom,buf,sizeof(buf),0);
		        printf("Fonction 1 => buf recu %s\n",buf);
		        sprintf(renvoi, "%d\n", countVoyelle(buf));
		        break;
		      case '2':
		      	printf("Fonction 2 => OK\n");
		      	send(scom,"ARK\n",4,0);      
		        bzero(buf,sizeof(buf));
		        recv(scom,buf,sizeof(buf),0);
		        printf("Fonction 2 => buf recu %s\n",buf);
		        sprintf(renvoi, "%d\n", countWord(buf));
		        break;
		      case '3':
		      	fin = 1;
		      	break;
		      default:
		      	erreur = 1;
		        printf("Erreur => Entrer un nombre entre 1 et 3\n");
		        if(strlen(buf)==0)
		        {
					printf("Perte de connexion\n");
					fin = 1;
		        }
		    }
		    if(!erreur)
		    {
				send(scom,renvoi,strlen(renvoi),0);       
			} 
			bzero(buf,sizeof(buf)); 
			if (fin == 1)    
					break;
		} 
		printf("Fin de connexion\n");
		close(scom);
	}
	close(socketnb); 
	return 0;
}