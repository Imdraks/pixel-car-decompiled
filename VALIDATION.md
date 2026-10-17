# Validation de la distribution Windows par compatibilité

Le jeu reste un APK exécuté dans un profil Android local. Le lanceur Windows
ne recompile pas le code GameMaker YYC et ne fusionne pas les bases 1.2.5 et
Unbound 1.1.80. L'APK Unbound fourni est inclus intégralement et lancé par défaut.

| Vérification | Résultat |
| --- | --- |
| Construction de `PixelCarRacerPC.exe`, Windows x64 | Réussie avec Go 1.27.2 ; format PE32+ et imports Windows vérifiés |
| Vérification statique Go pour Windows | Réussie |
| Identité des APK incorporés | Empreintes SHA-256 identiques aux deux fichiers fournis |
| Téléchargement HTTPS depuis Google par le code du lanceur | Réussi avec Platform Tools Windows ; empreinte et réutilisation du cache vérifiées |
| Installation et réutilisation du SDK Linux depuis les archives officielles | Réussies |
| Installation et réutilisation du SDK Windows depuis les archives officielles | Réussies sous Linux ; les exécutables Windows ne sont pas lancés par ce contrôle |
| Protection de l'extraction ZIP et des fichiers existants | Tests réussis : chemins sortant du dossier refusés, fichiers existants préservés |
| Intégrité des téléchargements | Corruption et troncature refusées par les tests |
| Exclusivité du profil du lanceur | Deux ouvertures simultanées du même dossier refusées |
| Démarrage réel des deux APK | Réussi sous Android 7.1 x86 en émulation logicielle, sans KVM |
| Interactions Unbound | Profil local de test, clavier à l'écran, écran Unbound, menu, options, concession et achat d'un véhicule virtuel exécutés |
| Deux appuis tactiles simultanés | Confirmés dans Android : `Last Raw Touch: pointerCount=2` et `Last Cooked Touch: pointerCount=2` ; appuis utilisables dans le jeu |
| Reconnaissance d'une installation existante | APK installé lu et comparé au SHA-256 de l'APK incorporé ; test réussi |
| Sauvegarde après fermeture et redémarrage complet | Réussie : les fichiers `pcrdata2` et `pcrdatc2` sont présents et leurs empreintes SHA-256 sont inchangées après le redémarrage sans snapshot |
| Fermeture et ouverture suivantes sous Linux | Réussies sans suppression manuelle du verrou : le processus QEMU arrêté a été récupéré et le SDK a ouvert une nouvelle instance du même profil |

Les sorties de validation sont conservées dans `/workspace/analysis/`, notamment
`pc-final-tests.log`, `pc-launcher-all-tests.log`, `pc-windows-sdk-install-test.log`,
`pc-official-download-test.log`, `pc-payload-live-test.log` et
`multitouch-held-input-dump.txt`. Les tests d'intégration optionnels sont activés
explicitement avec les variables `PCR_TEST_*` indiquées dans leurs messages ;
un test ignoré dans une exécution normale n'est pas présenté comme exécuté.

## Limites de la validation

L'environnement de construction est Linux. Le lancement du binaire sur un PC
Windows 10/11, l'accélération WHPX, le rendu par le GPU Windows, le réglage F8
via les API de fenêtres Windows et l'audio Windows restent à vérifier sur cette
plateforme. Le protocole tactile sous-jacent est validé dans Android.

Une course complète et les services en ligne, publicités, achats intégrés et
connexions à des comptes n'ont pas été validés. Aucun compte personnel n'a été
connecté ; les profils créés ici servent uniquement aux essais et ne sont pas
incorporés à la distribution.

L'image Android 11 initialement essayée en mode logiciel a présenté des blocages
de l'interface système. Elle a été remplacée dans le produit par l'image Android
7.1 x86. Le mode logiciel utilise un seul processeur virtuel ; le lancement
normal Windows utilise l'accélération disponible et le GPU automatique.

Le test de réouverture a détecté puis conduit à corriger une fermeture trop
rapide du processus parent de l'émulateur. Le lanceur attend désormais sa
terminaison normale avant de recourir à une fermeture forcée. Les seuls
verrous anciens retirés pendant le dépannage appartenaient aux émulateurs
de test dont les processus étaient confirmés arrêtés ; les sauvegardes et
les images de données ont été préservées.

Dans le conteneur Linux, le lanceur adopte aussi les processus orphelins de
l'émulateur et récupère uniquement le processus QEMU associé à son propre
profil. Le test réel de récupération d'un processus enfant est réussi.
