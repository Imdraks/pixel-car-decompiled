# Pixel Car Racer — Unbound Native 0.13.7

La version **0.13.7** remonte progressivement le son du LS/V8 dans les hauts
régimes en conservant le ralenti. La courbe s’applique au fichier sonore partagé
par LS, LSX, LT5 et Hemi. [AUDIO-MIX.md](AUDIO-MIX.md).

La version **0.13.6** corrige le mixage moteur : fondu charge/relâchement sans
désaccordage, pitch moins forcé, niveaux relatifs source et raccord des boucles
qui présentent une coupure nette. [AUDIO-MIX.md](AUDIO-MIX.md).

Dans le garage/customisation : **G** démarre ou éteint le moteur ; maintenir
**Z** accélère jusqu’au rupteur du moteur équipé. Relâcher Z revient au ralenti.
Le moteur reste stationnaire, s’arrête en quittant le garage et ne redémarre
pas automatiquement à la prochaine visite. Pendant une recherche de pièce, G/Z
servent uniquement à saisir du texte. Les préférences audio AUTO/manuelles
sont respectées. Le limiteur du garage est une adaptation native.

La version **0.13.3** permet d’accélérer moteur débrayé avec **Espace** maintenu :
le régime et le son moteur suivent l’accélérateur, les roues arrière restent bloquées,
et le NOS reste coupé. Relâcher Espace réengage le rapport conservé avec une
protection contre le surrégime. **Espace + Z/W/↑**, puis relâcher Espace pour partir.

La version **0.13.2** reprend le curseur bleu **WHEELIE → BALANCED** dans F9,
avec un effet progressif et une sauvegarde indépendante des masses avant/arrière.
Les moyeux suivent maintenant leurs fixations de suspension pendant le tangage ;
compression et détente sont limitées, et les passages de roue suivent la caisse.
Les wheelie bars du DRAG PRO restent fonctionnelles. Voir [DRAG.md](DRAG.md).

La version **0.13.1** corrige le préréglage Drag : lancement amorti, roues au
sol et répartition adaptée à la transmission. Le cabrage volontaire reste dans
le bouton Wheelie séparé. Appliquer **F9 → Drag → Enregistrer** pour remplacer
l’ancien réglage. [DRAG.md](DRAG.md) détaille la correction et la recherche du
code original ; les équations Android complètes ne sont pas encore importées.

La version **0.13.0** ajoute les jantes distinctes par essieu (**F2**, boutons
AV+AR/AVANT/ARRIÈRE), les nuances et matériaux source, les teintes des optiques
et le contrôle des variantes incompatibles. **F7** ouvre les catégories de style.
Les trois pots de capot suivent la surface du capot et du kit installé.
Voir [CUSTOMIZATION-COMPLETE.md](CUSTOMIZATION-COMPLETE.md) pour les fonctions,
les contrôles de toutes les carrosseries et les limites de reconstruction.

La version **0.12.0** ajoute une suspension avec ressorts et amortisseurs,
transfert de charge, cabrage et plongeon. Au garage, **F9** ou **F5 → Réglages
suspension** règle hauteur, rigidité, amortissement, répartition des masses et
wheelie autorisé/limité au sol. Les préréglages Route, Drag et Piste sont inclus.
**ABS et antipatinage** se désactivent séparément dans les paramètres, sous
la ligne du trafic. Appliquer puis Conserver enregistre ces choix.
Voir [SUSPENSION.md](SUSPENSION.md) pour l’utilisation et les limites du modèle.

La version **0.11.0** ajoute le burnout : en **première**, à l’arrêt ou presque,
maintenir **Z/W/↑ + S/↓**. Le frein retient la voiture, les roues motrices tournent
et la fumée prend la couleur des **Burn Slicks** équipés (vert, turquoise,
violet, rose, rouge, orange, jaune, bleu). Les autres pneus gardent une fumée
blanche, même lorsque leurs inscriptions sont colorées.

Maintenir **V** pour le point mort : le HUD affiche **N**, le moteur prend ses
tours sans entraîner les roues. Relâcher V réengage le rapport conservé, avec
un rapport supérieur de sécurité si nécessaire pour éviter un surrégime.
Le NOS reste sur **N** ; Espace reste le frein à main et coupe le burnout.

La version **0.10.0** remplace la voiture mécanique commune par les **191 fiches
d’origine** : masse, puissance, régime, adhérence de châssis et transmission
propres à chaque identifiant. Les noms et incertitudes s’affichent au garage.
Voir [VEHICLES.md](VEHICLES.md) et [PHYSICS.md](PHYSICS.md) : ces paramètres sont
récupérés, mais les équations Android complètes et les fiches constructeur ne
sont pas encore importées. Les deux silhouettes 101 et 154 restent à nommer.

Les anciennes conversions de transmission sont conservées. Pour retrouver la
transmission du modèle, ouvrez TRANSMISSION et choisissez **TRANSMISSION D’ORIGINE**.

La version **0.9.0** réunit Original et Unbound dans les mêmes catégories,
avec la provenance affichée sous chaque pièce. Elle corrige les ancrages des
pots, sièges, galeries et crochets à partir des coordonnées du jeu.
F7 : style, F8 : arceau, K : phares. Voir [CONTENT.md](CONTENT.md) et
[ATTACHMENTS.md](ATTACHMENTS.md).

