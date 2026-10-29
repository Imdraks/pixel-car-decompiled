# Musique des menus — 0.18.1

Le fichier fourni **Underground — Need for Speed Heat OST.wav** est intégré en
entier (2 min 50 s) et remplace la sélection musicale des menus.

- **Menu principal / showroom** : version normale.
- **Mon garage** : version avec basses légèrement renforcées, aigus adoucis,
  stéréo resserrée et quatre réflexions courtes pour une ambiance d’enceinte dans
  un garage.
- **Customisation, pièces et réglages** : même ambiance résonnante, environ
  **8 dB plus basse** pour laisser entendre le moteur et le turbo.
- **Conduite, pause et paramètres ouverts depuis la conduite** : musique coupée.

Les changements de menu utilisent un fondu d’environ 180 ms. Le morceau ne
redémarre pas quand on change de voiture, de banque de sons ou de volume. En
quittant la conduite, il reprend sa position. Les curseurs **Volume général** et
**Musique** restent indépendants du moteur et des bruitages.

Deux OGG stéréo 44,1 kHz sont lus en streaming, sur la même durée exacte. Les
niveaux sont normalisés avec réserve avant saturation ; début et fin sont fondus
pour éviter un clic lors de la répétition. Les anciens morceaux des banques
originales restent intacts dans les ressources. Le WAV fourni est conservé séparément dans l’espace de travail.

`tools/prepare_menu_music.py` reproduit la préparation avec FFmpeg. Les sorties
existantes sont sauvegardées dans le dossier de travail avant régénération.
`menu-music.json` décrit le fichier source, les effets et les mesures ; la copie
Windows est `musique-menu.json`. La lecture, le mélange, la continuité des volumes
et le silence en conduite sont vérifiés avec un processeur de capture PCM. Cela
ne constitue pas une écoute sur des enceintes physiques.
