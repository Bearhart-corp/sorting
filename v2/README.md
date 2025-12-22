Parce que oui il faut le faire ^^

bug a corriger : le bubble qui est super mal fait au niveau accès mémoire
les push (a et b) qui tiennent pas a jour la tete de lecture
le move3algo qui ne gère que des données en hard coding (tu as 3 valeurs donc 1 max 1 min et 1 middle) un simple cas de soustraction fonctionne
car les valeurs sont contigües.

prochaine étape après le débugg, le radix en 4 chunk 00,01,10,11 ce qui donne 2log( x < 512) = x < 9 donc max 8 rangées de bits
divisé par 2 = (4 * n) opération et possibilité de rrr, rr, ss (double move) mais les double move seront plus aisé avec 2chunks (à comparer)
le problème reste toujours le cout d'accès mémoire.
On pourrait aussi faire en 3 chunks, sur A on laisse les elem lourds et la moitié legère dans B, on garde en mémoire le top du chunk dans B puis on radix A
une fois A trié on radix B et on se sert du dessus de A pour trier B puis une fois triée on push sur A dans le bon sens

Elliot tu vas reprendre les fonctions de base et les optimiser pour te les approprier et car sinon tu seras perdu sur la suite.
Moi j'avance sur la suite en testant toutes les idées qui pourrait me passer par la tête
Dans un second temps je te propose de faire le checker et puis une fois nos tâches respectives terminées on échange et on optimise le code l'autre
(biensur on se faire un cour sur notre code avant) cela va nous aider a comprendre ce que l'on fait fondamentalement, améliorer
notre capacité à expliquer notre code, et ça mixera nos idées, donc le meilleur en ressortira !

LET'S GOOOOO BUDDDYYYYY !!!
