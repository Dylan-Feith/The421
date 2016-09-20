#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


/* Dans la procedure main, un tableau de structure de struct joueur,appele "j", sera cree. */
/* Pour chaque joueur, on stockera les informations suivantes :                            */

struct joueur{
    char nom[50];
    int id_joueur;              /* le joueur i aura pour id_joueur i-1. Ce nombre servira d'indice pour faire commencer le perdant au tour suivant (A la fin du tour k = celui qui va commencer le tour suivant = l'id_joueur du perdant du tour precedent */
    int jeton;                  /* nombre de jetons qu'il reste au joueur et qu'il doit encore se débarrasser pour gagner                                                                                                                                  */
    int comparaison;            /* A chaque combinaison on associe le nombre "comparaison". Il permet de déterminer si un score est meilleur qu'un autre. Pour cela, il suffit de comparer les nombres "comparaison"                                       */
    int valeur_lancer;          /* Si la combinaison ne correspond à aucun element (ex : 2,1,5) alors combinaison=1 et valeur_lancer = 521                                                                                                                 */
    int valeur_jeton;           /* correspond a la valeur reelle du nombre de jeton de la combinaison (qu'il faudra transferer au perdant                                                                                                                  */
    };


/* un tableau a trois dimensions de la structure suivante, appele dans le main "tableau_comparaion", sera un tableau de connaissances.       */
/* Par exemble si un joueur fait 2,4,1 on a tableau_comparaion[2][4][1].comparaison = 17 et tableau_comparaion[2][4][1].valeur.jeton=10.     */
/* Il suffira juste d'interroger le tableau parbuted la suite pour avoir les informations voulues.                                                */

struct info_score{
    int comparaison;
    int valeur_jeton;
    };

struct de{
    char nom[6];
    int val;
    int relance;
    };


/* Dans le main, on aura "gagnant" et "perdant" qui seront de type struct g_p.                                           */
/* A chaque tour, on regarde si le resultat du lancer final d'un joueur est meilleur que le gagnant provisoire.          */
/* Sinon on regarde si il est inferieur au perdant provisoire.                                                           */
/* les valeurs necessaires du gagnant et perdant provisoire sont stockees respectivement dans "gagnant" et "perdant".    */

struct g_p{
    int comparaison;
    int valeur_lancer;
    int valeur_jeton;
    struct joueur *joueur;
    };

int rand_ab(int a, int b) {                                                                      /* fonctionne */
    return a+(b-a+1)*(rand())/(1.+RAND_MAX);
}

int lancer_de() {                                                                                /* fonctionne */
    return rand_ab(1,6);
}

void initialisation_des(struct de *de1,struct de *de2,struct de *de3){                           /* fonctionne */
    strcpy(de1->nom, "dice 1") ;
    strcpy(de2->nom, "dice 2") ;
    strcpy(de3->nom, "dice 3") ;

    de1->val=lancer_de();
    de2->val=lancer_de();
    de3->val=lancer_de();

    de1->relance=3;
    de2->relance=3;
    de3->relance=3;
}

struct info_score ***creation_du_tableau_comparaison() {                                         /* fonctionne */
    int i,j,k;
    struct info_score *** valeur_lancer;

    valeur_lancer = malloc(7*sizeof (struct info_score **)) ;

    for ( i = 0 ; i < 7 ; i++ ) {
        valeur_lancer[i] = malloc(7*sizeof (struct info_score *)) ;
        for ( j = 0 ; j < 7 ; j++ )
            valeur_lancer[i][j] = malloc(7*sizeof (struct info_score)) ;
	}

    for ( i = 0 ; i < 7 ; i++ ) {
        for ( j = 0 ; j < 7 ; j++ ) {
            for ( k = 0 ; k<7 ; k++ ){
                if ( i==0 || j==0 || k==0 ) {
                    valeur_lancer[i][j][k].comparaison=0;
                    valeur_lancer[i][j][k].valeur_jeton=0;
                }
                else {
                    valeur_lancer[i][j][k].comparaison=1;
                    valeur_lancer[i][j][k].valeur_jeton=1;
                }
            }
        }
    }

