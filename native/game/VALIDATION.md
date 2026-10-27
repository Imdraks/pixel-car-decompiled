# Validation native 0.9.1 — correctif des échappements

- Classificateurs Android Original/Unbound récupérés séparément et identiques
  pour les 51 images ; coordonnées et branches de dessin conservées dans
  `native/evidence/merged/exhaust-rules.json`.
- 146 contrôles du cœur Linux réussis : 18336 transformations source, couches
  et racines de particules, plus les contrôles existants de physique et contenu.
- 45 contrôles graphiques Linux réussis. Quatre nouvelles planches du vrai
  moteur montrent 12 pots sur carrosserie standard, courte, longue et kit avec
  suspension modifiée. Contrôles pixels de vitesse et NOS/flammes réussis.
- Binaires Windows x64 et Linux compilés. La publication du correctif exige
  aussi les contrôles Windows via le workflow de release.
- Les pots de capot et directions des bouches restent des adaptations natives ;
  l’équivalence complète du rendu Android n’est pas revendiquée.
- Preuves Linux : `validation/exhaust-source-0.9.1/`.

Les validations ci-dessous concernent les versions antérieures.

# Validation native 0.9.0

- 143 contrôles du cœur : récupération de 4584 coordonnées, fitting de
  18718 configurations et 243334 variantes avec kits, source des pièces,
  239 ensembles visuels, migration des sièges/audio et arceau/phares.
- 45 contrôles graphiques : positions partagées pot/VFX, ancrages source,
  sièges des deux versions dans la même liste et mentions de provenance.
- 82 contrôles clavier/souris Linux (66 garage/audio, 16 affichage/trafic),
  dont sélection des variantes dans le même menu, arceau, phares et audio
  indépendant de la voiture.
- Physique, 192416 combinaisons et 188 sons conservés. La publication exige
  les contrôles Windows du cœur, fitting, rendu, physique et deux banques audio.
- Rapports locaux : `validation/attachments-0.9/`. Les adaptations de surface,
  de matériaux et les limites d’équivalence Android restent documentées.

## Publication et téléchargement vérifiés

- [Exécution Windows réussie](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40402394244) : 143 contrôles du cœur, 45 graphiques, 188 sons décodés, 18718 configurations de pot et 243334 fittings, 192416 combinaisons et physique Linux/Windows à 0,01 près.
- Captures Windows revues : provenance sous les sièges Original/Unbound dans la même liste, coordonnées récupérées et accessoires corrigés. Défilement et pixels NOS/flammes contrôlés sur les captures Windows.
- ZIP public redéchargé et vérifié : CRC, SHA-256, source compilée et exécutable. Les six aperçus publics sont identiques aux captures Windows validées.
- Restauration à froid et réutilisation : 247 ressources chacune. Rapports : `validation/windows-0.9/`.
- Rendu CI Mesa logiciel et mixage logiciel Linux ; GPU et haut-parleurs physiques restent à essayer.
- Source compilée : `eb5dde0a57318ac391ec530bf64c5288a069aa9f`.
- ZIP : 59231297 octets, SHA-256 `2c1a37ec106eef61fdde5fde2f9e87000bd6a879d4ae4548d2fbef6e70a555f4`.
- Exécutable : SHA-256 `ed44fce8b99043c1dc381cf496ad02a787d37846386820d0715224922e6dc460`.

## Historique : version 0.8.0

# Validation native 0.8.0

- 136 contrôles du cœur : 196 pièces, 521 recettes et images de jantes dans
  chaque banque, migration des sauvegardes et seize catégories esthétiques.
- 42 contrôles graphiques : jantes nommées, banque Original/Unbound, kits/livrée,
  cargaison au-dessus du toit, conduite personnalisée et corps visible après
  les changements d’affichage.
- 79 contrôles d’entrées Linux : 63 garage/équipement/audio, 16 affichage/trafic.
  Les seize catégories s’équipent par de vraies entrées, les jantes se cherchent
  par nom, les banques changent et l’ensemble survit au redémarrage.
