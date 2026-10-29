# Catégories de jantes — 0.17.1

Dans **Style → Carrosserie → Modifier les éléments → Roues**, ou **Performance → Pièces → Roues et pneus**, l’onglet **Jantes** propose : **Toutes, Offroad, Tuner, Muscle, Drag, Luxury et Hyper**. Cliquer une catégorie ou utiliser **0 à 6** hors du champ de recherche. La fiche indique le style et une seule provenance. Le changement de filtre prévisualise sans équiper ; **Équiper** applique le choix.

- **Offroad** : inspirations rallye, disques ventilés, familles Turbo Fan et 22B OEM.
- **Tuner** : jantes de préparation japonaise/européenne, route et circuit.
- **Muscle** : familles américaines classiques, USA Racing, VN et AR.
- **Drag** : Weld, Alum Star, Magnum, Race Star et ET.
- **Luxury** : VIP, grands voiles polis, jantes profondes et familles luxe.
- **Hyper** : carbone, forgées, aérodynamiques et inspirations supercars.

Répartition visible : **8 Offroad, 329 Tuner, 42 Muscle, 30 Drag, 51 Luxury et 70 Hyper**.

Les **530 jantes visibles** sont réparties dans les six catégories ; les neuf véritables variantes Underground héritent du style de leur recette d’origine. Les 37 copies identiques sont masquées et restent compatibles avec les sauvegardes.

Les 521 recettes sources récupérées ne contiennent pas de champ donnant ces six catégories. Cette répartition est donc une curation visuelle native, fondée sur les familles de jantes et leurs formes ; les modèles ambigus restent classés Tuner. Elle n’affecte ni puissance, ni grip, ni physique. L’onglet Pneus conserve sa propre liste et ne dépend pas du filtre de jantes.

Le détail par recette, avec justification, est dans `rim-styles.json`. Régénération : `python native/game/tools/classify_rims.py`.