    valeur_lancer[4][2][1].comparaison=17;
    valeur_lancer[4][2][1].valeur_jeton=10;
    valeur_lancer[4][1][2].comparaison=17;
    valeur_lancer[4][1][2].valeur_jeton=10;
    valeur_lancer[1][2][4].comparaison=17;
    valeur_lancer[1][2][4].valeur_jeton=10;
    valeur_lancer[1][4][2].comparaison=17;
    valeur_lancer[1][4][2].valeur_jeton=10;
    valeur_lancer[2][1][4].comparaison=17;
    valeur_lancer[2][1][4].valeur_jeton=10;
    valeur_lancer[2][4][1].comparaison=17;
    valeur_lancer[2][4][1].valeur_jeton=10;

    valeur_lancer[1][1][1].comparaison=16;
    valeur_lancer[1][1][1].valeur_jeton=7;

    valeur_lancer[6][6][6].comparaison=15;
    valeur_lancer[6][6][6].valeur_jeton=6;

    valeur_lancer[1][1][6].comparaison=14;
    valeur_lancer[1][1][6].valeur_jeton=6;
    valeur_lancer[1][6][1].comparaison=14;
    valeur_lancer[1][6][1].valeur_jeton=6;
    valeur_lancer[6][1][1].comparaison=14;
    valeur_lancer[6][1][1].valeur_jeton=6;

    valeur_lancer[5][5][5].comparaison=13;
    valeur_lancer[5][5][5].valeur_jeton=5;

    valeur_lancer[1][1][5].comparaison=12;
    valeur_lancer[1][1][5].valeur_jeton=5;
    valeur_lancer[1][5][1].comparaison=12;
    valeur_lancer[1][5][1].valeur_jeton=5;
    valeur_lancer[5][1][1].comparaison=12;
    valeur_lancer[5][1][1].valeur_jeton=5;

    valeur_lancer[4][4][4].comparaison=11;
    valeur_lancer[4][4][4].valeur_jeton=4;

    valeur_lancer[1][1][4].comparaison=10;
    valeur_lancer[1][1][4].valeur_jeton=4;
    valeur_lancer[1][4][1].comparaison=10;
    valeur_lancer[1][4][1].valeur_jeton=4;
    valeur_lancer[4][1][1].comparaison=10;
    valeur_lancer[4][1][1].valeur_jeton=4;

    valeur_lancer[3][3][3].comparaison=9;
    valeur_lancer[3][3][3].valeur_jeton=3;

    valeur_lancer[1][1][3].comparaison=8;
    valeur_lancer[1][1][3].valeur_jeton=3;
    valeur_lancer[1][3][1].comparaison=8;
    valeur_lancer[1][3][1].valeur_jeton=3;
    valeur_lancer[3][1][1].comparaison=8;
    valeur_lancer[3][1][1].valeur_jeton=3;

    valeur_lancer[2][2][2].comparaison=7;
    valeur_lancer[2][2][2].valeur_jeton=2;

    valeur_lancer[1][1][2].comparaison=6;
    valeur_lancer[1][1][2].valeur_jeton=2;
    valeur_lancer[1][2][1].comparaison=6;
    valeur_lancer[1][2][1].valeur_jeton=2;
    valeur_lancer[2][1][1].comparaison=6;
    valeur_lancer[2][1][1].valeur_jeton=2;

    valeur_lancer[4][5][6].comparaison=5;
    valeur_lancer[4][5][6].valeur_jeton=2;
    valeur_lancer[4][6][5].comparaison=5;
    valeur_lancer[4][6][5].valeur_jeton=2;
    valeur_lancer[5][4][6].comparaison=5;
    valeur_lancer[5][4][6].valeur_jeton=2;
    valeur_lancer[5][6][4].comparaison=5;
    valeur_lancer[5][6][4].valeur_jeton=2;
    valeur_lancer[6][4][5].comparaison=5;
    valeur_lancer[6][4][5].valeur_jeton=2;
    valeur_lancer[6][5][4].comparaison=5;
    valeur_lancer[6][5][4].valeur_jeton=2;

