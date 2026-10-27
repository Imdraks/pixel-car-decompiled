# Suspension, wheelie et aides à la conduite — 0.12.0

Au garage, appuyer sur **F9**, ou ouvrir **F5 → Réglages suspension**.
Les curseurs et boutons −/+ donnent un aperçu de la hauteur. **Enregistrer**
conserve la préparation ; **Annuler** conserve les réglages précédents.

| Réglage | Plage | Effet |
| --- | --- | --- |
| Hauteur | −60 à +120 mm | Ajustement ajouté à la suspension équipée ; modifie la caisse et le centre de gravité |
| Rigidité | ×0,40 à ×3,00 | Raideur des ressorts ; modifie le cabrage et le plongeon |
| Amortissement | 0,25 à 1,50 | Rapport d’amortissement ; contrôle les oscillations |
| Répartition avant | ±15 points | Déplace la répartition des masses autour de la calibration du châssis, sans ajouter de masse |
| Wheelie | Autorisé / limité au sol | Autorise la perte de contact ou applique une contrainte anti-levée |

Les préréglages **Route**, **Drag / Wheelie** et **Piste** combinent ces valeurs.
Ils conservent les pièces équipées. Les anciennes sauvegardes reçoivent un
ajustement de hauteur nul et un réglage Route ; leur suspension équipée reste en place.

Pour essayer un wheelie : choisir une propulsion puissante, des pneus adhérents,
le préréglage Drag et l’antipatinage activé. Accélérer ; le NOS peut aider une fois
la voiture en mouvement. Le réglage autorise le wheelie, mais ne garantit pas
qu’une voiture faible ou qui patine puisse lever. Le mode limité au sol empêche
la levée sans rendre les pneus infiniment adhérents.

## Modèle physique

Le châssis utilise un modèle longitudinal à deux essieux, avec deux degrés de
liberté : déplacement vertical de la masse suspendue et tangage. Chaque essieu
a un ressort préchargé par son poids statique et un amortisseur. Les forces
longitudinales aux pneus créent un moment autour du centre de gravité. Les
charges verticales qui en résultent déterminent l’effort transmissible aux pneus.

La fréquence de base des ressorts vaut 1,6 Hz ; le multiplicateur de rigidité
modifie leur raideur, et l’amortissement utilise le rapport réglé au garage.
La répartition de départ est une calibration native (60 % à l’avant pour une
traction, 48 % pour les autres transmissions), ajustable de ±15 points. La masse
totale et la puissance restent inchangées. L’empattement physique reste calibré
à 2,6 m ; il n’est pas une fiche constructeur propre à chaque carrosserie.

Les ressorts ne peuvent pas tirer la route : les charges restent positives ou
nulles. Après le débattement de détente, la roue peut quitter le sol et son
effort de traction disparaît. La roue, la caisse, le pot et les jets suivent les
mêmes transformations de tangage et de hauteur. Une roue en l’air ne produit
pas de fumée de contact au sol. Le châssis revient sous l’effet de la gravité,
des ressorts et des amortisseurs. Une butée angulaire à environ 31,5° empêche
un retournement complet dans ce mode libre.

L’intégration reste à 120 pas fixes par seconde. Le burnout volontaire reste
possible : à l’arrêt, la demande de freinage ne crée pas un faux plongeon de
caisse. Le point mort conserve l’inertie de la voiture et les mouvements de suspension.

## ABS et antipatinage

Les deux aides sont activées par défaut et se désactivent séparément dans
**Paramètres**, sous la ligne du trafic. **Appliquer**, puis **Conserver** valide
les choix ; le délai de rétablissement restaure aussi les aides non confirmées.
Les indicateurs **ABS** et **TC** montrent leur état et leurs interventions.

- **ABS** : régule le frein de service lorsque sa demande dépasse l’adhérence.
  Sans ABS, les roues peuvent se bloquer et le frottement glissant réduit
  l’effort de freinage. Le frein à main reste une commande indépendante de blocage arrière.
- **Antipatinage / TC** : réduit le couple livré lorsque la demande dépasse
  l’adhérence de l’essieu moteur. Désactivé, il laisse les roues patiner et
  l’effort peut baisser sous l’effet du glissement. Il ne modifie pas les chevaux
  annoncés au banc : le HUD montre la puissance effectivement livrée à cet instant.
- Le burnout volontaire contourne la régulation TC ; le NOS reste bloqué pendant
  le burnout et le point mort. Ces commandes existantes restent utilisables.

## Validation et limites

Le scénario de freinage du châssis de référence de série passe d’environ 48,62 m
avec roues bloquées à 36,83 m avec ABS, depuis 100 km/h. La préparation de
lancement testée parcourt environ 126,60 m en 5 secondes avec TC contre 99,52 m
sans TC. Ce sont des mesures du modèle natif, pas des valeurs constructeur.

Les tests couvrent 64 combinaisons extrêmes, la sauvegarde, le retour au sol,
les contacts des pneus, les réglages et l’indépendance aux FPS. Les mesures
sont dans `validation/` et le rapport Windows joint à la release.

Ce modèle reste une approximation longitudinale sur route plane : ressorts
linéaires, contacts simplifiés et adhérence calibrée. Il ne récupère pas les
équations complètes Android et ne simule pas encore une géométrie complète
de suspension, les bosses de route, les virages ou les caractéristiques constructeur.
Le banc générique historique est conservé pour les régressions ; les nouveaux
essais de suspension et d’aides utilisent les châssis natifs effectivement jouables.
