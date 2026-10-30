# Lamborghini Unbound 086 / 188 : identification et kits

L’emplacement Unbound **188** avait été nommé **Gallardo** après une première
identification visuelle. La comparaison de sa silhouette de base avec toutes ses
familles de kits ne confirme pas ce nom. Il porte désormais le nom
**Lamborghini Huracán — variante 188 (probable)**. La famille est une identification
visuelle probable ; le mod ne contient pas de nom de modèle permettant de certifier
l’année ou la finition. L’identification existante de la 086 est conservée.

Les kits ne sont pas échangés entre les emplacements 086 et 188. Chaque pièce
active a été reconstruite depuis les textures Android et comparée à son homologue
dans les atlas PC : **180 images concordantes** pour les deux emplacements dans
les trois banques Original, Unbound et Underground. Les deux emplacements de base
Original représentent d’autres voitures ; un même numéro n’établit donc pas une
identité commune entre les trois banques.

Certaines images de flanc, dont Fortune sur la 188, couvrent aussi les portes et
le toit. Ce sont des conversions visuelles présentes dans le mod, et pas seulement
des bas de caisse. Les déplacer vers la 086 au seul motif de leur nom de kit
introduirait une attribution sans preuve.

Les images restent intactes. Le véhicule enregistré conserve son identifiant
`pcr-unbound-187`, sa préparation, son moteur et ses sons. Aucun modèle Gallardo
authentifié supplémentaire n’est créé par cette correction de nom.

Pour reproduire la vérification avec les textures Android extraites :

```sh
python native/game/tools/audit_lamborghini_kits.py --output /tmp/audit-lamborghini
```

Le rapport et les trois planches de comparaison sont écrits dans le dossier choisi.
Le ZIP Windows contient `audit-kits-lamborghini.json`. La comparaison de pixels
vérifie l’import des pièces ; elle ne certifie pas une identification constructeur
et ne remplace pas une exécution du jeu Android.
