# Voitures distinctes et garage automatique — 0.16.0

**B** ou **CHOISIR UNE VOITURE** ouvre le catalogue. Les 239 entrées ont un nom,
un identifiant stable, une catégorie, un moteur par défaut et leur propre fiche
mécanique. L’indice du sprite reste un détail du rendu ; il ne sert plus à déplacer
la préparation d’une voiture à l’autre.

Catégories : Compactes, Berlines/Breaks, Sportives, Muscle cars, GT/Supercars,
Utilitaires, Classiques et À identifier. Recherche par marque/modèle avec Ctrl+F,
catégorie avec les flèches en haut, changement de page avec Page précédente/
suivante ; sélectionner puis **UTILISER CETTE VOITURE** ou Entrée.

## Préparation propre à chaque voiture

Changer de voiture enregistre automatiquement la préparation actuelle, puis
charge celle du modèle choisi. Une voiture jamais utilisée commence dans sa
configuration d’origine. Moteur, suralimentation, ECU, autres pièces, jantes,
accessoires, réglages de suspension/transmission, sons et record restent avec
cette voiture. Les flèches du garage chargent elles aussi la préparation propre
au modèle suivant ; elles ne changent plus simplement son image.

Les fichiers sont dans `vehicles/<identifiant>.ini` du dossier utilisateur
(`%LOCALAPPDATA%/PixelCarRacerNative` sous Windows). Une préparation remplacée
garde une copie `.bak` ; les sauvegardes identiques ne détruisent pas cette copie.
`profile.ini` garde la voiture active. F11 conserve les sauvegardes nommées : leur
chargement sauvegarde d’abord la voiture quittée et retrouve le bon modèle.

Les variantes dont le bundle Original/Unbound est identique partagent une entrée.
Les variantes distinctes ont des identifiants et sauvegardes séparés, même
lorsqu’elles occupent l’ancien même emplacement de sprite.

## Moteur d’origine et migration

Au premier chargement, une ancienne configuration sans modification reçoit son
moteur par défaut. Un moteur déjà choisi, des pièces, des jantes ou réglages
personnalisés empêchent ce remplacement automatique. Le fichier actif antérieur
est conservé dans **`profile.ini.pre-vehicles-v1.bak`**, sans écrasement lors des
redémarrages suivants. Nom de sauvegarde et record sont conservés.

- 58 entrées reçoivent la référence moteur du tableau NFS via les correspondances
  de modèle déclarées. L’année/la finition peuvent différer : ce sont les mêmes
  ponts documentés, sans prétendre à une certification du moteur constructeur.
- La 911 du mod reçoit une base **F6 3.6 / propulsion provisoire**, avec une masse
  de base estimée à 1350 kg. Elle ne reprend plus le moteur/traction de la Golf.
  Version et finition de cette 911 restent à confirmer.
- Les 180 autres entrées ont un bloc propre issu de leurs caractéristiques
  récupérées (puissance, cylindrée, régime). Aucun code moteur inconnu n’est
  inventé. Les sept modèles encore non identifiés restent signalés comme tels.

Les moteurs retirés volontairement ou modifiés ne sont pas réinstallés au
redémarrage. **REMETTRE BASE** rééquipe le moteur par défaut tout en conservant
le fonctionnement précédent du bouton pour les réglages et l’apparence.

## Swaps universels

**Les 145 moteurs NFS sont compatibles avec les 239 voitures.** F1 affiche tous
les moteurs ; le filtre restrictif « Cette auto » disparaît. Le donneur reste une
information descriptive. Passer d’un moteur thermique à électrique retire les
pièces incompatibles avec cette motorisation : cela ne restreint pas le swap.

Les sons suivent le moteur équipé ; les moteurs d’origine réutilisent les familles
simulées ou les enregistrements historiques adaptés disponibles. Ce sont des
approximations, avec écoute sur enceintes non établie. Les volumes restent des
réglages globaux, la musique reste limitée aux menus/garage.

Les données sont dans `vehicles.json`, incluant les paramètres propres à chaque
entrée et les limites des références. `generate_vehicle_catalog.py` régénère les
fiches depuis les identités et caractéristiques récupérées et le catalogue NFS.
La convention est **0 = Unbound, 1 = Original**. Les attributions NFS aux
remplacements visuels ont été corrigées : la BMW Original et l’hypercar Unbound
ne reçoivent plus la même attribution par confusion entre les deux banques.