    valeur_lancer[3][4][5].comparaison=4;
    valeur_lancer[3][4][5].valeur_jeton=2;
    valeur_lancer[3][5][4].comparaison=4;
    valeur_lancer[3][5][4].valeur_jeton=2;
    valeur_lancer[4][3][5].comparaison=4;
    valeur_lancer[4][3][5].valeur_jeton=2;
    valeur_lancer[4][5][3].comparaison=4;
    valeur_lancer[4][5][3].valeur_jeton=2;
    valeur_lancer[5][3][4].comparaison=4;
    valeur_lancer[5][3][4].valeur_jeton=2;
    valeur_lancer[5][4][3].comparaison=4;
    valeur_lancer[5][4][3].valeur_jeton=2;

    valeur_lancer[2][3][4].comparaison=3;
    valeur_lancer[2][3][4].valeur_jeton=2;
    valeur_lancer[2][4][3].comparaison=3;
    valeur_lancer[2][4][3].valeur_jeton=2;
    valeur_lancer[3][2][4].comparaison=3;
    valeur_lancer[3][2][4].valeur_jeton=2;
    valeur_lancer[3][4][2].comparaison=3;
    valeur_lancer[3][4][2].valeur_jeton=2;
    valeur_lancer[4][2][3].comparaison=3;
    valeur_lancer[4][2][3].valeur_jeton=2;
    valeur_lancer[4][3][2].comparaison=3;
    valeur_lancer[4][3][2].valeur_jeton=2;

    valeur_lancer[1][2][3].comparaison=2;
    valeur_lancer[1][2][3].valeur_jeton=2;
    valeur_lancer[1][3][2].comparaison=2;
    valeur_lancer[1][3][2].valeur_jeton=2;
    valeur_lancer[2][1][3].comparaison=2;
    valeur_lancer[2][1][3].valeur_jeton=2;
    valeur_lancer[2][3][1].comparaison=2;
    valeur_lancer[2][3][1].valeur_jeton=2;
    valeur_lancer[3][1][2].comparaison=2;
    valeur_lancer[3][1][2].valeur_jeton=2;
    valeur_lancer[3][2][1].comparaison=2;
    valeur_lancer[3][2][1].valeur_jeton=2;

	return valeur_lancer;
}

struct joueur *creation_tableau_joueur(int *nb_joueur){                                          /* fonctionne */
    int i,res;
    struct joueur *j;

    res=0;
    *nb_joueur=1;

    while ( res != 1 || *nb_joueur < 2 ) {

        printf("\nEnter the number of players:");
        fflush(stdin);
        res=scanf("%d",nb_joueur);

        if ( res!=1 || *nb_joueur < 2 )
            printf("Wrong input\n");

    }

    j = malloc((*nb_joueur)*sizeof (struct joueur)) ;
    fflush(stdin);
    printf("\n");

    for( i = 0 ; i < *nb_joueur ; i++ ) {

        printf("Who are you player %d ?:",i+1);
        fflush(stdin);
        res=scanf("%49s",j[i].nom);

        if ( res != 1 ){
            printf("reading error\n");
        }

        j[i].id_joueur=i;
        j[i].jeton=j[i].comparaison=j[i].valeur_lancer=j[i].valeur_jeton=0;
    }
    return j;
}

void echangevar(int *a,int *b){                                                                  /* fonctionne */
    int z;

    z=*a;
    *a=*b;
    *b=z;
}

