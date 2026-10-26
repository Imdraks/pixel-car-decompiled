# Ancrages et rendu des accessoires — 0.9.0

Les pots arrière, galeries, sièges et crochets utilisent maintenant les positions
par carrosserie de `scr_part_positions`, récupérées statiquement dans les deux
bibliothèques fournies. Les 382 enregistrements contiennent 4584 coordonnées,
avec les adresses des écritures dans `native/evidence/merged/attachment-positions.json`.
Le script `native/tools/recover_attachment_positions.py` vérifie les empreintes
des deux binaires et les comparaisons de carrosserie avant de générer le tableau.

Les coordonnées sont relatives à l’origine de la voiture (62,58). Le rendu
soustrait aussi l’origine du sprite : pot (40,62), galerie (60,45), siège (16,16),
crochet (12,13). Les positions fixes communes à toutes les voitures sont retirées.
Le siège et l’arceau se dessinent derrière les vitres translucides et les portes.
Les cargaisons disposent toujours d’une marge de 64 pixels au-dessus du toit.
Les écrous forment maintenant une couronne de cinq points autour du moyeu.

Les pots sont visibles après la carrosserie, y compris le pot de base. Leur
transformation est partagée avec les sorties NOS/flammes. Le placement arrière
suit aussi les dimensions du pare-chocs équipé ; le capot et les sorties latérales
utilisent la silhouette de la bonne version et le bas de caisse choisi. Les
18718 configurations corps/pot des deux banques, et 243334 cas avec les variantes
de kits, sont vérifiés. Les bouches/directions des pots et ces ajustements de
surface restent des adaptations natives, et non une récupération complète du
rendu Android.

Un kit sans image compatible pour la carrosserie conserve désormais le panneau
d’origine. Seul le kit Delete retire intentionnellement les panneaux. Les pièces
avant/arrière/côtés séparées priment sur le kit complet ; choisir CONFIGURATION
DE BASE pour ces catégories permet de revenir au kit complet.

## Contenu visuel transféré

- **F8 au garage** : arceau issu de `sp_rollcage`, adapté à chaque carrosserie.
- **K au garage/en conduite** : phares ; images d’éclairage d’origine, avec les
  variantes Fortune, Drag Pro et Tuner adaptées au kit.
- Sièges Original et Unbound disponibles dans la même catégorie, avec leur vraie
  image. Les 24 variantes Original sont conservées séparément quand les images
  diffèrent ; leurs noms et attributs de base restent ceux du catalogue source.

Arceau, phares et choix audio sont sauvegardés. Ces options ne changent pas le
modèle physique. Le rendu des matériaux et certains effets restent natifs ;
l’équivalence visuelle complète avec Android n’est pas démontrée.
