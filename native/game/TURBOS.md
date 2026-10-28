# Turbos PC — 0.14.0

18 nouveaux montages dans F4 → TURBOS, en plus des 16 pièces Original/Unbound.
La recherche « PC » affiche les ajouts, marqués **EXTENSION PC**. Les six classes
vont de COMMUN à CONTREBANDE. Équiper un montage biturbo ou quad équipe tout le
système dans un seul emplacement ; un compresseur et un montage turbo restent
exclusifs. Les montages sont conservés dans le profil et dans Mes voitures.

## Principes vérifiés sur Internet

- [Garrett — lecture des cartes compresseur](https://www.garrettmotion.com/knowledge-center-category/oem/expert/) :
  pression absolue, débit et rendement déterminent le choix du turbo. Deux
  turbos parallèles partagent la pression du collecteur ; leurs débits servent
  ensemble le moteur. Les PSI ne sont pas multipliés par le nombre de turbos.
- [Turbo Technics — turbo hybride de préparation](https://turbotechnics.com/what-is-a-hybrid-performance-turbo/) :
  assemblage ou modification de composants, notamment roues et carters, pour
  modifier le potentiel de débit et la réponse. Une reprogrammation et des
  adaptations peuvent être nécessaires. « Hybride » ne signifie pas forcément
  assistance électrique.
- [Garrett — E-Turbo](https://www.garrettmotion.com/emission-reduction/garrett-e-turbo/) :
  l’assistance électrique peut améliorer la réponse à bas régime. La récupération
  d’énergie et la gestion électrique constituent d’autres fonctions.
- [BorgWarner — technologies de suralimentation](https://www.borgwarner.com/technologies/boosting-technologies) :
  wastegate, géométrie variable et étagement régulé R2S correspondent à des
  architectures distinctes.
- [Bugatti — fiche technique Chiron](https://bugatti-newsroom.imgix.net/6670487131d99cf64fc74076/211122_BU_Chiron%20ENG-1.pdf),
  accessible depuis la [page constructeur](https://newsroom.bugatti.com/models/chiron) :
  quatre turbocompresseurs, suralimentation à deux étages et échangeur eau/air.

Recherche effectuée le 28 octobre 2026. Références, empreintes des textes
consultés et résumés vérifiés : `native/evidence/pc-turbos/research.json`.

## Modèle de jeu

Chaque nouveau montage définit sa pression, un potentiel de débit exprimé en
puissance moteur équivalente, ses seuils de montée en pression, sa vitesse de
réponse, sa masse et son profil sonore. La capacité indiquée en HP est un plafond
de préparation ; le gain effectif dépend du moteur, du régime et des pièces.

Le moteur fournit plus tôt les gaz nécessaires sur une grosse cylindrée. Une
correction native adapte donc les seuils et le délai du même montage à la
cylindrée équipée. Les biturbos parallèles ont une seule cible de pression.
Les séquentiels et quads répartissent cette cible entre un premier groupe et
un groupe supplémentaire qui entre progressivement en service. Les hybrides
utilisent leurs propres compromis de débit et de réponse. Les versions assistées
électriquement disposent d’une réponse plus rapide à bas régime.

L’échangeur conserve son rôle dans l’efficacité de suralimentation. Le débit
plafonne ensuite le gain de puissance des nouveaux systèmes ; il ne réduit pas
la puissance atmosphérique de base du moteur dans ce modèle. Le NOS est ajouté
après la puissance moteur. La préparation maximale compare maintenant les
couples moteur/montage avec la puissance réellement calculée.

Le jeu conserve le calcul des 16 anciens turbos, dont les données source ne
fournissent pas une carte de débit réelle. Les classes et le tri restent basés
sur la pression nominale dans la gamme du jeu ; le plafond de débit et la réponse
apportent les différences de comportement entre pièces d’une même classe.

## Catalogue

Les valeurs suivantes sont des **calibrations de jeu pour des pièces PC fictives**.
Elles ne sont pas des caractéristiques constructeur ni des performances garanties.
Les valeurs de réponse correspondent à une référence 3 L, avant adaptation à la
cylindrée équipée. Les modèles contrebande prolongent les préparations extrêmes
existantes du mod.

| Montage | Type | PSI | Capacité HP | Pleine pression de référence |
| --- | --- | ---: | ---: | ---: |
| PC S1 Street | Simple | 10 | 400 | 3600 tr/min |
| PC H1 OEM+ | Hybride de préparation | 16 | 600 | 3400 tr/min |
| PC T2 Street | Biturbo parallèle | 20 | 1000 | 4000 tr/min |
| PC E1 Response | Assisté électriquement | 22 | 800 | 2300 tr/min |
| PC H1 Sport | Hybride de préparation | 28 | 1000 | 4300 tr/min |
| PC T2 Sport | Biturbo parallèle | 32 | 1600 | 4400 tr/min |
| PC S1 Track | Simple | 35 | 1500 | 5500 tr/min |
| PC E1 Track | Assisté électriquement | 38 | 1800 | 3200 tr/min |
| PC S1 Race | Simple | 44 | 2200 | 6200 tr/min |
| PC T2 Race | Biturbo parallèle | 48 | 3200 | 5000 tr/min |
| PC H1 Race | Hybride de préparation | 52 | 2800 | 4800 tr/min |
| PC T2 Sequential | Biturbo séquentiel | 58 | 4200 | 5800 tr/min |
| PC Q4 Sequential | Quad séquentiel | 64 | 6000 | 6000 tr/min |
| PC E1 Pro | Assisté électriquement | 68 | 5200 | 3400 tr/min |
| PC T2 Drag | Biturbo parallèle | 74 | 9000 | 6400 tr/min |
| PC Q4 Drag | Quad séquentiel | 78 | 11000 | 6500 tr/min |
| PC T2 Hybrid Pro | Hybride de préparation | 82 | 12000 | 5600 tr/min |
| PC Q4 Contraband | Quad séquentiel | 85 | 14000 | 6500 tr/min |

## Sons et limites

Les profils adaptent le sifflement turbo déjà fourni par le jeu : hauteur,
niveau et évolution suivent la pression effective. Une valve de décharge par
défaut est associée au montage ; le choix manuel de valve reste prioritaire.
Ce sont des adaptations de sources audio du jeu, pas de nouveaux enregistrements
constructeur ou des sons de turbines exportés par Engine Sim. Les sons des
six moteurs simulés et les effets NOS/échappement continuent de fonctionner.

Le calcul est un modèle natif simplifié. Il n’intègre pas une carte compresseur
complète, le pompage, le sur-régime de turbine, les températures détaillées,
les pertes de tuyauterie, une batterie ou une récupération électrique.
L’étagement ne simule pas la multiplication des rapports de pression d’un
montage composé en série. Le seuil 3800 tr/min des exemples quads est un
choix de calibration, pas une donnée confirmée par la fiche Chiron consultée.
Les illustrations réutilisent les icônes de pièces existantes.

## Validation

72 associations de nouveaux turbos avec quatre familles de moteurs vérifient
pression, plafond de puissance et sauvegarde. Des essais distincts couvrent
l’étagement, la réponse temporelle, l’effet de cylindrée et l’exclusivité avec
le compresseur. Les 31 moteurs sont croisés avec ECU, induction et échangeurs :
175770 combinaisons. Les 267344 combinaisons de pièces de support restent
contrôlées. Les fichiers `pc-turbos.csv` et `turbo-response.csv` consignent les
résultats. Les profils sonores sont joués par le vrai mixeur logiciel Raylib.

Depuis la 0.14.1, G permet aussi d’entendre le turbo au ralenti dans le garage ;
maintenir Z renforce le sifflement et relâcher Z joue la valve. L’aperçu utilise
le montage équipé et fonctionne également pour les turbos historiques ou
d’usine. Le niveau de pression équivalent est réservé à l’audio du garage :
la voiture reste immobile, sans boost physique ni consommation de NOS.
