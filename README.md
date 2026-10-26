# Pixel Car Racer — reconstruction native Windows

**[Télécharger Windows x64 — version 0.4.1](https://github.com/Imdraks/pixel-car-decompiled/releases/download/v0.4.1-native-preview/PixelCarRacerNative-Windows-x64.zip)** · [Release et preuves Windows](https://github.com/Imdraks/pixel-car-decompiled/releases/tag/v0.4.1-native-preview)

Extraire toute l’archive, garder `assets` à côté de **PixelCarRacerNative.exe**,
puis lancer cet exécutable et choisir **MODE LIBRE**. Windows 10/11 x64 avec un
pilote OpenGL 3.3. Le jeu fonctionne hors ligne, sans Android ni émulateur.

## Disponible

- Mode libre continu avec circulation sur trois voies.
- Défilement de la route et du décor lié à la distance parcourue, circulation
  à la même échelle et roues animées selon le trajet, figées en pause.
- Boîte automatique/manuelle, rétrogradages, limiteur et frein moteur.
- Traction, propulsion ou quatre roues motrices sélectionnables au garage,
  avec effet du transfert de poids et choix sauvegardé.
- 191 images de carrosserie et 54 styles de jantes issus d’Unbound.
  La version 0.4.1 aligne les roues avec chaque carrosserie et conserve les ailes
  devant les pneus ; les 191 rendus ont été parcourus et revus.
- 194 pièces dans 11 catégories : moteurs, suspension, turbos, compresseurs, ECU,
  NOS, admissions, intercoolers, pistons, échappements et pneus. Recherche,
  équipement libre et sauvegarde dans **CUSTOMISATION**.
- Sons originaux de conduite, profils moteur réglables et effets de fumée,
  flammes, étincelles et NOS. AUTO moteur–son reste approximatif ; sélection
  manuelle indépendante disponible dans **SON DU MOTEUR**.
- Plein écran, fenêtre sans bordure ou avec bordure ; résolution, limite FPS,
  VSync, qualité graphique et son. Confirmation des changements d’affichage.

Commandes : **Z/W/↑** accélérer, **S/↓** freiner, **←/→** changer de voie,
**E/C** passer les rapports, **T** changer de boîte, **N** NOS,
**L + accélérateur** 2STEP avec ECU compatible, **H** klaxon, **Échap** pause.
Les [instructions complètes](native/game/README.md) expliquent aussi les
sauvegardes, le mode de secours et la construction.

## Physique d’abord

Cette version est une reconstruction native en C++17/Raylib, avec une physique
provisoire. Les carrosseries ne disposent pas encore de leurs statistiques
d’origine : le moteur de référence est commun, et la transmission est un choix
d’essai. L’équivalence avec la conduite Android n’est pas validée.

Le [protocole physique](native/game/PHYSICS.md) et le banc de mesure intégré
permettent de comparer départ, régime, rapports, reprise et freinage. Les
85 contrôles du cœur et 21 contrôles graphiques passent sur Windows ; les mesures
natives Linux/Windows concordent. Le rendu Windows de CI utilise Mesa logiciel.
Les 94 sons sont décodés sous Windows ; le mixage audio logiciel et 19 contrôles
clavier/souris passent sous Linux. GPU et haut-parleurs physiques restent à vérifier.

La [recherche ciblée YYC](native/evidence/unbound/physics/README.md) a vérifié
2 128 noms/identifiants de variables et récupéré deux fonctions annexes. Le calcul
principal et les données complètes par voiture restent à reconstruire. Les
économie des boutiques, progression, autres modes et fusion complète original 1.2.5 /
Unbound restent à reconstruire. Les formules des pièces et effets sont adaptées
nativement ; tous les VFX du jeu original ne sont pas encore reproduits.

Sources : [native/game](native/game/README.md). Preuves :
[validation](native/game/VALIDATION.md). Historique de l’analyse :
[native/README.md](native/README.md). L’ancien lanceur Android est documenté
séparément dans [pc/README.md](pc/README.md).
