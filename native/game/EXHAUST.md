# Pots et points d’émission natifs — 0.9

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

Les pots arrière utilisent désormais les coordonnées de `scr_part_positions`
pour chaque carrosserie et chaque banque. Les origines des sprites sont appliquées
explicitement, et la même transformation sert au rendu et aux émetteurs. Les
capots/bas de caisse et pare-chocs modifiés utilisent des ajustements natifs
de surface. Voir [ATTACHMENTS.md](ATTACHMENTS.md) pour la provenance et les limites.
Les contrôles couvrent 18718 configurations corps/pot et 243334 variantes de
fitting avec les kits. Le défilement, l’orientation et l’attachement des effets
restent vérifiés en conduite et pendant les changements de voie.

Les captures de validation VFX utilisent un état contrôlé pour montrer les
flammes et le NOS simultanément ; elles ne servent pas de mesure physique.