- 188 échantillons décodés ; mixage logiciel non silencieux des deux banques,
  seize profils par banque, turbo/compresseur/NOS et événements, sans erreur.
- 192416 combinaisons de performance, 9359 ancrages et physique de référence
  conservés. Les adaptations de matériaux/accessoires restent décrites dans
  CONTENT.md ; ni fidélité complète Android ni haut-parleurs physiques démontrés.
- Rapports locaux : `validation/merged-0.8/`. La publication exige les contrôles
  Windows du cœur, physique, rendu, combinaisons et décodage des deux banques.

## Publication et téléchargement vérifiés

- [Exécution Windows réussie](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40396656078) : 136 contrôles du cœur, 42 graphiques, 188 décodages, 192416 combinaisons, 9359 ancrages et mesures physiques Linux/Windows concordantes à 0,01 près.
- Les captures Windows montrent les jantes nommées, livrées, kits et cargaison au-dessus du toit ; les comparaisons de défilement/NOS/flammes passent aussi sur ces images.
- ZIP public redéchargé : CRC, SHA-256, source compilée et exécutable vérifiés. Les quatre aperçus publics correspondent exactement aux captures Windows validées.
- Restauration à froid et réutilisation : 247 ressources chacune. Rapports : `validation/windows-0.8/`.
- Rendu CI Mesa logiciel ; mixage sur périphérique audio logiciel Linux. GPU et haut-parleurs physiques restent à essayer.
- Source compilée : `1a062312344c6644cc1aea0908bd22c9a0762b7f`.
- ZIP : 59174529 octets, SHA-256 `30beaa74beaaf7294855ecc7c930db273788ed7b58e862ebd83fece72016d290`.
- Exécutable : SHA-256 `ab08600e233c169bd30d380c84103da2cd21c5d9ce8fdea32b12a214fdccb262`.

## Historique : version 0.7.1

# Validation native 0.7.1

- 129 contrôles du cœur : conservation des 23 identifiants de vraies jantes et
  migration des 31 anciens choix de pneus/effets, sans perte de pièces.
- 39 contrôles graphiques, dont exclusion des calques du catalogue ; captures
  des quatre pages pour revoir les 23 vignettes et leur rendu sur la voiture.
- 57 contrôles clavier/souris Linux : 41 garage/boîte/frein à main, 16 affichage
  et trafic. La dernière vraie jante s’équipe ; une recherche d’un effet ne
  permet plus de l’équiper.
- Rapports locaux : `validation/rims-0.7.1/`. Publication conditionnée aux contrôles
  Windows du cœur, physique, rendu, 188384 combinaisons, 9359 ancrages et 94 sons.

## Publication vérifiée

- [Exécution Windows réussie](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40390236234) : 129 contrôles du cœur, 39 graphiques, physique Linux/Windows à 0,01 près, 188384 combinaisons, 9359 ancrages, 94 sons et comparaisons défilement/VFX.
- Les quatre pages de jantes ont été capturées sous Windows ; les 23 styles sont visibles et les calques ne sont plus proposés.
- ZIP public redéchargé : CRC, SHA-256, source et exécutable vérifiés. Restauration à froid et réutilisation : 146 ressources chacune.
- Rapports : `validation/windows-0.7.1/`. Rendu CI Mesa logiciel ; GPU et haut-parleurs physiques restent à essayer.
- Source compilée : `bab2e5b427bcbdd677a5ae4903f2e535a8a7233f`.
- ZIP : 31721429 octets, SHA-256 `8e0defc432e0c9d976a63b38463afe715fd7099c6d771c136a0b2997c44961ab`.
- Exécutable : SHA-256 `1dd0e12df8db0bbb6a68e2d33abd6b69d2e2231cc20707e18fe32610b76be454`.

## Historique : version 0.7.0

# Validation native 0.7.0

