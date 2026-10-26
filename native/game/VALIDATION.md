# Validation de la reconstruction native 0.2

## Contrôles terminés dans le cloud Linux

- 22 vérifications du cœur : course de référence terminée, même résultat à
  30/60/120/144/165/240 FPS, mode libre au-delà de 400 mètres, freinage, voies,
  contacts avec la circulation, paramètres invalides, fichiers Unicode,
  remplacement d'un fichier existant, sauvegarde du garage et des préférences.
- Simulation libre de 70 secondes : environ 4,4 km parcourus sans événement de
  fin de course. Cette mesure concerne le modèle natif réimplémenté.
- 14 contrôles graphiques sous Xvfb/Mesa : avance du véhicule, entrée de voie,
  état sans bordure et taille du bureau, rétablissement après expiration,
  absence de sauvegarde d'un choix non confirmé, plein écran, retour avec bordure,
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

Le pipeline de publication `publish-native-release.yml` vérifie le même paquet
sur un runner Windows avant sa publication. Le rapport de cette exécution et
ses captures sont joints séparément à la release dans `Validation-Windows.zip`.
Le rendu de ce test utilise Mesa logiciel, installé uniquement sur le runner.
Cette bibliothèque de test n'est pas incluse dans la distribution du jeu.

Un essai préalable avec une installation Wine portable incomplète n'a pas pu
initialiser son propre environnement Windows. Il ne constitue pas une validation
du programme et n'est pas présenté comme un test réussi de l'exécutable.

Les essais sur un PC Windows physique, plusieurs écrans, les pilotes GPU des
fabricants, le HDR et l'audio réel restent à effectuer. Aucun achat ni compte
personnel n'est utilisé. Aucun APK ou émulateur n'est lancé dans cette application.
