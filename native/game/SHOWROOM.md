# Showroom et garage de huit voitures — 0.16.3

La voiture est présentée dans une grande scène, avec la fiche à droite et
un carrousel de six modèles en bas. Les flèches et la molette changent la
sélection ; Page précédente/suivante avance de six modèles. Recherche,
catégories et tri par modèle, catégorie ou puissance d’origine sont disponibles.
Les préparations équipées/archivées sont visibles dans la fiche. Consulter une
voiture ne remplace pas la voiture active. [Présentation et commandes](CINEMATIC-UI.md).

**GARAGE** dans le menu ou **B** depuis la customisation ouvre l’inventaire des
voitures possédées. Le compteur indique les places occupées sur **8**. Le showroom
est accessible directement dans le menu, avec le bouton **SHOWROOM** du garage,
ou **Tab** pour changer d’onglet. Il conserve les 239 modèles et variantes,
la recherche Ctrl+F et les catégories.

- **AJOUTER AU GARAGE** prend librement une voiture du showroom. Un exemplaire
  par modèle/variante ; aucune monnaie requise. L’ajout ne change pas la voiture
  active. Sélectionnez ensuite **UTILISER CETTE VOITURE** pour la conduire et la
  personnaliser. Une voiture déjà possédée n’occupe pas une deuxième place.
- **UTILISER CETTE VOITURE** retrouve ses pièces, moteur, sons et réglages.
  Les flèches de la customisation parcourent uniquement les voitures possédées.
- **RETIRER / Suppr**, puis confirmation avec Entrée ou le bouton Retirer, libère
  une place. Échap ou Annuler conserve la voiture. Retirer la voiture active
  sélectionne une voiture restante ; la dernière voiture peut aussi être retirée.
- Un garage vide reste vide au redémarrage. La conduite et la customisation
  renvoient vers le garage jusqu’à l’ajout d’une voiture, y compris avec le
  raccourci `Mode-libre.cmd`.
- Un garage plein bloque tout nouvel ajout et tout chargement F11 d’un modèle
  absent. Charger une préparation d’une voiture déjà possédée reste possible.

Les préparations nommées **F11** sont des archives de configuration ; elles ne
créent pas de places supplémentaires. Lorsqu’une voiture est retirée, sa dernière
préparation reste archivée : la reprendre dans le showroom restaure cette
préparation. La fiche de la voiture sélectionnée affiche son équipement et sa puissance
actuels, ainsi que son état dans le garage. La liste repère la voiture **ACTIVE**.

## Sauvegarde et reprise des anciennes versions

L’inventaire est enregistré atomiquement dans `garage-inventory.ini`, avec une
copie précédente `.bak`, dans `%LOCALAPPDATA%/PixelCarRacerNative`. Les préparations
restent dans `vehicles/<identifiant>.ini`. Un inventaire corrompu est signalé et
conservé, sans reconstruction silencieuse ni suppression des préparations.

À la première utilisation seulement, la voiture active est conservée en priorité,
puis les préparations automatiques les plus récentes, jusqu’à huit voitures.
Les autres anciennes préparations restent archivées et récupérables en reprenant
le modèle depuis le showroom lorsqu’une place est libre. Les sauvegardes F11 ne
sont pas supprimées. Un inventaire vide existant ne déclenche pas cette migration.

Les moteurs universels, les classes et les réglages de physique restent ceux de
la version 0.16.0. [Identités, moteurs par défaut et limites](VEHICLES-GARAGE.md).