- 127 contrôles du cœur : ressources UI originales, frein à main distinct du
  frein de service, arrêt sans marche arrière, rotation arrière bloquée/libérée,
  priorité sur accélération/NOS et fumée sur le bon essieu.
- 38 contrôles graphiques : atelier et inventaire originaux, catégories et jantes,
  transmission, VFX et frein à main. Les comparaisons du défilement et des pixels
  NOS/flammes sont conservées.
- 55 contrôles de vraies entrées Linux : 39 pour garage/boîte/frein à main et
  16 pour affichage/trafic. Équipement, aperçu, remplacement de recherche,
  Ctrl+A, molette, double-clic, sauvegarde, redémarrage, fenêtre 4:3 et Full HD.
- Les rapports locaux sont dans `validation/garage-pc-0.7/`. La publication
  exige les contrôles Windows du cœur, du rendu, de la physique, des 188384
  combinaisons, des 9359 ancrages et du décodage des 94 sons.
- Les jauges montrent le modèle natif ; économie et progression d'origine restent
  à reconstruire. La calibration physique reste décrite dans PHYSICS.md.

## Publication et téléchargement vérifiés

- [Exécution Windows réussie](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40388248419) : 127 contrôles du cœur, 38 graphiques, physique Linux/Windows à 0,01 près, 188384 combinaisons, 9359 ancrages, 94 sons décodés, défilement et VFX visibles.
- ZIP public redéchargé, CRC et empreintes vérifiés ; les deux aperçus publics sont identiques aux captures Windows validées. Restauration à froid et réutilisation : 146 ressources chacune.
- Rapports : `validation/windows-0.7/`. Rendu CI Mesa logiciel ; essais sur GPU et haut-parleurs physiques restent à effectuer.
- Source compilée : `44013341088a1c9ebabc085b7c9a3a69d1fec80b`.
- ZIP : 31719254 octets, SHA-256 `64a55eee952872d669dcdfb2d9cdf9f925bb1ea55d6a42a4819651024abe5b91`.
- Exécutable : SHA-256 `df18d90507638f3ca6a0691bc35d88eec6a5065583dbf7a299d4b8372e604588`.

## Historique : validation native 0.6.0

# Validation native 0.6.0

- 119 contrôles du cœur : 9359 placements carrosserie/pot, sorties multiples,
  direction et suspension, jets attachés à haute vitesse/changement de voie ;
  huit préréglages de boîte, quatre à dix rapports, passage 9→10 automatique,
  effet du pont sans gain artificiel de HP et sauvegarde/rechargement sécurisé.
- 36 contrôles graphiques ; 45 clavier/souris Linux (29 pièces/boîte, 16 paramètres),
  dont curseurs, boutons de rapport, choix du nombre de vitesses, sauvegarde,
  annulation, réinitialisation et reprise réelle de la boîte dix rapports.
- Cinq comparaisons du défilement et contrôle des pixels bleus NOS/chauds de
  flamme dans les captures. Les paramètres d'origine à six rapports conservent
  leur référence physique. Les 188384 combinaisons de pièces sont conservées.
- Les rapports locaux sont dans `validation/exhaust-gearbox-0.6/`. La publication
  exige les contrôles Windows du cœur, des images, du défilement, de la physique
  et des 94 sons. Les ancrages et adaptations de transmission sont natifs.

Exécution Windows réussie :
[40376544654](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40376544654).
119 contrôles du cœur, 36 graphiques, 9359 placements géométriques, huit
préréglages et dix rapports maximum ; les pixels NOS/flammes sont visibles
(83 bleus, 131 chauds dans la zone contrôlée). Les captures Windows de la boîte
à dix rapports et des échappements ont été vérifiées. Physique de base,
défilement, 188384 combinaisons de pièces et décodage des 94 sons réussis.
Rapports : `validation/windows-0.6/` et le ZIP de validation joint à la release.

