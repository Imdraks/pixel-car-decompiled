# Versions 0.19.0 / 0.19.1 : moteurs, pneus et commandes PC

Les dix fiches calibrées sont déclarées dans `vehicle-variants.json`. Les noms,
identifiants de voiture et recettes visuelles restent stables.

## Moteurs d'origine et sauvegardes

- Aventador 086 : famille V12 6.5L, calibration Aventador S existante de 730 HP.
- Huracán 188 : famille V10 5.2L, calibration EVO existante de 631 HP.
- Ford GT 2017 : V6 3.5L 646 HP du tableau Unbound conservé.
- BMW M5 2010, Lexus LFA, Civic Type R 2017 et Charger Hellcat : moteurs physiques
  existants associés aux modèles confirmés, y compris leurs variantes Underground
  lorsqu'elles portent cette identification. Les M5 non identifiées précisément
  ne sont pas transformées en M5 E60.

Les packs simulés V10/V12 déjà présents sont réellement utilisés par les nouvelles
Lamborghini d'origine. Aucun nouvel enregistrement audio spécifique n'est annoncé.
La fiche des deux Lamborghini identifie la famille, pas le millésime ou la finition :
les calibrations S/EVO sont des références jouables, pas une certification du dessin.

Les voitures encore entièrement d'origine passent à la nouvelle affectation. Les
préparations existantes conservent leurs pièces, sons choisis, jantes, transmission
et réglages. Même les anciens moteurs de secours gardent leurs anciennes valeurs
et leur ancien son lorsqu'ils étaient installés sur une préparation. Les sauvegardes
de voiture sont écrites avec leur sauvegarde de sécurité habituelle.

Les Lamborghini et la Ford GT ont un empattement, une répartition statique et une
masse de roulage distincts. L'empattement et la répartition Lamborghini sont issus
des fiches constructeur ; les masses en roulage (1700/1540/1520 kg) et les surfaces
aérodynamiques sont des estimations natives explicites. Le poids d'un changement
moteur est calculé relativement au moteur d'origine du modèle, sans compter son
poids deux fois. Les boîtes restent celles du système natif réglable.

Références consultées :
- https://www.lamborghini.com/en-en/history/aventador-s
- https://www.lamborghini.com/en-en/models/huracan/huracan-evo
- https://media.ford.com/content/fordmedia/fna/us/en/news/2017/01/25/all-new-ford-gt-top-speed.html

Le constructeur exprime les puissances Lamborghini en CV ; les valeurs du jeu
emploient les HP mécaniques. Les références de masses sèches ne sont pas prises
pour des mesures exactes de masse en roulage. Les autres voitures conservent les
statistiques récupérées ou les ponts de modèles du tableau Unbound, avec leurs
limites d'identification affichées.

## Conduite et drag

Chaque essieu possède une température de pneus, initialement à 25 °C. L'énergie
perdue au contact pendant le patinage et le blocage chauffe les pneus ; l'air et la
vitesse les refroidissent. La zone optimale améliore légèrement l'adhérence et la
surchauffe la dégrade. Le neutre et le frein à main qui débraye n'ajoutent aucune
chaleur de burnout. L'adhérence thermique agit sur la motricité, les freins par
roue/essieu et la capacité de changement de voie. Températures visibles en conduite.

La capacité thermique, le refroidissement et la courbe d'adhérence sont des
calibrations natives, pas une formule importée du jeu Android ni un modèle validé
sur piste. Le transfert de masse, les ressorts/amortisseurs, les barres anti-wheelie,
l'ABS et le TC existants sont conservés et retestés. Le curseur Wheelie/Balanced
reste l'unique réglage d'autorisation du cabrage.

## Commandes PC

Paramètres → COMMANDES : treize actions réassignables à la souris. Les doublons
échangent leurs touches ; Annuler conserve l'ancienne configuration ; Enregistrer
écrit les réglages. Échap, Entrée et les touches de fonction restent disponibles
pour la navigation et le secours. Les aides en conduite suivent les touches choisies.

Manette standard reconnue par Raylib : RT accélération et LT frein progressifs,
A frein à main, X neutre maintenu, Y NOS, LB/RB rapports, croix/stick gauche voies,
clic stick gauche launch control, clic stick droit klaxon, Start moteur au garage,
Select boîte auto/manuelle. Dans les menus : croix directionnelle, A valider,
B retour, stick droit pour déplacer un pointeur et A pour cliquer/glisser. Zone
morte réglable et possibilité de désactiver la manette. La disposition manette est
fixe ; seule l'affectation clavier est personnalisable dans cette version.

La manette physique n'est pas accessible dans l'environnement cloud : les forces
progressives sont testées dans le modèle, les entrées clavier/souris sont testées
sur l'application réelle ; les pilotes et dispositions de chaque manette restent
à vérifier sur le PC du joueur. Le premier contrôleur reconnu est utilisé.

## Finitions et revue du contenu

Les anciens masques de phares majoritairement hors de la silhouette assemblée sont
écartés lorsqu'ils sont hérités à l'identique d'Original ; les masques propres aux
mods et la peinture blanche restent conservés. Les règles de couches des pots
latéraux et arrière, ainsi que les trois sorties de capot, sont retestées.

L'audit de rendu couvre les 431 modèles enregistrés, les trois banques, les
conversions nommées et tous leurs kits disponibles. Il produit `model-fit.csv`,
`model-fit.json` et dix-huit planches d'accessoires. Les contrôles automatiques
vérifient 5588 compositions, 284988 placements d'échappement et 316785 compatibilités
cosmétiques. Cela détecte les rendus vides et les géométries invalides ; cela ne
certifie pas visuellement chaque accessoire de chaque combinaison. Les voitures
encore incertaines restent à identifier, sans leur inventer un nom.

La comparaison avant équipement affiche désormais puissance, poids, adhérence et
variation du temps de passage des rapports. Elle reste limitée à la catégorie
ouverte dans l'arborescence de customisation.

## Correctif 0.19.1 : phare DRAG PRO universel

Les trois sprites `HeadlightsDrag` contiennent **une seule image**, commune aux
carrosseries. Le rendu doit choisir l'image zéro, pas l'indice de la carrosserie.
La revue supplémentaire de la 0.19.0 a détecté 73 différences de nombre de pixels
entre Linux et Windows sur les kits DRAG PRO Underground : l'ancien accès lisait
hors du tableau. La 0.19.1 corrige cet accès et l'audit enregistre désormais une
empreinte RGBA sur chacune des 5588 compositions pour contrôler leur identité.
Les images d'origine ne sont pas retouchées.
