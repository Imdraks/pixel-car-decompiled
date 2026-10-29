# Revue du contenu — 0.17.1

Chaque fiche affiche une seule provenance : **Original**, **Unbound** (tableau NFS inclus) ou **Underground**. Les extensions créées pour le portage portent **Création PC** : elles ne sont pas présentées comme des extractions du jeu.

La comparaison utilise les pixels RGBA visibles, après neutralisation du RGB sous alpha nul. La révision précédente comptait des différences de remplissage transparent comme de nouveaux contenus. Les planches comparatives des carrosseries, jantes, freins, pneus, échappements, sièges, accessoires, peintures et habillages ont été examinées visuellement.

## Décisions et compatibilité

- **1 663 équipements visibles** sur 1 826 identifiants conservés. Les 163 copies identiques sont masquées : 118 éléments esthétiques, 37 jantes et huit pièces mécaniques.
- Les variantes visuelles réellement différentes restent séparées, avec le suffixe « variante Underground » et leur provenance propre : 114 éléments esthétiques, neuf jantes et vingt pièces (cinq échappements, quinze pneus).
- **287 choix au showroom** sur 430 identifiants historiques : 142 copies graphiques et mécaniques sont masquées. Une même apparence reste distincte si le moteur ou les caractéristiques diffèrent. Le kart à physique de Smart n’est plus proposé à l’acquisition.
- Les voitures déjà possédées et leurs préparations restent accessibles, y compris les anciens doublons et le kart. Aucun véhicule possédé n’est supprimé. Les anciens identifiants de pièces identiques sont résolus vers leur équivalent à la lecture des configurations.
- Les 108 peintures Underground étaient identiques : aucune fausse palette supplémentaire. Les habillages différents restent disponibles et leurs noms descriptifs ont été corrigés.

## Identification et moteurs

Le binaire x86 `libyoyo.so` Underground est identique à celui d’Unbound (SHA-256 `fb3726e175e7d1c643e0ddac1ec1a365901c4d52a16ded97e89fd672f6a9e9cc`). Les 1 185 chaînes du `game.droid` sont aussi identiques. Les fichiers INI et productlist n’apportent pas de table supplémentaire de noms de véhicules. La relecture des recettes retrouve 194 pièces mécaniques et les seize mêmes blocs moteur ; aucun V12 exclusif Underground supplémentaire n’est identifié.

Les reconnaissances visuelles retenues comprennent Ford GT40 (Underground 007), BMW M3 E36 (167), Ferrari F40 (183) et plusieurs transformations cabriolet, break ou pick-up. Les familles encore incertaines portent un nom descriptif et leur numéro, sans marque inventée. Les identifications confirmées par l’utilisateur, Unbound 086 Huracán et 188 Gallardo, sont conservées.

Les variantes sonores réellement distinctes du mod restent intégrées ; cette revue n’invente pas de nouveaux enregistrements moteur.

## Reproduction

Après les extractions Underground et la fusion initiale, exécuter :

```sh
python native/game/tools/curate_content.py
python native/game/tools/generate_vehicle_catalog.py
python native/game/tools/classify_rims.py
```

`catalogue-review.json` contient les correspondances d’alias et les décisions. Les ressources et les identifiants historiques restent disponibles pour les sauvegardes. Le script de revue utilise la version publiée `919084744cf44ecd993be033899443d330c86237` comme référence d’import.
