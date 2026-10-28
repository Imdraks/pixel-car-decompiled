# Volumes — 0.14.3

Ouvrez **PARAMÈTRES → VOLUMES...**, près de la ligne Son. Les sept curseurs se
règlent à la souris de 0 à 100 %. Vous pouvez cliquer dans la barre ou faire
glisser sa poignée ; le niveau reste borné même en sortant de la barre.

- **Général** : niveau final de l’ensemble du jeu.
- **Moteur** : moteurs historiques/simulés, démarrage et extinction.
- **Turbo / compresseur** : sifflement, compresseur et valves de décharge.
- **Bruitages** : NOS, klaxon, collisions, changements de rapports et retours d’échappement.
- **Ambiance** : fond sonore du garage/de la ville.
- **Interface** : clics, installation et autres sons de menus.
- **Musique** : morceaux du menu et du garage, séparés de l’ambiance.

La musique est coupée en conduite, y compris dans les paramètres ouverts depuis
la route. Au retour au garage, le morceau reprend sa position. Les morceaux
proviennent de la banque Original ou Unbound sélectionnée pour le son.

Les changements sont audibles immédiatement. **ENREGISTRER** garde les niveaux,
**ANNULER** ou Échap revient aux niveaux enregistrés. **TOUT À 100 %** réinitialise
l’aperçu ; Enregistrer confirme ce choix. Sauver uniquement les volumes ne change
pas l’affichage et n’ouvre pas de confirmation de résolution.

Au garage, démarrez le moteur avec G avant d’ouvrir les paramètres ; dans la page
Volumes, Z permet de l’écouter et d’ajuster séparément moteur et turbo. En conduite,
la simulation reste suspendue pendant les paramètres ; la page Volumes donne un
aperçu sonore de l’état courant. Le commutateur Son de la page précédente garde
son rôle général : il doit être activé pour écouter le jeu.

Les niveaux sont enregistrés dans `settings.ini` du dossier utilisateur, normalement
`%LOCALAPPDATA%/PixelCarRacerNative` sous Windows. Ils sont globaux et indépendants
des sauvegardes de voitures. Les anciennes configurations sans curseurs conservent
les niveaux précédents à 100 %. Les valeurs invalides sont bornées ou réinitialisées.
Le général est appliqué une seule fois sur le périphérique, et chaque catégorie
agit sur ses sources. Les flux moteur restent chargés pendant les réglages.
