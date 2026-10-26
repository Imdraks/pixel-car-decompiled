# Priorité : valider la conduite avant d'ajouter du contenu

Le mode libre sert de banc de conduite natif. Les boutiques, nouvelles pièces,
nouveaux véhicules, progression et autres modes attendent la validation de cette
base. Les images déjà présentes au garage restent des choix visuels avec des
performances communes.

## État de la base

Le calcul avance à 120 pas fixes par seconde, indépendamment des FPS de rendu.
Le modèle longitudinal utilise une courbe de couple provisoire, six rapports,
un pont final, une masse et un rayon de roue. Les efforts prennent en compte
une limite d'adhérence, la traînée aérodynamique, le roulement et le frein moteur.
Le freinage est borné par l'adhérence et ne fait pas reculer la voiture.

La boîte automatique monte les rapports en charge et rétrograde à faible régime,
avec des seuils différents pour éviter les oscillations. Les changements coupent
la traction pendant 150 ms. Un rétrogradage manuel dépassant le régime maximal
est refusé. Le frein a priorité sur l'accélérateur. Le limiteur coupe la traction.
À bas régime, l'embrayage est représenté par un patinage simplifié ; il n'y a pas
encore de simulation séparée de l'inertie moteur ou du glissement des pneus.

Les constantes de `src/model.hpp` sont regroupées dans `Vehicle`, en unités SI
sauf les régimes en tr/min. Elles sont provisoires : aucune équivalence avec la
physique d'origine n'est annoncée. L'adhérence reste un plafond d'effort ; transfert
de masse, type de transmission, suralimentation et pneus détaillés restent à
reconstruire. Les changements de voie et contacts restent des approximations.

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
   sans dépendance aux FPS. La release 0.2 publiée conserve l'ancien modèle ;
   les corrections postérieures exigent une nouvelle compilation et validation.
5. Ajouter les statistiques de plusieurs voitures, puis leurs pièces et autres
   contenus une fois cette comparaison acceptée. Le nombre de sprites disponibles
   ne prouve pas que leurs comportements ont été récupérés.
