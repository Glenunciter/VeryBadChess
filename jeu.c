#include <jeu.h>



void acquisitioncoordonnees(int taille, int coordonnee[2])
{
    char rep[50];
    char abcissetmp;
    int abcisse;
    int ordonne;

    printf("rentrer une lettre pour les abcisses et un nombre pour les "
           "ordonn%ces\n",
           130);

    scanf("%s", rep);
    fflush(stdin);

    while (sscanf(rep, "%c%d", &abcissetmp, &ordonne) == EOF || (abcissetmp < 65 || abcissetmp > taille + 65) ||
           (ordonne < 0 || ordonne > taille))
    {
        printf("Oups, il semblerait que les coordonn%ces rentr%ce ne soit pas "
               "valide.(exemple de coordonn%ces valident #%c%d# pour la taille "
               "%d par "
               "%d)\n",
               130, 130, 130, 65, taille, taille, taille);
        scanf("%s", rep);
        fflush(stdin);
    }

    abcisse = abcissetmp;
    switchbase(&abcisse, &ordonne, taille);

    coordonnee[0] = ordonne;
    coordonnee[1] = abcisse;
}

void switchbase(int* abscisse, int* ordonnee, int taillechiquier)
{
    *abscisse = *abscisse - 65;
    *ordonnee = taillechiquier - *ordonnee;
}

void Mouvement(int coordonneedepart[2], int coordonneearriver[2], Piece** echiquier)
{
    Piece tmp;
    tmp.aff = ' ';
    tmp.nom = -1;
    tmp.nom = 0;

    echiquier[coordonneearriver[0]][coordonneearriver[1]] = echiquier[coordonneedepart[0]][coordonneedepart[1]];
    echiquier[coordonneedepart[0]][coordonneedepart[1]] = tmp;
}



Bool FouVerification(int coordonneedepart[2], int coordonneearriver[2], Piece** echiquier)
{
    Bool verif = FAUX;

    if (coordonneedepart[1] == coordonneearriver[1])
    {
        return verif;
    }

    int y0 = coordonneedepart[0];
    int x0 = coordonneedepart[1];
    int y = coordonneearriver[0];
    int x = coordonneearriver[1];
    int coeff = (y - y0) / (x - x0);
    int deltaY = (y - y0);

    if (abs(x0 - x) == abs(y0 - y))
    {
        if (coeff > 0 && deltaY < 0)
        {
            int i = 1;

            while (((x0 - i != x) && (y0 - i != y)) && (echiquier[y0 - i][x0 - i].aff == ' '))
            {
                i++;
            }
            verif = VerificationFou(i, y, y0, x, x0, echiquier);
        }
        if (coeff > 0 && deltaY > 0)
        {
            int i = 1;

            while (((x0 + i != x) && (y0 + i != y)) && (echiquier[y0 + i][x0 + i].aff == ' '))
            {
                i++;
            }

            verif = VerificationFou(i, y, y0, x, x0, echiquier);
        }
        if (coeff < 0 && deltaY < 0)
        {
            int i = 1;

            while (((x0 + i != x) && (y0 - i != y) && (echiquier[y0 - i][x0 + i].aff == ' ')))
            {
                i++;
            }
            verif = VerificationFou(i, y, y0, x, x0, echiquier);
        }
        if (coeff < 0 && deltaY > 0)
        {
            int i = 1;

            while (((x0 - i != x) && (y0 + i != y)) && (echiquier[y0 + i][x0 - i].aff == ' '))
            {
                i++;
            }
            verif = VerificationFou(i, y, y0, x, x0, echiquier);
        }
    }

    return verif;
}



Bool VerificationFou(int i, int y, int y0, int x, int x0, Piece** echiquier)
{
    Bool verif = FAUX;

    if (i != abs(y - y0))
    {
        verif = FAUX;
    }
    else if (i == abs(y - y0) && echiquier[y][x].couleur != echiquier[y0][x0].couleur)
    {
        verif = VRAI;
    }
    return verif;
}



Bool CavalierVerification(int coordonneedepart[2], int coordonneearriver[2], Piece** echiquier)
{
    Bool verif = FAUX;

    int y0 = coordonneedepart[0];
    int x0 = coordonneedepart[1];
    int y = coordonneearriver[0];
    int x = coordonneearriver[1];

    if (((abs(y0 - y) == 2 && abs(x0 - x) == 1) || (abs(y0 - y) == 1 && abs(x0 - x) == 2)) &&
        (echiquier[y][x].couleur != echiquier[y0][x0].couleur))
    {
        verif = VRAI;
    }

    return verif;
}



Bool TourVerification(int coordonneedepart[2], int coordonneearriver[2], Piece** echiquier)
{
    Bool verif = FAUX;

    int y0 = coordonneedepart[0];
    int x0 = coordonneedepart[1];
    int y = coordonneearriver[0];
    int x = coordonneearriver[1];

    if (x == x0)
    {
        int i = 1;
        if (y < y0)
        {
            while ((y != y0 - i) && echiquier[y0 - i][x].aff == ' ')
            {
                i++;
            }
            if ((i == abs(y0 - y)) && (echiquier[y][x].couleur != echiquier[y0][x0].couleur))
            {
                verif = VRAI;
            }
        }
        if (y > y0)
        {
            while ((y != y0 + i) && echiquier[y0 + i][x].aff == ' ')
            {
                i++;
            }
            if ((i == abs(y0 - y)) && (echiquier[y][x].couleur != echiquier[y0][x0].couleur))
            {
                verif = VRAI;
            }
        }
    }
    if (y0 == y)
    {
        int i = 1;
        if (x < x0)
        {
            while ((x != x0 - i) && echiquier[y][x0 - i].aff == ' ')
            {
                i++;
            }
            if ((i == abs(x0 - x)) && (echiquier[y][x].couleur != echiquier[y0][x0].couleur))
            {
                verif = VRAI;
            }
        }
        if (x > x0)
        {
            while ((x != x0 + i) && echiquier[y][x0 + i].aff == ' ')
            {
                i++;
            }
            if ((i == abs(x0 - x)) && (echiquier[y][x].couleur != echiquier[y0][x0].couleur))
            {
                verif = VRAI;
            }
        }
    }
    return verif;
}

