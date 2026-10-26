# Pixel Car Racer — reconstruction native Windows

**[Télécharger Windows x64 — version 0.3](https://github.com/Imdraks/pixel-car-decompiled/releases/download/v0.3.0-native-preview/PixelCarRacerNative-Windows-x64.zip)** · [Release et preuves Windows](https://github.com/Imdraks/pixel-car-decompiled/releases/tag/v0.3.0-native-preview)

Extraire toute l’archive, garder `assets` à côté de **PixelCarRacerNative.exe**,
puis lancer cet exécutable et choisir **MODE LIBRE**. Windows 10/11 x64 avec un
pilote OpenGL 3.3. Le jeu fonctionne hors ligne, sans Android ni émulateur.

## Disponible

- Mode libre continu avec circulation sur trois voies.
- Boîte automatique/manuelle, rétrogradages, limiteur et frein moteur.
- Traction, propulsion ou quatre roues motrices sélectionnables au garage,
  avec effet du transfert de poids et choix sauvegardé.
- 191 images de carrosserie et 54 styles de jantes issus d’Unbound.
- Plein écran, fenêtre sans bordure ou avec bordure ; résolution, limite FPS,
  VSync, qualité graphique et son. Confirmation des changements d’affichage.

Commandes : **Z/W/↑** accélérer, **S/↓** freiner, **←/→** changer de voie,
**E/C** passer les rapports, **T** changer de boîte, **Échap** pause.
Les [instructions complètes](native/game/README.md) expliquent aussi les
sauvegardes, le mode de secours et la construction.

## Physique d’abord

Cette version est une reconstruction native en C++17/Raylib, avec une physique
provisoire. Les carrosseries ne disposent pas encore de leurs statistiques
d’origine : le moteur de référence est commun, et la transmission est un choix
d’essai. L’équivalence avec la conduite Android n’est pas validée.

Le [protocole physique](native/game/PHYSICS.md) et le banc de mesure intégré
permettent de comparer départ, régime, rapports, reprise et freinage. Les
43 contrôles du cœur et 15 contrôles graphiques passent sur Windows ; les mesures
natives Linux/Windows concordent. Le rendu Windows de CI utilise Mesa logiciel.
Les essais sur GPU physique et l’audio réel restent à effectuer.

La [recherche ciblée YYC](native/evidence/unbound/physics/README.md) a vérifié
2 128 noms/identifiants de variables et récupéré deux fonctions annexes. Le calcul
principal et les données complètes par voiture restent à reconstruire. Les
boutiques, pièces, progression, autres modes et fusion complète original 1.2.5 /
Unbound attendent la validation de cette base.

Sources : [native/game](native/game/README.md). Preuves :
[validation](native/game/VALIDATION.md). Historique de l’analyse :
[native/README.md](native/README.md). L’ancien lanceur Android est documenté
séparément dans [pc/README.md](pc/README.md).
