# Pixel Car Racer — reconstruction native Windows

**[Télécharger Windows x64 — version 0.14.0](https://github.com/Imdraks/pixel-car-decompiled/releases/download/v0.14.0-native-preview/PixelCarRacerNative-Windows-x64.zip)** · [Release et preuves Windows](https://github.com/Imdraks/pixel-car-decompiled/releases/tag/v0.14.0-native-preview)

Extraire toute l’archive, garder `assets` à côté de **PixelCarRacerNative.exe**,
puis lancer cet exécutable et choisir **MODE LIBRE**. Windows 10/11 x64 avec un
pilote OpenGL 3.3. Le jeu fonctionne hors ligne, sans Android ni émulateur.

## Disponible

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
