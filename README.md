# Pixel Car Racer — reconstruction native Windows

**[Télécharger Windows x64 — version 0.17.0](https://github.com/Imdraks/pixel-car-decompiled/releases/download/v0.17.0-native-preview/PixelCarRacerNative-Windows-x64.zip)** · [Release et preuves Windows](https://github.com/Imdraks/pixel-car-decompiled/releases/tag/v0.17.0-native-preview)

Extraire toute l’archive, garder `assets` à côté de **PixelCarRacerNative.exe**,
puis lancer cet exécutable et choisir **MODE LIBRE**. Windows 10/11 x64 avec un
pilote OpenGL 3.3. Le jeu fonctionne hors ligne, sans Android ni émulateur.

## Disponible

La **0.17.0** réunit **Original, Unbound et Underground** : 430 variantes de
voitures, 1 826 choix d’équipement, décors et banque audio Underground. Les
anciens éléments NFS sont étiquetés Unbound ; le garage conserve huit places et
les variantes de pièces gardent un équilibre commun. Validation Windows réussie :
409 contrôles du cœur, 126 graphiques et 134 contrôles clavier/souris sous Linux. [Contenu et limites](native/game/UNDERGROUND.md).

La version **0.16.5** corrige le pot arrière qui recouvrait la roue : dessin
derrière les roues et la carrosserie, avec ancrages et sorties des particules
conservés. Correctif commun aux aperçus, miniatures et conduite, vérifié en
hauteur normale, abaissée, rehaussée et cabrage. [Détails](native/game/EXHAUST.md).

La version **0.16.4** ouvre d’abord l’accueil **Style / Performance / Acheter et
vendre / Toutes mes voitures**, puis les sous-menus. Style → Carrosserie →
Kits / Éléments / Posture, peintures, effets, accessoires, sons et familles
mécaniques rejoignent les fonctions natives. Entrée ouvre un niveau ; Échap
retrouve le parent. Voitures, préparations et huit places conservées.
[Arborescence, commandes et correspondances](native/game/RIDES-NAVIGATION.md).

La version **0.16.3** applique la présentation inspirée des références au
**showroom et à la customisation** : grande voiture, fiche à droite, catégories
et carrousels en bas. Recherche, tris du showroom, classes/provenance des pièces,
comparaison avant équipement, moteurs/roues/style et commandes de réglage restent
accessibles. Garage de huit voitures et sauvegardes conservés.
[Présentation et commandes](native/game/CINEMATIC-UI.md).

La version **0.16.2** affiche la **voiture en grand à gauche** et les **menus à
droite** dans le showroom et le garage : modèles, recherche, catégories, pages
et actions. La fiche présente la préparation sélectionnée, son moteur, sa
puissance, son poids et sa transmission. La limite de huit voitures et les
sauvegardes restent conservées. [Commandes](native/game/SHOWROOM.md).

La version **0.16.1** ajoute un **showroom** et un **garage limité à huit voitures**.
**B / GARAGE** ouvre les voitures possédées ; **SHOWROOM / Tab** présente tout le
catalogue. Ajoutez librement un modèle, utilisez sa préparation ou retirez-le
pour libérer une place. Les préparations retirées restent archivées. Les
chargements F11 respectent aussi les huit places ; un garage vide reste vide au
redémarrage. [Commandes et migration](native/game/SHOWROOM.md).

La version **0.16.0** sépare les **239 voitures et variantes** : catégories, identifiants stables,
fiche mécanique et préparation automatique indépendante par modèle. **B / CHOISIR
UNE VOITURE** ouvre le catalogue. Les 145 moteurs NFS sont universels. Les anciennes
configurations non modifiées reçoivent leur moteur d’origine, avec sauvegarde
protégée ; les préparations existantes restent conservées.
[Voitures, migration et limites](native/game/VEHICLES-GARAGE.md).

La version **0.15.0** importe le tableau fourni : **145 moteurs**, **113 pièces** et
neuf extensions Contrebande. Classes **Basic → Sport → Pro → Super → Elite →
Contrebande**, 623 associations pour 50 modèles, 20 catégories mécaniques et
cinq nouvelles familles audio simulées (80 WAV + 80 OGG). F1 : rechercher NFS
ou le donneur ; CETTE AUTO filtre les associations du tableau.
[Contenu, accès, sons et limites](native/game/NFS-CATALOGUE.md).

Les sept curseurs de volume incluent la musique, uniquement dans les menus et
le garage. La sauvegarde des configurations de voitures reste disponible.

La version **0.14.2** ajoute **Paramètres → Volumes** : six curseurs pour le
général, le moteur, le turbo/compresseur, les bruitages, l’ambiance et l’interface.
Aperçu immédiat, enregistrement persistant, annulation et retour à 100 %.
Au garage, le moteur allumé reste écoutable avec Z dans cette page.
[Réglages et catégories](native/game/VOLUMES.md).

La version **0.14.1** fait entendre le turbo équipé dans le menu custom :
**G** démarre le moteur avec un léger sifflement au ralenti, **Z** le fait monter
avec le régime et le relâchement déclenche la valve. Les profils des nouveaux
montages sont conservés. L’aperçu sonore du garage n’ajoute pas de pression
à la physique de conduite.

La version **0.14.0** ajoute **18 montages turbo PC** : simples, biturbos
parallèles/séquentiels, hybrides de préparation, assistance électrique et quads.
Pression, débit, réponse selon la cylindrée, classes et profils sonores varient
selon la pièce. F4 → TURBOS, rechercher **PC**. Les pièces sont des calibrations
de jeu inspirées des principes techniques consultés.
[Catalogue, sources et fonctionnement](native/game/TURBOS.md).

La version **0.13.9** active les sons simulés des six moteurs au garage et
sur la route : **LS, AMG, Huracán, Aventador, V6 F1 et Coyote**. Mettre les deux
lignes de son sur **AUTO** pour les entendre ; G démarre/arrête et Z accélère
au garage. Les sons restent des simulations approximatives.

Le bouton **MES VOITURES / F11** permet de nommer, enregistrer et recharger
plusieurs voitures avec leur configuration complète. Une mise à jour conserve
la configuration précédente en sauvegarde.
[Détails audio](native/game/AUDIO-SIMULATION.md) · [Sauvegardes](native/game/SAVED-CARS.md).

La version **0.13.8** ajoute **15 moteurs inspirés de modèles réels** : AMG
GT63 S, Huracán V10, Aventador V12, V6 F1, Ford Coyote et dix autres.
31 swaps disponibles, avec courbes de couple, régimes et inerties propres.
Les ajouts sont marqués **EXTENSION PC** ; sons adaptés des ressources existantes.
Six packs de sons simulés sont aussi fournis : **99 WAV + 99 OGG**.
Ces packs, fournis en 0.13.8, sont activés dans le jeu depuis la 0.13.9.
[Détails des packs et du skill](native/game/AUDIO-SIMULATION.md).
[Détails et limites](native/game/PC-ENGINES.md).

La version **0.13.7** donne au son du LS/V8 une montée plus marquée dans les
tours, avec un ralenti conservé. Le réglage s’applique aussi aux LSX, LT5 et Hemi
qui partagent ce fichier sonore. [Courbe et limites](native/game/AUDIO-MIX.md).

La version **0.13.6** reprend le mixage des moteurs : hauteur moins forcée,
fondu entre charge et relâchement, gains des ressources et raccord des boucles
VR38/FR9. [Calculs et limites](native/game/AUDIO-MIX.md).

La version **0.13.5** permet de démarrer/éteindre le moteur au garage avec **G**
et de le faire monter au rupteur en maintenant **Z**. Le son suit le moteur
équipé ; relâcher Z ramène le ralenti. La saisie de recherche ignore ces touches.

La version **0.13.4** corrige les sons AUTO des **16 moteurs équipables**, en
reprenant les associations vérifiées dans les deux codes source. Les réglages
manuels restent prioritaires. [Tableau et preuves](native/game/ENGINE-AUDIO.md).

La version **0.13.3** permet de prendre des tours avec **Espace + accélérateur**,
comme au point mort, en gardant les roues arrière bloquées. Relâcher Espace
réengage la transmission et permet le départ. Avec le TC désactivé, relâcher
le frein à main ou le point mort à haut régime fait patiner les roues motrices :
le couple et l’inertie déterminent la durée et l’intensité, ainsi que la fumée.
Le son moteur suit le régime.

La version **0.13.2** ajoute la barre bleue **Wheelie → Balanced** et corrige la
liaison des roues à leurs points de suspension pendant le cabrage. Les courses
de compression et de détente sont bornées. **F9** permet de régler le comportement
et de conserver séparément la répartition des masses. [Détails](native/game/DRAG.md).

La version **0.13.1** sépare **Drag** (départ amorti, roues au sol) de **Wheelie**
et adapte la répartition aux roues motrices. Les petites roues arrière du **DRAG PRO**
limitent maintenant le cabrage par leur appui au sol. Appliquer **F9 → Drag → Enregistrer**
pour remplacer l’ancien réglage. Le code de conduite original est localisé, mais
ses équations complètes ne sont pas encore importées. [Correction et preuves](native/game/DRAG.md).

La version **0.13.0** affine les peintures et matériaux, sépare les jantes avant/arrière
et vérifie les accessoires sur les deux banques de carrosseries. Les trois pots
de capot suivent la géométrie du capot et de la pièce avant installée. Les variantes
incompatibles sont signalées. [Personnalisation PC et limites](native/game/CUSTOMIZATION-COMPLETE.md).

La version **0.12.0** ajoute les ressorts et amortisseurs physiques, le réglage
**F9** de hauteur/rigidité/amortissement/répartition et le mode wheelie ou limité
au sol. **ABS et antipatinage** se désactivent séparément dans les paramètres.
Voir [SUSPENSION.md](native/game/SUSPENSION.md).

La version **0.11.0** ajoute le **burnout** : en première, à l’arrêt ou presque,
maintenir accélérateur + frein. Les Burn Slicks équipés colorent la fumée.
**V maintenu** garde le point mort ; relâcher V réengage la transmission.
N reste la touche du NOS et Espace celle du frein à main.

La version **0.10.0** applique les **191 fiches mécaniques par carrosserie**
récupérées dans les deux jeux : masse, puissance, régime, adhérence relative et
transmission d’origine. Les noms et les identifications incertaines sont visibles
au garage. [Fiches des véhicules](native/game/VEHICLES.md).
Les équations complètes Android et les fiches constructeur restent à reconstruire.

La version 0.9.0 fusionne les boutiques Original 1.2.5 + Unbound : **1220 choix d’équipement**,
avec jantes nommées, esthétique et sélection des deux banques d’images/sons.
[Contenu et commandes](native/game/CONTENT.md).

- Garage avec atelier, pont, icônes, jauges et police du jeu original adaptés au PC.
  Six catégories, aperçu, recherche, tri, double-clic et raccourcis F1–F6.
  [Commandes du garage](native/game/GARAGE-PC.md).
- **Espace : frein à main arrière**, roues arrière bloquées et moteur débrayé.
  Maintenir l’accélérateur permet de prendre des tours ; relâcher Espace réengage
  la transmission. Le NOS reste coupé. Z/W/↑ restent les accélérateurs.

- Mode libre continu avec circulation sur trois voies, désactivable dans
  **Paramètres → Trafic en mode libre**. Choix sauvegardé, sans collisions
  cachées lorsque le trafic est retiré.
- Défilement de la route et du décor lié à la distance parcourue, circulation
  à la même échelle et roues animées selon le trajet, figées en pause.
- Transmission à **4–10 rapports**, curseurs +/−, pont final et vitesses théoriques,
  sauvegarde/annulation ; huit préréglages dont sept familles réelles TREMEC/GM.
  Sources et adaptations : [TRANSMISSION.md](native/game/TRANSMISSION.md).
- Pots d’origine visibles et flammes/NOS attachés à leurs sorties, y compris
  capot, latérales, doubles et triples. [EXHAUST.md](native/game/EXHAUST.md).
- Boîte automatique/manuelle, rétrogradages, limiteur et frein moteur.
- Traction, propulsion ou quatre roues motrices sélectionnables au garage,
  avec effet du transfert de poids et choix sauvegardé.
- 239 ensembles visuels dans le même sélecteur (carrosserie, feux et kits), et
  **521 jantes nommées**, composées depuis les recettes du jeu.
  La version 0.9.0 aligne les roues avec chaque carrosserie et conserve les ailes
  devant les pneus ; les 191 rendus ont été parcourus et revus.
- 196 pièces de performance dans 11 catégories : moteurs, suspension, turbos, compresseurs, ECU,
  NOS, admissions, intercoolers, pistons, échappements et pneus. Recherche,
  équipement libre et sauvegarde dans **CUSTOMISATION**.
- **F7 : STYLE / ACCESSOIRES**, 503 éléments dans seize catégories : peintures,
  livrées, ailerons, galeries/cargaisons, kits complets ou séparés, freins, sièges,
  crochets, écrous, vitres, teintes de feux et ampoules. Aperçu et sauvegarde.
- Une seule liste par catégorie : **ORIGINAL**, **UNBOUND** ou **ORIGINAL + UNBOUND**
  sous les pièces. Les variantes de sièges sont conservées séparément.
- Positions des pots arrière, sièges, galeries et crochets récupérées dans les
  deux jeux ; les pots arrière/latéraux suivent leurs deux ancrages et les couches
  du code original. VFX et pots partagent leur placement.
  [Ancrages et limites](native/game/ATTACHMENTS.md). **F8** : arceau ; **K** : phares.
- Deux banques de 94 sons, choisies dans **SON DU MOTEUR** indépendamment de la
  voiture et des pièces.
- Puissance combinée des pièces, courbes du **BANC PUISSANCE**, tri de commun à
  contrebande et **PRÉPA MAX** : environ 4438 HP sans NOS / 4688 HP avec NOS.
  Turbo et compresseur sont exclusifs. Règles natives détaillées dans
  [PERFORMANCE.md](native/game/PERFORMANCE.md), sans équivalence Android démontrée.
- Sons originaux de conduite, profils moteur réglables et effets de fumée,
  flammes, étincelles et NOS. AUTO suit les sons source des 16 moteurs équipables ; sélection
  manuelle indépendante disponible dans **SON DU MOTEUR**.
- Plein écran, fenêtre sans bordure ou avec bordure ; résolution, limite FPS,
  VSync, qualité graphique et son. Confirmation des changements d’affichage.

Commandes : **Z/W/↑** accélérer, **S/↓** freiner, **Espace** frein à main, **←/→** changer de voie,
**E/C** passer les rapports, **T** changer de boîte, **N** NOS,
**L + accélérateur** 2STEP avec ECU compatible, **H** klaxon, **Échap** pause.
Les [instructions complètes](native/game/README.md) expliquent aussi les
sauvegardes, le mode de secours et la construction.

## Physique d’abord

Cette version est une reconstruction native en C++17/Raylib, avec une physique
provisoire. Les carrosseries utilisent leurs paramètres de base récupérés ; les courbes de
couple, coefficients SI et équations de conduite restent natifs. Les conversions
de transmission sont conservées. L’équivalence avec Android n’est pas validée.

Le [protocole physique](native/game/PHYSICS.md) et le banc de mesure intégré
permettent de comparer départ, régime, rapports, reprise et freinage. Les
336 contrôles du cœur et 86 contrôles graphiques passent sous Linux et Windows ; les mesures
natives Linux/Windows concordent. Le rendu Windows de CI utilise Mesa logiciel.
Les 188 sons des deux banques sont décodés sous Windows ; le mixage audio logiciel et 160 contrôles
clavier/souris et 192 416 combinaisons de groupes de pièces passent sous Linux. GPU et haut-parleurs physiques restent à vérifier.

La [recherche ciblée YYC](native/evidence/unbound/physics/README.md) a vérifié
2 128 noms/identifiants de variables et récupéré deux fonctions annexes. Le calcul
principal et les données complètes par voiture restent à reconstruire. Les
économie des boutiques, progression et autres modes restent à reconstruire.
Les catalogues sont fusionnés ; certains matériaux et placements restent des
adaptations natives. Les formules des pièces et effets sont adaptées
nativement ; tous les VFX du jeu original ne sont pas encore reproduits.

Sources : [native/game](native/game/README.md). Preuves :
[validation](native/game/VALIDATION.md). Historique de l’analyse :
[native/README.md](native/README.md). L’ancien lanceur Android est documenté
séparément dans [pc/README.md](pc/README.md).
