# Ford GT 2017 — conversion Unbound identifiée

L’utilisateur a identifié la Ford GT 2017 dans la planche **Unbound 187 / Fortune**.
Le mod stocke cette silhouette dans un kit de l’emplacement 187, et non dans une
carrosserie de base distincte. Le showroom propose maintenant **2017 Ford GT**
comme voiture à part entière, en catégorie GT / Supercars.

- Identifiant stable : `pcr-unbound-186-ford-gt-2017`.
- Silhouette de base : composition exacte des pièces Fortune de cet emplacement.
  Elle reste présente quand les pièces de carrosserie sont remises à zéro.
- Moteur initial : **V6 3.5L, 646 HP**, moteur `20077` du tableau NFS Unbound fourni.
  Il utilise le profil audio V6 existant ; aucun nouveau son enregistré n’est créé.
- Sauvegardes distinctes de la Ford GT 2005 et de la voiture d’origine du même
  emplacement. Les pièces, moteurs et huit places de garage fonctionnent normalement.
- Les autres kits de cet emplacement, dessinés pour d’autres silhouettes, ne sont
  pas équipables comme pièces Ford GT. Aucune variante de kit Ford supplémentaire
  n’est inventée. Les lampes intégrées au dessin Ford sont conservées ; les masques
  de phares de la voiture de base ne sont pas superposés.

Le centre de roue avant est ajusté à **162,5 pixels** dans le dessin source, avec
le même essieu arrière et le même rayon. Les ancrages de capot suivent le kit Fortune.

Le modèle possède sa propre variante visuelle enregistrée (`visual_variant`, format
de profil 9). Les anciennes sauvegardes sans ce champ restent des variantes zéro et
ne sont pas transformées automatiquement en Ford GT. `vehicle-variants.json` décrit
la recette ; Windows la livre sous `variantes-vehicules.json`.

La puissance et le moteur sont ceux du tableau de jeu fourni. Masse, grip et autres
paramètres de châssis restent une calibration issue de l’emplacement source, pas
une validation constructeur de la physique de la GT 2017. La boîte reste réglable
avec le système natif existant.