void tri_ordre_croissant(int *a,int *b,int *c){                                                  /* fonctionne */

    if(*b<*c) echangevar(b,c); /* ici on sait que *c<*b */
    if(*a<*b) echangevar(a,b); /* ici on sait que *a est donc la valeur max mais on ne sait pas entre *b et*c */
    if(*b<*c) echangevar(b,c);
}


/* demande si le joueur veut relancer uniquement un seul de         */
/* Si oui, la procedure renvoie une nouvelle valeur entre 1 et 6    */
/* Sinon, elle renvoie la valeur initiale du de                     */

int demande_relance_de(struct de de) {                                                           /* fonctionne */

    de.relance=3;

    while (1) {
        printf("%s :",de.nom);
        fflush(stdin);
        scanf("%d",&(de.relance));

        if (de.relance==1)
            return lancer_de();

        if (de.relance==2)
            return de.val;

        else {
            printf("Wrong input\n\n");
        }
    }

}


/* Si le joueur veut relancer, on applique, pour chaque de, la procedure precedente */

void selection_de_a_relancer( struct de *de1,struct de *de2, struct de *de3){                    /* fonctionne */

    printf("\nWhich dice do you want to reroll?\n\nType 1 to reroll and 2 to keep\n");
    de1->val=demande_relance_de(*de1);
    de2->val=demande_relance_de(*de2);
    de3->val=demande_relance_de(*de3);

}


/* demande au joueur si il veut relancer les des ou si il prefere conserver la combinaison actuelle. */

int demande_relance(struct de *de1,struct de *de2,struct de *de3){                                                               /* fonctionne */
    int relance;

    printf("Results:      %s: %d      %s: %d      %s: %d\n\n",(*de1).nom,(*de1).val,(*de2).nom,(*de2).val,(*de3).nom,(*de3).val);

    while (1) {
        printf("Do you want to reroll?(1 to reroll, 2 otherwise): ");
        fflush(stdin);
        scanf("%d",&relance);

        if ( relance == 1 || relance == 2 )
            return relance;

        printf("Wrong input\n\n");
    }
}


/* Lorsque un joueur a fini tous ses lancers, on traite les donnees.                                                         */
/* Puisque les variables de1, de2 et de3 vont être ecrasees pour le joueur suivant, il faut stocker le resultat du lancer.   */

void traitement_de_donnee(struct joueur *j,struct de *de1,struct de *de2,struct de *de3,struct info_score ***tableau) {         /* fonctionne */

    j->comparaison=tableau[de1->val][de2->val][de3->val].comparaison;
    j->valeur_jeton=tableau[de1->val][de2->val][de3->val].valeur_jeton;
    j->valeur_lancer=0;

    if (j->valeur_jeton==1) {
        tri_ordre_croissant(&(de1->val),&(de2->val),&(de3->val));
        j->valeur_lancer=(de1->val)*100+(de2->val)*10+de3->val;
    }

}


/* C'est une des procedure centrale du code.                                                    */
/* A chaque tour, pour chaque joueur, on applique la procedure suivante.                        */
/* Il reutilise toutes les procedures precedentes.                                              */

