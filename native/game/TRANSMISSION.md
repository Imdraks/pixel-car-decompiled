# Transmission native : jusqu'à 10 rapports

Ouvrir **CHÂSSIS → TRANSMISSION** ou l’engrenage sous les statistiques du garage.
La présentation reprend deux colonnes de cinq rapports. Chaque rapport possède
un curseur et des boutons −/+, son ratio et sa vitesse théorique au limiteur.
Le pont final, le nombre de rapports (4 à 10), le temps de passage et le mode
automatique/manuel sont réglables, ainsi que traction/propulsion/4 roues motrices.

**ENREGISTRER** applique et sauvegarde la configuration. **ANNULER** ou Retour/
Échap abandonne les changements non enregistrés. **RÉINITIALISER** remet la
boîte native à six rapports ; enregistrer pour conserver ce choix. **PRENDRE LA
ROUTE** enregistre puis démarre le mode libre. Les choix survivent au redémarrage.

## Préréglages inspirés de boîtes du marché

| Configuration | Rapports avant sélectionnés |
| --- | --- |
| Origine native 6 | 3,15 / 2,10 / 1,55 / 1,22 / 1,00 / 0,82 |
| Auto 4 — GM SuperMatic 4L75-E | 3,06 / 1,62 / 1,00 / 0,70 |
| Manuelle 5 — TREMEC TKX | 2,87 / 1,89 / 1,28 / 1,00 / 0,68 |
| Manuelle 6 — TREMEC Magnum | 2,66 / 1,78 / 1,30 / 1,00 / 0,80 / 0,63 |
| DCT 7 — TREMEC TR-9070 | 3,14 / 2,05 / 1,43 / 1,10 / 0,86 / 0,68 / 0,56 |
| Auto 8 — GM SuperMatic 8L90-E | 4,56 / 2,97 / 2,08 / 1,69 / 1,27 / 1,00 / 0,85 / 0,65 |
| Auto 6 — GM SuperMatic 6L80-E | 4,02 / 2,36 / 1,53 / 1,15 / 0,85 / 0,67 |
| Auto 10 — GM SuperMatic 10L90-E | 4,70 / 2,99 / 2,15 / 1,80 / 1,52 / 1,28 / 1,00 / 0,85 / 0,69 / 0,64 |

Les sept familles réelles couvrent des boîtes routières/OE et aftermarket.
Leurs étagements sont repris des documents constructeur ci-dessous ; TKX utilise
la variante TCET17765/TCET17805, et TR-9070 le jeu « Ratio A ». La boîte native
à six rapports conserve le comportement des versions précédentes.

Sources consultées le 26 octobre 2026 :

- [Chevrolet Performance — transmissions, catalogue 2026](https://www.chevrolet.com/performance-parts/transmissions) : 4L75-E, 6L80-E, 8L90-E, 10L90-E et Super Magnum.
- [TREMEC TKX](https://tremec.com/product/tkx/) et [fiche TKX, tableau page 2](https://tremec.com/wp-content/uploads/2023/05/TKX-Card_F_09.2020-1.pdf).
- [TREMEC Magnum](https://tremec.com/product/magnum/), variante 2,66 ; mêmes rapports que le Super Magnum listé chez Chevrolet.
- [TREMEC double embrayage](https://tremec.com/products-and-services/conventional-drivetrain/dual-clutch-transmissions/) et [fiche TR-9070, Ratio A](https://tremec.com/wp-content/uploads/2023/05/Product.Sheet_TR-9070.DCT_.pdf).

Le pont final et les temps de passage sont des calibrations **natives**, pas
la promesse d'un ensemble moteur/pont homologué par ces fabricants. Le mode
manuel peut aussi représenter une commande séquentielle au clavier. Les limites
de couple, l'usure, l'hydraulique et la mécanique séparée des deux embrayages ne
sont pas simulées. Les noms désignent des inspirations, pas des produits officiels
ou des pièces retrouvées dans Unbound : son catalogue ne contient pas de boîtes.

Modifier le nombre de rapports ou les ratios crée une configuration personnalisée.
Les rapports réservés au-delà de ceux de la boîte réelle sont des valeurs natives.
Le jeu garde des rapports positifs, décroissants, et refuse les rétrogradages qui
feraient dépasser le régime maximal. Les profils mal formés reviennent à des
valeurs sûres, avec un maximum de dix rapports.

## Effet mécanique

Un pont ou un rapport plus court multiplie davantage le couple aux roues et
réduit la vitesse à un régime donné ; un rapport plus long fait l'inverse.
Le temps de passage détermine la coupure de traction. La transmission ne crée
pas de puissance moteur supplémentaire et ne modifie pas la valeur du banc.

`vitesse km/h = régime × 2π × rayon du pneu / (rapport × pont × 60) × 3,6`

Il s'agit de la vitesse théorique au limiteur avec les pneus équipés. La puissance,
la traînée et l'adhérence déterminent si la voiture peut réellement l'atteindre.
