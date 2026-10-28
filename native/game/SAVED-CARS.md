# Mes voitures — 0.13.9

Dans le garage, cliquez **MES VOITURES** ou appuyez sur **F11**.
Donnez un nom à la voiture actuellement équipée et choisissez
**ENREGISTRER UNE NOUVELLE**. Entrée dans le champ du nom enregistre aussi une
nouvelle voiture. Les noms acceptent les accents ; Ctrl+A efface le champ.

Chaque sauvegarde conserve la carrosserie, les jantes avant/arrière, l’apparence,
tous les accessoires et pièces, le moteur, la transmission et les dix rapports,
le pont, les suspensions, la répartition des masses, le réglage wheelie, les
préférences sonores, le record et les autres paramètres propres à la voiture.
Les options générales, comme les volumes, l’affichage, le trafic, l’ABS et l’antipatinage,
restent des options du jeu.

Sélectionnez une carte puis **CHARGER**, ou Entrée hors du champ du nom, pour
restaurer sa configuration dans le garage. **METTRE À JOUR** remplace la carte
sélectionnée avec la voiture actuellement équipée et le nom saisi. L’ancienne
configuration est conservée dans un fichier `.ini.bak` avant toute mise à jour.
Changer simplement de voiture dans le garage ne modifie pas les cartes déjà
sauvegardées. Échap et Retour garage ferment la collection.

Les cartes sont conservées d’une session à l’autre dans le sous-dossier `cars`
des données utilisateur, soit normalement
`%LOCALAPPDATA%/PixelCarRacerNative/cars` sous Windows. Les fichiers
`car-1.ini`, `car-2.ini`, etc. sont indépendants du profil courant `profile.ini`.
Ils ne dépendent pas du dossier de l’exécutable ; une mise à jour du jeu garde
la collection. L’écriture du profil est atomique ; la collection ignore les
fichiers temporaires et les sauvegardes `.bak`.

Les flèches et Page précédente/Page suivante parcourent les pages de six cartes.
F10 conserve son rôle d’affichage de secours ; F11 ouvre la collection.
