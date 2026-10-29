# Fonds de menus — 0.18.1

Le cadrage utilise la zone utile des décors avant de couvrir toute la fenêtre,
sans étirement. Les quinze décors des banques Original, Unbound et Underground
sont couverts. L’interface conserve ses positions et ses coordonnées de souris.

Les images de 940 × 480 contenaient des espaces réservés à l’ancienne interface :
80 pixels noirs de chaque côté pour les garages Original, et notamment 228 pixels
à gauche pour certains décors Unbound. Agrandir le rectangle complet reproduisait
ces espaces même lorsque la fenêtre entière était peinte.

`tools/prepare_menu_backdrops.py` mesure les limites du contenu visible, après
neutralisation du RGB des pixels totalement transparents. `menu-backdrops.json`
et `src/menu_backdrops.hpp` contiennent les quinze rectangles. La version Windows
inclut ces mesures dans `cadrage-fonds.json`. Aucune image source n’est réécrite.

La présentation utilise également le framebuffer réel pour éviter de dépendre
d’une ancienne zone de rendu après redimensionnement sous Windows. Le format
16:9 de l’interface reste centré ; le décor remplit aussi les marges en 4:3 ou
sur écran large.

Vérifications : pixels des marges comparés aux rectangles utiles ; contrôle
supplémentaire de contenu visible sur les deux côtés en écran large ; navigation
et clics testés après redimensionnement. Les ombres naturellement présentes dans
les images sont conservées.
