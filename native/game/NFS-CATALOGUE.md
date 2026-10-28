# Catalogue du tableau NFS — 0.15.0

Le fichier fourni `NFS_Unbound_catalogue_performance_moteurs_voitures.xlsx` est
importé comme **données de référence NFS Unbound**, distinctes du mod Pixel Car
Racer Unbound. Son SHA-256, les lignes, sources, prix manquants et incertitudes
figurent dans `nfs-catalog.json`. Aucune instruction du classeur n’est exécutée.

## Contenu jouable

- **145 nouveaux moteurs**, en plus des 31 précédents : puissance de base,
  cylindrée, grade du tableau, courbe de couple/inertie et masse estimées.
- **113 pièces du tableau** et neuf nouvelles extensions Contrebande. Les
  pièces historiques et leurs identifiants sont conservés. Total : 496 pièces
  mécaniques et 20 catégories, soit 1520 choix avec jantes/accessoires.
- Classes **Basic → Sport → Pro → Super → Elite → Contrebande**. Les grades
  du tableau sont explicites ; les anciennes classes changent de nom.
- **623 liens origine/swap**, sur 50 modèles et 97 couples carrosserie/banque.
  Les ponts entre versions proches sont déclarés ; les modèles inconnus et les
  remplacements visuels du mod restent sans association automatique.
- Toutes les voitures peuvent recevoir les moteurs en **swap libre PC**.
  Le bouton **CETTE AUTO** dans F1 filtre les associations du tableau. Rechercher
  `NFS`, le nom d’un donneur, la cylindrée ou la puissance. Le survol donne le
  véhicule donneur et la relation au tableau ; aucune nouvelle carrosserie
  n’est créée pour les donneurs absents du jeu.

## Accès aux catégories

| Menu | Pièces |
|---|---|
| F1 Moteur | Moteurs, ECU, accès Électrique |
| F1 → Électrique | Batterie, système, composants moteur, surcharge |
| F2 Roues | Jantes et pneus, dont grip/drift/route/tout-terrain |
| F3 NOS | Nitro historique et NFS |
| F4 Suralimentation | Turbo simple/double, compresseurs, intercoolers |
| F5 Châssis | Suspensions, freins, différentiel, accès Boîtes |
| F5 → Boîtes | Boîtes, embrayages, réglages des rapports |
| F6 Pièces | Admission, pistons, échappement, carburant |

Les boîtes du tableau vont de **1 à 8 rapports** ; la préparation Contrebande
propose 10 rapports. Les préréglages précédents inspirés de boîtes réelles et le
réglage manuel restent disponibles. Embrayage et freins modifient respectivement
le temps de changement et la décélération. Le différentiel agit sur l’efficacité
de la traction longitudinale du modèle 2D. Les pneus Drift réduisent le grip sur
la route ; les variantes tout-terrain restent des réglages pour la surface
actuellement présente, sans création de circuit hors-route.

Les deux moteurs électriques utilisent un plateau de couple puis de puissance,
un ensemble moteur/batterie de masse estimée, les composants électriques et une
surcharge temporaire. Ils refusent admission/carburant/échappement/turbo/NOS de
combustion ; une conversion nettoie les équipements incompatibles. Ils n’émettent
pas de son de combustion. Les hybrides utilisent la puissance totale annoncée,
sans simulation séparée de batterie/récupération.

## Puissance et limites de la référence

Le tableau ne fournit ni équations physiques, ni courbes complètes, ni régimes
maximums : ces paramètres sont des **calibrations natives estimées**. La physique
stock récupérée pour les 191 carrosseries reste inchangée. Les pièces ne sont
pas une importation du moteur physique de NFS.

Pour un moteur NFS équipé des pièces NFS, la progression utilise le potentiel du
classeur : admission 15 %, ECU 20 %, carburant 20 %, échappement 15 % et
suralimentation 30 %. Les grades appliquent 4/15/35/65/100 % de ces parts.
Le plein ensemble Elite atteint le potentiel annoncé **sans NOS**, vérifié pour
chaque moteur. Une valeur ambiguë prend la borne basse ; une valeur inconnue
conserve la puissance de base. Le turbo/compresseur modifie la réponse sous charge
et le couple est normalisé au potentiel au plein boost, sans compter deux fois
la puissance de suralimentation. Les pièces historiques utilisent leur précédent
modèle ; les montages mixtes PC peuvent dépasser le potentiel NFS. Turbo et
compresseur restent exclusifs, y compris pour les kits doubles.

Les prix absents restent `null` dans le rapport. Le prototype permet d’équiper
librement les pièces ; il n’ajoute pas d’économie ni de dépenses simulées.
Quatre compatibilités mentionnent un V8 641 HP / 4.0 L absent de la liste des
145 moteurs : elles restent signalées non résolues, sans substitution silencieuse.
Les 29 auxiliaires et six équipements de poursuite sont conservés dans le rapport
comme non implémentés : les systèmes police, dégâts/réparation, récompenses et
Lockdown correspondants n’existent pas dans le mode libre natif.

## Sons

Cinq nouvelles familles sont réellement générées avec le simulateur physique
Engine Sim : **I4 2.0, I6 2.6, boxer quatre 2.457, V6 routier 3.5 et V8 à
vilebrequin plat 4.5**. Chaque famille ajoute 16 WAV et 16 OGG : démarrage,
arrêt, accélération/décélération et boucles à quatre régimes et trois charges.

Les banques précédentes AMG, Coyote, LS, Huracán et Aventador sont réutilisées
selon le donneur/la famille. **129 moteurs du tableau partagent des banques
simulées** ; ce sont des approximations de familles, avec cames/échappement
estimés, sans enregistrement constructeur ou audio de NFS. Les 14 moteurs
F6/F12/I3/Wankel/W16 gardent des échantillons historiques adaptés explicitement
approximatifs ; les deux électriques n’ont pas de son de combustion.

Le mixeur conserve les transitions de régime/charge, les démarrages, les sons
historiques turbo/compresseur/valve, G/Z au garage, les profils manuels et les
sept curseurs de volume. La musique reste limitée au menu et au garage.
Les anciens fichiers audio sont inchangés ; les nouveaux sont dans des dossiers
séparés avec leurs manifestes, mesures et licence Engine Sim.

## Reproduction

```bash
python native/game/tools/import_nfs_catalog.py chemin/du/classeur.xlsx
python native/game/tools/generate_nfs_audio.py \
  --exporter-root /chemin/exporter --output /nouveau/dossier
```

Le générateur exige un dossier neuf. Le skill
[car-engine-audio](https://github.com/Imdraks/pixel-car-decompiled/blob/main/.agents/skills/car-engine-audio/SKILL.md) explique le
simulateur et les limites. `install_simulated_audio.py` accepte `--catalog` et un
`--extra-pack` par nouvelle famille, vérifie les SHA et refuse d’écraser des
ressources différentes. La compilation, le mixeur réel, les contrôles des boucles
et les vérifications Windows restent nécessaires avant publication.