Bool PionVerification(int coordonneedepart[2], int coordonneearriver[2], int taille, Piece** echiquier)
{

    Bool verif = FAUX;
    Piece tmp;
    tmp.aff = ' ';
    tmp.couleur = EMPTY;
    tmp.nom = VIDE;

    int y0 = coordonneedepart[0];
    int x0 = coordonneedepart[1];
    int y = coordonneearriver[0];
    int x = coordonneearriver[1];

    if (echiquier[y0][x0].coup == 0)
    {   
        
        if(y0 == taille -2){
            if ((y0 - y == 2 || y0 - y == 1) && x == x0 )
            {
                verif = VRAI;
            }
           
        }
        
    if ((y0 - y) == 1 && abs(x - x0) == 1 && (echiquier[y][x].couleur != tmp.couleur) &&
        (echiquier[y][x].couleur != echiquier[y0][x0].couleur))
    {
        verif = VRAI;
    }

    if (x == x0 && (y0 - y) == 1 && (echiquier[y][x].aff == ' '))
    {
        verif = VRAI;
    }
       
    }else{
         if ( (y0 - y) == 1 && abs(x - x0) == 1 && (echiquier[y][x].couleur != tmp.couleur) && (echiquier[y][x].couleur != echiquier[y0][x0].couleur))
        {
            verif = VRAI;
        }

        if ( x == x0 && (y0 - y) == 1 && (echiquier[y][x].aff == ' '))
        {
            verif = VRAI;
        }
    }
    

    return verif;
}




Bool RoiVerification(int coordonneedepart[2], int coordonneearriver[2], Piece** echiquier){
       
    Bool verif = FAUX;

    int y0 = coordonneedepart[0];
    int x0 = coordonneedepart[1];
    int y = coordonneearriver[0];
    int x = coordonneearriver[1];

    if((x0 == x && abs(y0-y)==1 && echiquier[y0][x0].couleur != echiquier[y][x].couleur)||(y0 == y && abs(x0-x)==1 && echiquier[y0][x0].couleur != echiquier[y][x].couleur)){
        
        verif = VRAI;
    }else{
        if((abs(x0-x)==abs(y0-y)) && echiquier[y0][x0].couleur != echiquier[y][x].couleur ){
            verif = VRAI ; 
        }
    }

    return verif;

}



Bool DameVerification(int coordonneedepart[2], int coordonneearriver[2], Piece** echiquier){
    
    Bool verif = FAUX;

    int y0 = coordonneedepart[0];
    int x0 = coordonneedepart[1];
    int y = coordonneearriver[0];
    int x = coordonneearriver[1];

    if (abs(x0 - x) == abs(y0 - y))
    {
        int coeff = (y - y0) / (x - x0);
        int deltaY = (y - y0); 

        if (coeff > 0 && deltaY < 0) 
        {
            int i = 1;

            while (((x0 - i != x) && (y0 - i != y)) && (echiquier[y0 - i][x0 - i].aff == ' ')) 
            {
                i++;
            }                                                                                           
            verif = VerificationFou(i,y,y0,x,x0,echiquier); // La dame ayant une combianaison des mouvements du fou et de la tour, nous avons réutilisé la fonction seravant pour le fou                                                                                                                                                                  
        }
        if (coeff > 0 && deltaY > 0)
        {
            int i = 1;

            while (((x0 + i != x) && (y0 + i != y)) && (echiquier[y0 + i][x0 + i].aff == ' '))
            {
                i++;
            }

            verif = VerificationFou(i,y,y0,x,x0,echiquier);    
        }
        if (coeff < 0 && deltaY < 0)
        {
            int i = 1;

            while (((x0 + i != x) && (y0 - i != y) && (echiquier[y0 - i][x0 + i].aff == ' ')))
            {
                i++;
            }
            verif = VerificationFou(i,y,y0,x,x0,echiquier);  
        }
        if (coeff < 0 && deltaY > 0)
        {
            int i = 1;

            while (((x0 - i != x) && (y0 + i != y)) && (echiquier[y0 + i][x0 - i].aff == ' '))
            {
                i++;
            }
            verif = VerificationFou(i,y,y0,x,x0,echiquier);  
        }
    }
    if(x == x0){
        int i = 1;
        if(y<y0){
            while((y != y0-i)&&echiquier[y0-i][x].aff == ' '){
                i++;
            }
            if ((i == abs(y0-y)) && (echiquier[y][x].couleur != echiquier[y0][x0].couleur))
            {
                verif = VRAI;
            }
            
        }
        if(y>y0){
            while((y != y0+i)&&echiquier[y0+i][x].aff == ' '){
                i++;
            }
            if ((i == abs(y0-y)) && (echiquier[y][x].couleur != echiquier[y0][x0].couleur))
            {
                verif =VRAI;
            }
            
        }
    }
    if(y0 == y){
        int i = 1;
        if(x<x0){
            while((x != x0-i)&&echiquier[y][x0-i].aff == ' '){
                i++;
            }
            if ((i == abs(x0-x)) && (echiquier[y][x].couleur != echiquier[y0][x0].couleur))
            {
                verif = VRAI;
            }
            
        }
        if(x>x0){
            while((x != x0+i)&&echiquier[y][x0+i].aff == ' '){
                i++;
            }
            if ((i == abs(x0-x)) && (echiquier[y][x].couleur != echiquier[y0][x0].couleur))
            {
                verif =VRAI;
            }
            
        }
    }
    
    return verif;
}



