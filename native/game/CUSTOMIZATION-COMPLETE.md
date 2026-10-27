# Personnalisation PC — 0.13.0

Les catalogues Original et Unbound restent réunis : 1220 choix d’équipement,
avec provenance sous chaque pièce. Aucun éditeur de livrées n’est ajouté ;
les livrées prédéfinies du catalogue restent utilisables.

## Commandes et contenu

- F1–F6 : moteur, jantes/pneus, NOS, suralimentation, châssis et composants.
- F2 : les boutons AV+AR, AVANT et ARRIÈRE, en haut du sélecteur, permettent
  des jantes différentes par essieu. AV+AR rétablit une sélection commune.
- F7 : peintures, livrées prédéfinies, spoilers, galeries, kits complets,
  pièces avant/arrière/latérales, freins, sièges, écrous, crochets, vitres,
  teintes des phares et feux arrière, ampoules. F8 : arceau. K : phares.
- F9 : suspension ; TRANSMISSION : rapports et pont final. Les réglages,
  aides ABS/antipatinage et pièces mécaniques des versions précédentes restent disponibles.

Les variantes sans image pour la carrosserie choisie sont signalées et ne
peuvent plus être équipées silencieusement. Un kit partiel conserve les panneaux
d’origine manquants. Une pièce déjà sauvegardée reste mémorisée lors d’un
changement de carrosserie et redevient visible sur une carrosserie compatible.

## Matériaux et accessoires

Les deux palettes source fournissent 2376 nuances RGBA. Le masque de peinture
reprend la tolérance du shader source ; mat, brillant et chrome utilisent leurs
nuances dessinées, sans reflet 3D inventé. Les livrées prédéfinies utilisent le
masque et la somme RGB du shader récupéré. Les vitres translucides, sièges,
arceau et optiques sont traités séparément. Les dix teintes de phares et les
trois assombrissements arrière sont distincts ; les feux rouges conservent
leur couleur. Les paramètres de teinte des optiques restent adaptés nativement.
Les jantes reprennent leurs passes fixes de reflet et d’ombre source, en plus
de la rotation des rayons. La masse des accessoires reprend leur poids de
catalogue ; ils n’ajoutent pas de chevaux.

Le canevas agrandi préserve les bords des accessoires sur les deux banques.
Les galeries, sièges et crochets conservent leurs coordonnées récupérées par
carrosserie. Les trois pots de capot sont ajustés à la surface opaque du capot
réellement monté, après application de la pièce avant ; les sorties des flammes
et du NOS utilisent la même transformation.

**Limite des pots de capot :** les branches Draw récupérées rendent les types
1/4 devant et 2/3 derrière, mais pas le type 0 des images 48–50. Le placement
de ces trois pots est donc une reconstruction géométrique native, et pas une
coordonnée Android retrouvée. Sans capot (Delete ou variante absente), un
ancrage mécanique de repli est conservé : 1242 cas sur 14898.

## Vérification reproductible

`tools/prepare_customization.py` vérifie les empreintes des textures et génère
palettes, matériaux des jantes et contacts de capot. Les références et limites
sont dans `native/evidence/merged/customization-render.json`.

`PixelCarRacerNative.exe --assets-dir assets --check-customization-dir audit`
produit les feuilles des 191 carrosseries de chaque banque, les compatibilités
et les empreintes des compositions. Le contrôle couvre :

- 192146 associations pièce/carrosserie : 129 variantes absentes signalées et
  2309 kits partiels ; aucun rejet général des pièces compatibles.
- 27122 montages d’accessoires et leurs limites de canevas.
- 1528 compositions de carrosserie (sans roues), sur les 382 entrées des deux banques.
- 14898 montages carrosserie/pièce avant/pot de capot, avec contact vérifié
  sur le capot quand il existe ; les replis sont comptés séparément.

Ces contrôles ne prouvent pas une équivalence visuelle complète avec Android.
Les particules, éclairages et conduite restent adaptés au moteur natif.
