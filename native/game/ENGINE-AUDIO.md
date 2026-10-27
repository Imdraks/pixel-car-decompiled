# Sons des moteurs — vérification source 0.13.4

L’association AUTO des 16 moteurs interchangeables est désormais récupérée dans
les deux codes Android, plutôt qu’attribuée par famille supposée. Les deux banques
utilisent les mêmes identifiants de sons, mais leurs fichiers audio sont différents.

Dans **SONS DU MOTEUR**, mettre les lignes accélération et décélération sur
**AUTO** pour entendre l’association du moteur équipé. Les choix manuels
sauvegardés restent prioritaires ; changer de moteur ne les efface pas.

| Moteur équipé | Accélération | Relâchement |
| --- | --- | --- |
| SR20 | `sfx_engine2` | `sfx_engine` |
| 2JZ | `sfx_engine2` | `sfx_engine` |
| K20 | `sfx_engine2` | `sfx_engine` |
| RB25 | `sfx_engine2` | `sfx_engine` |
| RB26 | `sfx_engine2` | `sfx_engine` |
| 1JZ | `sfx_engine2` | `sfx_engine` |
| VR38 | `sfx_engine_6` | `sfx_engine3` |
| LS | `sfx_engine4` | `sfx_engine` |
| FR9 | `engine_test1` | `sfx_engine` |
| F1X | `sfx_engine` | `sfx_engine4` |
| Hemi | `sfx_engine4` | `sfx_engine` |
| Hemi 24K | `sfx_engine4` | `sfx_engine` |
| LSX | `sfx_engine4` | `sfx_engine` |
| LT5 | `sfx_engine4` | `sfx_engine` |
| Spoon | `sfx_engine2` | `sfx_engine` |
| 2AR | `sfx_engine2` | `sfx_engine` |

Le jeu partage plusieurs sons entre moteurs : il n’existe pas un enregistrement
unique pour chacun des 16 moteurs. La table donne les fichiers du jeu, sans leur
attribuer un réalisme constructeur. `sfx_engine2e` était utilisé par approximation
pour plusieurs moteurs PC ; il n’est pas le son de relâchement prévu pour ces swaps.

## Preuve et reproduction

Le script lit statiquement les ELF x86, vérifie leurs SHA-256 puis remonte la chaîne :
`engine_hp` du moteur de remplacement → écritures des profils `e_s` / `e_s2` →
dispatch vers les sons. Les 15 gardes de puissance couvrent les 16 pièces, car
certaines partagent la même puissance et le même branchement. Le résultat est
identique dans Original et Unbound. Le code Android n’est jamais exécuté.

Le compilateur du jeu original stocke les cas du switch dans une table de
`YYRValue` suivis d’un numéro de branche. Ce numéro n’est pas toujours le profil
sonore : le script reconstruit les valeurs littérales avant de comparer avec Unbound.
Il traite aussi le profil `-1`, qui choisit le son de relâchement par défaut.

```bash
python native/tools/recover_engine_assignments.py \
  --output /tmp/engine-audio.json --header /tmp/engine_assignments.hpp
```

[Rapport source avec adresses et empreintes](../evidence/merged/engine-audio-assignments.json).
Le rapport est aussi fourni dans le ZIP Windows sous `associations-moteurs-sons.json`.
Les tests contrôlent les 32 sélections moteur/banque et la priorité indépendante
des choix manuels. Le mixeur logiciel couvre les 16 moteurs en accélération et
au relâchement dans chaque banque, avec recherche d’échecs de décodage.

## Limites

La sélection des sons des **moteurs stock**, sans swap équipé, n’est pas établie
par cette extraction et conserve son comportement PC précédent. Les équations
originales de pitch, de volume et de transition restent à reconstruire. La preuve
concerne le choix des fichiers, pas une équivalence complète du mixage Android,
ni une écoute sur des haut-parleurs physiques.