int tour_un_joueur(struct joueur *j,int coup_max,struct de *de1,struct de *de2,struct de *de3,struct info_score ***tableau) {   /* fonctionne*/
    int relance;

    printf("\nIt is your turn %s!\n", (*j).nom);

    de1->val=lancer_de();
    de2->val=lancer_de();
    de3->val=lancer_de();

    if ( coup_max == 1 ) {
        traitement_de_donnee(j,de1,de2,de3,tableau);
        printf("final results:%s : %d, %s : %d, %s : %d\n\n",de1->nom,de1->val,de2->nom,de2->val,de3->nom,de3->val);
        return 1;
    }

    else {
        relance=demande_relance(de1,de2,de3);

        if ( relance == 2 ) {
            traitement_de_donnee(j,de1,de2,de3,tableau);
            printf("final results:%s : %d, %s : %d, %s : %d\n\n",de1->nom,de1->val,de2->nom,de2->val,de3->nom,de3->val);
            return 1;
                }

        else {
            selection_de_a_relancer(de1,de2,de3);

            if ( coup_max == 2 ) {
                traitement_de_donnee(j,de1,de2,de3,tableau);
                printf("final results:%s : %d, %s : %d, %s : %d\n\n",de1->nom,de1->val,de2->nom,de2->val,de3->nom,de3->val);
                return 2;
            }

            else {
                relance=demande_relance(de1,de2,de3);

                    if ( relance == 2 ) {
                        traitement_de_donnee(j,de1,de2,de3,tableau);
                        printf("final results:%s : %d, %s : %d, %s : %d\n\n",de1->nom,de1->val,de2->nom,de2->val,de3->nom,de3->val);
                        return 2;
                    }

                    else {
                        selection_de_a_relancer(de1,de2,de3);
                        traitement_de_donnee(j,de1,de2,de3,tableau);
                        printf("final results:%s : %d, %s : %d, %s : %d\n\n",de1->nom,de1->val,de2->nom,de2->val,de3->nom,de3->val);
                        return 3;
                    }
            }
        }
    }
}


/* On compare les resultats des lancers entre gagnant, qui est le gagnant provisoire,           */
/* et nouveau, qui est le dernier joueur à avoir lancer les des.                                */
/* Si nouveau est meilleur, il prend la place de gagnant.                                       */
/* retourne 1 si nouveau prend la place de gagnant et 0 sinon.                                  */

int determination_gagnant(struct g_p *gagnant,struct joueur *nouveau) {                                                         /* fonctionne*/

    if ( gagnant->comparaison == 1 && nouveau->comparaison == 1) {
        if ( nouveau->valeur_lancer > gagnant->valeur_lancer ) {
            gagnant->comparaison = nouveau->comparaison;
            gagnant->valeur_lancer = nouveau->valeur_lancer;
            gagnant->valeur_jeton = nouveau->valeur_jeton;
            gagnant->joueur = nouveau;
            return 1;
        }
    }

    if ( nouveau->comparaison > gagnant->comparaison ) {
        gagnant->comparaison = nouveau->comparaison;
        gagnant->valeur_jeton = nouveau->valeur_jeton;
        gagnant->joueur = nouveau;
        return 1;
    }

    if ( nouveau->comparaison == gagnant->comparaison && gagnant->comparaison != 1) {
        gagnant->comparaison = nouveau->comparaison;
        gagnant->valeur_jeton = nouveau->valeur_jeton;
        gagnant->joueur = nouveau;
        return 1;
    }

    return 0;
}


/* Idem que ci-dessus.                                                                          */
/* Si nouveau a un lancer inferieur au perdant provisoire, il prend sa place.                   */

int determination_perdant(struct g_p *perdant,struct joueur *nouveau) {                                                         /* fonctionne*/

    if ( perdant->comparaison == 1 && nouveau->comparaison == 1 ) {
        if ( nouveau->valeur_lancer <= perdant->valeur_lancer ) {
            perdant->comparaison = nouveau->comparaison;
            perdant->valeur_lancer = nouveau->valeur_lancer;
            perdant->valeur_jeton = nouveau->valeur_jeton;
            perdant->joueur = nouveau;
            return 1;
        }
    }

    if ( nouveau->comparaison < perdant->comparaison ) {
        perdant->comparaison = nouveau->comparaison;
        perdant->valeur_jeton = nouveau->valeur_jeton;
        perdant->joueur = nouveau;
        return 1;
    }

    if ( nouveau->comparaison == perdant->comparaison && perdant->comparaison != 1 ) {
        perdant->comparaison = nouveau->comparaison;
        perdant->valeur_jeton = nouveau->valeur_jeton;
        perdant->joueur = nouveau;
    }

    return 0;
}


/* On teste si nouveau est gagnant                                                              */
/* Si oui, la procedure s'arrete, si non, on teste si nouveau est perdant                       */

