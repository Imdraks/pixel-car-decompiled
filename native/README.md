# Étude du portage natif Windows — 26 octobre 2026

Depuis cette étude, une [première reconstruction native du mode libre](game/README.md)
a été implémentée. Les observations ci-dessous décrivent la phase d'analyse
précédant ce prototype ; elles ne sont pas une validation de fidélité au jeu original.

L'objectif est un jeu exécuté directement sous Windows, sans émulateur Android.
La release `v0.1.0-windows-preview` et le dossier `pc/` correspondent au prototype
précédent utilisant Android. Ils ne réalisent pas cet objectif.

Les APK permettent de récupérer des ressources, la structure du jeu et des
fragments de logique. **Une reconstruction native progressive est une piste
concrète ; une conversion complète ou automatique n'est pas démontrée.** Aucun
jeu natif Windows jouable n'est produit par cette étude.

## Ce qui est établi sur les fichiers fournis

| Observation | Unbound 1.1.80 | Original 1.2.5 |
| --- | ---: | ---: |
| Génération détectée par UndertaleModTool | GMS1 | GMS2 |
| Compilation YYC détectée par UndertaleModTool | oui | oui |
| Bloc `CODE` dans `game.droid` | absent | absent |
| Sprites | 377 | 530 |
| Objets | 101 | 114 |
| Salles | 13 | 13 |
| Instances placées dans les salles | 111 | 113 |
| Fonctions de jeu exportées en x86, type ELF `STT_FUNC` | 698 | 2 534 |
| Événements d'objet associés par nom exact | 419 | 614 |
| Objets possédant ces événements nommés | 95 | 114 |

Les 6 objets d'Unbound sans fonction événementielle nommée ne sont pas déclarés
inutiles : leur comportement peut dépendre de l'héritage ou d'autres objets.
Les listes de scripts représentent des métadonnées, pas du GML récupéré.

La précédente estimation de 3 822 « symboles de jeu » pour l'original mélangeait
des fonctions avec des données, notamment les pointeurs `g_FUNC_gml_Script_*`.
Le présent inventaire distingue explicitement les fonctions ELF des données.
La somme des tailles des symboles de fonctions n'est pas une mesure de couverture
de décompilation ni un nombre de lignes source.

Les deux APK contiennent `lib/x86/libyoyo.so`. L'original comporte aussi une
bibliothèque x86-64, mais Unbound ne contient pas cette architecture. Le code
x86 de la voiture existe donc bien : il n'est pas nécessaire de partir d'ARM.
Cela ne rend pas une bibliothèque ELF Android directement chargeable par Windows.

L'inventaire des extensions `.gml`, `.yy`, `.yyp`, `.gmx`, `.cpp`, `.cc`, `.c` et
`.h` n'a trouvé aucun fichier source candidat dans les APK. Les bibliothèques
x86 examinées n'ont pas de section de débogage `.debug*`.

## UndertaleModTool : utile, testé, avec une limite précise

