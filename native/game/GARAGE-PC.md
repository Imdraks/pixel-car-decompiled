# Garage original adapté au PC — 0.8

Garage et Customisation ouvrent désormais le même atelier : voiture sur le pont,
statistiques à gauche et six catégories en bas. Le décor, le pont, les icônes,
les jauges et la police pixel viennent des exports du jeu original 1.2.5 fourni.
Les carrosseries, jantes, pièces et performances Unbound déjà intégrées sont
conservées. Les images de pièces du mod sont conservées lorsqu'elles diffèrent.

Les panneaux, l'inventaire et les interactions sont réécrits nativement pour le
PC. Le bandeau propose **ORIGINAL 1.2.5 / UNBOUND** ; l’équipement reste libre.
Économie et progression originales
restent à reconstruire. Les valeurs affichées correspondent au modèle natif :
identifiant de carrosserie, moteur choisi, puissance sans NOS (extension bleue
pour le NOS), poids en kg et adhérence. **VIT. THÉO.** est la vitesse au limiteur
dans le dernier rapport ; l'infobulle rappelle les limites de puissance/traînée.

F7 ouvre aussi **STYLE / ACCESSOIRES** : seize catégories supplémentaires,
521 jantes nommées et conservation des deux banques visuelles/sonores.
Voir [CONTENT.md](CONTENT.md) pour la fusion du contenu en 0.8.

## Catégories

| Touche | Catégorie | Contenu |
| --- | --- | --- |
| F1 | Moteur | Moteurs, ECU |
| F2 | Roues | 23 jantes, pneus |
| F3 | NOS | Bouteilles NOS |
| F4 | Suralimentation | Turbos, compresseurs, intercoolers |
| F5 | Châssis | Suspensions, accès à la transmission |
| F6 | Pièces | Admissions, pistons, échappements |

Les quatre icônes sous les statistiques ouvrent la vue d'ensemble, la transmission,
le banc de puissance et les sons moteur. Les flèches de carrosserie et le bouton
Décor restent disponibles, ainsi que Prépa max et Remettre base. La flèche rouge
en haut à droite démarre le mode libre.

## Souris et clavier

- Cliquer une catégorie puis un sous-onglet ouvre l'inventaire, avec les images,
  noms, raretés colorées, équipement actif et aperçu du gain.
- Cliquer une pièce montre son effet sur la voiture et les statistiques avant
  équipement. **ÉQUIPER**, **Entrée** ou un double-clic l'équipe et sauvegarde.
- **Ctrl+F** sélectionne la recherche pour saisir une nouvelle requête ; **Ctrl+A**
  et Retour arrière permettent de la remplacer. Le bouton de tri inverse l'ordre.
- Dans l'inventaire : flèches pour sélectionner, Home/End pour début/fin,
  Page précédente/suivante ou molette pour changer de page.
- **Tab / Maj+Tab** changent de catégorie hors du champ de recherche.
- **Échap** quitte d'abord la recherche, puis ferme l'inventaire, puis revient
  au menu. Sans inventaire, les flèches gauche/droite changent la carrosserie.
- Le survol affiche les infobulles. F3 ouvre le NOS au garage ; ailleurs, il
  conserve son rôle d'affichage des FPS.

L'interface utilise un repère 1280×720 mis à l'échelle ; les formats différents
conservent des bandes pour préserver les proportions. Les coordonnées de souris
suivent ce rendu, vérifié en 960×540, Full HD et fenêtre 1200×900.

## Frein à main

**En conduite, Espace est désormais le frein à main**, et ne sert plus à accélérer.
Z/W/↑ restent les accélérateurs, S/↓ le frein de service. Le frein à main agit sur
l'adhérence de l'essieu arrière, coupe la traction et le NOS, bloque la rotation
visuelle arrière et produit la fumée arrière à vitesse suffisante. Relâcher
Espace libère les roues. Le modèle reste longitudinal avec changement de voie ;
un modèle complet de dérive latérale n'est pas ajouté par cette commande.

Les sauvegardes antérieures restent compatibles. Extraire tout le nouveau ZIP :
les deux atlas `original-ui-00.png` et `original-ui-01.png` sont nécessaires.

## Ressources et vérifications

`tools/prepare_original_ui.py` vérifie les SHA-256 des atlas exportés, copie les
pixels RGBA sans redimensionner les images source et génère `src/original_ui.hpp`.
Le réassemblage conserve les offsets des glyphes/images. Les 16 groupes et 576
images incluent les éléments d'interface originale et les images de pièces du
mod. Les empreintes sont dans `validation/original-ui-source.json`.
Le reconditionnement nécessite Pillow pour la génération ; le jeu Windows n'a
aucune dépendance Python. Lancer ce script après prepare_assets.py/prepare_audio.py.

La suite `tests/pc_garage_input_test.py` utilise de vraies entrées clavier/souris,
vérifie l'équipement des onze catégories, jantes, aperçu sans achat, tri,
pagination, molette, double-clic, saisie/recherche, boîte, formats de fenêtre,
redémarrage et Espace en conduite. Elle attend une première image rendue pour
éviter d'envoyer des clics pendant le chargement des atlas.

## Correctif 0.7.1 : jantes et calques

Le sprite `sp_rims` contient 54 images mais seulement 23 sont des styles de
jantes : indices source 8–28, 36 et 42. Les 31 autres sont des pneus et des
calques d’ombre, de reflet ou de couleur ; ils ne sont plus proposés comme
équipement. Les numéros de jantes gardent les identifiants source (09–29,
37 et 43), afin que les choix valides existants gardent leur apparence.
Les vignettes composent pneu et jante sur leur canevas commun, sans agrandir
indépendamment les images rognées. Le rendu de la voiture et du trafic emploie
le même catalogue. Une sauvegarde utilisant un ancien calque invalide retrouve
la jante 09 sans perdre ses autres réglages.
