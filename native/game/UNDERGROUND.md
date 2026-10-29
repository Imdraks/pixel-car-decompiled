# Original, Unbound et Underground — 0.17.0

Le catalogue unifié affiche trois origines : **Original**, **Unbound** (y compris
les moteurs et pièces importés du tableau NFS Unbound) et **Underground**.
Les badges composés signalent les ressources identiques présentes dans plusieurs
packs. Les identifiants historiques des voitures, pièces et sauvegardes sont conservés.
Le garage reste limité à huit voitures ; retirer une voiture conserve sa préparation archivée.

## Contenu intégré

- 430 variantes de véhicules : les 239 précédentes et 191 ensembles Underground.
  Un ensemble comprend aussi les variantes de carrosserie, phares, feux et ailerons.
  Cela ne signifie pas 430 modèles automobiles différents.
- 1 826 choix d'équipement : 524 pièces mécaniques, 735 éléments cosmétiques et
  567 jantes. Les ajouts sélectionnables comprennent 232 éléments cosmétiques,
  46 jantes et 28 variantes d'échappements/pneus. Les images identiques sont réutilisées.
- Palette Underground, peintures, habillages, sièges, accessoires, kits, éclairage,
  jantes composées à partir des recettes source et sorties d'échappement.
- Cinq décors de garage Underground et ses couches ciel/montagne/ville en conduite.
- Banque audio Underground : 94 associations, dont 75 fichiers partagés et 19 sons
  différents (moteurs, bruitages, ambiances et musique). Dans « Son de l'échappement »,
  le bouton SON(S) parcourt Original, Unbound et Underground. Les moteurs simulés
  continuent à utiliser leur pack physique en mode automatique ; les profils manuels
  permettent d'écouter les échantillons de la banque choisie.
- Huracán Unbound 086 et Gallardo Unbound 188 identifiées selon la confirmation utilisateur.

La recherche accepte aussi l'origine : taper « Underground » dans le showroom ou
un catalogue de pièces permet de retrouver ses éléments. Les pièces restent
triées de Basic à Elite, puis Contrebande.

## Équilibre et conservation

Le `libyoyo.so` x86 fourni est strictement identique à celui du pack Unbound :
SHA-256 `fb3726e175e7d1c643e0ddac1ec1a365901c4d52a16ded97e89fd672f6a9e9cc`.
Les statistiques de boutique et les règles compilées sont donc partagées.
Une variante Underground conserve puissance, poids et rareté de son équivalent,
sans multiplicateur lié au pack. Les swaps restent universels ; turbo et
compresseur restent exclusifs. La physique native et ses limites restent documentées
dans PHYSICS.md : il ne s'agit pas d'une équivalence certifiée au moteur Android.

Les 650 anciens fichiers restent présents : 649 ressources sont inchangées et
leur index de provenance est étendu. Quatre atlas et 19 sons
s'ajoutent. Les fichiers audio source sont conservés dans l'extraction de travail ;
16 copies de jeu sont atténuées pour donner une marge au décodage. Les 19 copies
sont réellement décodées et leur crête vérifiée inférieure à 0,99.
La musique reste exclusivement dans les menus, jamais en conduite.

## Limites vérifiées

64 silhouettes Underground modifiées restent à identifier : le catalogue les
signale explicitement, sans inventer modèle, année ou finition. Les mécaniques
récupérées des emplacements source sont conservées provisoirement. Les autres
silhouettes partagent l'identification de l'Original et portent la mention Underground.
Les cinq identités incertaines précédentes subsistent, soit 69 variantes à identifier.
Les ancrages arrière/latéraux viennent du code partagé ; les passages de roues
sont mesurés sur les images Underground. Deux cas (indices 22 et 182) conservent
l'ancrage précédent faute d'arc mesurable. Les trois pots de capot utilisent
2 483 ajustements de silhouette propres à Underground.

Le kit latéral Pandem de l'index 183 référence une ligne sous son atlas source.
L'extracteur garde le décalage source et remplit seulement la zone hors image de
transparence. Cette anomalie est inscrite dans `underground-catalog.json`.
Les ressources de modes Android absents ne créent pas de nouveaux modes natifs.
L'interface PC existante est conservée.

## Reproduction de l'import

Assembler `.001`, `.002`, `.003` dans cet ordre et vérifier le CRC du ZIP, puis
extraire l'APK, `assets/game.droid`, ses fichiers audio et `lib/x86/libyoyo.so`.
Utiliser les exporteurs de textures/sprites existants et UndertaleModTool avec
`export_audio.csx` et `export_backgrounds.csx` en lecture seule. Le seul dépassement
TPAG connu ci-dessus doit être rapporté, pas corrigé par déplacement arbitraire.
Ensuite, dans cet ordre :

```sh
python native/game/tools/import_underground.py --root /workspace/underground
python native/game/tools/import_underground_audio.py --audio /workspace/underground/audio
python native/game/tools/prepare_underground_geometry.py --textures /workspace/underground/textures
python native/game/tools/generate_vehicle_catalog.py
bash native/game/build.sh
```

Le premier import sauvegarde ses fichiers de référence dans `build/pre-underground`.
Sur une nouvelle copie, le générateur reprend les sources de la 0.16.5 par leur
commit exact. Il ajoute des atlas sans réécrire les atlas précédents. FFmpeg et
Pillow sont nécessaires aux imports ; le jeu Windows ne les requiert pas.
Les rapports sont `underground-catalog.json`, `validation/underground-audio.json`
et `validation/underground-hoods.json`.
