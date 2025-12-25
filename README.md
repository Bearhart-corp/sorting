NOUVELLES IMPLEMENTATIONS DE L'algo adaptatif local:

PREMIERE OPTI: Normalisation, les valeurs de la liste sont changé par l'index où ils devraient être
ex: 12, 24, 6, 4, devient -> 2, 3, 1, 0

DEUXIEME OPTI: on push la moitié faible de la stack A vers B
ex: Pour N = 50: 0..49 ∈ stack A devient -> 25..49 ∈ A et 0..24 ∈ B
Puis: (0..12 + 25..49 ∈ A et 13..24 ∈ B) OU  (13..24 + 25..49 ∈ A et 0..12 ∈ B) 
a voir ce qui fait payer le moins lors d'un merge (tout dépend de où se place le top de la stack au moment du merge)
Si tout en haut le cout sera de N (element dans le chunk) sinon 0.
Cette opti coute 2*n mais abaisse le travail des algo et réduit le désordre naturellement.

TROISIEME OPTI: Si le chunk est déjà triée alors on return (la branche récursive ou la fonction si triée à 100% de base)

QUATRIEME OPTI: Backtracking et récursion.
On appel récursivement la fonction en splittant à chaque appel si il n'y a aucun algo qui peut régler le problème
avec un cout inferieur à n log n.(ou moins à tester).

CINQUIEME OPTI: implémentation d'un turk algo amélioré qui sera déclanché uniquement si il ne coute pas cher
(en sachant qu'il annule cout du merge car insère juste au bon endroit)

5.1) utiliser la fonction qui calcul le chemin le plus cour vers le prochain petit nombre. (haut ou bas).
Utiliser la fonction qui repère les groupes de valeurs contigües (croissant ou décroissante) et commencer 
par insérer les groupes ce qui fera payer moins cher les prochains déplacement !

SIXIEME OPTI: RADIX si le chaos et supérieur à 50% et qu'il n'y a pas de groupe de valeurs contigüe
ou plus simplement: use radix if turk + cher que radix à ce moment là (local)

6.1) on renormalise temporairement le chunk, exemple: 12..24 se voit soustraire le min_val a toutes ses valeurs
devenant donc une liste 0.12, ce qui économise en moyenne 1 bit a checker * n élements.

6.2) si la bit analysé en cours sur chaque élement du chunk donne 0,1,0,1,0,1,1,1 (pour n = 8)
Alors la taille a analyser tombe à 5 car les 3 uns consécutif peuvent rester sur place.
Néanmoins il faut que cela colle avec la règle B hold les 1 et A les 0 (INVARIANT)

6.3) biensur si par chance la liste devient triée avant la fin du check de toutes les rangés alors on stop le radix


LET'S GOOOOO BUDDDYYYYY !!!

visualisation: pour  1,4,3,0,2 le turk prend 18 coups et le merge éparnié était gratuit donc moins d'opti sur ce point
avec le radix meme opti:
SI CHUNK DANS B alors on inverse pour que le push a soit dans l'ordre croissant !
B hold toujours les 1 et A les 0 car sinon la réinsertion est trop couteuse (rrb, pa * n element !) contre juste un pa (on /2 les couts)
f(0) f(1) f2   f3   
001  001  011  011   
100  011  010  010
011  100  001  001
000  000  100  000
010  010  000  100

          
010  000  001
000  100  010
100  001  011

5(rb,pa,rb,pa,pa) + 3(pb) + 6(rrb,rrb,pa,rb,pa,pa) + 3(pb) + 6(pa, 5(rrb)) + pb + 5(pa) = 29 coups !!
LE COUT EN REINSERSION EST IMMENSE ! l'opti de réduire la size fait perdre le même nombre de cout au retour et complexifie l'algo