Archive publique retéléchargée et vérifiée : 29 754 752 octets, SHA-256
`168fdffb7914ab1297701148827433ed13d2fe684f56bb2c022f35015989bfbe`.
EXE : `ec8526fa2c5c580ce2a229329faad4064284a1c6207aacdb642dc85e796ed78f`.
Source compilée : `e26b8a3db5982f9b54744c31f1b62090183354e2`.
Les 144 ressources ont été restaurées en dossier neuf et réutilisées dans le
répertoire de travail sans modification. Les images source ajoutent les
atlas nécessaires aux échappements ; les données originales sont conservées.

## Historique : validation native 0.5.1

# Validation native 0.5.1

- 105 contrôles du cœur, dont circulation désactivée sans déplacement des NPC,
  collisions ou dépassements ; réactivation à distance et ancienne sauvegarde.
- 30 contrôles graphiques : option appliquée/enregistrée, absence de collisions
  cachées, réactivation, annulation d'un essai et nouvelle session sans trafic.
- 37 contrôles clavier/souris Linux : 21 pour les pièces et 16 pour les paramètres,
  dont désactivation du trafic sauvegardée, appliquée et reprise après redémarrage.
- Les comparaisons de défilement, 188 384 combinaisons de pièces et le banc
  physique de base restent inchangés. Rapports : `validation/traffic-0.5.1/`.
- La publication exige les contrôles Windows du cœur, de la puissance, de la
  physique, du rendu/défilement et du décodage des 94 sons.

Exécution Windows réussie :
[40370059371](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40370059371).
105 contrôles du cœur, 30 graphiques, 188 384 combinaisons de groupes de pièces,
94 sons décodés et comparaisons du banc physique et du défilement réussis.
La capture Windows sans trafic et la préférence `traffic=0` ont été vérifiées.
Rapports : `validation/windows-0.5.1/` et le ZIP de validation joint à la release.

Archive publique retéléchargée, CRC et identités source/EXE vérifiés :
28 732 455 octets, SHA-256
`d75abc7fcc2298944df824449b3cb200e5e27ae88f909a3d78e4b5f2fadd9fea`.
EXE : `5250adac5c6b28fbdb46748cda20e6ec8b563aa41d2d77d068556d70bb5241be`.
Source compilée : `c34605f076f42a3e87ca3d8da4b207af3960873f`.
Les 140 ressources sont restaurées en dossier neuf et réutilisées dans le
répertoire de travail sans modification.

## Historique : validation native 0.5.0

# Validation native 0.5.0

- 101 contrôles du cœur, dont 188 384 combinaisons de groupes de pièces et
  chacune des 194 substitutions de la préparation maximale.
- Vérification du calcul composé de puissance, rôle de l'intercooler, gain ECU,
  classement monotone, variantes cosmétiques, exclusivité turbo/compresseur,
  puissance réelle au pic et coupure du NOS au limiteur.
- 24 contrôles graphiques et 21 clavier/souris : rareté/tri, PRÉPA MAX, banc,
  puissance active en mode libre et conservation des choix au redémarrage.
- Les cinq comparaisons du défilement 0.4.1 sont conservées.
- La référence physique du véhicule sans pièces est inchangée. Les équations
  des pièces et raretés sont natives ; l'équivalence Android n'est pas établie.
- Rapports : `validation/power-0.5/`. La publication exige les contrôles Windows
  du cœur, des combinaisons, du banc physique, des images et des 94 sons.

Exécution Windows réussie :
[40368604089](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40368604089).
Les 101 contrôles du cœur, 24 graphiques, 188 384 combinaisons de groupes de
pièces, 94 sons et comparaisons de physique et de défilement réussissent.
Les rapports de puissance Linux et Windows sont identiques : 4288,88 HP sans
NOS et 4538,88 HP avec NOS. Les captures Windows du classement et du banc
ont été vérifiées. Rapports : `validation/windows-0.5/` et le ZIP de validation
joint à la release.