[UndertaleModTool 0.9.2.0](https://github.com/UnderminersTeam/UndertaleModTool/releases/tag/0.9.2.0)
a réellement ouvert les deux `game.droid`. Les résultats `info` sont conservés
dans `evidence/*/utmt-info.txt`. L'outil indique `Is YYC - True` pour les deux.

Un exporteur C# en lecture seule a extrait les noms des scripts, les objets,
leurs sprites et parents, les salles et les instances placées. Les deux exports
ont réussi. Ils sont disponibles dans `evidence/*/utmt-structure.json`.
Ils ont ensuite été associés aux événements compilés par correspondance exacte
des noms, dans `evidence/*/reconstruction-map.json`, sans objet natif non associé.

La [documentation officielle](https://github.com/UnderminersTeam/UndertaleModTool#main-features)
précise que l'édition de code GML VM ne prend pas en charge YYC. Dans la version
testée, la commande `dump` quitte même explicitement en mode YYC en indiquant
qu'il n'y a pas de code à exporter. L'exporteur fourni ici utilise donc `load`
avec un script de lecture, sans option d'enregistrement du fichier d'origine.

L'outil peut aider à préparer un projet Windows en récupérant les ressources et
la structure. Il ne restitue pas, à lui seul, les fonctions compilées dans
`libyoyo.so`. Modifier des textures avec cet outil et porter le moteur sont
deux opérations distinctes.

## Décompilation native ciblée : trois résultats réels

Ghidra 12.1.4, avec un JDK Temurin 21 complet, a produit du pseudocode pour :

| Fonction Unbound | Offset dans le fichier ELF | Taille du symbole |
| --- | --- | ---: |
| `gml_Script_ease_linear` | `0x004d3af0` | 672 octets |
| `gml_Object_ob_car_Step_2` | `0x005afe90` | 472 octets |
| `gml_Script_scr_car_var` | `0x00496c50` | 6 004 octets |

Les fichiers sont dans `evidence/unbound/selected-decompile/`. Le rapport
`coverage.txt` donne les adresses réellement chargées et les symboles observés.
La correspondance utilise les offsets de fichier : Ghidra applique ici un
décalage de chargement de `0x10000`. Confondre offset ELF et adresse d'analyse
peut sélectionner une autre fonction.

Cette passe ciblée n'effectue pas l'auto-analyse de tout le programme. Le
pseudocode conserve des types inconnus, des appels non typés et des artefacts
de pile, notamment autour des retours de structures C++. **Ces fichiers ne sont
pas des sources C compilables ni une preuve d'équivalence fonctionnelle.**

Une tentative distincte via REA 6.5.0/Ghidra a terminé l'auto-analyse Ghidra
environ 655 secondes après son lancement, puis est restée dans la phase de
correction des fonctions sans retour de REA. La requête a expiré après
1 200 secondes sans résultat de décompilation exploitable. Ce parcours complet
est donc **non validé** pour cette bibliothèque ; les trois résultats ci-dessus
proviennent de la passe Ghidra ciblée, vérifiée séparément. Le journal d'échec
est conservé dans `evidence/rea-full-probe.log`.

Le désassemblage annoté par les relocations GOT complète ces résultats. Par
exemple, les appels d'opérateurs dans `ease_linear` permettent de reconnaître
le chemin numérique `(argument[2] * argument[0]) / argument[3] + argument[1]`.
Cela ne valide pas les comportements génériques de `YYRValue`, les erreurs ou
les cas particuliers du moteur.

L'événement principal `gml_Object_ob_car_Step_0` représente à lui seul 592 716
octets de code machine. Il n'a pas été reconstruit dans cette étude. Le script
de base d'objets du magasin dépasse également 1 Mo. Récupérer trois fonctions
ne permet donc pas de déduire que le reste du jeu est déjà portable.

## Pistes externes vérifiées

| Projet | Constat | Conséquence pour ces APK |
| --- | --- | --- |
| [UndertaleModTool](https://github.com/UnderminersTeam/UndertaleModTool) | Lecture des deux fichiers et export de structure réussis | À utiliser pour les ressources et la structure |
| [OpenGM](https://github.com/misternebula/OpenGM) | Sa documentation cible les jeux non-YYC | Ne fournit pas le code absent de `game.droid` |
| [YYC Toolbox](https://github.com/Valkyrians/yyc-toolbox) | Le décompilateur est indiqué comme retiré ; outil d'injection/modification du runner | Pas de conversion Android vers Windows démontrée |
| [YYC-DEC](https://github.com/shayderrr/YYC-DEC) | L'arbre public examiné ne contient qu'un README | Aucun décompilateur public à exécuter dans ce dépôt |
| [kwik-yyc](https://github.com/kwik-gms2/kwik-yyc) | Prototype pour ELF64 x86-64 Linux ; émet aussi des corps incomplets ou de secours | Son module de découverte refuse l'ELF32 Unbound ; zéro entrée récupérée sur l'ELF64 de l'original |
| [gmloader-next](https://github.com/JohnnyonFlame/gmloader-next) | Chargeur ELF et couche de compatibilité Android, avec des implémentations ARM | Pas un port Windows natif prêt à l'emploi pour ces APK |

Le test `kwik-yyc` compile et exécute uniquement ses modules de lecture ELF et
de découverte des fonctions, à la révision conservée dans
`evidence/research-provenance.json`. Il ne valide pas son compilateur complet.
Les sorties et codes de retour sont dans `evidence/kwik-probe-results.json`.
Les conclusions documentaires sur les autres moteurs ne constituent pas des
essais d'exécution de Pixel Car Racer sur ces moteurs.

## Stratégie recommandée pour le natif

1. Construire une première version native d'Unbound, avec ses propres indices
   de ressources, avant d'intégrer des fonctionnalités de la base 1.2.5. Cela
   évite de mélanger immédiatement deux générations de moteur et de données.
2. Utiliser les atlas, sons, objets et salles exportés pour reconstruire le
   projet et son affichage. Les ressources seules ne constituent pas le jeu.
3. Récupérer les identifiants de variables, les types `YYRValue`, les événements
   et les appels du moteur nécessaires à une seule course. Reconstruire ensuite
   le comportement de la voiture : régime, rapports, couple, adhérence et
   chronométrage, en distinguant ce qui est observé de ce qui est réimplémenté.
4. Implémenter ces systèmes dans un moteur compilable pour Windows, ou dans un
   projet GameMaker récupéré/reconstruit. Remplacer les dépendances Android par
   des services Windows pour le rendu, le son, les entrées et les sauvegardes.
5. Valider les calculs et une course complète avant de restaurer le garage,
   l'inventaire, la progression et les différences fonctionnelles d'Unbound.

Le projet source GameMaker d'Unbound, s'il devient disponible, permettrait de
reconsidérer la voie directe de recompilation. Avec les seuls APK, le travail
établi ici reste une rétro-ingénierie et une reconstruction, pas un export
automatique vers `.exe`. Aucun délai fiable de reconstruction complète n'est
déduit de cet échantillon.

Une adaptation ELF/ABI vers Windows sans système Android complet constitue
une autre piste de recherche, mais elle réutiliserait encore le moteur Android
et nécessiterait un chargeur et des remplacements d'API. Elle n'est pas retenue
comme réalisation du portage natif demandé, et n'a pas été implémentée.

## Reproduire les vérifications

Les outils ci-dessous sont des scripts d'analyse ; aucun ne lance le jeu.
Les APK, bibliothèques, SDK et exécutables d'analyse ne sont pas ajoutés à Git.

```bash
python3 native/tools/inventory_native.py \
  --unbound /chemin/Unboundtester.apk \
  --original /chemin/original.apk \
  --output /chemin/analyse

PCR_AUDIT_OUTPUT=/chemin/analyse/unbound/utmt-structure.json \
  /chemin/UndertaleModCli load /chemin/unbound/game.droid \
  --scripts native/tools/export-structure.csx
# Répéter l'export pour original/utmt-structure.json.
python3 native/tools/map_reconstruction.py --root /chemin/analyse
```

Pour la décompilation ciblée, lire `tools/SelectedYYC.java` et utiliser Ghidra
12.1.4 avec un JDK 21 complet. Les offsets sont propres à l'empreinte Unbound
consignée dans l'inventaire. Le script vérifie les noms de fonctions avant de
décompiler. Les empreintes des téléchargements officiels sont conservées dans
`evidence/tool-downloads.json`.

Les APK et `game.droid` d'origine sont conservés à l'identique. Cette étude
statique n'a exécuté ni Android, ni émulateur, ni nouveau jeu Windows natif.
