# Pots et points d’émission natifs — 0.9.1

## Correction 0.16.5

Un pot arrière pouvait se superposer au pneu ou aux rayons : il était dessiné
après les roues, avant la carrosserie. Le rendu applique maintenant l’ordre
**pot arrière → roues → carrosserie**. Les pots de premier plan conservent leur
couche prévue. Les ancrages source et les bouches de particules ne sont pas déplacés.
Le pot suit le même mouvement de caisse pendant le cabrage ; la suspension et
les roues gardent leurs transformations propres.

Un contrôle GPU compare les pixels à l’intérieur de la roue avec et sans le
pot arrière, sur quatre cas Original/Unbound, hauteur d’origine, abaissée,
rehaussée et cabrage. Ils doivent être identiques, tandis que la sortie du pot
reste visible à l’extérieur. Le correctif concerne toutes les vues utilisant
le rendu de voiture : accueil, showroom, pièces, miniatures et conduite.


Les 48 échappements équipables et le pot de base utilisent leurs images Unbound
originales. Ils apparaissent au garage, au menu et en conduite. Leur placement
et les points d'émission partagent la fonction `placeExhaust` : changer de
carrosserie, de suspension ou de voie déplace ensemble le pot et ses effets.

Les sorties arrière, latérales, verticales et de capot ont des positions et
orientations propres. Les versions doubles et triples émettent à chaque bouche.
Le pied de chaque image de flamme animée est mesuré dans ses pixels d'origine.
Les retours de flamme sont teintés chaud ; le NOS forme un jet bleu visible.
Les flammes et le NOS restent attachés au pot pendant leur durée de vie. Les
fumées de pneus et étincelles continuent de suivre le sol et leur propre mouvement.

Les pots utilisent les deux ancrages de `scr_part_positions` et les types de
`exhaust_get_type`, récupérés dans les deux banques. Comme dans le code original,
les types arrière 2/3 sont derrière la carrosserie ; les types latéraux 1/4 sont
devant, à `part_exhaust2_x/y`. Le placement estimé au milieu du bas de caisse et
les corrections artificielles selon les kits sont supprimés. Les trois pots de
capot conservent leur adaptation native. Voir [ATTACHMENTS.md](ATTACHMENTS.md)
pour les adresses source et les limites.
Les contrôles couvrent 18718 configurations corps/pot et 243334 variantes de
fitting avec les kits. Le défilement, l’orientation et l’attachement des effets
restent vérifiés en conduite et pendant les changements de voie.

Les captures de validation VFX utilisent un état contrôlé pour montrer les
flammes et le NOS simultanément ; elles ne servent pas de mesure physique.