void determination_gagnant_perdant(struct g_p *gagnant,struct g_p *perdant, struct joueur *nouveau) {                           /* fonctionne*/
    int changement;

    changement = determination_gagnant(gagnant,nouveau);

    if ( changement == 0 )
        determination_perdant(perdant,nouveau);
}

/* transfere les jetons du gagnant au perdant                                               */

void transfert_jeton(struct g_p *gagnant,struct g_p *perdant) {                                                                 /* fonctionne*/

    if ( gagnant->joueur->jeton > gagnant->valeur_jeton ) {
        gagnant->joueur->jeton -= gagnant->valeur_jeton;
        perdant->joueur->jeton += gagnant->valeur_jeton;
    }

    else {
        perdant->joueur->jeton += gagnant->joueur->jeton;
        gagnant->joueur->jeton = 0;
    }

}


/* transfere les jetons correspondant à la combinaison du gagnant du pot vers le perdant    */

void transfert_jeton_pot(int *pot,struct g_p *gagnant,struct g_p *perdant) {

    if ( *pot > gagnant->valeur_jeton ) {
        perdant->joueur->jeton += gagnant->valeur_jeton;
        *pot -= gagnant->valeur_jeton;
        printf("\n\nIt remains %d tokens to distribute",*pot);
    }

    else {
        perdant->joueur->jeton += *pot;
        *pot=0;
        printf("\n\nNo more tokens to distribute");
    }
}


void lecture_fichier(char *nom_fichier) {                                                                                       /* fonctionne*/
    char c[2000];
    char *res;
    FILE *pf;

	pf=fopen(nom_fichier,"r") ;

	if ( pf == NULL )
		printf("\nThe file can't be opened\n") ;

	else {

            for (;;) {

                res=fgets(c,2000,pf);

                if ( res == NULL )
                    break;

                else
                    printf("%s",c);
            }
    }

    fclose(pf);

}


/* ecrit dans nom_fichier le "nom" du joueur ainsi que le "nb_tour"                         */

void ecriture_fichier(char *nom_fichier,char *nom,int nb_tour) {                                                                /* fonctionne*/

    FILE *pf;

    pf = fopen(nom_fichier,"a");

    if ( pf == NULL )
		printf("\nThe file can't be opened\n");

	fprintf(pf,"%s   %d\n",nom,nb_tour);
    fclose(pf);

}


/* verifie si un joueur n'a plus de jetons.                                                 */
/* Si oui le jeu s'arrete, on a un gagnant.                                                 */
/* renvoie 1 si on a un ou des gagnant(s) et 0 sinon.                                       */

int test_gagnant_final(struct joueur *j,struct g_p *gagnant,int pot,int nb_joueur) {                                            /* fonctionne*/
    int i;

        for ( i = 0 ; i < nb_joueur ; i++ ) {

            if ( j[i].jeton == 0 )
                return 1;
        }

        return 0;
}

int menu_partie() {                                                                                                             /* fonctionne*/
    int i,res;

    printf("Welcome in the 421 !");
    printf("\n\n\tContents:\n\n\t1 ... New game\n\n\t2 ... lasts results\n\n\t3 ... Rules of the game\n\n\t4 ... Exit\n\n\n");

    while (1) {
        printf("What do you want to do?:");
        fflush(stdin);
        res=scanf("%d",&i);

        if ( res == 0 || ( i != 1 && i != 2 && i != 3 && i !=4 ) )
            printf("Wrong input\n\n");

        if ( i == 1 )
            return 0;

        if ( i == 2 ) {
            printf("\n");
            lecture_fichier("results.txt");
            printf("\n\n\tContents:\n\n\t1 ... New game\n\n\t2 ... Lasts results\n\n\t3 ... Rules of the game\n\n\t4 ... Exit\n\n\n");
            i=0;
        }

        if ( i == 3 ) {
            printf("\n\n");
            lecture_fichier("rules.txt");
            printf("\n\n\tContents:\n\n\t1 ... New game\n\n\t2 ... Lasts results\n\n\t3 ... Rules of the game\n\n\t4 ... Exit\n\n\n");
            i=0;
        }

        if ( i == 4 ) {
            printf("\n\nThanks for playing\n\n");
            return 1;
        }
    }
}

