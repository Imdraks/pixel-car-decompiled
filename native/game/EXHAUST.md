# Pots et points d'émission natifs

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

Les ancrages de carrosserie viennent de la silhouette alpha : bord arrière,
ligne de capot et bas de caisse. Les bouches des pots sont identifiées dans
leurs images ; elles sont dans `validation/exhaust-anchors.json`, générées par
`tools/generate_exhaust_anchors.py`. Il s'agit d'un placement natif cohérent,
pas des offsets YYC d'origine récupérés. Les pots longs et extravagants du mod
conservent leurs formes. Les atlas et sons d'origine ne sont pas réencodés.

Les contrôles géométriques couvrent 191 carrosseries × 49 variantes disponibles,
soit 9359 configurations, ainsi que l'orientation, les sorties multiples, le
rabaissement et l'attachement à grande vitesse/changement de voie. Les captures
natives montrent arrière, capot, latéral et variantes triples. Le rendu est
également contrôlé par la présence effective de pixels NOS bleus et de flammes
chaudes dans une zone isolée, pour détecter un jet invisible malgré sa simulation.

Les captures de validation VFX utilisent un état contrôlé pour montrer les
flammes et le NOS simultanément ; elles ne servent pas de mesure physique.
