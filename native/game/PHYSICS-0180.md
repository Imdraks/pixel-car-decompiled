# Conduite et physique — 0.18.0

**Wheelie → Balanced est désormais le seul réglage de cabrage** : le bouton d’activation est supprimé. Le curseur autorise et limite la levée selon sa position, sans forcer une voiture insuffisamment puissante à se cabrer. Les anciens fichiers restent lisibles.

Cette étape améliore les interactions entre moteur, roues, freinage et changements de voie. Les voitures, préparations et réglages existants sont conservés.

## Patinage pendant l’accélération

Auparavant, hors départ au rupteur, le régime suivait la vitesse au sol alors que les roues et la fumée montraient un patinage calculé depuis le couple demandé. Désormais, si le couple dépasse l’adhérence avec le TC désactivé, les roues motrices et l’inertie moteur réfléchie dans la transmission évoluent séparément de la vitesse de la voiture, y compris en deuxième, troisième ou rapport supérieur.

L’excès de couple accélère ces roues ; la force transmise à la route dépend du glissement et de la charge de l’essieu. Le solveur utilise de petits sous-pas pour la pente du pneu à basse vitesse. Le régime, la rotation visible et le son moteur suivent ce mouvement. Le rupteur coupe effectivement le couple, et le NOS ne contourne pas cette coupure. Un burnout relâché utilise le même transfert de rotation qu’un départ après maintien de V ou Espace.

Le TC coupe rapidement le couple qui dépasse l’adhérence et le réapplique progressivement. Avec beaucoup de puissance, le désactiver peut donc ralentir un départ : davantage de chevaux ne donne pas automatiquement davantage d’accélération. La courbe d’adhérence et les inerties restent des calibrations natives.

## Freinage par essieu

Le frein de service distribue sa demande à **68 % à l’avant et 32 % à l’arrière**, auxquels s’ajoute le frein moteur sur l’essieu moteur. Chaque essieu est limité par sa charge verticale réelle et l’adhérence restante. Un essieu peut donc se bloquer alors que l’autre continue à rouler ; l’ABS régule seulement l’essieu qui dépasse sa capacité. Des roues avant en l’air ne produisent plus de force de freinage avant.

Le frein à main reste prioritaire sur les roues arrière même si le frein de service et l’ABS sont actifs. Ce biais hydraulique est un réglage natif commun, pas une donnée constructeur importée pour chacune des voitures.

## Changements de voie

Les flèches gauche/droite demandent une voie, mais la voiture y arrive par une vitesse latérale progressive, avec une accélération limitée par les pneus. Le déplacement est plus lent à basse vitesse et impossible à l’arrêt. Une inversion de direction freine d’abord le mouvement latéral existant. Une roue avant délestée réduit la direction ; un wheelie sans contact avant ne permet plus de changer immédiatement de voie.

Accélérer et freiner consomment la même réserve d’adhérence que tourner : la capacité longitudinale diminue selon un cercle de friction. Une résistance longitudinale représente le coût énergétique du mouvement latéral, avec une régularisation à basse vitesse. Les trois voies restent un guidage de jeu, avec limites de route, et non une simulation libre en 3D du braquage ou du drift.

## Vérification et essai

Les contrôles couvrent le patinage en troisième, l’inertie, le TC, la sortie de burnout, le blocage indépendant des essieux, l’ABS, le frein à main, la perte de direction en wheelie, l’adhérence en virage, les 430 identifiants de véhicules et la stabilité à 30/60/144 FPS avec le pas physique fixe de 120 Hz.

Pour comparer : choisir une préparation puissante, couper le TC, accélérer puis passer en deuxième avec E ; observer le régime et le patinage. Refaire avec le TC actif dans Paramètres. À vitesse de route, demander une voie en accélérant puis en roue libre. À l’arrêt, V + Z fait monter le régime ; relâcher V transmet la rotation à la transmission.

Les fichiers `driving-physics.csv` et `driving-physics.json` des preuves de validation donnent les mesures. Les équations Android complètes, les géométries de trains réelles et les collisions de carrosserie ne sont pas importées par cette étape.

## Fonds de menus

Les décors du garage, de la customisation, du showroom et des réglages couvrent la fenêtre entière, y compris après un redimensionnement en 4:3 ou en écran large. Leur cadrage est centré et leur proportion conservée ; l’interface garde ses repères et ses commandes à la souris. Le décor est raccordé au même cadrage dans la zone de l’interface et dans les marges.
