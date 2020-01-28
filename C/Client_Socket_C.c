#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h> 
#include <strings.h>
#include <string.h> 
#include <stdlib.h>

void mainMenu()
{
  printf("-------------------------------------------------\n");
  printf("*                   Menu                        *\n");
  printf("-------------------------------------------------\n");
  printf("*        1.Compter nombre de voyelle            *\n");
  printf("*        2.Compter nombre de mots               *\n");
  printf("*        3.Quitter                              *\n");
  printf("-------------------------------------------------\n");
  printf("Enter un nombre:  \n");
}

void getPhrase(char toSender[])
{
  int c,i =0;

  while((c=getchar()) != '\n')
    toSender[i++] = c;
  toSender[i++] ='\n';
}

void main(int argc, char *argv[])
{
  char buffer[200],texte[200];
  int port, rc, sock,i,c ,fin;
  struct sockaddr_in addr;
  struct hostent *entree;

  if (argc !=3)  
  {
    printf("usage : clientv4 nom_serveur port\n");
	  exit(1);    
  }
  
  addr.sin_port=htons(atoi(argv[2]));
  addr.sin_family=AF_INET;
  entree=(struct hostent *)gethostbyname(argv[1]);
  bcopy((char *)entree->h_addr,(char *)&addr.sin_addr,entree->h_length);
    
  sock= socket(AF_INET,SOCK_STREAM,0);

  if (connect(sock, (struct sockaddr *)&addr,sizeof(struct sockaddr_in)) < 0) 
  {
    printf("probleme connexion\n");
    exit(1); 
  }

  printf("connexion passe\n");

  fin = 0;
  while (1) 
  {
    system("clear");
    bzero(texte,sizeof(texte)); 
    bzero(buffer,sizeof(buffer)); 
    mainMenu();
    getPhrase(texte);
    switch(texte[0])
    {
      case '1':
        printf("-------------------------------------------------\n");
        printf("*          Compter nombre de Voyelle            *\n");
        printf("-------------------------------------------------\n");
        printf("Entrer une phrase : \n");
        send(sock,"1\n",2,0);
        recv(sock,buffer,sizeof(buffer),0);
        bzero(buffer,sizeof(buffer)); 
        getPhrase(texte);
        send(sock,texte,strlen(texte),0);
        recv(sock,buffer,sizeof(buffer),0);
        printf("\nReponse :\n");
        printf("%s\n",buffer);
        printf("Cliquer sur entrer pour retourner au menu...\n\n");
        getPhrase(texte);
        break;
      case '2':
        printf("-------------------------------------------------\n");
        printf("*          Compter nombre de mots               *\n");
        printf("-------------------------------------------------\n");
        printf("Entrer une phrase : \n");
        send(sock,"2\n",2,0);
        recv(sock,buffer,sizeof(buffer),0);
        bzero(buffer,sizeof(buffer)); 
        getPhrase(texte);
        send(sock,texte,strlen(texte),0);
        recv(sock,buffer,sizeof(buffer),0);
        printf("\nReponse :\n");
        printf("%s\n",buffer);
        printf("Cliquer sur entrer pour retourner au menu...\n\n");
        getPhrase(texte);
        break;
      case '3':
        send(sock,"3\n",2,0);
        fin = 1;
        break;
      default:
        printf("Erreur => Entrer un nombre entre 1 et 3\n");
        printf("Cliquer sur entrer pour retourner au menu...\n\n");
        getPhrase(texte);
    }
    if (fin == 1)	break;
  }
  close(sock); 
    printf("Deconnection -> Fin de programme\n");
}