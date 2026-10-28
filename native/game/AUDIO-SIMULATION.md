# Sons simulés — 0.13.9

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

Les six banques sont désormais **actives dans le jeu**, au garage et en conduite :
LS, AMG GT63 S, Huracán EVO, Aventador, V6 F1 et Ford Coyote. Dans **SONS DU
MOTEUR**, les lignes accélération et décélération sur **AUTO** utilisent les
boucles simulées du moteur équipé. Un réglage manuel reste prioritaire pour
sa ligne ; deux réglages manuels reviennent entièrement aux profils historiques.
La banque Original/Unbound continue de déterminer ces profils et les effets.
Le LSX, le LT5 et les autres moteurs gardent leurs associations précédentes.

Le moteur Aventador S du catalogue emploie le pack V12 SVJ comme approximation ;
les deux variantes ne sont pas présentées comme identiques. G démarre le moteur
au garage avec son événement simulé ; G l’arrête avec le son d’extinction.
Maintenir Z fait varier les boucles avec le régime réel du moteur. L’entrée
sur la route commence directement avec le moteur en marche.

Le mixeur lit les associations compilées depuis les manifestes validés. Il garde
les 12 ou 15 flux de chaque pack en mémoire, interpole les deux régimes voisins
et les charges 0/30/100 %, ajuste la hauteur autour de chaque régime d’ancrage et
lisse volumes/hauteurs en 35 ms. Les flux ne redémarrent pas à chaque changement
de tours. Le démarrage se fond dans les boucles ; le ralenti, le rupteur, les
changements de rapports et la décélération suivent la conduite et le garage.
Le gain total des boucles reste borné à 0,55. Pause et désactivation du son
rendent les boucles muettes ; changer de moteur libère la banque précédente.
Si un pack manque, le mixeur reprend les sons historiques de ce moteur.

Les WAV/OGG sont stockés séparément dans `assets/engine-packs` avec les manifestes,
rapports, descriptions et licences. Les 188 sons d’origine restent intacts.
Les exports bruts et les scripts complets sont toujours téléchargeables dans
les six packs de la [release 0.13.8](https://github.com/Imdraks/pixel-car-decompiled/releases/tag/v0.13.8-native-preview).
Les sweeps accélération/décélération servent d’aperçus hors jeu ; en conduite,
le son continu est construit depuis les boucles pour suivre le régime réel.

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