void PositionRoi(int CoordonneeRoi[2], Couleur Roi, int taille, Piece** echiquier)
{

    for (int i = 0; i < taille; i++)
    {
        for (int j = 0; j < taille; j++)
        {
            if (echiquier[i][j].couleur == Roi && echiquier[i][j].nom == ROI)
            {
                CoordonneeRoi[0] = i;
                CoordonneeRoi[1] = j;
               
            }
        }
    }
}


Bool MouvementPieceEchec(int taille,int coordonnee[2],int coordonneeRoi[2],Piece** echiquier){
    
    int l = coordonnee[0]; // l pour lignes
    int c = coordonnee[1]; // c pour colonnes 
    Bool verif = FAUX;
    
    if (echiquier[l][c].nom == PION)
    {
       verif = PionVerification(coordonnee,coordonneeRoi,taille, echiquier);
    }
    if (echiquier[l][c].nom == CAVALIER)
    {
       verif = CavalierVerification(coordonnee,coordonneeRoi,echiquier);
    }
    if (echiquier[l][c].nom == FOU)
    {
       verif = FouVerification(coordonnee,coordonneeRoi, echiquier);
    }
    if (echiquier[l][c].nom == TOUR)
    {
       verif = TourVerification(coordonnee,coordonneeRoi,echiquier);
    }
    if (echiquier[l][c].nom ==DAME)
    {
       verif = DameVerification(coordonnee,coordonneeRoi,echiquier);
    }
    
    if (echiquier[l][c].nom ==ROI)
    {
       verif = RoiVerification(coordonnee,coordonneeRoi,echiquier);
    }

   return verif;
}



int** EchecRoi(int taille, int CoordonneRoi[2], Piece** echiquier,Couleur MiseEnEchec, Couleur MetEnEchec, int* tailleTabtmp)
{
    
    Bool verif = FAUX;
    int Coordonnee[2];
    *tailleTabtmp = 1;
    int taillel = *tailleTabtmp;

    int** TabPieceEchec = (int**)malloc(sizeof(int*)*taillel);

    if(TabPieceEchec != NULL){
        *TabPieceEchec = NULL;
        for (int i = 0; i < taille; i++)
        {

            for (int j = 0; j < taille; j++)
            {   
                verif = FAUX;
                if (echiquier[i][j].couleur == MetEnEchec && echiquier[i][j].aff != ' ')
                {   
                    
                    Coordonnee[0] = i;
                    Coordonnee[1] = j;
                    verif = MouvementPieceEchec(taille,Coordonnee,CoordonneRoi,echiquier);
                    
                    if(verif) {
                        
                        if(taillel > 1)
                        {
                        
                            TabPieceEchec = realloc(TabPieceEchec,sizeof(int*)*taillel);
                            TabPieceEchec[taillel-1] = (int*)malloc(sizeof(int)*2);
                            TabPieceEchec[taillel-1][0] = i;
                            TabPieceEchec[taillel-1][1] = j;
                            taillel++;      
                        }

                        if( taillel == 1){
                            TabPieceEchec[taillel-1] = (int*)malloc(sizeof(int)*2);
                            TabPieceEchec[taillel-1][0] = i;
                            TabPieceEchec[taillel-1][1] = j;
                            taillel++;
                        }    
                    }
                }


            }
        }
    }    
    if (*TabPieceEchec == NULL){
        free(TabPieceEchec);
        TabPieceEchec = NULL;
        *tailleTabtmp = 0 ;
    }


    *tailleTabtmp = taillel -1;


    return TabPieceEchec;
}


