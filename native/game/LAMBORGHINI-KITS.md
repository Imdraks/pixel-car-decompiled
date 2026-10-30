# Lamborghini : Aventador 086 et Huracán 188

| Banque | Nº affiché | Identité retenue | Base de l’identification |
| --- | ---: | --- | --- |
| Unbound | 086 | Lamborghini Aventador | Revue de la silhouette et des onze familles de kits ; comparaison avec les photographies de référence Aventador |
| Unbound | 188 | Lamborghini Huracán | L’utilisateur a confirmé le sprite exact montré dans la planche Unbound |

Aucune année ni finition précise n’est certifiée. La précédente étiquette
« Huracán » sur la 086 était erronée. La 188 n’était pas une Gallardo à retirer :
elle est rétablie comme Huracán. Les deux voitures gardent leurs identifiants
`pcr-unbound-085` et `pcr-unbound-187`, et leurs kits propres.

Si la version 0.18.2 avait retiré la 188 du garage, elle peut être reprise dans le
showroom : sa préparation archivée est retrouvée. Les configurations nommées sont
également chargeables à nouveau. Les copies `.pre-retired-188.bak` restent intactes.
Aucune voiture n’est ajoutée automatiquement à un garage déjà migré, et la limite
de huit places reste appliquée.

Les numéros sont propres à chaque banque. Dans Original, la 086 représente une
Audi RS7 et la 188 une Audi R8. Les variantes Underground 188/189 restent signalées
comme non identifiées ; elles ne sont pas assimilées aux Lamborghini Unbound sur
la seule base de leur numéro. La revue des 191 silhouettes Original n’a pas
identifié de Huracán ou d’Aventador parmi les carrosseries de base.

La revue couvre **573 carrosseries de base** dans les trois banques. Les
**17 190 images** de carrosserie, masques et pièces de kits concordent avec les
textures Android dont les empreintes sont vérifiées. Les planches des hypercars
candidates ont aussi été examinées avec leurs onze familles de kits. Les flancs
Fortune peuvent redessiner portes et toit directement dans les ressources du mod.
Cette vérification confirme l’import des images ; elle ne certifie pas une année,
une finition ou une équivalence de rendu avec l’exécution Android.

Les fichiers d’images, les pièces et sons existants restent identiques. Les valeurs
mécaniques héritées des emplacements source ne sont pas des fiches constructeur
validées pour les Lamborghini identifiées visuellement.

```sh
python native/game/tools/audit_lamborghini_kits.py --all-bodies --output /tmp/audit-lamborghini
```

Le rapport `audit-kits-lamborghini.json` est livré avec Windows. Les planches
reproductibles sont écrites dans le dossier choisi. Référence photographique de
la famille Aventador : [Lamborghini Aventador SVJ](https://www.lamborghini.com/en-en/history/aventador-svj).

La même revue a identifié, sur l’image fournie ensuite par l’utilisateur, la
**Ford GT 2017 dans la conversion Fortune de l’emplacement Unbound 187**. Elle
est ajoutée comme voiture distincte. Voir [Ford GT 2017](FORD-GT-2017.md).

## Phares des carrosseries remplacées

Les anciens masques de phares et de feux, restés identiques à ceux de la voiture
Original, ne sont plus superposés aux modèles remplacés dans les mods. Les calques
qui ont réellement été adaptés sont conservés. La couleur blanche des carrosseries
et les optiques intégrées aux nouveaux dessins ne sont pas supprimées.