int fin_de_partie() {                                                                                                           /* fonctionne*/
int quitter;

    while (1) {
        printf("\n\n\nDo you want to exit? (1 to exit, 0 to stay): ");
        fflush(stdin);
        scanf("%d",&quitter);

        if (quitter==1) {
            printf("\n\n\nThanks for playing\n\n");
            return quitter;
        }

        if (quitter==0) {
            printf("\n\n\n");
            return quitter;
        }

        else {
            printf("\n\nWrong input\n");
        }
    }
}


/* a savoir : k est l'indice du premier joueur a jouer a chaque tour                      */
/*            t est le nombre de tour                                                     */
/*            (permet de comptabiliser en combien de tour le joueur gagne)                */

int main(){

    struct info_score ***tableau_comparaison;
    struct joueur *j;
    struct g_p gagnant,perdant;
    struct de de1,de2,de3;
    int nb_joueur,nb_coup_joue;
    int k,i,t,pot,quitter,fin,i_gagnant_final;

    fin=quitter=0;
    i_gagnant_final=-2;
    srand(time(NULL));

        while ( quitter == 0 ){

            fin=menu_partie();
            if (fin==1)
                break;

            pot=21;
            t=1;

            initialisation_des(&de1,&de2,&de3);
            tableau_comparaison=creation_du_tableau_comparaison();
            j=creation_tableau_joueur(&nb_joueur);
            k=rand_ab(0,nb_joueur-1);

            while (1) {

                printf("\n\n***************************\n\n\tTurn %d : \n\n", t);

                nb_coup_joue=tour_un_joueur(&(j[k]),3,&de1,&de2,&de3,tableau_comparaison);
                gagnant.comparaison=perdant.comparaison=j[k].comparaison;
                gagnant.valeur_jeton=perdant.valeur_jeton=j[k].valeur_jeton;
                gagnant.valeur_lancer=perdant.valeur_lancer=j[k].valeur_lancer;
                gagnant.joueur=perdant.joueur=&(j[k]);

                for ( i=1 ; i<nb_joueur ; i++ ) {
                    tour_un_joueur(&(j[(k+i)%(nb_joueur)]),nb_coup_joue,&de1,&de2,&de3,tableau_comparaison);
                    determination_gagnant_perdant(&gagnant,&perdant,&(j[(k+i)%(nb_joueur)]));
                }

                if( pot > 0 ) {
                    transfert_jeton_pot(&pot,&gagnant,&perdant);
                    k=perdant.joueur->id_joueur;
                }

                else {
                    transfert_jeton(&gagnant,&perdant);
                    k=perdant.joueur->id_joueur;
                }

                printf("\n");
                for ( i=0 ; i<nb_joueur ; i++ )
                    printf("%s has %d tokens\n",j[i].nom,j[i].jeton);

                if ( pot == 0 ) {
                    i_gagnant_final=test_gagnant_final(j,&gagnant,pot,nb_joueur);

                    if ( i_gagnant_final == 1 ) {

                        for ( i = 0 ; i < nb_joueur ; i++) {
                            if ( j[i].jeton == 0) {
                                printf("\n\n\n******************************************************\n\t%s wins the game in %d turns!\n******************************************************\n",j[i].nom, t);
                                ecriture_fichier("results.txt",j[i].nom,t);
                            }
                        }
                        break;
                    }
                }

                else
                    printf("***************************\n\n\nThe player %s wins the turn %d\n\n", gagnant.joueur->nom,t);

                t++;
            }

        quitter=fin_de_partie();

        }

    return 0;
}


