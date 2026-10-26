# Pixel Car Racer — Unbound Native 0.3

Cette première reconstruction **native Windows x64** propose un mode libre
jouable avec les ressources d'Unbound. Le programme ne lance ni APK, ni Android,
ni émulateur. Il fonctionne hors ligne après extraction de l'archive.

Ce n'est pas encore le portage complet et fidèle du jeu original : la conduite
et la circulation sont réimplémentées. La base originale 1.2.5 n'est pas fusionnée
avec le mod. Le moteur GameMaker YYC d'origine n'a pas été recompilé.

## Priorité actuelle : physique

La conduite est prioritaire sur l’ajout de contenu. Voir [PHYSICS.md](PHYSICS.md)
pour le modèle provisoire, les corrections de boîte et le protocole de comparaison
avec le jeu d’origine. La version 0.3 inclut les corrections de boîte, de freinage et le banc de mesure.
La fidélité au jeu Android reste à valider avant l’ajout de contenu.

## Jouer

Extraire **toute** l'archive, puis ouvrir `PixelCarRacerNative.exe` et choisir
**MODE LIBRE**. Conserver le dossier `assets` à côté de l'exécutable.

Prérequis : Windows 10/11 x64, un pilote graphique prenant en charge OpenGL 3.3,
environ 100 Mo libres. Aucun composant Android n'est téléchargé ou installé.

| Commande | Action |
| --- | --- |
| Z, W, flèche haut ou Espace | Accélérer |
| S ou flèche bas | Freiner |
| Flèches gauche/droite, Q/A et D | Changer de voie |
| E ou Maj gauche / C | Monter / descendre un rapport |
| T | Basculer entre boîte automatique et manuelle |
| Échap | Pause, retour des paramètres, ou rétablissement d'un affichage en essai |
| Alt + Entrée | Essayer le mode avec/sans bordure, puis confirmer |
| F3 | Afficher/masquer les FPS |
| F10 | Revenir immédiatement à un affichage de secours |
| Ctrl + Q | Quitter |

Le mode libre continue au-delà de 400 mètres. La circulation utilise trois
voies ; les contacts ralentissent le véhicule. Les paramètres et la pause
arrêtent la simulation, puis reprennent la session en cours.

Le garage permet de choisir parmi **191 images de carrosserie** et **54 styles
de jantes** extraits d'Unbound. Ces nombres ne désignent pas 191 véhicules dont
les statistiques d'origine auraient été reconstruites. Les performances de base
sont communes à cette version, et les coordonnées des roues sont estimées.

## Paramètres dans le jeu

- Fenêtre avec bordure, fenêtre sans bordure occupant le bureau, plein écran.
- Résolution de la fenêtre ou du plein écran ; résolution de rendu en mode sans
  bordure. Les formats différents de 16:9 peuvent présenter des bandes noires.
  Les tailles de fenêtre proposées tiennent compte des bordures et de l'espace
  disponible sur le bureau ; le plein écran utilise les modes signalés par Windows.
- Limite de 30, 60, 120, 144, 165 ou 240 FPS, ou limite désactivée.
- VSync activée/désactivée ; le pilote et la fréquence du moniteur peuvent
  déterminer le rythme final de présentation.
- Qualité faible, moyenne ou élevée. Elle modifie effectivement les ombres,
  les couches du décor et les détails de la route ; elle ne change pas la physique.
- Compteur FPS et son.

Un changement passe par **Appliquer**, puis **Conserver**. Sans confirmation,
les réglages précédents sont restaurés après 15 secondes. Échap les restaure
immédiatement. Seuls les changements confirmés sont enregistrés.

`Mode-secours.cmd` ignore les paramètres sauvegardés pour ouvrir une fenêtre
960 × 540. Les nouveaux paramètres peuvent ensuite être appliqués dans le jeu.

Sauvegardes : `%LOCALAPPDATA%\PixelCarRacerNative\settings.ini` et `profile.ini`.
Elles sont distinctes de celles d'Android et du prototype `pc/`. Le profil retient
la carrosserie, les jantes et le choix de boîte. La distance d'une session est
consignée dans `last-session.txt` ; les positions de circulation ne sont pas
restaurées au lancement suivant.

## Validation et limites

Les calculs de conduite, la persistance des réglages et du garage ont été testés.
Le rendu natif Linux, les changements de mode, le rétablissement automatique et
un parcours réel clavier/souris ont également été vérifiés. Voir `VALIDATION.md`.
La validation Windows automatisée, lorsqu'elle accompagne la release, utilise
un rendu logiciel Mesa de test. Un PC Windows physique avec son pilote GPU et
son périphérique audio reste à vérifier.

Les boutiques, améliorations, réglages détaillés des moteurs, livrées, progression,
services en ligne, sauvegardes Android et autres modes du jeu original ne sont
pas reconstruits. Certains éléments graphiques, palettes et animations peuvent
différer de l'original. Le son du moteur est synthétisé dans cette version.

## Construire

Code : `src/`. Tests : `tests/`. Le programme utilise C++17 et Raylib 6.2.
Il n'utilise pas les bibliothèques Android `libyoyo.so` à l'exécution.

Dans l'environnement préparé :

```bash
PCR_BACKGROUND_OUTPUT=/workspace/native-runtime/backgrounds.json \
  /workspace/tools/utmt-cli-0.9.2.0/UndertaleModCli load \
  /workspace/windows-port/recovered/assets/game.droid \
  --scripts native/game/tools/export_backgrounds.csx
python3 native/game/tools/prepare_assets.py
bash native/game/build.sh
```

La construction Linux utilise GCC ; celle de Windows utilise Zig 0.17.0 avec
la bibliothèque Raylib Windows officielle. Les archives sont vérifiées par
SHA-256 avant installation. Les APK et les ressources générées restent exclus
de Git. Les métadonnées `src/art.hpp` peuvent être régénérées à partir des exports.

Le premier test graphique de `tests/ui_input_test.py` a mis en évidence des
appuis synthétiques trop courts pour le rythme de présentation. Le test corrigé
maintient les touches et boutons assez longtemps pour être lus entre deux images.
Il vérifie les préférences sauvegardées et les déplacements réellement produits.

Les options `--data-dir`, `--assets-dir`, `--no-audio`, `--free-drive` et
`--safe-mode` servent aux essais et au lancement direct. `--smoke-test` exige un
dossier de données explicitement choisi et neuf ; il ne doit pas utiliser les
réglages d'un joueur. Les captures F12 ne sont activées qu'avec `--capture-dir`.

## Banc de mesure de la conduite

L’exécutable peut calculer des essais reproductibles sans ouvrir de fenêtre,
sans ressources graphiques et sans périphérique audio :

```powershell
.\PixelCarRacerNative.exe --physics-benchmark-dir "$env:TEMP\PCR-mesures-03"
```

Choisir un **dossier neuf** à chaque essai. Les sorties `physics-report.json` et
`telemetry.csv` contiennent départ arrêté, freinage, lever de pied, reprise et
premier rapport au limiteur. Elles n’affectent pas les sauvegardes du joueur.
La référence `native-physics-baseline.json` du paquet décrit le modèle natif
provisoire ; ce n’est pas une référence physique issue du jeu original.
