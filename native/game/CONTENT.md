# Catalogue fusionné Original + Unbound — 0.9.0

Un seul garage et une seule liste par catégorie remplacent les boutons globaux
Original/Unbound. Sous chaque pièce, une mention indique **ORIGINAL**, **UNBOUND**
ou **ORIGINAL + UNBOUND**. Les pièces communes ne sont pas dupliquées ; les
variantes d’apparence réellement différentes restent sélectionnables ensemble.

## Contenu et accès PC

- **196 pièces de performance** : les onze catégories F1–F6, dont les turbos
  Diamond et Ruby présents seulement dans le catalogue original.
- **521 jantes nommées**, dans F2 : assemblage des couronnes/moyeux et rayons
  selon les 521 recettes récupérées. Pneus et effets ne sont pas proposés comme
  jantes. Les anciens identifiants valides restent lisibles dans les sauvegardes.
- **503 choix esthétiques**, dans F7 / STYLE : les 479 entrées du catalogue et
  les 24 images de sièges Original différentes de celles d’Unbound.
  Les seize catégories regroupent peintures, livrées, ailerons, galeries,
  kits complets, pare-chocs avant/arrière, bas de caisse, freins, sièges,
  crochets, écrous, vitres, teintes de phares/feux et ampoules.
- **239 ensembles de carrosserie** dans un sélecteur unique : 191 bases, plus
  les 48 variantes Original qui diffèrent par la carrosserie, les feux, un kit
  ou un aileron. Il s’agit de variantes visuelles, pas de 239 modèles mécaniques
  distincts. Les seules images de carrosserie principales représentent 201
  images distinctes ; les autres différences concernent les calques associés.
- **F8** : arceau. **K** : phares. Voir [ATTACHMENTS.md](ATTACHMENTS.md) pour les
  nouveaux ancrages et les limites des adaptations de rendu.
- Deux banques de **94 sons** sont conservées sans réencodage. Le bouton
  **SONS : ORIGINAL / UNBOUND**, dans le panneau SON DU MOTEUR, choisit la banque
  indépendamment de la voiture et de l’équipement. AUTO moteur/son reste une
  association native approximative ; les profils manuels sont conservés.

Les 1196 équipements abstraits des boutiques sont transférés. Le sélecteur compte
1220 choix après conservation des 24 variantes de sièges supplémentaires.
Les noms, attributs et adresses source figurent dans `native/evidence/merged/` ;
les atlas sont vérifiés par SHA-256 avant réassemblage. Les variantes de siège
sont des choix d’image supplémentaires, pas de nouvelles performances inventées.

Recherche Ctrl+F, aperçu, Entrée/double-clic, molette et sauvegarde restent actifs.
Tab / Maj+Tab parcourent les catégories esthétiques. Les sauvegardes précédentes
conservent leur apparence et leur banque audio lors de la migration. L’équipement
reste libre ; la progression, les achats, courses/tournois et éditeur de livrées
ne sont pas encore reconstruits.

## Ressources et reproduction

- `catalog.json` : littéraux des deux boutiques ; 1195 lignes communes et deux
  turbos supplémentaires dans l’original.
- `rims.json` : identifiants, cinq champs et adresses des recettes de jantes.
- `attachment-positions.json` : positions des pièces pour les deux banques.
- `validation/merged-content.json` et `merged-audio.json` : comptages/empreintes.
- `tools/prepare_content.py`, `generate_catalog.py`, `prepare_base_audio.py` et
  `native/tools/recover_attachment_positions.py` : préparation et récupération.

Après les préparations initiales, générer les coordonnées puis le contenu et le
catalogue. Les exports `original-items.json`, `unbound-items.json` et
`original-parts-rescan.json` doivent être dans le dossier `--exports`. Python,
Pillow, UndertaleModTool et Ghidra servent uniquement à la préparation ; le jeu
Windows est natif C++ et fonctionne hors ligne.

Extraire **tout le ZIP**, y compris les atlas `content-*.png` et `audio-original`.
Les matériaux/placements restent partiellement adaptés nativement ; la physique
et son absence d’équivalence Android démontrée sont détaillées dans PHYSICS.md.
