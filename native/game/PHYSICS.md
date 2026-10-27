## Départ à haut régime et patinage (0.13.3)

Avec le **TC désactivé**, prendre des tours avec **Espace + accélérateur** ou
**V + accélérateur**, puis relâcher Espace/V en gardant les gaz, provoque un
patinage selon le couple moteur, le régime initial, les rapports et l’adhérence.
Les roues motrices tournent indépendamment de la vitesse au sol ; la fumée suit
le glissement et conserve la couleur des pneus. Le TC activé régule le départ.
[Calcul natif et limites](DRAG.md#départ-au-rupteur--0133).

## Moteur libre au frein à main (0.13.3)

Avec Espace maintenu, le moteur est débrayé : l’accélérateur fait monter les tours
comme au point mort, sans couple aux roues ni NOS. Les roues arrière restent
bloquées. Les rapports automatiques sont conservés pendant le maintien ; le
réengagement applique le délai de changement et une protection contre le surrégime.
Le son de charge moteur suit l’accélérateur même avec le frein à main.

La progression du cabrage avec la puissance est vérifiée séparément à châssis,
masse et pneus constants : voir `DRAG.md` et `power-wheelie.csv`. L’adhérence,
les aides et les passages de rapports peuvent limiter la levée à très forte puissance.

## Roues et curseur Wheelie → Balanced (0.13.2)

Les roues suivent leurs axes de suspension attachés à la caisse, avec des
courses mécaniques bornées indépendamment de la raideur des ressorts. Le curseur
bleu limite progressivement le cabrage sans déplacer la masse. Les équations
Android complètes restent à reconstruire. Voir [DRAG.md](DRAG.md).

## Correctif Drag 0.13.1

Le préréglage de lancement est séparé du wheelie, amorti et adapté aux essieux
moteurs. Le code original de motricité/chauffe/RPM a été localisé dans les deux
ELF ; les équations complètes ne sont pas importées. Voir [DRAG.md](DRAG.md)
pour les preuves, limites et six scénarios de lancement.

# Châssis et aides — 0.12.0

Les voitures jouables utilisent désormais un modèle de suspension à deux essieux :
ressorts préchargés, amortisseurs, déplacement vertical et tangage. Les charges
aux essieux influencent les efforts aux pneus et la perte de contact en wheelie.
Les réglages du garage et les aides ABS/TC sont décrits dans
[SUSPENSION.md](SUSPENSION.md), avec les calibrations et les limites.

Le banc générique historique ci-dessous reste une référence de régression.
Il ne valide pas ces nouveaux comportements : `suspension-aids.json` et
`suspension-physics.csv` ajoutent les scénarios de suspension, de wheelie et d’aides.

# Burnout et point mort — 0.11.0

- En première, frein de service + accélérateur active le burnout sous 3 m/s.
  Le frein maintient l’arrêt ; la distance de rotation des roues est indépendante
  de celle du décor. Seul l’essieu moteur tourne (les deux en transmission intégrale).
- Relâcher une des deux commandes termine le burnout. Le frein à main est
  prioritaire. Hors de ces conditions, frein + accélérateur continue de freiner.
- V maintenu désaccouple le moteur. L’accélérateur augmente le régime sans force
  motrice ni frein moteur. Freinage, inertie et résistance au roulement restent actifs.
  Les changements automatiques/manuels sont suspendus pendant le maintien.
- Au relâchement, le rapport conservé est réengagé avec le délai d’embrayage ;
  un rapport supérieur évite un surrégime si la vitesse l’exige.
- Le NOS ne se consomme pas en burnout ou au point mort. Les sons moteur suivent
  l’accélérateur et le régime dans ces deux modes.
- Les Burn Slicks 9..16 définissent les huit teintes de fumée. Les particules
  gardent leur teinte d’émission ; les autres pneus émettent une fumée blanche.

Ces comportements, régimes de maintien et teintes RGB sont des adaptations natives.
Ils ne constituent pas une récupération des équations Android de chauffe des pneus,
d’usure ou d’adhérence thermique. Les sorties de particules suivent les ancrages
existants des roues. Aucun bonus de grip permanent n’est ajouté par un burnout.

# Physique par voiture — 0.10.0

Les 191 carrosseries utilisent désormais leurs fiches mécaniques d’origine,
récupérées dans `ob_car_Step_0` des deux bibliothèques Android. Chaque branche
est liée à son intervalle d’identifiant de voiture ; les 382 bornes sont
vérifiées. Les 1337 valeurs de chaque banque sont identiques : poids, HP,
adhérence brute, vitesse catalogue, régime, cylindrée brute et transmission.
Les adresses des écritures, empreintes et valeurs sont dans
`../evidence/merged/stock-vehicles.json`. Reproduction :
`python native/tools/recover_vehicle_data.py`.

## Ce qui influence réellement la conduite

- Masse propre à la carrosserie, convertie de lb en kg. Le plancher à 600 kg
  est retiré : la petite voiture de 1150 lb conserve ses 521,6 kg.
- Puissance d’origine calibrée sur le pic de la courbe native, puis moteur
  remplacé et pièces ajoutées. Changer de carrosserie ne ramène plus tous les
  moteurs d’origine à la même puissance de référence.
- Limiteur propre à la voiture ; ECU, changements de rapports et courbe native
  se basent sur ce régime. Les 16 moteurs de remplacement utilisent aussi leurs
  régimes et cylindrées source (15 familles mécaniques, deux Hemi partageant
  la même fiche), vérifiés indépendamment dans les deux banques.
- Adhérence relative du châssis conservée avec les pneus équipés. Le coefficient
  SI utilise encore la calibration native `1.08 × grip_source / 1200`.
- Transmission d’origine : 33 tractions, 126 propulsions, 32 intégrales. Une
  conversion choisie manuellement reste prioritaire ; le bouton TRANSMISSION
  D’ORIGINE rétablit le suivi automatique de la carrosserie.
- Sauvegardes version 3. Les anciennes préférences de transmission sont
  conservées ; un nouveau profil démarre avec la transmission d’origine.

La vitesse catalogue et la cylindrée figurent dans la fiche ; elles ne servent
pas de plafond artificiel de vitesse ou de multiplicateur de puissance.
La vitesse réelle résulte toujours des rapports, du couple, de la masse et des
résistances. Les variantes visuelles du mod gardent leur fiche mécanique source :
un changement d’image ne suffit pas à attribuer les caractéristiques d’un autre
modèle réel.

## Limites de fidélité

Les **paramètres de stock** sont récupérés. Les **équations complètes Android**
ne le sont pas. Courbe de couple, coefficient d’adhérence, géométrie SI,
aérodynamique, inertie et pneus restent des adaptations natives. Les données du
jeu peuvent aussi différer des fiches constructeur ; elles ne sont pas présentées
comme une simulation homologuée des vraies voitures. Les identités visuelles
et leurs degrés de certitude sont documentés séparément.

Le banc historique ci-dessous conserve sa voiture de référence générique pour
les comparaisons entre plateformes ; il ne représente pas toutes les voitures.
Le nouveau `stock-vehicle-physics.csv` contrôle les 191 configurations en
accélération et au freinage et `stock-vehicle-physics.json` en conserve la
couverture. Quatre cadences de rendu sont aussi comparées pour une voiture source.

## Historique de la reconstruction

# Physique native et pièces 0.7

Le mode libre dispose désormais du catalogue demandé. La fidélité physique au
jeu Android reste à valider ; les mesures natives servent à éviter les régressions.

## État de la base

Le calcul avance à 120 pas fixes par seconde, indépendamment des FPS de rendu.
Le modèle longitudinal utilise une courbe de couple provisoire, quatre à dix rapports configurables (six par défaut),
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

## Adaptation provisoire des pièces

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
de couple de suralimentation utilise désormais 1 + pression/14,7 × rendement.
En 0.5, le rendement dépend de l’intercooler et la courbe ECU est étendue ;
voir [PERFORMANCE.md](PERFORMANCE.md) pour les équations et leur provenance native.

NOS ajoute sa puissance source avec une réserve native de 10 secondes par
nouvelle session ; il nécessite accélération et vitesse > 2 m/s. Le frein prime.
Les ECU explicitement +2STEP permettent L + accélérateur à l'arrêt : embrayage
ouvert, régime 4200 tr/min et montée en pression ; relâcher L transmet le couple.
Il s'agit de comportements reconstruits, sans calibration Android démontrée.
Les huit mesures du véhicule de base restent identiques à la référence 0.3.

## Affichage de la vitesse 0.4.1

`src/road_scene.hpp` définit l'échelle commune de 48 pixels par mètre, adaptée
à l'empattement visible d'environ 125 pixels pour 2,6 mètres. Ce choix règle
l'affichage, sans changer les unités SI de la simulation ni ses performances.
À 100 km/h, le sol parcourt 1333,33 pixels logiques par seconde ; à 200 km/h,
2666,67 pixels. Les tirets mesurent 4 mètres et se répètent tous les 12 mètres.
Les montagnes, la ville et les arbres suivent respectivement 3,5 %, 16 % et
55 % du déplacement du sol. Toutes les qualités conservent la même échelle.
La circulation est projetée à partir de sa distance relative réelle ; les
particules déjà émises suivent la variation exacte de position de la caméra.
La rotation des roues dépend de distance / rayon, sans horloge de rendu.

Les captures contrôlées du smoke test montrent le déplacement sur 0,1 seconde
à 100 et 200 km/h et l'immobilité du rendu à l'arrêt et en pause à vitesse non
nulle. `tests/check_motion_captures.py` mesure le déplacement des pixels du
marquage, avec une tolérance d'un pixel de rastérisation par mesure. Les tests
du cœur vérifient aussi l'indépendance des FPS et l'alignement route/circulation.

## Transmission et points d'émission 0.6

Les rapports de boîte, pont final et temps de passage viennent désormais du
profil. Le modèle de base à six rapports est conservé. Les préréglages réels
et les éléments calibrés nativement sont décrits dans TRANSMISSION.md.
Les flammes/NOS suivent les bouches des pots ; ils ne sont plus advectés comme
des particules au sol. Le traitement des fumées et étincelles est conservé.

## Frein à main arrière 0.7

Espace actionne un frein distinct du frein de service. La force est limitée à
l'adhérence arrière, avec une réduction quasi statique du poids arrière au
freinage : `masse × g × grip × fraction_arrière / (1 + grip × hauteur_CG / empattement)`.
Le frein de service reste prioritaire si les deux sont pressés. Le frein à main
coupe la traction et le NOS sans consommer sa réserve ; il ne fait pas reculer.
Une distance de roulement arrière séparée bloque sa rotation visuelle pendant
le verrouillage, puis la reprend au relâchement. La fumée est localisée à l'essieu
arrière, y compris en traction. Les voies restent un déplacement latéral simplifié,
sans nouvelle simulation de dérive. Sans frein à main, les mesures de référence
restent inchangées.
