# Contenu fusionné Original 1.2.5 + Unbound — 0.8.0

Le garage utilise maintenant le catalogue des deux APK fournis, lu statiquement
sans exécuter Android ni le moteur YYC. L’équipement reste libre.

## Disponible et accès PC

- **196 pièces de performance**, dans les onze catégories précédentes. Les deux
  turbos de l’original absents de la boutique Unbound sont ajoutés :
  Reddy T60D (Diamond) et Reddy T60AD (Ruby). Leurs statistiques littérales sont
  conservées ; turbo et compresseur restent exclusifs.
- **521 jantes avec leurs vrais noms**, dans F2 → Jantes : Four Racing, Sleepers,
  Welds, TE38, etc. Elles assemblent les couronnes/moyeux de `sp_adv_lip` et les
  rayons de `sp_adv_rims`, suivant les 521 recettes récupérées dans
  `scr_rim_setup`. Le nombre de rayons et leurs images ne sont pas inventés.
  Les ombres/reflets ne sont jamais des pièces indépendantes.
- **479 éléments esthétiques**, accessibles par **F7** ou **STYLE / ACCESSOIRES**.
  Les flèches de l’en-tête parcourent seize catégories : peinture, livrées,
  ailerons, galeries/cargaisons, kits complets, pare-chocs avant, pare-chocs
  arrière, bas de caisse, freins, sièges, crochets, écrous, vitres, teinte des
  phares, teinte des feux et ampoules. Tab / Maj+Tab changent de catégorie.
- Les boutons **ORIGINAL 1.2.5 / UNBOUND** choisissent les images de carrosserie
  et d’accessoires de chaque version. Les deux banques ont 191 carrosseries,
  dont 10 images de carrosserie différentes : ce sont 201 images distinctes,
  et non 382 voitures uniques. Les ressources identiques sont dédoublonnées.
- **Deux banques de 94 sons**, sélectionnées par les mêmes boutons : les
  échantillons de l’original et ceux du mod sont conservés sans réencodage.
  Les 188 fichiers ont des identifiants/noms compatibles, mais des octets
  différents. Les profils moteur manuels restent disponibles ; AUTO conserve
  son association native approximative.

Recherche Ctrl+F, aperçu sans équipement, Entrée/double-clic, retrait par
CONFIGURATION DE BASE, molette et pagination restent disponibles. Le choix de
banque, les jantes nommées et les seize catégories sont sauvegardés. Choisir une
banque ne supprime pas les pièces de l’autre : la boutique est commune.
Les pneus de performance sont conservés séparément des jantes et composés avec
elles dans les vignettes et sur la voiture. Frein à main Espace inchangé.

Les 23 anciens identifiants de jantes valides restent lisibles dans les
sauvegardes ; la nouvelle boutique propose uniquement les 521 styles nommés du
catalogue. Les anciens calques invalides sont réparés sans supprimer l’équipement.

## Ce qui est reconstruit nativement

Les pièces sont visibles au garage et en conduite. Les kits/ailerons utilisent
les images propres à chaque carrosserie ; galeries, sièges et crochets utilisent
les ressources d’accessoires. Les freins et écrous se dessinent dans les roues.
Le composite dispose d’une marge au-dessus du toit pour conserver les cargaisons.

Le masque de peinture/livrée, la teinte des vitres/feux et certains placements
sont des adaptations natives. Leur équivalence pixel par pixel avec les shaders
et coordonnées du jeu Android n’est pas établie. Certains accessoires peuvent
nécessiter un ajustement selon la carrosserie ; la transformation d’un kit ne
récupère pas les statistiques d’origine de la voiture. Ces éléments esthétiques
n’ajoutent pas de puissance et ne modifient pas la calibration physique actuelle.

Cette fusion couvre les **1196 équipements des boutiques** (1197 lignes source,
moins l’option None). Elle ne reconstitue pas la progression, les achats, les
courses, les tournois, le dessin libre de livrées ni tous les services du jeu.
Les valeurs de performance suivent toujours le modèle décrit dans PHYSICS.md
et PERFORMANCE.md ; la fidélité physique Android reste à établir.

## Provenance et reproduction

- `native/evidence/merged/catalog.json` : noms, valeurs et adresses d’insertion
  des deux catalogues. 1195 lignes communes, deux turbos supplémentaires dans
  l’original ; aucune duplication artificielle des entrées communes.
- `native/evidence/merged/rims.json` : chaque identifiant source, ses cinq champs
  et les adresses des comparaisons/écritures YYC. Images des deux banques
  vérifiées par SHA-256 avant réassemblage.
- `validation/merged-content.json` : comptages et empreintes des atlas sources.
- `tools/prepare_content.py` : assemblage radial au plus proche pixel, dédoublonnage,
  atlas et métadonnées. `native/tools/recover_part_catalog.py` accepte les deux
  binaires vérifiés ; `native/tools/recover_rim_recipes.py` récupère les recettes.

Après les préparations des ressources, sons et interface, lancer
`python3 native/game/tools/prepare_content.py`, puis
`python3 native/game/tools/generate_catalog.py`. Les exports statiques
`original-items.json`, `unbound-items.json` et `original-parts-rescan.json`
doivent se trouver dans le dossier indiqué par `--exports`.

Extraire **tout le ZIP** : les six atlas `content-00.png` à `content-05.png` sont
nécessaires. Le jeu distribué reste un exécutable C++ Windows natif ; Python,
Pillow, UndertaleModTool et Ghidra ne sont utilisés que pour la préparation.