Bool RoiMouvementElementaire(int taille, int CoordonneRoi[2], Couleur MiseEnEchec, Couleur MetEnEchec,Piece **echiquier)
{

    Bool verif = FAUX;
    int **TabPieceEchec;
    int tailleuseless;
    int yR = CoordonneRoi[0];
    int xR = CoordonneRoi[1];
    int NewCoordonneeRoi[2];

    if (yR - 1 >= 0 && xR == CoordonneRoi[1] && echiquier[yR - 1][xR].couleur != MiseEnEchec)
    {

        NewCoordonneeRoi[0] = yR - 1;
        NewCoordonneeRoi[1] = xR;
        TabPieceEchec = EchecRoi(taille, NewCoordonneeRoi, echiquier, MiseEnEchec, MetEnEchec, &tailleuseless);
        if (TabPieceEchec == NULL)
        {
            verif = VRAI;
            return verif;
        }

        freeTab(&TabPieceEchec, tailleuseless);
    }
    if (yR + 1 < taille && xR == CoordonneRoi[1] && echiquier[yR + 1][xR].couleur != MiseEnEchec)
    {

        NewCoordonneeRoi[0] = yR + 1;
        NewCoordonneeRoi[1] = xR;
        TabPieceEchec = EchecRoi(taille, NewCoordonneeRoi, echiquier, MiseEnEchec, MetEnEchec, &tailleuseless);

        if (TabPieceEchec == NULL)
        {
            verif = VRAI;
            return verif;
        }
        freeTab(&TabPieceEchec, tailleuseless);
    }

    if (xR - 1 >= 0 && yR == CoordonneRoi[0] && echiquier[yR][xR - 1].couleur != MiseEnEchec)
    {
        NewCoordonneeRoi[0] = yR;
        NewCoordonneeRoi[1] = xR - 1;
        TabPieceEchec = EchecRoi(taille, NewCoordonneeRoi, echiquier, MiseEnEchec, MetEnEchec, &tailleuseless);

        if (TabPieceEchec == NULL)
        {
            verif = VRAI;
            return verif;
        }

        freeTab(&TabPieceEchec, tailleuseless);
    }

    if (xR + 1 < taille && yR == CoordonneRoi[0] && echiquier[yR][xR + 1].couleur != MiseEnEchec)
    {

        NewCoordonneeRoi[0] = yR;
        NewCoordonneeRoi[1] = xR + 1;
        TabPieceEchec = EchecRoi(taille, NewCoordonneeRoi, echiquier, MiseEnEchec, MetEnEchec, &tailleuseless);

        if (TabPieceEchec == NULL)
        {
            verif = VRAI;
            return verif;
        }

        freeTab(&TabPieceEchec, tailleuseless);
    }
    if (yR - 1 >= 0 && xR - 1 >= 0 && echiquier[yR - 1][xR - 1].couleur != MiseEnEchec)
    {

        NewCoordonneeRoi[0] = yR - 1;
        NewCoordonneeRoi[1] = xR - 1;
        TabPieceEchec = EchecRoi(taille, NewCoordonneeRoi, echiquier, MiseEnEchec, MetEnEchec, &tailleuseless);

        if (TabPieceEchec == NULL)
        {
            verif = VRAI;
            return verif;
        }

        freeTab(&TabPieceEchec, tailleuseless);
    }
    if (yR - 1 >= 0 && xR + 1 < taille && echiquier[yR + 1][xR + 1].couleur != MiseEnEchec)
    {

        NewCoordonneeRoi[0] = yR - 1;
        NewCoordonneeRoi[1] = xR + 1;
        TabPieceEchec = EchecRoi(taille, NewCoordonneeRoi, echiquier, MiseEnEchec, MetEnEchec, &tailleuseless);

        if (TabPieceEchec == NULL)
        {
            verif = VRAI;
            return verif;
        }

        freeTab(&TabPieceEchec, tailleuseless);
    }
    if (yR + 1 < taille && xR + 1 < taille && echiquier[yR + 1][xR + 1].couleur != MiseEnEchec)
    {

        NewCoordonneeRoi[0] = yR + 1;
        NewCoordonneeRoi[1] = xR + 1;
        TabPieceEchec = EchecRoi(taille, NewCoordonneeRoi, echiquier, MiseEnEchec, MetEnEchec, &tailleuseless);

        if (TabPieceEchec == NULL)
        {
            verif = VRAI;
            return verif;
        }

        freeTab(&TabPieceEchec, tailleuseless);
    }
    if (yR + 1 < taille && xR - 1 >= 0 && echiquier[yR + 1][xR - 1].couleur != MiseEnEchec)
    {

        NewCoordonneeRoi[0] = yR + 1;
        NewCoordonneeRoi[1] = xR - 1;
        TabPieceEchec = EchecRoi(taille, NewCoordonneeRoi, echiquier, MiseEnEchec, MetEnEchec, &tailleuseless);

        if (TabPieceEchec == NULL)
        {
            verif = VRAI;
            return verif;
        }

        freeTab(&TabPieceEchec, tailleuseless);
    }

   return verif; 
}

