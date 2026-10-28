# Moteurs supplémentaires PC — 0.13.8

15 swaps ajoutés aux 16 moteurs du jeu : **31 moteurs équipables**.
Dans le garage, F1 → MOTEURS, chercher le nom et équiper. G démarre/arrête,
maintenir Z fait monter les tours. Le moteur équipé persiste dans la sauvegarde.
Les ajouts portent la provenance **EXTENSION PC** ; les moteurs récupérés
Original/Unbound gardent leur provenance et leurs associations audio vérifiées.

Les valeurs sont des calibrations natives inspirées des versions indiquées,
pas des fiches constructeur vérifiées ni des pièces extraites des archives Android.
HP désigne ici le cheval mécanique (745,7 W), différent du cheval métrique PS/ch.
Les masses sont des estimations de jeu sur l’échelle lb des pièces existantes.
La cylindrée, le régime, la forme du couple et l’inertie varient par moteur ;
la puissance de pointe sans pièce supplémentaire est ajustée au chiffre indiqué.

| Moteur / version de référence | HP | Régime maxi (tr/min) | L |
| --- | ---: | ---: | ---: |
| AMG GT63 S 2021 - M177 V8 | 621 | 7000 | 4 |
| Huracan EVO - V10 5.2 | 631 | 8500 | 5.2 |
| Aventador S - V12 6.5 | 730 | 8500 | 6.5 |
| F1 moderne - V6 1.6T | 750 | 15000 | 1.6 |
| Ford Mustang GT - Coyote V8 5.0 | 460 | 7500 | 5 |
| BMW M5 E60 - S85 V10 | 500 | 8250 | 5 |
| Lexus LFA - 1LR V10 4.8 | 553 | 9000 | 4.8 |
| Ferrari 458 - F136 V8 4.5 | 562 | 9000 | 4.5 |
| Porsche 911 GT3 - Flat-6 4.0 | 503 | 9000 | 4 |
| BMW M3 G80 - S58 I6 3.0T | 503 | 7200 | 3 |
| Audi RS3 - I5 2.5T | 394 | 7000 | 2.5 |
| Honda Civic Type R - K20C1 I4 | 306 | 7000 | 2 |
| Mazda RX-7 - 13B rotatif | 276 | 8000 | 1.3 |
| Dodge Hellcat - V8 6.2 SC | 707 | 6200 | 6.2 |
| Bugatti Chiron - W16 8.0T | 1479 | 6700 | 8 |

Le V6 F1 est un moteur thermique générique, sans ERS/MGU-K/MGU-H ni batterie.
Ses 750 HP sont un choix de simulation ; ce n’est pas un groupe propulseur
complet d’une écurie. Les repères sont Huracán EVO, Aventador S, Mustang GT
5.0 génération 3, M3 Competition G80, GT3 992, RS3 8Y, Type R FK8 US,
RX-7 FD japonais et Chiron standard. Le W16 complète volontairement la gamme
au-delà des moteurs routiers classiques.

## Physique et préparation

Les courbes sont des profils gaussiens de couple paramétrés, normalisés à la
puissance de pointe. Elles ne reproduisent pas des relevés de banc réels.
L’inertie intervient dans le réembrayage, le patinage et le départ ; les pneus,
la transmission, le transfert de charge et les aides conservent leur rôle.
Le swap garde le châssis, sa transmission choisie et sa répartition des masses.

La suralimentation montée d’usine est incluse dans la puissance et la courbe
annoncées ; un bruit de turbo/compresseur accompagne ces moteurs en charge.
Il n’y a pas de deuxième multiplicateur de puissance d’usine. Le montage d’un
turbo ou d’un compresseur du catalogue remplace cette couche sonore. Les gains
des pièces restent ceux de la préparation native du jeu, appliqués à la base
nominale, sans simulation de remplacement physique des turbos d’origine,
limite de résistance interne ni validation de compatibilité mécanique réelle.
Turbo et compresseur du catalogue restent mutuellement exclusifs.
Le bouton de préparation maximale compare désormais la puissance calculée de
chaque moteur dans la combinaison équipée, au lieu de choisir uniquement son
chiffre de puissance stock.

## Audio et visuels

Depuis la 0.13.9, six moteurs utilisent leurs banques simulées en AUTO : LS,
AMG, Huracán, Aventador (pack SVJ adapté), V6 F1 et Coyote. Les autres moteurs
utilisent les 12 échantillons historiques comme familles sonores adaptées.
Il ne s’agit pas d’enregistrements constructeur. Un V10/V12/F1 n’est donc pas garanti fidèle
au moteur réel. AUTO choisit une paire propre à la fiche PC ; les choix manuels
restent prioritaires. Les deux banques Original et Unbound sont utilisables.
Les icônes moteur sont réutilisées ; elles ne sont pas des illustrations exactes.
Le son d’usine est une approximation de charge, pas une mesure de pression turbo.

## Vérification

Tests de puissance nominale, courbe, inertie, sauvegarde/rechargement, sélection
audio, rupteur au garage et roulage pour les 15 ajouts. Le tableau `pc-engines.csv`
est produit par les tests du cœur Linux/Windows. Les croisements exhaustifs
couvrent les 31 moteurs avec ECU, induction, refroidissement et pièces de support.
La table source des 16 moteurs Android reste contrôlée séparément.
