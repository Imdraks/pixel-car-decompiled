# Sons simulés — 0.13.8

Six packs réellement générés avec le simulateur physique et l’exporteur de
[Talhasarac](https://github.com/Talhasarac/engine-sim-sound-exporter), révision
`a548360a33c6ddcc28265ac08b71b8a5f514ed3c`. Le moteur de combustion, le solveur
mécanique et le synthétiseur amont sont réutilisés ; seuls le port Linux,
les commandes d’export et les configurations sont adaptés.

| Pack | WAV | OGG | Boucles régime/charge |
| --- | ---: | ---: | ---: |
| Aventador SVJ V12, approximation | 19 | 19 | 15 |
| LS V8 7.0, approximation | 16 | 16 | 12 |
| AMG GT63 S 2021 V8, approximation | 16 | 16 | 12 |
| Huracán EVO V10, approximation | 16 | 16 | 12 |
| Ford Coyote V8 5.0, approximation | 16 | 16 | 12 |
| V6 F1 thermique générique | 16 | 16 | 12 |

**99 WAV et 99 OGG** au total. Chaque pack comprend démarrage, arrêt,
montée et descente en régime contrôlées au banc, puis les boucles aux charges
0 %, 30 % et 100 %. Les WAV sont mono PCM16 à 44,1 kHz ; les OGG Vorbis q6
sont encodés puis décodés avec FFmpeg pour contrôle. Les événements durent
3 secondes ; les boucles conditionnées durent 2,97 secondes.

## Disponibilité et intégration

Les ZIP sont fournis séparément dans la release et dans **Audio-Simulation**
du téléchargement Windows. Ils contiennent les WAV bruts, WAV/OGG traités,
le script `.mr` adapté, la description JSON, le journal de simulation,
les empreintes SHA-256, la licence et le plan d’intégration.

**Ces packs ne sont pas encore activés dans le mixeur du jeu.** Les 31 swaps
jouables utilisent encore les familles sonores du jeu. Le plan prévoit une
banque séparée pour interpoler les régimes et les charges sans changer les IDs
partagés par les moteurs Original/Unbound ni les choix audio manuels.
Les dossiers d’intégration sont préparés et validés ; aucun son d’origine
n’est écrasé. Les 188 fichiers source ont été comparés au ZIP public 0.13.7 :
identiques octet par octet.

Le skill réutilisable se trouve dans
[`.agents/skills/car-engine-audio/SKILL.md`](../../.agents/skills/car-engine-audio/SKILL.md).
Il permet de résoudre une demande en langage naturel, sélectionner/adapter une
configuration, exécuter l’export, contrôler puis préparer l’intégration. Les
scripts refusent les dossiers de sortie existants. Le bootstrap Linux extrait
ses dépendances localement et a été recompilé depuis un dossier vierge.

## Vérification et limites

Chaque fichier a été contrôlé : durée, fréquence, canaux, profondeur PCM,
non-silence, valeurs finies, saturation source et crête après décodage OGG.
Aucun échantillon brut ne touche les rails PCM16. Les raccords de boucles sont
mesurés ; le traitement utilise recouvrement, fondus de 3 ms aux extrémités et
gain constant. Les bruts sont conservés. Le journal vérifie aussi que chaque
régime fixe est effectivement atteint par la simulation, avec garde de 5 %
ou 150 tr/min. Les contrôles numériques ne remplacent pas une écoute sur enceintes.

Ce sont des simulations approximatives, pas des enregistrements constructeur.
Les configurations héritent notamment de cames, culasses, admission et géométrie
du modèle de départ. Le V12 adapte le Ferrari 412 T2 à 60°, 95 × 76,4 mm et
8700 tr/min. Le V10 Huracán hérite encore de la géométrie 72° du LFA : il n’est
pas une reproduction exacte du V10 Lamborghini. Les sweeps sont contrôlés au
banc et ne mesurent pas une accélération libre du véhicule réel.
Le V6 F1 ne simule ni hybride ni turbo. Aucun sifflement de turbo ni retour
d’échappement supplémentaire n’a été inventé : ils ne sont pas générés ici.
Les métadonnées turbo d’une description ne suffisent pas à les simuler.

Rapports complets : `validation/engine-simulation-0.13.8/`.
