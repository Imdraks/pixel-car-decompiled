# Retrait de la voiture Unbound 188

La voiture Unbound **188**, précédemment nommée **Gallardo**, est retirée du jeu à la demande de l’utilisateur : showroom, garage possédé et configurations chargeables. La **086 reste disponible**.

Si la 188 était active, le jeu sélectionne une autre voiture déjà possédée. Si elle était la seule voiture, le garage devient vide et permet de choisir un autre modèle au showroom. Sa place est libérée. Les préparations restent archivées sur disque, et les fichiers actifs/inventaire d’avant migration sont conservés dans des copies `.pre-retired-188.bak`. Ces copies ne sont pas réécrites au redémarrage. Les anciennes configurations ne permettent pas de réintroduire le modèle.

L’identifiant `pcr-unbound-187` et les images partagées des atlas sont conservés en interne pour reconnaître ces anciennes sauvegardes. Ils ne représentent plus une voiture sélectionnable.

## Vérification effectuée avant le retrait

L’emplacement Unbound **188** avait été nommé **Gallardo** après une première
identification visuelle. La comparaison de sa silhouette de base avec toutes ses
familles de kits ne confirme pas ce nom. L’étiquette conservée dans les données archivées est
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
