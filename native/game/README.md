# Pixel Car Racer — Unbound Native 0.5.0

Cette première reconstruction **native Windows x64** propose un mode libre
jouable avec les ressources d'Unbound. Le programme ne lance ni APK, ni Android,
ni émulateur. Il fonctionne hors ligne après extraction de l'archive.

Ce n'est pas encore le portage complet et fidèle du jeu original : la conduite
et la circulation sont réimplémentées. La base originale 1.2.5 n'est pas fusionnée
avec le mod. Le moteur GameMaker YYC d'origine n'a pas été recompilé.

La version **0.5.0** combine moteur, pièces atmosphériques, ECU, suralimentation,
intercooler et NOS avec le même calcul pour le banc et la conduite. Le garage
montre les HP sans/avec NOS, le gain de la pièce sélectionnée, et un banc de
puissance. **PRÉPA MAX** équipe les meilleures pièces : environ **4289 HP sans
NOS / 4539 HP avec NOS**. Turbo et compresseur restent strictement exclusifs.

Les pièces sont triées de **commun à contrebande**, avec raretés colorées et tri
inversible. Contrebande désigne le sommet de performance de chaque catégorie.
Ces raretés et formules sont des règles natives ; voir [PERFORMANCE.md](PERFORMANCE.md).
Les données brutes restent celles d'Unbound ; la fidélité Android n'est pas établie.

La version **0.4.1** synchronise le défilement avec la distance réelle du mode
libre : route, circulation et fumées partagent la même échelle de 48 pixels par
mètre dans le repère 1280 × 720. Montagnes, ville et arbres défilent plus lentement
selon leur profondeur. Les roues tournent selon le trajet et le rayon du pneu,
et restent immobiles en pause. Les performances physiques ne changent pas.

La version **0.4.0** ajoute **194 pièces** dans 11 catégories, avec recherche,
pagination, équipement et sauvegarde : 16 moteurs, 16 suspensions, 14 turbos,
10 compresseurs, 8 ECU, 5 NOS, 21 admissions, 13 intercoolers, 7 pistons,
48 échappements et 36 pneus. Ouvrir **CUSTOMISATION** depuis le menu ou le garage.
Les pièces sont librement équipables, sans économie simulée.

Les 94 fichiers audio d'origine sont inclus. Le mixage de conduite utilise les
boucles moteur en charge/décélération, turbo, compresseur et NOS, ainsi que les
valves, passages de rapports, détonations, collisions et klaxon. **La liaison
exacte entre chaque moteur et son profil audio n'est pas prouvée** : AUTO est
une attribution native approximative par famille. **SON DU MOTEUR** permet de
choisir séparément charge, décélération et valve, avec préécoute.
Fumée, flammes et étincelles utilisent les images originales ; le jet bleu NOS
est procédural. Tous les événements et animations du jeu Android ne sont pas
reconstruits. Voir [CUSTOMIZATION.md](CUSTOMIZATION.md) et [PHYSICS.md](PHYSICS.md).

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
| N maintenu | NOS, si équipé, réserve de 10 secondes par session |
| L + accélérateur | 2STEP avec ECU compatible ; relâcher L pour partir |
| H | Klaxon |
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
les statistiques d'origine auraient été reconstruites. Les performances moteur de base
sont communes à cette version. Les points de roue utilisent l’origine des sprites
et leurs passages transparents, vérifiés sur l’ensemble des carrosseries.
Le bouton **TRACTION / PROPULSION / 4 ROUES MOTRICES** du garage choisit une
configuration d’essai : elle change réellement l’adhérence au départ et l’effet
du transfert de poids. Le choix est sauvegardé et indiqué en mode libre. Il ne
prétend pas représenter la transmission d’origine de chaque carrosserie.

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
la carrosserie, les jantes, la transmission, les pièces et les choix audio. La distance d'une session est
consignée dans `last-session.txt` ; les positions de circulation ne sont pas
restaurées au lancement suivant.

## Validation et limites

Les calculs de conduite, la persistance des réglages et du garage ont été testés.
Le rendu natif Linux, les changements de mode, le rétablissement automatique et
un parcours réel clavier/souris ont également été vérifiés. Voir `VALIDATION.md`.
La validation Windows automatisée, lorsqu'elle accompagne la release, utilise
un rendu logiciel Mesa de test. Un PC Windows physique avec son pilote GPU et
son périphérique audio reste à vérifier.

L’économie des boutiques, les réglages détaillés des moteurs, les livrées, la progression,
services en ligne, sauvegardes Android et autres modes du jeu original ne sont
pas reconstruits. Certains éléments graphiques, palettes et animations peuvent
différer de l'original. Les formules physiques des améliorations restent provisoires.

## Construire

Code : `src/`. Tests : `tests/`. Le programme utilise C++17 et Raylib 6.2.
Il n'utilise pas les bibliothèques Android `libyoyo.so` à l'exécution.

Les ressources peuvent être restaurées depuis le paquet Windows vérifié :

```bash
python3 native/game/tools/restore_assets.py --destination native/game/assets
```

L’archive est contrôlée par SHA-256 ; un fichier existant différent est refusé.
Le paquet 0.4.0 inclut les pneus, effets et 94 sons. Pour régénérer les
métadonnées depuis les exports d’origine, dans l’environnement préparé :

```bash
PCR_BACKGROUND_OUTPUT=/workspace/native-runtime/backgrounds.json \
  /workspace/tools/utmt-cli-0.9.2.0/UndertaleModCli load \
  /workspace/windows-port/recovered/assets/game.droid \
  --scripts native/game/tools/export_backgrounds.csx
python3 native/game/tools/prepare_assets.py
PCR_AUDIO_OUTPUT=/workspace/native-runtime/game-audio \
PCR_AUDIO_SOURCE=/workspace/windows-port/recovered/assets \
  /workspace/tools/utmt-cli-0.9.2.0/UndertaleModCli load \
  /workspace/windows-port/recovered/assets/game.droid \
  --scripts native/game/tools/export_audio.csx
python3 native/game/tools/prepare_audio.py --source /workspace/native-runtime/game-audio
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
