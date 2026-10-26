# Recherche ciblée de la physique d’Unbound

Bibliothèque Android x86 analysée en lecture seule : SHA-256
`fb3726e175e7d1c643e0ddac1ec1a365901c4d52a16ded97e89fd672f6a9e9cc`.
Aucun Android n’est exécuté et aucune bibliothèque Android n’est embarquée dans
le programme Windows natif.

## Résultats vérifiés

- `recover_yyc_fields.py` exporte 2 128 noms de variables depuis les symboles
  ELF `g_VAR_*`. Chaque pointeur de nom est vérifié contre son symbole.
- L’identifiant est le second mot de 32 bits. La valeur sentinelle `0xffffffff`
  est conservée comme `null` ; aucun offset d’instance n’en est déduit.
  Les autres identifiants sont uniques. Le pas de 16 octets est corroboré par
  les accès directs et les appels de lecture dans le désassemblage déjà conservé.
- `physics-fields.json` sélectionne les variables utiles ; `yyc-fields.json`
  conserve la table complète. Exemples : `RPM`, `gear_final`, `weight_to_power`,
  `wind_friction`, `peak_hp_RPM`, `peak_tq_RPM`.
- Ghidra 12.1.4 / JDK 21 récupère du pseudo-C de `ob_car_Step_1` et du script
  `kdbg_car_dump`. Les noms sont vérifiés aux offsets de fichier avant lecture.
  Ce pseudo-C conserve des types inconnus et des artefacts de pile : il ne peut
  pas être compilé directement ni traité comme du GML fidèle.

## Ce qui n’a pas été récupéré

`ob_car_Create_0` atteint la limite de décompilation de 150 s.
`ob_car_Step_0` (592 716 octets de symbole) dépasse d’abord la limite d’instructions.
Une seconde passe limitée à cette fonction, avec un plafond porté à 500 000
instructions et 100 Mo de réponse, atteint aussi la limite de 150 s.
Les échecs sont conservés dans `coverage.txt` et `large-main-coverage.txt`.

Les noms de champs ne fournissent ni les constantes par voiture, ni les unités,
ni les équations de couple, de boîte et de résistance. Ils ne justifient pas de
remplacer le modèle natif par des chiffres présentés comme ceux d’Unbound.
La fidélité de la conduite n’est donc pas établie par cette passe.

## Reproduire

```bash
python3 native/tools/recover_yyc_fields.py \
 --binary /workspace/windows-port/recovered/lib/x86/libyoyo.so \
 --output /tmp/pcr-yyc-fields.json
```

Pour Ghidra, employer `native/tools/PhysicsYYC.java`, `-noanalysis`, `-readOnly`
et un répertoire de projet temporaire. Le premier argument du script est le
répertoire de sortie ; le second argument optionnel `main-large` active la passe
principale avec un plafond d’instructions supérieur. Les offsets sont propres à
l’empreinte ci-dessus. Ne pas appliquer ces offsets à la version originale 1.2.5.

La suite demande une analyse par blocs du calcul principal avec résolution des
appels YYRValue, puis une comparaison à des séquences de conduite du jeu d’origine.
Le banc de mesure natif permet maintenant de collecter les mêmes grandeurs côté
Windows ; sa référence reste explicitement marquée comme provisoire.
