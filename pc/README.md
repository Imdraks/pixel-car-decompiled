# Prototype historique par compatibilité Android

Lanceur Windows x64 pour les deux APK fournis. Unbound est le choix par défaut.
Cette distribution exécute le jeu Android dans un moteur Android local ; elle
ne constitue pas une recompilation Windows native du moteur GameMaker YYC.
Unbound conserve son contenu tel que fourni. L'original 1.2.5 est un choix
séparé, avec ses propres sauvegardes : son code n'est pas fusionné avec Unbound.

## Utilisation Windows

1. Extraire l'archive et lancer `PixelCarRacerPC.exe` pour Unbound.
2. Au premier démarrage, lire et accepter la licence Google Android SDK.
   Le lanceur télécharge les composants depuis Google et vérifie leurs
   empreintes avant extraction. Le jeu lui-même est inclus dans le lanceur.
3. Jouer à la souris. Pour attribuer des commandes clavier : placer le focus
   dans la fenêtre du jeu, presser F8, survoler un bouton avec la souris et
   presser la touche choisie, puis F8 pour terminer. Touches disponibles :
   Z, W, S, Q, D, A, E, Espace, Haut et Bas. Plusieurs touches peuvent être
   maintenues simultanément. Les réglages sont distincts pour chaque version.
4. Fermer la fenêtre Android pour quitter. Le lanceur ne supprime pas les
   sauvegardes et n'utilise pas l'option de remise à zéro des données.

`Jouer-original.cmd` ouvre l'original 1.2.5. Le second fichier `.cmd` force
l'émulation CPU si l'accélération matérielle ne fonctionne pas.

Prérequis : Windows 10/11 x64, 8 Go de RAM conseillés, environ 12 Go d'espace
libre pour les composants, caches et deux profils. Le premier téléchargement
représente environ 780 Mo. L'image Android 7.1 x86 est choisie pour la
compatibilité avec ces versions du jeu. L'accélération via Windows Hypervisor Platform est
préférable ; si elle est indisponible, le lanceur utilise le mode logiciel,
dont le premier démarrage peut prendre plusieurs minutes.

Données et journaux : `%LOCALAPPDATA%\PixelCarRacerPC`. Les profils Android
`PCRUnboundPC_API25` et `PCROriginalPC_API25` sont séparés. Les fichiers de configuration
du clavier sont `keyboard-unbound.json` et `keyboard-original.json`.

L'image Android est une image AOSP sans Google Play. Les achats Google Play
ne sont pas pris en charge ; les autres fonctions en ligne ne sont pas validées.
Voir [`VALIDATION.md`](../VALIDATION.md) pour les contrôles réalisés et leurs limites.

## Sources et construction

Le code du lanceur est dans `pc/`. Il utilise uniquement la bibliothèque
standard Go, sans module externe. La construction effectuée dans cet
environnement utilise Go 1.27.2, Linux x64 vers Windows x64.

Placer les APK fournis dans `pc/payload/unbound.apk` et
`pc/payload/original.apk`. Ils sont exclus de Git et incorporés au binaire
par `go:embed`. Pour construire depuis l'environnement préparé :

```bash
bash /workspace/pixel-car-decompiled/pc/build.sh
```

Le lanceur Linux permet de vérifier le même cycle d'installation et de
démarrage, sans fenêtre :

```bash
pc/build/pixel-car-linux --headless --software \
  --sdk-root /workspace/pc-runtime/linux-sdk \
  --data-dir /workspace/pc-runtime/test-unbound
```

Le lanceur n'installe pas d'outil global ni de service Windows. Il lance son
émulateur sur deux ports locaux libres et le ferme en quittant. Le moteur et
l'image Android sont téléchargés directement de Google sur le PC de
l'utilisateur ; les archives Google ne sont pas redistribuées dans le paquet.

La comparaison et l'extraction des ressources GameMaker sont conservées dans
`/workspace/windows-port/`. Les documents fournis dans les archives ont été
traités comme données à analyser.