Bool EchecEtMatContre(int taille, Piece **echiquier, int coordonneePieceMetenEchec[2], Couleur MetEnEchec,
                      Couleur MisenEchec, int coordonneeRoi[2])
{

    Piece tmp; // utile pour les verifications
    Bool verif = FAUX;
    Bool verifEchecRoi = VRAI;
    int yp = coordonneePieceMetenEchec[0];
    int xp = coordonneePieceMetenEchec[1];
    int **TabPieceProtegeRoi; // utile pour stockée les coordonnées des pièces qui peuvent éventuellement protéger le
                              // Roi en prise
    int tailleTab = 0;
    int **tabok;
    int Tailletabok = 0; // useless
    int i = 0;
    int CoordonneeVerif[2];

    if (echiquier[yp][xp].nom == CAVALIER || echiquier[yp][xp].nom == PION)
    {
        i = 0;
        TabPieceProtegeRoi =
            EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec,
                     &tailleTab); // ici la fonction echec Roi cherche toutes les pièces de la couleur du Roi en prise
                                  // qui peuvent prendre la pièce qui met en echec le roi

        if (TabPieceProtegeRoi != NULL)
        { // Finalité --> dire si une pièce de la couleur du ROI peut prendre la pièce en question
            tmp = echiquier[yp][xp];

            while (i < tailleTab && verifEchecRoi)
            {

                CoordonneeVerif[0] = TabPieceProtegeRoi[i][0];
                CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                if (tabok == NULL)
                {
                    verifEchecRoi = FAUX;
                }
                Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                          echiquier);    // on remet la pièce à  sa place fin de vérification
                echiquier[yp][xp] = tmp; // on remet à sa place la pièce

                if (verifEchecRoi == VRAI)
                {
                    freeTab(&tabok, Tailletabok);
                    Tailletabok = 0;
                }
                i++;
            }

            if (i < tailleTab)
            {
                verif = VRAI;
            }
        }

        freeTab(&TabPieceProtegeRoi, tailleTab);
        tailleTab = 0;
    }

    if (echiquier[yp][xp].nom == TOUR)
    {

        int h = 0; // indique le sens de déplacement ici vertical (hauteur)
        int l = 0; // horizontal (lignes);

        if (xp == coordonneeRoi[1])
        {

            h = abs(coordonneeRoi[0] - yp);
            if (yp < coordonneeRoi[0])
            {

                for (int k = 0; k < h; k++)
                {

                    coordonneePieceMetenEchec[0] = yp + k;
                    tmp = echiquier[yp + k][xp];
                    i = 0;
                    TabPieceProtegeRoi =
                        EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);

                    if (TabPieceProtegeRoi != NULL)
                    {
                        while (i < tailleTab && verifEchecRoi)
                        {

                            CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                            CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                            Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                            tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                            if (tabok == NULL)
                            {
                                verifEchecRoi = FAUX;
                            }
                            Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                      echiquier);        // on remet la pièce à  sa place fin de vérification
                            echiquier[yp + k][xp] = tmp; // on remet à sa place la pièce
                            if (verifEchecRoi == VRAI)
                            {

                                freeTab(&tabok, Tailletabok);
                                Tailletabok = 0;
                            }
                            i++;
                        }

                        if (i < tailleTab)
                        {
                            verif = VRAI;
                            freeTab(&TabPieceProtegeRoi, tailleTab);
                            tailleTab = 0;
                            return verif;
                        }
                    }
                }
            }
            else
            {

                for (int k = 0; k < h; k++)
                {
                    coordonneePieceMetenEchec[0] = yp + k;
                    tmp = echiquier[yp - k][xp];
                    i = 0;
                    TabPieceProtegeRoi =
                        EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                    if (TabPieceProtegeRoi != NULL)
                    {
                        while (i < tailleTab && verifEchecRoi)
                        {

                            CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                            CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                            Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                            tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                            if (tabok == NULL)
                            {
                                verifEchecRoi = FAUX;
                            }
                            Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                      echiquier);        // on remet la pièce à  sa place fin de vérification
                            echiquier[yp - k][xp] = tmp; // on remet à sa place la pièce
                            if (verifEchecRoi == VRAI)
                            {

                                freeTab(&tabok, Tailletabok);
                                Tailletabok = 0;
                            }
                            i++;
                        }
                        if (i < tailleTab)
                        {
                            verif = VRAI;
                            freeTab(&TabPieceProtegeRoi, tailleTab);
                            tailleTab = 0;
                            return verif;
                        }
                    }
                }
            }
        }
        if (yp == coordonneeRoi[0])
        {
            l = abs(coordonneeRoi[1] - xp);
            if (xp < coordonneeRoi[1])
            {

                for (int k = 0; k < l; k++)
                {
                    coordonneePieceMetenEchec[1] = xp + k;
                    tmp = echiquier[yp][xp + k];
                    i = 0;
                    TabPieceProtegeRoi =
                        EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                    if (TabPieceProtegeRoi != NULL)
                    {
                        while (i < tailleTab && verifEchecRoi)
                        {

                            CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                            CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                            Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                            tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                            if (tabok == NULL)
                            {
                                verifEchecRoi = FAUX;
                            }
                            Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                      echiquier);        // on remet la pièce à  sa place fin de vérification
                            echiquier[yp][xp + k] = tmp; // on remet à sa place la pièce

                            if (verifEchecRoi == VRAI)
                            {

                                freeTab(&tabok, Tailletabok);
                                Tailletabok = 0;
                            }
                            i++;
                        }
                        if (i < tailleTab)
                        {
                            verif = VRAI;
                            freeTab(&TabPieceProtegeRoi, tailleTab);
                            tailleTab = 0;
                            return verif;
                        }
                    }
                }
            }
            else
            {

                for (int k = 0; k < l; k++)
                {
                    coordonneePieceMetenEchec[1] = xp - k;
                    tmp = echiquier[yp][xp - k];
                    i = 0;
                    TabPieceProtegeRoi =
                        EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                    if (TabPieceProtegeRoi != NULL)
                    {
                        while (i < tailleTab && verifEchecRoi)
                        {

                            CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                            CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                            Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                            tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                            if (tabok == NULL)
                            {
                                verifEchecRoi = FAUX;
                            }
                            Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                      echiquier);        // on remet la pièce à  sa place fin de vérification
                            echiquier[yp][xp - k] = tmp; // on remet à sa place la pièce
                            if (verifEchecRoi == VRAI)
                            {

                                freeTab(&tabok, Tailletabok);
                                Tailletabok = 0;
                            }
                            i++;
                        }
                        if (i < tailleTab)
                        {
                            verif = VRAI;
                            freeTab(&TabPieceProtegeRoi, tailleTab);
                            tailleTab = 0;
                            return verif;
                        }
                    }
                }
            }
        }
    }

    if (echiquier[yp][xp].nom == FOU)
    {

        int dsg = 0; // diagonal supérieur gauche vat être utile pour l'écart de case entre le roi et le fou en question
        int dsd = 0;
        int dig = 0;
        int did = 0;

        if (xp - coordonneeRoi[1] < 0 && yp - coordonneeRoi[0] < 0)
        {
            dsg = abs(yp - coordonneeRoi[0]);

            for (int k = 0; k < dsg; k++)
            {
                coordonneePieceMetenEchec[0] = yp + k;
                coordonneePieceMetenEchec[1] = xp + k;
                tmp = echiquier[yp + k][xp + k];
                i = 0;
                TabPieceProtegeRoi =
                    EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                if (TabPieceProtegeRoi != NULL)
                {
                    while (i < tailleTab && verifEchecRoi)
                    {

                        CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                        CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                        Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                        tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                        if (tabok == NULL)
                        {
                            verifEchecRoi = FAUX;
                        }
                        Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                  echiquier);            // on remet la pièce à  sa place fin de vérification
                        echiquier[yp + k][xp + k] = tmp; // on remet à sa place la pièce
                        if (verifEchecRoi == VRAI)
                        {
                            freeTab(&tabok, Tailletabok);
                            Tailletabok = 0;
                        }
                        i++;
                    }
                    if (i < tailleTab)
                    {
                        verif = VRAI;
                        freeTab(&TabPieceProtegeRoi, tailleTab);
                        tailleTab = 0;
                        return verif;
                    }
                }
            }
        }

        if (xp - coordonneeRoi[1] > 0 && yp - coordonneeRoi[0] < 0)
        {
            dsd = abs(yp - coordonneeRoi[0]);

            for (int k = 0; k < dsd; k++)
            {
                coordonneePieceMetenEchec[0] = yp + k;
                coordonneePieceMetenEchec[1] = xp - k;
                tmp = echiquier[yp + k][xp - k];
                i = 0;
                TabPieceProtegeRoi =
                    EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                if (TabPieceProtegeRoi != NULL)
                {
                    while (i < tailleTab && verifEchecRoi)
                    {

                        CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                        CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                        Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                        tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                        if (tabok == NULL)
                        {
                            verifEchecRoi = FAUX;
                        }
                        Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                  echiquier);            // on remet la pièce à  sa place fin de vérification
                        echiquier[yp + k][xp - k] = tmp; // on remet à sa place la pièce

                        if (verifEchecRoi == VRAI)
                        {
                            freeTab(&tabok, Tailletabok);
                            Tailletabok = 0;
                        }
                        i++;
                    }
                    if (i < tailleTab)
                    {
                        verif = VRAI;
                        freeTab(&TabPieceProtegeRoi, tailleTab);
                        tailleTab = 0;
                        return verif;
                    }
                }
            }
        }
        if (xp - coordonneeRoi[1] < 0 && yp - coordonneeRoi[0] > 0)
        {
            dig = abs(yp - coordonneeRoi[0]);

            for (int k = 0; k < dig; k++)
            {
                coordonneePieceMetenEchec[0] = yp - k;
                coordonneePieceMetenEchec[1] = xp + k;
                tmp = echiquier[yp - k][xp + k];
                i = 0;
                TabPieceProtegeRoi =
                    EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                if (TabPieceProtegeRoi != NULL)
                {
                    while (i < tailleTab && verifEchecRoi)
                    {

                        CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                        CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                        Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                        tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                        if (tabok == NULL)
                        {
                            verifEchecRoi = FAUX;
                        }
                        Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                  echiquier);            // on remet la pièce à  sa place fin de vérification
                        echiquier[yp - k][xp + k] = tmp; // on remet à sa place la pièce

                        if (verifEchecRoi == VRAI)
                        {
                            freeTab(&tabok, Tailletabok);
                            Tailletabok = 0;
                        }
                        i++;
                    }
                    if (i < tailleTab)
                    {
                        verif = VRAI;

                        freeTab(&TabPieceProtegeRoi, tailleTab);
                        tailleTab = 0;
                        return verif;
                    }
                }
            }
        }
        if (xp - coordonneeRoi[1] > 0 && yp - coordonneeRoi[0] > 0)
        {

            did = abs(yp - coordonneeRoi[0]);

            for (int k = 0; k < did; k++)
            {
                coordonneePieceMetenEchec[0] = yp - k;
                coordonneePieceMetenEchec[1] = xp - k;
                tmp = echiquier[yp - k][xp - k];
                i = 0;
                TabPieceProtegeRoi =
                    EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                if (TabPieceProtegeRoi != NULL)
                {
                    while (i < tailleTab && verifEchecRoi)
                    {

                        CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                        CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                        Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                        tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                        if (tabok == NULL)
                        {
                            verifEchecRoi = FAUX;
                        }
                        Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                  echiquier);            // on remet la pièce à  sa place fin de vérification
                        echiquier[yp - k][xp - k] = tmp; // on remet à sa place la pièce

                        if (verifEchecRoi == VRAI)
                        {
                            freeTab(&tabok, Tailletabok);
                            Tailletabok = 0;
                        }

                        i++;
                    }
                    if (i < tailleTab)
                    {
                        verif = VRAI;

                        freeTab(&TabPieceProtegeRoi, tailleTab);
                        tailleTab = 0;

                        return verif;
                    }
                }
            }
        }
    }

    if (echiquier[yp][xp].nom == DAME)
    {

        int dsg = 0; // diagonal supérieur gauche vat être utile pour l'écart de case entre le roi et le fou en question
        int dsd = 0;
        int dig = 0;
        int did = 0;
        int h = 0;
        int l = 0;

        if (xp == coordonneeRoi[1])
        {

            h = abs(coordonneeRoi[0] - yp);
            if (yp < coordonneeRoi[0])
            {

                for (int k = 0; k < h; k++)
                {

                    coordonneePieceMetenEchec[0] = yp + k;
                    tmp = echiquier[yp + k][xp];
                    i = 0;
                    TabPieceProtegeRoi =
                        EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);

                    if (TabPieceProtegeRoi != NULL)
                    {
                        while (i < tailleTab && verifEchecRoi)
                        {

                            CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                            CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                            Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                            tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                            if (tabok == NULL)
                            {
                                verifEchecRoi = FAUX;
                            }
                            Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                      echiquier);        // on remet la pièce à  sa place fin de vérification
                            echiquier[yp + k][xp] = tmp; // on remet à sa place la pièce
                            if (verifEchecRoi == VRAI)
                            {

                                freeTab(&tabok, Tailletabok);
                                Tailletabok = 0;
                            }
                            i++;
                        }

                        if (i < tailleTab)
                        {
                            verif = VRAI;
                            freeTab(&TabPieceProtegeRoi, tailleTab);
                            tailleTab = 0;
                            return verif;
                        }
                    }
                }
            }
            else
            {

                for (int k = 0; k < h; k++)
                {
                    coordonneePieceMetenEchec[0] = yp + k;
                    tmp = echiquier[yp - k][xp];
                    i = 0;
                    TabPieceProtegeRoi =
                        EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                    if (TabPieceProtegeRoi != NULL)
                    {
                        while (i < tailleTab && verifEchecRoi)
                        {

                            CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                            CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                            Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                            tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                            if (tabok == NULL)
                            {
                                verifEchecRoi = FAUX;
                            }
                            Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                      echiquier);        // on remet la pièce à  sa place fin de vérification
                            echiquier[yp - k][xp] = tmp; // on remet à sa place la pièce
                            if (verifEchecRoi == VRAI)
                            {

                                freeTab(&tabok, Tailletabok);
                                Tailletabok = 0;
                            }
                            i++;
                        }
                        if (i < tailleTab)
                        {
                            verif = VRAI;
                            freeTab(&TabPieceProtegeRoi, tailleTab);
                            tailleTab = 0;
                            return verif;
                        }
                    }
                }
            }
        }
        if (yp == coordonneeRoi[0])
        {
            l = abs(coordonneeRoi[1] - xp);
            if (xp < coordonneeRoi[1])
            {

                for (int k = 0; k < l; k++)
                {
                    coordonneePieceMetenEchec[1] = xp + k;
                    tmp = echiquier[yp][xp + k];
                    i = 0;
                    TabPieceProtegeRoi =
                        EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                    if (TabPieceProtegeRoi != NULL)
                    {
                        while (i < tailleTab && verifEchecRoi)
                        {

                            CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                            CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                            Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                            tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                            if (tabok == NULL)
                            {
                                verifEchecRoi = FAUX;
                            }
                            Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                      echiquier);        // on remet la pièce à  sa place fin de vérification
                            echiquier[yp][xp + k] = tmp; // on remet à sa place la pièce

                            if (verifEchecRoi == VRAI)
                            {

                                freeTab(&tabok, Tailletabok);
                                Tailletabok = 0;
                            }
                            i++;
                        }
                        if (i < tailleTab)
                        {
                            verif = VRAI;
                            freeTab(&TabPieceProtegeRoi, tailleTab);
                            tailleTab = 0;
                            return verif;
                        }
                    }
                }
            }
            else
            {

                for (int k = 0; k < l; k++)
                {
                    coordonneePieceMetenEchec[1] = xp - k;
                    tmp = echiquier[yp][xp - k];
                    i = 0;
                    TabPieceProtegeRoi =
                        EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                    if (TabPieceProtegeRoi != NULL)
                    {
                        while (i < tailleTab && verifEchecRoi)
                        {

                            CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                            CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                            Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                            tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                            if (tabok == NULL)
                            {
                                verifEchecRoi = FAUX;
                            }
                            Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                      echiquier);        // on remet la pièce à  sa place fin de vérification
                            echiquier[yp][xp - k] = tmp; // on remet à sa place la pièce
                            if (verifEchecRoi == VRAI)
                            {

                                freeTab(&tabok, Tailletabok);
                                Tailletabok = 0;
                            }
                            i++;
                        }
                        if (i < tailleTab)
                        {
                            verif = VRAI;
                            freeTab(&TabPieceProtegeRoi, tailleTab);
                            tailleTab = 0;
                            return verif;
                        }
                    }
                }
            }
        }
        if (xp - coordonneeRoi[1] < 0 && yp - coordonneeRoi[0] < 0)
        {
            dsg = abs(yp - coordonneeRoi[0]);

            for (int k = 0; k < dsg; k++)
            {
                coordonneePieceMetenEchec[0] = yp + k;
                coordonneePieceMetenEchec[1] = xp + k;
                tmp = echiquier[yp + k][xp + k];
                i = 0;
                TabPieceProtegeRoi =
                    EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                if (TabPieceProtegeRoi != NULL)
                {
                    while (i < tailleTab && verifEchecRoi)
                    {

                        CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                        CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                        Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                        tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                        if (tabok == NULL)
                        {
                            verifEchecRoi = FAUX;
                        }
                        Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                  echiquier);            // on remet la pièce à  sa place fin de vérification
                        echiquier[yp + k][xp + k] = tmp; // on remet à sa place la pièce
                        if (verifEchecRoi == VRAI)
                        {
                            freeTab(&tabok, Tailletabok);
                            Tailletabok = 0;
                        }
                        i++;
                    }
                    if (i < tailleTab)
                    {
                        verif = VRAI;
                        freeTab(&TabPieceProtegeRoi, tailleTab);
                        tailleTab = 0;
                        return verif;
                    }
                }
            }
        }

        if (xp - coordonneeRoi[1] > 0 && yp - coordonneeRoi[0] < 0)
        {
            dsd = abs(yp - coordonneeRoi[0]);

            for (int k = 0; k < dsd; k++)
            {
                coordonneePieceMetenEchec[0] = yp + k;
                coordonneePieceMetenEchec[1] = xp - k;
                tmp = echiquier[yp + k][xp - k];
                i = 0;
                TabPieceProtegeRoi =
                    EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                if (TabPieceProtegeRoi != NULL)
                {
                    while (i < tailleTab && verifEchecRoi)
                    {

                        CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                        CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                        Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                        tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                        if (tabok == NULL)
                        {
                            verifEchecRoi = FAUX;
                        }
                        Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                  echiquier);            // on remet la pièce à  sa place fin de vérification
                        echiquier[yp + k][xp - k] = tmp; // on remet à sa place la pièce

                        if (verifEchecRoi == VRAI)
                        {
                            freeTab(&tabok, Tailletabok);
                            Tailletabok = 0;
                        }
                        i++;
                    }
                    if (i < tailleTab)
                    {
                        verif = VRAI;
                        freeTab(&TabPieceProtegeRoi, tailleTab);
                        tailleTab = 0;
                        return verif;
                    }
                }
            }
        }
        if (xp - coordonneeRoi[1] < 0 && yp - coordonneeRoi[0] > 0)
        {
            dig = abs(yp - coordonneeRoi[0]);

            for (int k = 0; k < dig; k++)
            {
                coordonneePieceMetenEchec[0] = yp - k;
                coordonneePieceMetenEchec[1] = xp + k;
                tmp = echiquier[yp - k][xp + k];
                i = 0;
                TabPieceProtegeRoi =
                    EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                if (TabPieceProtegeRoi != NULL)
                {
                    while (i < tailleTab && verifEchecRoi)
                    {

                        CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                        CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                        Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                        tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                        if (tabok == NULL)
                        {
                            verifEchecRoi = FAUX;
                        }
                        Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                  echiquier);            // on remet la pièce à  sa place fin de vérification
                        echiquier[yp - k][xp + k] = tmp; // on remet à sa place la pièce

                        if (verifEchecRoi == VRAI)
                        {
                            freeTab(&tabok, Tailletabok);
                            Tailletabok = 0;
                        }
                        i++;
                    }
                    if (i < tailleTab)
                    {
                        verif = VRAI;

                        freeTab(&TabPieceProtegeRoi, tailleTab);
                        tailleTab = 0;
                        return verif;
                    }
                }
            }
        }
        if (xp - coordonneeRoi[1] > 0 && yp - coordonneeRoi[0] > 0)
        {

            did = abs(yp - coordonneeRoi[0]);

            for (int k = 0; k < did; k++)
            {
                coordonneePieceMetenEchec[0] = yp - k;
                coordonneePieceMetenEchec[1] = xp - k;
                tmp = echiquier[yp - k][xp - k];
                i = 0;
                TabPieceProtegeRoi =
                    EchecRoi(taille, coordonneePieceMetenEchec, echiquier, MetEnEchec, MisenEchec, &tailleTab);
                if (TabPieceProtegeRoi != NULL)
                {
                    while (i < tailleTab && verifEchecRoi)
                    {

                        CoordonneeVerif[0] = TabPieceProtegeRoi[i][0]; // pièce qui protege le roi
                        CoordonneeVerif[1] = TabPieceProtegeRoi[i][1];
                        Mouvement(CoordonneeVerif, coordonneePieceMetenEchec, echiquier);
                        tabok = EchecRoi(taille, coordonneeRoi, echiquier, MisenEchec, MetEnEchec, &Tailletabok);
                        if (tabok == NULL)
                        {
                            verifEchecRoi = FAUX;
                        }
                        Mouvement(coordonneePieceMetenEchec, CoordonneeVerif,
                                  echiquier);            // on remet la pièce à  sa place fin de vérification
                        echiquier[yp - k][xp - k] = tmp; // on remet à sa place la pièce

                        if (verifEchecRoi == VRAI)
                        {
                            freeTab(&tabok, Tailletabok);
                            Tailletabok = 0;
                        }

                        i++;
                    }
                    if (i < tailleTab)
                    {
                        verif = VRAI;

                        freeTab(&TabPieceProtegeRoi, tailleTab);
                        tailleTab = 0;

                        return verif;
                    }
                }
            }
        }
    }
    return verif;
}

