# Ancrages et rendu des accessoires — 0.13.0

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
Le canevas 225 × 138, décalé de (3,66), couvre les accessoires des deux banques.
Les écrous forment maintenant une couronne de cinq points autour du moyeu.

Les échappements suivent les deux branches d’ancrage et l’ordre de dessin du
`gml_Object_ob_car_Draw_0` original, confirmés dans Unbound : types 2/3 derrière
la carrosserie à `part_exhaust_x/y`, types 1/4 devant à `part_exhaust2_x/y`.
Les types sont récupérés séparément dans les deux `exhaust_get_type` (51 images,
tableaux identiques), avec les cibles des branches dans
`native/evidence/merged/exhaust-rules.json`. Le script reproductible est
`native/tools/recover_exhaust_rules.py`.

Les sorties latérales 40,41,44–47 et les grands pots latéraux 32,34,37–39
utilisent donc le second ancrage. Les pots 33,35,36 et le Downpipe 43 restent
sur le premier, derrière la carrosserie. Les ajustements estimés de bas de
caisse/pare-chocs sont supprimés : ces branches d’origine ne les ajoutent pas.
Le pot et ses sorties NOS/flammes partagent toujours exactement la même
transformation, avec le mouvement de suspension.

Les 18336 transformations des images 0–47 sur les 191 carrosseries des deux
banques sont vérifiées contre les coordonnées récupérées, avec les couches de
dessin et les racines des particules. Les contrôles existants couvrent aussi
18718 configurations corps/pot et 243334 variantes avec kits.
Les bouches/directions et les trois pots de capot (type 0) restent adaptés
nativement : aucune des quatre branches de dessin récupérées ne dessine ces
images de capot, et leur rendu Android complet n’est pas encore reconstitué.
En 0.13, leurs pieds suivent le contour opaque du capot et du kit avant monté.
Voir [CUSTOMIZATION-COMPLETE.md](CUSTOMIZATION-COMPLETE.md) pour les 14898
contrôles de montage et les replis sans capot.

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
