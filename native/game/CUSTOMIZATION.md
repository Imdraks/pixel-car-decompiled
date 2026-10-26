# Customisation native 0.5

| Catégorie | Pièces |
| --- | ---: |
| Moteurs | 16 |
| Suspension | 16 |
| Turbos | 14 |
| Superchargers | 10 |
| ECU | 8 |
| NOS | 5 |
| Intakes | 21 |
| Intercoolers | 13 |
| Pistons | 7 |
| Exhausts | 48 |
| Tires | 36 |

Total : 194 pièces issues de la base Unbound. Chaque catégorie propose aussi
la configuration de base. Un turbo remplace le compresseur et inversement.
Le catalogue conserve noms, statistiques brutes, prix source, poids relatif et
identifiant d'image ; le prix est informatif. Les choix survivent au redémarrage.
Le catalogue JSON source accompagne le paquet sous `catalogue-pieces.json`.

Les moteurs modifient la courbe de couple, les ECU le régime maximal, les pneus
l'adhérence et leur image, les suspensions la hauteur, turbo/compresseur la
suralimentation et les autres pièces la puissance ou la masse estimée. Ces
adaptations sont natives et provisoires : les équations originales ne sont pas
entièrement récupérées. Les carrosseries partagent encore une base mécanique.

94 sons originaux sont conservés sans réencodage. Les 16 paires de dispatch
charge/décélération sont récupérées, mais leur association aux 16 moteurs du
catalogue reste inconnue. AUTO choisit une famille approximative. Les choix
manuels charge/décélération (16 profils chacun) et valve (4) sont indépendants,
sauvegardés, et disposent d'une préécoute. Les événements de conduite utilisent
les échantillons d'origine ; les gains, hauteurs et transitions sont recalibrés.
Les sons des autres modes ne sont pas tous déclenchés dans le mode libre.

Effets actuels : fumée d'accélération/freinage, flammes de changement et 2STEP,
étincelles de collision, jet NOS bleu et icône de bouteille originale.
Le placement et les conditions sont réimplémentés. Les autres effets du jeu
original ne sont pas intégralement reproduits.

Sources : `native/evidence/unbound/parts/` dans le dépôt. Scripts de récupération
statiques : `native/tools/recover_part_catalog.py` et `recover_engine_audio.py`.
Aucun code Android n'est exécuté par le jeu Windows.

## Puissance et classement 0.5

Le détail complet est dans [PERFORMANCE.md](PERFORMANCE.md). Le garage présente
les HP avec suralimentation sans/avec NOS, un aperçu du gain avant équipement,
un banc de puissance et PRÉPA MAX. Le classement de commun à contrebande reflète
les performances par catégorie ; les prix/couleurs ne créent pas de gain caché.
L'intercooler agit sur le rendement de suralimentation, l'ECU étend aussi la courbe
de couple. L'exclusivité turbo/compresseur est conservée, même avec PRÉPA MAX.
