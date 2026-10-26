# Physique native et pièces 0.4

Le mode libre dispose désormais du catalogue demandé. La fidélité physique au
jeu Android reste à valider ; les mesures natives servent à éviter les régressions.

## État de la base

Le calcul avance à 120 pas fixes par seconde, indépendamment des FPS de rendu.
Le modèle longitudinal utilise une courbe de couple provisoire, six rapports,
un pont final, une masse et un rayon de roue. La traction, la propulsion et les
quatre roues motrices utilisent des limites de traction différentes. Le transfert
de poids dépend de la hauteur du centre de gravité et de l’empattement.
Les efforts prennent en compte
une limite d'adhérence, la traînée aérodynamique, le roulement et le frein moteur.
Le frein moteur et le frein de service partagent la limite d’adhérence ;
le freinage ne fait pas reculer la voiture.

La boîte automatique monte les rapports en charge et rétrograde à faible régime,
avec des seuils différents pour éviter les oscillations. Les changements coupent
la traction pendant 150 ms. Un rétrogradage manuel dépassant le régime maximal
est refusé. Le frein a priorité sur l'accélérateur. Le limiteur coupe la traction.
À bas régime, l'embrayage est représenté par un patinage simplifié ; il n'y a pas
encore de simulation séparée de l'inertie moteur ou du glissement des pneus.

Les constantes de `src/model.hpp` sont regroupées dans `Vehicle`, en unités SI
sauf les régimes en tr/min. Elles sont provisoires : aucune équivalence avec la
physique d'origine n'est annoncée. L'adhérence reste un plafond d'effort ;
le transfert de masse est calculé de façon quasi statique selon l’essieu moteur.
Les paramètres réels par voiture et les équations originales des pièces restent
à reconstruire. Les changements de voie et contacts restent des approximations.

## Vérification reproductible

`bash native/game/build.sh` exécute les contrôles du cœur et construit les deux
exécutables natifs. Le test écrit `build/test-data/physics-baseline.csv` : temps,
vitesse, régime, rapport et distance, à intervalles de 0,1 s pendant 30 s.
Le rapport affiche aussi le 0–100 km/h, le 100–0 km/h et le 402 m du modèle.
Ces valeurs servent à détecter les régressions ; ce ne sont pas des mesures du
jeu Android. Les bornes larges des tests sont des contrôles de cohérence.

Les tests couvrent les FPS 30/60/120/144/165/240, le freinage, la reprise depuis
un rapport trop élevé, le retour en première après arrêt, la protection au
rétrogradage, la coupure de couple pendant le passage, le frein moteur selon le
rapport, la priorité au frein, l'effet de la masse, la limite d'adhérence, le
limiteur manuel et l'absence d'oscillation des rapports en décélération.

## Suite pour valider la fidélité

1. Choisir une seule voiture de référence et figer moteur, pneus, boîte et
   réglages. Conserver séparément les observations d'Unbound et celles de la
   version originale 1.2.5 : les générations GameMaker et bases diffèrent.
2. Identifier les variables et constantes du calcul moteur et de la boîte dans
   les événements natifs du véhicule. Les preuves existantes sont dans
   `../evidence/unbound/` ; le pseudo-C partiel de `car_variables.c` ne permet pas
   encore de reconstituer une voiture complète. `ob_car_Step_0` reste à analyser.
3. Comparer des séquences identiques : départ arrêté, 0–100, 402 m, reprise,
   lever de pied, 100–0, régime avant/après chaque rapport et vitesse maximale.
   Pour chaque référence, conserver provenance, réglages et précision de mesure.
4. Ajuster le modèle à ces références et fixer des tolérances explicites selon
   leur précision. Vérifier ensuite le même comportement dans l'EXE Windows,
   sans dépendance aux FPS. La version 0.3 doit également passer la validation Windows
   du cœur, du rendu et du banc de mesure avant sa publication.
5. Comparer les configurations équipées aux mêmes pièces dans Unbound avant de
   déclarer leur comportement fidèle.

## Avancée de recherche de la version 0.3

Les identifiants de 2 128 variables YYC sont vérifiés, dont ceux de régime,
couple, rapports, poids et adhérence. Les résultats et les limites des trois
passes Ghidra sont dans `../evidence/unbound/physics/README.md` (depuis le dépôt,
`native/evidence/unbound/physics/README.md`). L’équation principale n’a pas été
récupérée : le modèle natif n’est donc pas déclaré équivalent au jeu original.

Le nouveau banc intégré `--physics-benchmark-dir DOSSIER_NEUF` écrit cinq
séquences et un rapport JSON sans lancer le rendu ou l’audio. La CI Windows
compare chaque mesure à `native-physics-baseline.json`, avec une tolérance de
0,01 dans l’unité de chaque mesure. C’est une comparaison entre compilations
natives, indépendante de la future comparaison au jeu d’origine.

La validation de publication Windows 0.3 est réussie :
[exécution 40315185715](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40315185715).
Les huit mesures concordent avec Linux ; 43 contrôles du cœur et 15 contrôles
graphiques passent. Cette preuve n’établit pas la fidélité au jeu Android.

## Adaptation provisoire des pièces 0.4

Les données source comprennent puissance, poids relatif, prix et variante.
Le champ générique `hp` est interprété selon la catégorie : puissance moteur et
pièces atmosphériques, régime ECU, pression de suralimentation et indice de pneu.
Ces interprétations et les formules ne prouvent pas l'équivalence à Android.
La puissance moteur normalise une courbe de couple native ; la masse part de
1240 kg et applique les écarts de poids source avec un facteur 0,45359237.
L'unité d'origine du poids n'est pas prouvée. L'adhérence des pneus vaut
0,8 + 0,002 × indice ; le rayon suit leur image. Suspension : hauteur et centre
de gravité sont calibrés nativement. Le turbo possède un temps de montée ; le
compresseur suit davantage le régime et applique une perte de 6 %. Le facteur
de couple de suralimentation utilise 1 + pression/14,7 × 0,7.

NOS ajoute sa puissance source avec une réserve native de 10 secondes par
nouvelle session ; il nécessite accélération et vitesse > 2 m/s. Le frein prime.
Les ECU explicitement +2STEP permettent L + accélérateur à l'arrêt : embrayage
ouvert, régime 4200 tr/min et montée en pression ; relâcher L transmet le couple.
Il s'agit de comportements reconstruits, sans calibration Android démontrée.
Les huit mesures du véhicule de base restent identiques à la référence 0.3.
