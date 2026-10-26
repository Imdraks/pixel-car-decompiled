# Puissance et rareté natives 0.8

Le garage affiche la puissance maximale **avec la suralimentation**, séparément
sans et avec NOS. Le banc trace les courbes atmosphérique, boost et boost + NOS.
Le calcul du banc et celui de la conduite partagent les mêmes fonctions de couple,
pression et puissance. Les valeurs sont des HP moteur estimés, avant pertes de
transmission, limite d'adhérence et traînée ; ce ne sont pas des HP aux roues.

## Combinaison des pièces

1. La puissance du moteur choisi conserve la valeur du catalogue fusionné Original/Unbound.
2. Admission, pistons et échappement ajoutent leurs gains source au moteur.
3. L'ECU étend le régime et la courbe de couple avec le facteur
   `(8100 + supplément ECU) / 8100`, sans renormaliser pour effacer le gain.
4. Un **turbo OU un compresseur**, jamais les deux, multiplie le couple par
   `1 + pression / 14,7 × rendement`. Le turbo doit monter en pression en conduite.
   Le compresseur suit le régime et conserve une perte d'entraînement de 6 %.
5. L'intercooler améliore le rendement de suralimentation :
   `0,65 + 0,35 × indice / 107`. Sans suralimentation il n'ajoute pas de puissance.
6. Le NOS ajoute sa puissance source après la suralimentation, seulement lorsqu'il
   est activé avec une réserve disponible. Il ne contourne plus le limiteur.

Le banc échantillonne la même courbe que la conduite, à 10 tr/min d'intervalle.
Le HUD indique la puissance moteur au régime et à la pression courants, avec les
coupures de passage de rapport, de freinage, de 2STEP et de limiteur.
Suspension et pneus améliorent hauteur, masse ou adhérence, sans chevaux fictifs.

Exemple **PRÉPA MAX** : LT5 755 HP, admission +38, pistons +100, échappement +95,
ECU +2300 tr/min, turbo 35 psi, intercooler 107 et NOS 250.
La somme atmosphérique avant ECU vaut 988 HP. Le facteur de régime est
10400/8100 et le facteur de pression à plein boost vaut 1 + 35/14,7.
Résultat : environ **4289 HP sans NOS**, **4539 HP avec NOS**.
Les gains à bas régime restent différents des valeurs maximales du banc.

## Classement

**Commun → Peu commun → Rare → Épique → Légendaire → Contrebande**.
Le tri peut être inversé. Chaque ligne et fiche porte sa rareté et sa couleur.
La rareté n'ajoute aucun multiplicateur caché : elle décrit les performances.
Le maximum de chaque catégorie est Contrebande ; les autres niveaux suivent
la position entre le minimum et le maximum, répartie en cinq intervalles égaux.
Les variantes à performances identiques gardent la même rareté, même si leur
prix ou couleur diffère. La suspension est classée selon l'allègement et la
hauteur native ; les pneus selon l'adhérence ; l'ECU selon l'extension de régime.
Le meilleur intercooler n'apporte son bénéfice qu'avec une suralimentation.

PRÉPA MAX choisit le maximum par catégorie, puis les variantes les plus légères
à performance égale ; les égalités restantes utilisent l'identifiant stable.
Le meilleur turbo et le meilleur compresseur sont comparés au banc et un seul
est conservé. Apparence, transmission et préférences audio sont préservées.
Les pièces sont toujours librement équipables, sans achats simulés.

## Provenance et limites

Les noms et statistiques brutes viennent de la récupération statique Unbound.
**Les formules d'association, rendement, courbe ECU et raretés sont des règles
natives de cette reconstruction**, pas une récupération démontrée du jeu Android.
Le poids source reste d'unité inconnue ; sa conversion est une calibration native.
Le plafond d'adhérence et la boîte peuvent limiter l'accélération malgré une
puissance moteur très élevée. Les données complètes par carrosserie restent à
récupérer. Les prix et couleurs ne prouvent pas une meilleure performance.

Les contrôles couvrent 50 400 combinaisons moteur/ECU/suralimentation/intercooler
et 137 984 combinaisons moteur/admission/pistons/échappement, ainsi que chacune
des 194 substitutions de la préparation maximale, les raretés, l'exclusivité,
la conduite au pic et le limiteur avec NOS. Ce découpage teste les interactions ;
il ne prétend pas énumérer le produit cartésien complet de toutes les pièces.

La version 0.8 ajoute les turbos Diamond et Ruby du jeu original (35 psi) :
196 pièces de performance, 54432 combinaisons moteur/ECU/induction/intercooler
et 137984 combinaisons atmosphériques, soit 192416 contrôles. Les équipements
esthétiques et les jantes ne créent aucun cheval supplémentaire.
