# Validation de la reconstruction native 0.3.1

## Correction des roues 0.3.1

- Le placement proportionnel à la largeur de la carrosserie est supprimé. Le
  point arrière utilise l’origine du sprite ; le point avant est mesuré dans
  les ouvertures transparentes. La recherche échoue explicitement si un nouveau
  sprite est ambigu, au lieu de choisir des coordonnées approximatives.
- Pneus et jantes utilisent le même canevas de 62 × 62 et leur origine 31 × 31.
  Le pneu original est rendu à demi-échelle de la carrosserie. Le fond du passage
  de roue et les roues sont derrière les ailes, y compris les ailes couvrantes.
- Cas signalé, carrosserie 021 : arrière (62, 58), avant (160, 58) ; rayon extérieur
  du pneu 12,5 pixels dans le repère de la carrosserie.
- Les 191 carrosseries ont été sélectionnées via les vrais boutons du garage,
  capturées avec la jante 09 et revues sur 12 planches de rendu natif Linux.
  Le sprite spécial 183 ne possède pas de passages de roue ; les roues ajoutées
  artificiellement sont retirées sur ce modèle.
- 46 contrôles du cœur et 15 contrôles graphiques Linux passent. La physique du
  modèle de référence est conservée ; les mesures du banc ne changent pas.
- Métadonnées : `validation/wheel-anchors.json`. Rapports :
  `validation/wheels-0.3.1/`. Reproduction visuelle sous XTest :
  `tests/wheel_visual_audit.py`, dans un écran X isolé et un dossier neuf.
- Le test graphique Windows de la release utilise maintenant la carrosserie 021
  et la jante 09 pour produire les captures du cas signalé. La publication est
  conditionnée aux contrôles Windows du cœur, du banc et du rendu.

Exécution Windows 0.3.1 réussie :
[40319746159](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40319746159).
Les 46 contrôles du cœur, les 15 contrôles graphiques et la comparaison du banc
réussissent. La capture Windows du garage montre la carrosserie 021 avec la
jante 09. Le paquet public a été retéléchargé et vérifié : 7 950 681 octets,
SHA-256 `71d33b788a70a6b91889f7f7a7328b0ac072363f5c9c908d3f891ff63469a990`.
Source compilée : `4974757f9f9535c107c546a07dbfed12b0c04198`.
Les aperçus des 191 carrosseries sont joints à la release dans
`Verification-roues-191-carrosseries.zip` ; les originaux de capture restent dans
le répertoire d’audit du cloud.

## Historique : contrôles de la version 0.3

- 43 contrôles du cœur réussis sur Linux : simulation indépendante des FPS,
  conduite, boîte, adhérence commune aux freins, transfert de poids selon
  l’essieu moteur, persistance et banc de mesure.
- 15 contrôles du rendu Linux et 13 contrôles de vraies entrées clavier/souris
  réussis après les corrections. Le mode libre reprend après les paramètres.
- Construction Linux et Windows x64 sans avertissement du compilateur.
- Le banc intégré fonctionne sans écran ni audio, produit JSON/CSV et refuse
  de remplacer un dossier existant. Aucun profil de joueur n’est modifié.
- Référence native provisoire : 0–100 km/h en 4,507 s ; 402 m en 12,727 s ;
  freinage depuis 100 km/h en quatrième : 42,99 m et 3,108 s.
  Ces nombres ne sont pas des références Android.
- Rapports : `validation/physics-core-linux.txt`, `physics-graphics-linux.txt`,
  `physics-ui-input-linux.json` et `native-physics-baseline.json`.
- La publication 0.3 est conditionnée à l’exécution sous Windows du cœur, du
  banc de mesure et du programme graphique. Les mesures Windows doivent être
  à moins de 0,01 des mesures Linux, dans l’unité de chaque grandeur.
  Le rapport effectif accompagne la release dans `Validation-Windows.zip`.

Exécution Windows réussie : [40315185715](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40315185715).
Le paquet public a été retéléchargé et vérifié : SHA-256
`fdf3a352d6a6dacc52cc9a1c7a442d83ce44ac78b475ccfa618d64500373a643`,
7 582 601 octets. Source compilée :
`c9fe0982b364959c9567fe087303afd316ea5e8d`.
Les rapports Windows sont aussi dans `validation/windows-0.3/`.

La fidélité au jeu original reste à valider. Le calcul principal YYC n’a pas
été reconstitué par les trois passes ciblées Ghidra ; voir `PHYSICS.md` et les
preuves dans `native/evidence/unbound/physics/` du dépôt.

## Historique de validation : release 0.2

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
