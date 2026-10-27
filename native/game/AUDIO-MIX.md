# Mixage moteur — 0.13.6

La sélection des 16 moteurs reste celle récupérée des deux codes source. Cette
version corrige le **rendu PC** de ces fichiers ; elle n’ajoute pas d’enregistrements
constructeur et ne prétend pas reproduire toutes les équations audio Android.

- La boucle en charge domine à l’accélération, celle de relâchement domine sans
  les gaz. Un fondu de 65/100 ms remplace la superposition permanente.
- Les deux couches utilisent la même hauteur pendant le fondu. L’ancien décalage
  de 6 % et les doublons identiques pouvaient créer un effet de chorus/phase.
- La courbe native devient `0,5 + RPM / 10000`, bornée à 0,5–1,65, au lieu de
  `0,45 + RPM / 6500`. À 8000 tr/min, le facteur passe de 1,68 à 1,30. Le pitch
  suit les transitions avec un lissage de 35 ms ; il continue à suivre le régime.
- Les gains des 188 ressources sont conservés depuis leurs métadonnées, puis
  appliqués aux boucles. Les niveaux relatifs moteur, souffle et décélération
  ne sont plus traités comme si tous les enregistrements avaient le même gain.
- Les jonctions dépassant 4 % de pleine échelle reçoivent un raccord en mémoire
  de 12 ms, avec poids complémentaires. Les petites jonctions restent intactes.
  Les fichiers et banques source ne sont pas réencodés sur disque.
- Au garage, le rupteur module le moteur sans déclencher obligatoirement le son
  de détonation toutes les 130 ms. Les détonations du 2STEP en conduite restent actives.

## Vérifications

Les 24 enregistrements moteur/banque sont décodés et vérifiés sans hausse de pic
ni dégradation de la jonction. Dans Original, le saut du VR38 passe de 0,113 à
0,010 ; celui du FR9 de 0,235 à 0,038, en amplitude normalisée. Le pic global de
chaque enregistrement reste identique. Ces mesures détectent les raccords, pas
une amélioration perceptive universelle.

Le mixeur réel Raylib couvre les deux banques, profils manuels, 16 moteurs AUTO,
démarreur et rupteur. Les tests de garage contrôlent toujours G/Z et la protection
de recherche. Le comportement reste natif et le rendu final dépend aussi des
fichiers source et du matériel d’écoute.
