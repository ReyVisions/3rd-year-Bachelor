#include <stdio.h>
#include <stdlib.h>
#include "File.c"

int main(){
    t_file* dliste=NULL;
    dliste = (t_file*) malloc(sizeof(dliste));
    
    printf("\nOn cree une liste vide : ");
    fflush(stdout);
    initDliste(dliste);
    afficherDliste(dliste);

    printf("\nOn enfile 0 : ");
    fflush(stdout);
    enfiler(0,dliste);
    afficherDliste(dliste);

    printf("\nOn enfile 1 : ");
    fflush(stdout);
    enfiler(1,dliste);
    afficherDliste(dliste);

    printf("\nOn enfile 2 : ");
    fflush(stdout);
    enfiler(2,dliste);
    afficherDliste(dliste);

    printf("\nOn defile: ");
    fflush(stdout);
    defiler(dliste);
    afficherDliste(dliste);

    free(dliste);
    printf("la liste a ete effacee");
    fflush(stdout);
    return(0);
}