Le paquet public retéléchargé et vérifié mesure 28 731 040 octets ; SHA-256
`5eb9e860af6621882ad6f0715aead72833f6651f95068972ec78acc3b993f030`.
EXE : `c361ff39412246446f244eec2362c899554ce4e5416e61c03972bac8f1d81644`.
Source compilée : `414c350f0f444c4f7b5bb80b26f7397c4428b5b0`.
Les 140 ressources ont été restaurées en dossier neuf puis réutilisées dans le
répertoire de travail sans modification.

## Historique : validation native 0.4.1

# Validation native 0.4.1

- 85 contrôles du cœur : échelle route/circulation, parallaxe, rotation des
  roues, déplacements selon les FPS, fumée ancrée au sol et pause des effets.
- Les 21 contrôles graphiques et 18 contrôles clavier/souris du garage sont
  repris avec le nouveau rendu ; le code audio est conservé depuis 0.4.0.
- Captures contrôlées : arrêt, pause à vitesse non nulle, 100 et 200 km/h.
  La mesure des pixels vérifie le déplacement réel du marquage sur 0,1 seconde.
- Rapports : `validation/motion-0.4.1/`. La publication exige en plus les
  contrôles Windows du rendu, du déplacement des images, de la physique et du
  décodage des 94 sons. La référence physique 0.3 reste inchangée.

Exécution Windows réussie :
[40350423994](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40350423994).
85 contrôles du cœur, 21 graphiques, décodage des 94 sons, concordance du banc
physique et comparaison des captures réussis. Les images Windows mesurent
101 pixels à 100 km/h et 200 pixels à 200 km/h sur 0,1 seconde à 960 × 540 ;
la différence d'un pixel est due à la rastérisation. À l'arrêt et en pause à
vitesse non nulle, les images sont identiques. Rapports : `validation/windows-0.4.1/`.

Paquet public retéléchargé et vérifié : 28 718 194 octets, SHA-256
`6712b2680edd48f007f42cc9ee2960a78053adf9695843aa93bf24f8f66c095a`.
EXE : `adf61e01130051afb6e5210d7b74fef70616b7f1ab64d0ce818190b41d5cb69a`.
Source compilée : `5bf20af2cf08ea8669ff0a7d07dbe40db1e1d419`.
Les 140 ressources du paquet ont été restaurées en dossier neuf et réutilisées
sans modification dans le dossier de travail.

## Historique : validation native 0.4.0

# Validation native 0.4.0

- Linux : 75 contrôles du cœur, 21 graphiques, 19 de vraies entrées clavier/souris,
  dont équipement des 11 catégories, pagination, exclusivité et redémarrage.
- 94 sons originaux décodés ; échantillons moteur non silencieux.
- Mixage réel Raylib sur périphérique logiciel : 16 paires moteur, turbo,
  compresseur, NOS et événements ; PCM non nul, aucun échec de chargement.
- Le programme graphique initialise aussi son backend audio sans échec.
- Rapports : `validation/customization-0.4/`. Ces essais ne valident ni un
  haut-parleur Windows physique ni la correspondance originale moteur–son.
- La publication exige les contrôles Windows du cœur, du banc, du rendu et
  du décodage des 94 sons. Le rapport effectif accompagne la release.

Exécution Windows 0.4 réussie :
[40346990077](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40346990077).
75 contrôles du cœur, 21 graphiques, 94 sons décodés et huit mesures du banc
concordantes avec Linux. Rapports : `validation/windows-0.4/` et
`Validation-Windows.zip` sur la release. Captures Windows du garage,
customisation, profils audio, NOS et collisions vérifiées.

Source compilée : `163765c9441c05b52137ec8d5a9ea899e91cadd5`.
Archive publique : 28 716 585 octets ; SHA-256
`e50087133a9f49c8152f3fbac8d7312e5bf2824765875c123edb39f8e21738c7`.
EXE SHA-256 : `25dc5a12539b5f573529aea41338cfe879a97f044ca0765d686b0276078cd1ef`.

## Historique 0.3.1

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
