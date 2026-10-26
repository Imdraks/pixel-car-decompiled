# Validation de la reconstruction native 0.2

## Corrections de physique après la release 0.2

Ces résultats concernent les sources après la release ; ils ne remplacent pas
la preuve Windows du paquet 0.2 publié ci-dessous.

- 36 contrôles du cœur réussis sur Linux, dont 14 nouveaux contrôles de conduite.
- 15 contrôles du rendu Linux réussis après les corrections.
- Exécutables Linux et Windows x64 reconstruits sans erreur. Le nouveau binaire
  Windows n'a pas encore été exécuté sur Windows ; les résultats Windows plus
  bas concernent exclusivement l'ancienne release.
- Modèle provisoire : 0–100 km/h en 4,1 s ; 100–0 en 41,39 m et 3,01 s ;
  402 m en 12,418 s. Ces nombres ne sont pas des références Android.
- Rapports `validation/physics-core-linux.txt` et `physics-graphics-linux.txt`,
  série temporelle `validation/physics-baseline.csv`. Protocole : `PHYSICS.md`.

## Contrôles terminés dans le cloud Linux

- 22 vérifications du cœur : course de référence terminée, même résultat à
  30/60/120/144/165/240 FPS, mode libre au-delà de 400 mètres, freinage, voies,
  contacts avec la circulation, paramètres invalides, fichiers Unicode,
  remplacement d'un fichier existant, sauvegarde du garage et des préférences.
- Simulation libre de 70 secondes : environ 4,4 km parcourus sans événement de
  fin de course. Cette mesure concerne le modèle natif réimplémenté.
- 15 contrôles graphiques sous Xvfb/Mesa : avance du véhicule, entrée de voie,
  état sans bordure et taille du bureau, rétablissement après expiration,
  absence de sauvegarde d'un choix non confirmé, plein écran et sa résolution, retour avec bordure,
  résolution appliquée, demande VSync, limite à 30 FPS, persistance et reprise.
- Mesure de la limite à 30 FPS : au moins 0,9 seconde pour 30 images. La durée
  observée est conservée dans le rapport de chaque exécution. Le drapeau VSync
  vérifié est une demande au pilote, pas une mesure de synchronisation physique.
- 11 contrôles de vraies entrées XTest : choix d'une carrosserie et de jantes,
  accélération, voie, boîte, mode sans bordure, FPS, VSync, qualité et compteur.
  Le véhicule a parcouru plus de 35 mètres dans ce parcours d'essai.
- Construction du PE Windows x64 et contrôle de ses imports : bibliothèques
  système Windows et UCRT, sans bibliothèque Android ou moteur d'émulation.

Ces essais vérifient la reconstruction, pas l'équivalence avec la physique et
la progression du jeu GameMaker.

## Windows

Exécution réussie : [40305565837](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40305565837),
sur Windows Server 2025, avec 22 contrôles du cœur et 15 contrôles graphiques.
L'archive testée porte le SHA-256
`dfe16f0c55049cd32c26ff1489709ed6147e647a691d03ec4423f9807b42c425`.
Les rapports texte correspondants sont aussi conservés dans `validation/`.

Le pipeline de publication `publish-native-release.yml` vérifie le même paquet
sur un runner Windows avant sa publication. Le rapport de cette exécution et
ses captures sont joints séparément à la release dans `Validation-Windows.zip`.
Le rendu de ce test utilise Mesa logiciel, installé uniquement sur le runner.
Cette bibliothèque de test n'est pas incluse dans la distribution du jeu.

Un essai préalable avec une installation Wine portable incomplète n'a pas pu
initialiser son propre environnement Windows. Il ne constitue pas une validation
du programme et n'est pas présenté comme un test réussi de l'exécutable.

Le premier essai sur Windows Server 2025 a détecté une fenêtre plus petite que
les 1 280 pixels demandés sur le bureau virtuel. La correction limite les choix
fenêtrés à l'espace utilisable, bordures et DPI compris. Le plein écran demande
aussi explicitement le mode vidéo choisi au backend GLFW, et un contrôle séparé
vérifie que sa résolution est bien appliquée.

Les essais sur un PC Windows physique, plusieurs écrans, les pilotes GPU des
fabricants, le HDR et l'audio réel restent à effectuer. Aucun achat ni compte
personnel n'est utilisé. Aucun APK ou émulateur n'est lancé dans cette application.