Cette première reconstruction **native Windows x64** propose un mode libre
jouable avec les ressources d'Unbound. Le programme ne lance ni APK, ni Android,
ni émulateur. Il fonctionne hors ligne après extraction de l'archive.

Ce n'est pas encore le portage complet et fidèle du jeu original : la conduite
et la circulation sont réimplémentées. Les boutiques et les banques visuelles de l’original et du mod sont fusionnées ;
les autres modes et la progression ne sont pas encore reconstruits. Le moteur GameMaker YYC d'origine n'a pas été recompilé.

La version **0.7.0** reprend le garage et le menu de customisation du jeu de
base : atelier, pont élévateur, icônes de catégories, jauges et police pixel
originales, avec inventaire adapté à la souris/clavier. Les statistiques et
la voiture montrent l'aperçu de la pièce avant équipement. Ctrl+F, molette,
F1–F6, Entrée et double-clic accélèrent la navigation ; les choix sont sauvegardés.
Les 194 pièces, 191 carrosseries par banque, 521 jantes nommées et réglages précédents sont conservés.
Voir [GARAGE-PC.md](GARAGE-PC.md) pour les catégories et commandes.

**Espace est le frein à main en conduite**, avec roues arrière bloquées,
ralentissement, fumée arrière et coupure du NOS. Avec l’accélérateur, le moteur
prend librement ses tours, débrayé.
Extraire tout le ZIP pour installer les nouveaux atlas de l'interface.

La version **0.6.0** ajoute **TRANSMISSION** depuis le garage et la customisation :
huit préréglages, dont sept inspirés de boîtes réelles TREMEC et GM, et jusqu'à
**10 rapports**. Deux colonnes de curseurs −/+, vitesse théorique au limiteur,
pont final, temps de passage, mode auto/manuel, traction/propulsion/4 roues
motrices. **ENREGISTRER** sauvegarde ; **ANNULER** abandonne les modifications.
Les étagements constructeur et les adaptations natives sont distingués dans
[TRANSMISSION.md](TRANSMISSION.md).

Les pots d'origine sont maintenant dessinés, avec les points de sortie communs
aux flammes et au NOS : arrière, latéral, capot et sorties multiples. Les jets
restent attachés au véhicule. Voir [EXHAUST.md](EXHAUST.md).

La version **0.5.1** permet de retirer le trafic : **PARAMÈTRES → Trafic en
mode libre → Désactivé → Appliquer → Conserver**. Le choix est sauvegardé et
repris au prochain lancement. Les voitures et leurs collisions sont désactivées ;
la conduite continue normalement. En réactivant le trafic, les véhicules sont
replacés à distance devant vous. Les anciennes sauvegardes gardent le trafic actif.

La version **0.5.0** combine moteur, pièces atmosphériques, ECU, suralimentation,
intercooler et NOS avec le même calcul pour le banc et la conduite. Le garage
montre les HP sans/avec NOS, le gain de la pièce sélectionnée, et un banc de
puissance. **PRÉPA MAX** équipe les meilleures pièces : environ **4438 HP sans
NOS / 4688 HP avec NOS**. Turbo et compresseur restent strictement exclusifs.

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

Les deux banques de 94 fichiers audio sont incluses. Depuis **0.13.4**, AUTO
utilise les associations source des **16 moteurs équipables**, vérifiées dans
les deux bibliothèques Android. La sélection des moteurs stock reste à confirmer.
Les réglages manuels charge/décélération et valve restent prioritaires, avec
préécoute. La hauteur, les volumes et transitions restent natifs.
Voir [ENGINE-AUDIO.md](ENGINE-AUDIO.md) pour les correspondances et les limites.
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
| Z, W ou flèche haut | Accélérer |
| Espace maintenu | Frein à main arrière ; accélérateur autorisé, moteur débrayé |
| S ou flèche bas | Freiner |
| Flèches gauche/droite, Q/A et D | Changer de voie |
| E ou Maj gauche / C | Monter / descendre un rapport |
| F9 au garage | Régler suspension et wheelie |
| V maintenu | Point mort ; relâcher pour réengager |
| 1re + accélérateur + frein | Burnout à l’arrêt ou à très basse vitesse |
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

Le garage permet de choisir parmi **191 images de carrosserie** et **521 styles nommés
de jantes** extraits d'Unbound. Ces nombres ne désignent pas 191 véhicules dont
les statistiques d'origine auraient été reconstruites. Les performances moteur de base
sont communes à cette version. Les points de roue utilisent l’origine des sprites
et leurs passages transparents, vérifiés sur l’ensemble des carrosseries.
L’écran **Transmission**, accessible par l’engrenage sous les statistiques ou
Châssis, choisit entre **TRACTION / PROPULSION / 4 ROUES MOTRICES** pour une
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
- Compteur FPS, son et trafic activé/désactivé en mode libre.

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
python3 native/game/tools/prepare_original_ui.py
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


Avec le **TC désactivé**, prendre des tours avec **Espace + accélérateur** ou
**V + accélérateur**, puis relâcher Espace/V en gardant les gaz, provoque un
patinage selon le couple moteur, le régime initial, les rapports et l’adhérence.
Les roues motrices tournent indépendamment de la vitesse au sol ; la fumée suit
le glissement et conserve la couleur des pneus. Le TC activé régule le départ.
[Calcul natif et limites](DRAG.md#départ-au-rupteur--0133).