Bool PasEchecEtMat(int taille, int CoordonneRoi[2], Couleur MiseEnEchec, Couleur MetEnEchec, Piece **echiquier)
{
    Bool verif = VRAI;
    Bool verifMvtElementaire = FAUX;
    Bool verifContre = FAUX;
    int **TabEchec;
    int tailletableau = 0;
    int CoordonnePieceMetEnEchec[2]; // dans le cas où le roi serait effectivement en echec et qu'il ne peut
                                     // bouger
    TabEchec = EchecRoi(taille, CoordonneRoi, echiquier, MiseEnEchec, MetEnEchec, &tailletableau);
    if (TabEchec != NULL)
    {
        verifMvtElementaire = RoiMouvementElementaire(taille, CoordonneRoi, MiseEnEchec, MetEnEchec, echiquier);
        if (verifMvtElementaire == FAUX)
        {
            CoordonnePieceMetEnEchec[0] = TabEchec[0][0];
            CoordonnePieceMetEnEchec[1] = TabEchec[0][1];
            verifContre = EchecEtMatContre(taille, echiquier, CoordonnePieceMetEnEchec, MetEnEchec, MiseEnEchec,
                                           CoordonneRoi);
            if (verifContre == FAUX)
            {
                verif = FAUX;
            }
        }
    }
    freeTab(&TabEchec, tailletableau);
    tailletableau = 0;
    return verif;
}

void freeTab(int ***tab, int tailleTab)
{
    if (tab != NULL)
    {
        for (int i = 0; i < tailleTab; i++)
        {
            if ((*tab) != NULL)
            {
                free((*tab)[i]);
                (*tab)[i] = NULL;
            }
        }
        free(*tab);
        tab = NULL;
    }
}