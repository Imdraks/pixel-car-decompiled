# Drag : correction du préréglage et recherche de la physique originale

## Correction 0.13.1

Dans F9, **Drag** et **Wheelie** ont maintenant deux boutons distincts.
Le précédent « Drag / Wheelie » imposait +120 mm, des ressorts ×0,50,
un amortissement de 0,30 et 15 points de masse vers l’arrière. C’était un
réglage de démonstration de cabrage, appliqué même aux tractions.

Le nouveau **Drag** utilise −10 mm, des ressorts ×1,35 et un amortissement de
0,90. La répartition est ajustée selon les roues motrices : +4 points à l’avant
pour une traction, −6 pour une propulsion, neutre pour une intégrale. Le cabrage
avec perte de contact est désactivé ; le transfert de charge et le tangage
restent actifs. Moteur, pneus, rapports, transmission et choix des aides sont
conservés. Ce sont des calibrations natives, pas des valeurs extraites d’Android.

Le bouton **Wheelie** conserve l’ancien réglage extrême pour qui souhaite lever.
Les sauvegardes ne sont pas réécrites automatiquement : ouvrir **F9 → Drag →
Enregistrer** pour remplacer l’ancienne préparation.

Sur le banc natif de lancement puissant, les six combinaisons traction/
propulsion/intégrale et TC activé/désactivé gardent des charges positives aux
deux essieux pendant dix secondes. Le pic de tangage maximal est d’environ
0,0243 rad (1,39°), inférieur au réglage Route dans les six cas. Ces résultats
ne sont ni des temps constructeur ni une comparaison de fidélité Android.

## Curseur de balance

F9 affiche une barre de **balance avant/arrière**, les deux pourcentages et la
masse en kilogrammes sur chaque essieu. Le repère cliquable **BALANCED 50/50**
règle exactement la répartition statique à parts égales. Le curseur conserve
sa plage de réglage par châssis et n’ajoute aucune masse. Les réglages de wheelie
et les pièces équipées restent indépendants.

50/50 est un repère statique, pas une garantie contre le cabrage : l’accélération
transfère de la charge vers l’arrière, et les besoins d’une traction et d’une
propulsion diffèrent. Le bouton Drag reste adapté aux roues motrices ; les
wheelie bars interviennent physiquement si le rouleau atteint la route.

## Wheelie bars du DRAG PRO

Les petites roues arrière sont dans le sprite source `sp_drag2_rear`, sur les
191 carrosseries de chacune des deux banques. Équiper **F7 → Pare-chocs AR. →
DRAG PRO (Rear)** ou le kit complet **DRAG PRO Kit** active cet appui. Une pièce
arrière différente, y compris Delete, le retire même si le kit complet reste équipé.
Le kit Drag ordinaire sans petites roues ne reçoit pas cet effet.

Le contact est calculé à partir du rouleau visible, de l’empattement natif et
de la hauteur réglée. Lorsque le rouleau atteint le sol, sa réaction freine le
cabrage ; le réglage Wheelie est conservé et aucun cheval ni adhérence gratuite
n’est ajouté. Le HUD indique WHEELIE BAR pendant l’appui. En retirant la pièce,
le comportement de cabrage de la préparation est retrouvé.

Les 382 montages source ont été lancés pendant six secondes avec une préparation
puissante : pas de pénétration du plan de contact, valeurs finies et levée avant
nulle dans ces scénarios. Sur la référence, la levée sans barre atteint 0,38 m.
Les images et points du rouleau sont récupérés ; **sa réaction mécanique reste
une implémentation native**, pas une équation Android retrouvée.

## Ce que contient réellement le jeu de base

La vérification statique des bibliothèques fournies confirme du code de conduite
original dans `gml_Object_ob_car_Step_0` :

| Banque | Adresse x86 | Taille |
| --- | --- | --- |
| Original 1.2.5 | `0x0117a650` | 602649 octets |
| Unbound | `0x005b1590` | 592716 octets |

Les accès aux champs `xspeed`, `run_acc`, `RPM`, `currentgear`, `gear_final`,
`weight_to_power`, `wind_friction`, `no_traction`, `tire_heat` et `wheel_spin`
sont localisés par identifiants vérifiés dans chaque banque. Les fragments
conservent les opérations YYRValue et les branchements utiles pour poursuivre
la traduction. Un nom de champ ne suffit pas à établir son unité ou sa formule.

Il existe donc une physique de jeu à reconstruire, mais pas un module Windows
à copier. La fonction dépend des instances GameMaker, des opérateurs YYRValue,
des commandes et de l’état des courses. Charger la bibliothèque Android ne
fournirait pas une conversion native Windows.

Les 191 fiches de masse, puissance, régime, adhérence relative et transmission
sont déjà importées. Les équations complètes de motricité, chauffe des pneus,
embrayage, régime et accélération **ne sont pas encore importées**. Les ressorts,
amortisseurs et paramètres de wheelie actuels restent propres à la reconstruction
native. Les fragments trouvés ne justifient pas de leur attribuer une origine Android.

## Reproduire et poursuivre

```bash
python native/tools/inspect_drag_physics.py --output /tmp/pcr-drag-source
```

Le script vérifie les empreintes des deux ELF et n’exécute aucun code Android.
Il produit les adresses d’accès et les fragments d’assembleur. Les preuves sont
conservées dans `native/evidence/merged/drag-physics/` ; le résumé est aussi
fourni dans l’archive Windows sous `drag-physique-source.json`.

La prochaine étape de fidélité est de reconstruire par blocs les fonctions
thermiques/de motricité et la chaîne RPM–rapports–accélération, avec résolution
des appels indirects, unités et conditions de course. Elles doivent ensuite être
comparées à des relevés du jeu original avant de remplacer les équations natives.
La correction 0.13.1 stabilise le préréglage ; elle ne prétend pas achever ce portage.
