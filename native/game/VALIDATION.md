# Validation 0.14.0 — turbos et étagement

- 355 contrôles du cœur Linux/Windows compilés : 72 couples nouveau turbo/moteur,
  plafonds de pression et de puissance, biturbo sans multiplication des PSI,
  étagement quad progressif, effet de cylindrée, montée effective dans le temps,
  exclusivité turbo/compresseur et sauvegarde.
- 175770 combinaisons moteur/ECU/induction/échangeur et 267344 combinaisons de
  pièces de support. Préparation maximale : 14000 HP, 14250 avec NOS, selon les
  calibrations natives fictives du catalogue contrebande.
- 93 contrôles graphiques Linux : recherche des 18 ajouts, provenance PC et
  sauvegarde d’un montage quad. Les 10 essais de collection avec clics/touches
  restent valides après ajout des pièces.
- Vrai mixeur Raylib sur périphérique logiciel : 18 profils turbo/valve joués
  avec les 12 cas moteur/banque. Crête mesurée 0,468229, valeurs finies et aucun
  échec de chargement. Sons turbo adaptés des échantillons du jeu.
- Les 470 ressources, dont 188 sons historiques et 198 fichiers moteur simulés,
  restent identiques octet par octet à la release 0.13.9. Les figures de référence
  des suspensions gardent les pièces historiques pour isoler les régressions.
- Recherche : sources Garrett, Turbo Technics, BorgWarner et fiche Chiron Bugatti
  effectivement consultées ; principes repris et limites documentés dans TURBOS.md.
- Rapports : `validation/turbos-0.14.0/`. Les chiffres de pièces et les courbes
  sont des calibrations du jeu, sans équivalence constructeur ou thermodynamique
  complète. Écoute sur enceintes non établie.

# Validation 0.13.9 — audio simulé actif et collection de voitures

- 348 contrôles du cœur : interpolation régime/charge des six banques, somme
  des gains, transitions aux ancrages, priorité indépendante des profils manuels,
  sauvegarde complète des voitures nommées et copie de sécurité à la mise à jour.
- 91 contrôles graphiques Linux, dont enregistrement de deux carrosseries puis
  rechargement de la première. 10 contrôles supplémentaires avec de vrais clics
  et touches : nom accentué, plusieurs configurations, restauration de tous les
  champs, mise à jour avec backup et persistance après redémarrage de l’application.
- Les 198 WAV/OGG simulés sont décodés et vérifiés par le jeu : 44,1 kHz mono,
  valeurs finies, non-silence, durées, crêtes <0,99 et raccords de boucles ≤0,04.
- Mixage Raylib réel sur périphérique logiciel : 12 cas moteur/banque simulés,
  aucun redémarrage de flux pendant les changements de tours et de charge,
  événements de démarrage/arrêt, profils manuels partiels et complets, mute et
  retour à un moteur historique. Les essais G/Z réels couvrent LS et V6 F1 :
  47 contrôles chacun, dont la banque effectivement sélectionnée et l’arrêt.
- Les configurations mécaniques, les fichiers source Original/Unbound et les
  sauvegardes existantes sont préservés. Les packs bruts restent en release 0.13.8.
- Audio simulé approximatif ; écoute sur enceintes et équivalence constructeur
  non établies. Rapports : `validation/active-audio-0.13.9/` et
  `validation/saved-cars-0.13.9/`.

## Publication Windows vérifiée — 0.13.9

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40671070629) :
  348 contrôles du cœur, 91 graphiques, 188 sons historiques et 198 fichiers
  simulés décodés, avec 24 raccords historiques conservés ou améliorés.
- La collection enregistre deux voitures et recharge la première sous Windows.
  La copie de sécurité avant mise à jour et tous les champs sérialisés sont
  vérifiés aussi dans les tests du cœur Windows.
- Les 1528 compositions et les trajectoires mécaniques restent identiques à
  Linux à 0,01 près. Les six banques simulées sont incluses et actives en AUTO.
- Archive publique, CRC, SHA-256, EXE, source compilée, quatorze aperçus et
  470 ressources vérifiés, avec comparaison de chaque ressource aux fichiers
  testés. Restauration vide puis réutilisation : 470 ressources à chaque passage. Les 248 ressources précédentes restent identiques.
- Le mixeur réel logiciel Linux passe les 12 cas moteur/banque à une crête
  mesurée de 0,254707 ; les réglages manuels indépendants, démarrage, extinction,
  changements de tours sans redémarrage de flux et mute sont contrôlés.
  L’écoute sur enceintes et un périphérique audio Windows physique restent
  non établis. Le décodage et l’interpolation sont vérifiés sous Windows.
- Rapports : `validation/windows-0.13.9/`, `validation/active-audio-0.13.9/`
  et `validation/saved-cars-0.13.9/`.
- Source compilée : `139f3a9f5b6539015cb5e3f0c4f5bd716e92efd3`.
- ZIP : 86549102 octets, SHA-256 `4d03bc85ef74002eddc822e4bf8f210f759742dbcf07da910f8cadfe43bb23b2`.
- EXE : SHA-256 `b3ae9dc53e813909e446a87dc7e2d7919339711b77184b8ec22275bd7151f820`.

# Validation 0.13.8 — moteurs PC et export audio

- 339 contrôles du cœur Linux, exécutables Linux/Windows compilés ;
  105462 combinaisons moteur/ECU/induction/intercooler et 267344 combinaisons
  moteur/admission/pistons/échappement vérifiées. 15 ajouts, 31 swaps au total.
- 88 contrôles graphiques Linux, recherche AMG/provenance PC et rupteur V6 F1
  à 15000 tr/min compris. Les régressions suspension gardent le châssis LT5
  historique ; les nouveaux moteurs ont leurs propres essais de roulage.
- Mixeur Raylib réel sur périphérique logiciel : 31 moteurs AUTO par banque,
  profils manuels et événements. Aucun échec de chargement sonore.
- Six simulations exportées et traitées : 99 WAV + 99 OGG, sans saturation
  source ni crête de sortie ≥0,99, chaque OGG redécodé et mesuré. Les 188 sons
  du jeu sont identiques au téléchargement 0.13.7. Les packs restent non activés.
- Bootstrap du simulateur reconstruit dans un dossier vierge ; les données
  d’export sont conservées avec empreintes, descriptions, scripts et journaux.
- Rapports : `validation/pc-engines-0.13.8/` et
  `validation/engine-simulation-0.13.8/`. Écoute sur enceintes et fidélité à
  chaque moteur réel non établies ; modèles physiques/audio approximatifs.

## Publication Windows vérifiée — 0.13.8

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40662561584) :
  339 contrôles du cœur, 88 graphiques, 188 sons décodés et 24 boucles source.
- Les 15 moteurs PC sont validés aussi sous Windows ; tableau des puissances,
  régimes et inerties identique à Linux à 0,01 près. Les 1528 compositions de
  carrosserie et les trajectoires physiques concordent entre plateformes.
- Téléchargement public vérifié : CRC, SHA-256, EXE et commit source, treize
  aperçus, six archives audio et les empreintes de leurs 99 WAV + 99 OGG.
  Les packs contiennent également les WAV bruts et restent non activés.
  Restauration vide puis réutilisation : 248 ressources à chaque passage.
- Rapports : `validation/windows-0.13.8/`. Les échantillons simulés ont été
  contrôlés sous Linux avec FFmpeg ; les tests Windows décodent la banque
  actuellement utilisée par le jeu. Écoute sur enceintes non établie.
- Source compilée : `37224e665166292859db4a661b7d2ce25a136075`.
- ZIP : 109886568 octets, SHA-256 `5743bcf37fb1794f64ba387f3aa2c09c71bf1b9f67374dfa95285dcdd24c6db8`.
- EXE : SHA-256 `7edbdae82719411367717d736c38bea98ed265516e7cb3f048640774c2f39e00`.

# Validation 0.13.7 — montée en régime du son LS/V8

- 336 contrôles du cœur Linux : timbre bas régime conservé, élévation du LS/V8
  vérifiée à 8000 et 9500 tr/min, progression monotone et plafond respecté
  jusqu’à 14000 tr/min. Les autres profils gardent la courbe précédente.
- Le mixeur logiciel couvre les deux banques, profils et moteurs AUTO, et
  désormais explicitement le LS au garage jusqu’au rupteur, puis son extinction.
- La courbe audio suit le régime absolu, pas le réglage du rupteur. Elle concerne
  le fichier sfx_engine4 et conserve le fondu charge/relâchement de 0.13.6.
- Réglage natif soumis à l’écoute utilisateur, sans équivalence Android revendiquée.

## Publication Windows vérifiée — 0.13.7

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40645316578) : 336 contrôles du cœur, 86 graphiques et 188 sons décodés.
- Bas régime du LS/V8 conservé, montée plus haute à 8000/9500 tr/min et
  progression bornée testées sous Windows. Le test du mixeur Linux joue
  explicitement le LS au garage jusqu’au rupteur dans chaque banque.
- Les 24 boucles moteur conservent ou réduisent leur jonction sans augmenter
  leur pic. Les 1528 compositions et mesures physiques concordent avec Linux.
  Les contrôles pixels des matériaux, effets et défilement passent.
- Archive publique, CRC, EXE, source compilée, tableau des sons et treize
  aperçus Windows vérifiés ; restauration vide puis réutilisation : 248 ressources.
- Rapports : `validation/windows-0.13.7/` et `validation/ls-audio-0.13.7/`.
  Audio et rendu sur périphériques logiciels ; courbe audio native, perception
  finale à confirmer à l’écoute utilisateur.
- Source compilée : `dd6de90acae766cd27ac9bbc69a77db748499ae0`.
- ZIP : 59490038 octets, SHA-256 `0fc9ac1f4c8f08d36eaece42e7f8284d8ce3dc23e6a2c38e01b0fe0b4c9ca47d`.
- EXE : SHA-256 `fe24412e4121fb274ddf857b56c0efe14fe7b7e73b0474383f9e981368ac3b70`.

# Validation 0.13.6 — rendu audio moteur

- 333 contrôles du cœur Linux, dont enveloppe de charge, transitions de pitch,
  arrêt et raccord de boucle sans hausse des pics.
- 188 sons décodés ; les 24 cas moteur/banque ont une jonction conservée ou
  réduite et ne dépassent pas leur pic initial. Fichiers source non modifiés.
- Le mixeur logiciel couvre banques, 16 moteurs AUTO, profils manuels, G/Z,
  démarreur et rupteur ; aucune erreur de décodage des flux.
- 86 contrôles graphiques et 39 essais de touches avec audio réussis sous Linux.
- Il s’agit d’un réglage du mixage natif, pas d’une validation subjective sur
  tous les matériels ni d’une récupération complète du mixage Android.

## Publication Windows vérifiée — 0.13.6

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40583909362) : 333 contrôles du cœur, 86 graphiques et 188 sons décodés.
- Les 24 cas moteur/banque conservent ou réduisent leur saut de jonction sans
  augmenter les pics, sous Windows comme sous Linux. Les fichiers source restent inchangés.
- Le mixeur logiciel Linux couvre charge/relâchement, les deux banques, profils
  et moteurs AUTO ; les 39 essais de touches avec audio passent également.
- Six captures avant/après sur 2JZ, LT5 et FR9 : aucune valeur non finie ni
  écrêtage. Fréquence du PCM de capture étalonnée à 48000 Hz avec un signal
  1000 Hz. Comparatif public à RMS 0,12 par gain constant, sans égalisation ou
  compression dynamique. Ces captures ne sont pas alignées à l’échantillon près.
- Les 1528 compositions et mesures physiques concordent avec Linux ; les
  contrôles pixels des effets, matériaux et défilement passent.
- ZIP public, EXE, CRC, source compilée, tableau des sons et treize aperçus
  Windows vérifiés. Le ZIP du comparatif et les six empreintes WAV sont vérifiés.
- Restauration sur dossier vide puis réutilisation : 248 ressources.
- Rapports : `validation/windows-0.13.6/` et `validation/audio-mix-0.13.6/`.
  Rendu Mesa et périphérique audio logiciel ; aucune promesse de qualité
  subjective universelle ni d’équivalence complète du mixage Android.
- Source compilée : `431dfa114448c2e8580a8abc682ec0a5e44db8e7`.
- ZIP : 59488759 octets, SHA-256 `40b5c6ddb298310fddf9f443d18153d23571bd39090db5f4d5a7b3052086eb26`.
- EXE : SHA-256 `d44361eb253cbe0bb1f13fa26079a726572c1c69e2988f22c66601f9364f31b8`.

# Validation 0.13.5 — moteur au garage

- 327 contrôles du cœur Linux : G/Z au garage, ralenti, limiteur borné, retour
  au ralenti, changement de régime maximal avec le moteur et extinction.
- La voiture et les roues restent immobiles ; aucun NOS n’est consommé.
- Le mixeur logiciel couvre démarreur, régime au garage, limiteur et arrêt
  dans les deux banques, en plus des 16 associations moteur/son.
- Les raccourcis sont bloqués pendant la recherche de pièces et les dialogues.
  Le moteur s’arrête en quittant le garage ; cet état temporaire n’est pas sauvegardé.
- 86 contrôles graphiques et 39 essais de touches réelles avec audio passent
  sous Linux. Les captures et contrôles pixels des effets et matériaux passent.
- Preuves : `validation/garage-engine-0.13.5/`.
- Le comportement de régime/limiteur reste une adaptation native.

## Publication Windows vérifiée — 0.13.5

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40579889724) : 327 contrôles du cœur, 86 graphiques et 188 sons décodés.
- Démarrage au garage, régime jusqu’au limiteur et arrêt vérifiés dans
  l’application Windows. Capture du régime et de l’indication RUPTEUR revue.
- Les 39 essais de touches avec audio et le mixage du démarreur/limiteur
  concernent Linux et un périphérique logiciel, pas des haut-parleurs physiques.
- 1528 compositions et mesures physiques concordent avec Linux ; les contrôles
  pixels des matériaux, huit fumées, NOS/flammes et défilement réussissent.
- Archive publique redéchargée : CRC, SHA-256, EXE, source compilée, tableau des
  sons et treize aperçus Windows vérifiés. Restauration vide puis réutilisation :
  248 ressources. Rapports : `validation/windows-0.13.5/`.
- Rendu Mesa de CI ; GPU physique et équivalence audio complète Android non établis.
- Source compilée : `cb867e6cfaf273dd62d963d3f6b2d4a7bb537fda`.
- ZIP : 59482374 octets, SHA-256 `b84112e0553e5b598e50b22719ad3b6cba61cbf93a5f5d32055fa05f2738b9ff`.
- EXE : SHA-256 `ad828071d5ae3e086b0e57d914b511aef735c45b5a50ae2aad8003fa7e69180e`.

# Validation 0.13.4 — associations source moteur/son

- Les 15 gardes de puissance couvrant 16 moteurs interchangeables sont extraites
  séparément des deux ELF vérifiés ; profils et identifiants audio concordent.
- AUTO reprend les sons source de charge et de relâchement. Les préférences
  manuelles restent prioritaires. La sélection des moteurs stock reste à confirmer.
- 321 contrôles du cœur Linux, dont 32 cas moteur/banque et priorité des overrides.
- Mixage des 16 moteurs dans les deux banques, en charge et au relâchement,
  sur périphérique logiciel ; aucune revendication d’écoute physique.
- Correspondances : `ENGINE-AUDIO.md` et `../evidence/merged/engine-audio-assignments.json`.

## Publication Windows vérifiée — 0.13.4

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40559696895) : 321 contrôles du cœur, 83 graphiques et 188 sons décodés.
- Les 32 cas moteur/banque sont vérifiés sous Windows. La table des profils,
  les 16 associations AUTO et le profil par défaut de relâchement sont récupérés
  indépendamment dans les deux codes source Android.
- Mixage logiciel Linux des 16 profils manuels et des 16 moteurs AUTO dans chaque
  banque, charge et relâchement : PCM non silencieux, aucune erreur de décodage.
- 1528 compositions et mesures physiques concordent avec Linux ; les contrôles
  pixels des matériaux, huit fumées, NOS/flammes et défilement réussissent.
- Archive publique redéchargée : CRC, SHA-256, EXE, source compilée et treize
  aperçus Windows vérifiés. Restauration vide puis réutilisation : 248 ressources.
- Rapports : `validation/windows-0.13.4/` et `validation/engine-audio-0.13.4/`.
  Périphérique audio logiciel et rendu Mesa ; haut-parleurs et GPU physiques non testés.
- Source compilée : `28cd5877cbdc221c7d4533f6cd1e3e6cdec3e5e7`.
- ZIP : 59478750 octets, SHA-256 `3c2888c196bc135b3e0cc461dfa9537d3201f009eb11919cd10e164bf40350ab`.
- EXE : SHA-256 `c494663eb5c53eed81ee419bafc4a7d604da9110c9b2b87eebefce16d467637b`.

# Validation 0.13.3 — régime libre au frein à main et puissance/cabrage

- 319 contrôles du cœur Linux réussis. Trois transmissions vérifiées : régime
  libre au frein à main, aucune transmission de couple aux roues, maintien du
  rapport, NOS coupé, retour au ralenti et réengagement protégé.
- Cinq niveaux de puissance comparés sur le même châssis, à masse et adhérence
  identiques, sans NOS : 200/400/800/1200/2000 ch donnent 0/0/0,040/0,206/0,385 m
  de levée. Les moteurs plus puissants lèvent plus tôt dans ces scénarios.
  Les limites d’adhérence, le TC et les passages de rapports restent actifs.
- 83 contrôles graphiques et 160 essais clavier/souris Linux : 29 châssis/curseur,
  28 burnout/point mort/frein à main, 18 personnalisation, 69 garage/audio et
  16 affichage/trafic. Contrôles pixels des matériaux et effets réussis.
- Départ au rupteur TC coupé : 200/400/1200 ch donnent 6,09/7,75/27,75 m
  de glissement sur le même châssis. Parité frein à main/point mort, TC,
  régime initial, énergie au couplage et essieux motrices vérifiés.
- Preuves : `validation/handbrake-0.13.3/`. Modèle natif calibré, sans équivalence
  complète avec les équations Android ou les mesures constructeur.

## Publication Windows vérifiée — 0.13.3

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40556300412) : 319 contrôles du cœur, 83 graphiques et 188 sons décodés.
- Départs au rupteur, progression du cabrage avec la puissance, 191 voitures,
  suspension, barres et réglages concordent avec Linux à 0,01 près sur les CSV.
  Les 1528 empreintes de compositions de carrosserie sont identiques.
- Capture Windows du départ fumant revue. Matériaux, huit fumées, NOS/flammes
  et défilement passent les contrôles pixels. Les 160 essais clavier/souris
  Linux restent réussis ; ils ne sont pas revendiqués comme essais Windows.
- Archive publique redéchargée : CRC, SHA-256, EXE et source compilée vérifiés.
  Les treize aperçus correspondent aux captures Windows validées.
- Restauration sur dossier vide puis réutilisation : 248 ressources chacune.
- Rapports : `validation/windows-0.13.3/`. Rendu Mesa logiciel ; GPU et
  haut-parleurs physiques non testés. Modèle natif calibré, sans équivalence Android complète.
- Source compilée : `fc7ec0a6c0df8aaf8df42f3b3251cc4415841626`.
- ZIP : 59473879 octets, SHA-256 `a3641a8e8e4c3593e0c68a34cb5f4c2ae0afc21892d3f47b2f235d3ac88f4b27`.
- EXE : SHA-256 `30ff5a5f0dde837cc4789ac359dadbc3c5fe93690bf9c03377cd3f709d92cc0e`.

# Validation 0.13.2 — roues attachées et curseur Wheelie → Balanced

- 304 contrôles du cœur Linux réussis, dont 9168 vérifications des axes de
  fixation des moyeux sur les deux banques, trois hauteurs et quatre tangages.
- Compression mécanique limitée à 80 mm et détente à 120 mm, indépendantes de
  la raideur ; les cinq réglages de lancement respectent les butées vérifiées.
- Cinq positions du curseur donnent 0,2795 / 0,2445 / 0,1570 / 0,0697 / 0 m de
  levée sur la référence, sans changer sa répartition des masses.
- Sauvegarde et migration du curseur, extrêmes châssis, 382 montages de barres,
  six départs Drag et paramètres des 191 voitures conservés.
- 79 contrôles graphiques et 147 essais clavier/souris Linux réussis : 29 châssis/
  Drag/barres/balance/curseur bleu, 15 burnout, 18 personnalisation, 69 garage/audio,
  16 affichage/trafic. Les contrôles pixels existants passent aussi.
- Captures du réglage bleu et du wheelie revues. Preuves :
  `validation/wheel-carriers-0.13.2/`. Modèle natif calibré ; équations complètes
  Android, trains réels et géométrie d’anti-squat non importés.

## Publication Windows vérifiée — 0.13.2

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40549637636) : 304 contrôles du cœur, 79 graphiques, 188 sons décodés,
  contrôle des 9168 points de liaison et des cinq réglages progressifs réussi.
- Les mesures des 191 voitures, 382 montages de barres, départs Drag, trajectoires
  de suspension et cinq réglages concordent avec Linux à la précision des CSV.
  Les 1528 empreintes des compositions de carrosserie sont identiques.
- Captures Windows du curseur bleu et du wheelie revues ; les contrôles pixels
  des matériaux, huit fumées, NOS/flammes et défilement réussissent.
- Archive publique redéchargée : CRC, SHA-256, EXE et source compilée vérifiés.
  Les treize aperçus correspondent aux captures Windows, dont le nouveau curseur.
- Restauration sur dossier vide puis réutilisation : 248 ressources chacune.
- Rapports : `validation/windows-0.13.2/`. Rendu Mesa logiciel ; GPU et
  haut-parleurs physiques non testés. Aucune équivalence complète Android.
- Source compilée : `98dc4fa93297467b56d5682b454f4efd3a23c523`.
- ZIP : 59469777 octets, SHA-256 `add57d7571a86f81ec3461cb9e54e3f76c4e70de7d9763bfaaed22ea6a36ba4c`.
- EXE : SHA-256 `b9dce7e6d5156a89c9424e9b199a071a024a88a2b350d5196109c5cdb90bc525`.

# Validation 0.13.1 — Drag, wheelie bars et balance

- 297 contrôles du cœur Linux réussis. Les six lancements traction/propulsion/
  intégrale avec et sans TC conservent le contact au sol dans le préréglage Drag.
- Les wheelie bars DRAG PRO des 382 entrées source ont été testées pendant six
  secondes : valeurs finies et respect du plan de contact ; levée maximale nulle
  dans ces scénarios. Référence sans barre : 0,379724 m ; avec barre : 0 m.
- Le repère Balanced 50/50 donne des charges statiques égales pour les trois
  transmissions ; pièces, masse et réglage Wheelie restent indépendants.
- 78 contrôles graphiques Linux et 141 essais clavier/souris : 23 châssis/Drag/
  barres/balance, 15 burnout, 18 personnalisation, 69 garage/audio, 16 affichage/trafic.
- Les captures des matériaux, huit fumées, NOS/flammes et défilement passent les
  contrôles pixels. Preuves : `validation/drag-0.13.1/`.
- Analyse statique des deux bibliothèques : code de conduite localisé, mais
  équations complètes Android non importées. La réaction des barres et les
  préréglages sont natifs. Voir `DRAG.md` et `native/evidence/merged/drag-physics/`.

## Publication Windows vérifiée — 0.13.1

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40528066686) : 297 contrôles du cœur, 78 graphiques, audit des 382 entrées et
  188 sons décodés. Archive publique, EXE, source, CRC et treize aperçus vérifiés.
- Source compilée : `cc21df5a4e10496b9998ef1422d5b8997ee71031`.
- ZIP : 59461066 octets, SHA-256 `59a55569be89b9c7d351d1a764488ecbaf44b035b05d977df845c4c4d4795789`.
- EXE : SHA-256 `37fa23453f797a808568add8aee67a56e6f0c5e8572abe39a0deac5800c4c069`.
- Rapports : `validation/windows-0.13.1/`. Mesa logiciel ; aucune équivalence
  complète avec Android ni validation sur GPU physique.

# Validation 0.13.0 — personnalisation et matériaux

- 277 contrôles du cœur Linux réussis ; 2376 nuances source, 521 recettes de
  finition de jantes et sauvegarde indépendante des essieux vérifiées.
- Audit des 382 entrées de carrosserie : 192146 associations, 129 variantes
  absentes signalées, 2309 kits partiels, 27122 montages d’accessoires.
- 1528 compositions de carrosserie exportées et 14898 montages des pots de capot
  contrôlés ; 1242 replis sans capot distingués des contacts géométriques.
- 74 contrôles graphiques et 133 contrôles clavier/souris Linux réussis : 18
  nouveaux de personnalisation, 15 châssis, 15 burnout, 69 garage/audio et 16
  affichage/trafic. Les matériaux et pots sont aussi revus sur captures.
- Preuves : `validation/customization-0.13/`. Les coordonnées Android des pots
  de capot ne sont pas récupérées ; leur ajustement est natif. Aucune équivalence
  complète Android n’est revendiquée. Voir `CUSTOMIZATION-COMPLETE.md`.

## Publication Windows vérifiée — 0.13.0

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40522763934) : 277 contrôles du cœur, 74 graphiques,
  188 sons décodés, audit des 382 entrées et douze peintures distinctes vérifiés.
- Les 1528 empreintes de compositions de carrosserie sont identiques à Linux ;
  mesures des 191 voitures et trajectoire de suspension concordantes à 0,01 près.
- Captures Windows des matériaux et pots de capot revues ; contrôles pixels des
  matériaux, flammes, NOS, huit fumées et défilement réussis.
- Archive publique redéchargée : CRC, SHA-256, EXE et source compilée vérifiés.
  Les treize aperçus publics correspondent aux captures Windows validées.
- Restauration sur dossier vide puis réutilisation : 248 ressources chacune.
- Rapports : `validation/windows-0.13/`. Rendu Mesa logiciel ; GPU et
  haut-parleurs physiques non testés. Aucune équivalence complète Android.
- Source compilée : `b35ae7d0dda82b42799c6a556b09698d99fd5d98`.
- ZIP : 59447865 octets, SHA-256 `709dbe4bfcafc334b11cb0d79d43b0cbc722d989d5e6ccd4cf0de8119003a2cb`.
- EXE : SHA-256 `92325d54838f3daf14cf9417cd44cb74625a3f92ac599b61bc33133db7d72a5d`.

# Validation 0.12.0 — suspension, wheelie, ABS et antipatinage

- 263 contrôles du cœur Linux réussis, dont 64 combinaisons extrêmes de hauteur,
  ressorts, amortissement, équilibre, autorisation de levée et antipatinage.
- Précharge statique, oscillations amorties, réglages conservés, perte de contact,
  retour au sol, contraintes anti-levée, points d’émission et cadences de rendu testés.
- Référence native : ABS 36,83 m contre 48,62 m avec blocage depuis 100 km/h ;
  lancement TC 126,60 m contre 99,52 m en 5 s ; levée maximale testée 0,38 m.
- 70 contrôles graphiques Linux réussis : menu suspension, wheelie, mode au sol,
  indicateurs ABS/TC, sauvegarde des aides et retour après essai non confirmé.
- 115 contrôles d’entrées réelles Linux réussis : 15 châssis/aides, 15 burnout/
  point mort, 69 garage/audio et 16 affichage/trafic.
- Preuves Linux : `validation/chassis-0.12/`. Windows est aussi validé par CI.
- Modèle longitudinal natif calibré ; aucune équivalence complète Android ou
  constructeur n’est revendiquée. Le banc générique historique est inchangé.

## Publication Windows vérifiée — 0.12.0

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40504627540) : 263 contrôles du cœur, 70 graphiques, 188 sons décodés ; couverture
  des 64 réglages extrêmes et effets des aides vérifiés sous Windows.
- Rapport châssis, trajectoire de wheelie et mesures des 191 voitures concordent
  avec Linux à 0,01 près. Menu suspension et wheelie Windows revus visuellement.
- Archive publique redéchargée : CRC, SHA-256, EXE et source compilée vérifiés.
  Les onze aperçus publics correspondent aux captures Windows validées.
- Contrôles pixels du décor, des roues, des flammes, du NOS et des huit fumées
  réussis. Restauration sur dossier vide puis réutilisation : 247 ressources chacune.
- Rapports : `validation/windows-0.12/`. Rendu Mesa logiciel ; GPU et
  haut-parleurs physiques non testés.
- Source compilée : `bbbd337f58f363582e92ab5e7ce2628b1bb008c8`.
- ZIP : 59313198 octets, SHA-256 `398b0fa18149a598c50903891dbe9c6215fb0e776deb4a2a72899fdf7803feac`.
- EXE : SHA-256 `cf65ec0bc9a3f9fcb8cca7d8ba387284585cbee7216d23dfe8d482ffd0212aa3`.

# Validation 0.11.0 — burnout et point mort

- 233 contrôles du cœur : burnout FWD/RWD/AWD, immobilité du décor et rotation
  des essieux, frein prioritaire à vitesse élevée, frein à main, point mort,
  inertie, freinage, régime, NOS bloqué et réengagement sans surrégime.
- 40 images de pneus contrôlées : seules les 8 Burn Slicks colorent la fumée.
  La couleur est conservée pendant la vie de chaque particule.
- 60 contrôles graphiques Linux réussis ; les huit couleurs sont visibles selon
  les contrôles pixels et les captures burnout/point mort ont été revues.
- 100 contrôles d’entrées réelles Linux réussis : 15 burnout/point mort,
  69 garage/audio et 16 affichage/trafic.
- Windows x64 validé par CI : mêmes contrôles du cœur et des captures réussis.
- Preuves Linux : `validation/burnout-0.11/`.
- Il s’agit d’une adaptation native ; la chauffe des pneus Android n’est pas portée.

## Publication Windows vérifiée — 0.11.0

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40499296308) : 233 contrôles du cœur, 60 graphiques, 188 sons décodés et huit
  couleurs de fumée vérifiées sur les captures Windows. Aperçu du burnout revu.
- Mesures des 191 voitures identiques à Linux à la précision des CSV exportés.
  Contrôles pixels du décor, des roues, des flammes et du NOS réussis.
- Archive publique redéchargée : CRC, SHA-256, EXE et source compilée vérifiés.
  Les neuf aperçus publics correspondent aux captures Windows validées.
- Restauration sur dossier vide puis réutilisation : 247 ressources chacune.
  Rapports dans `validation/windows-0.11/`. Rendu Mesa logiciel ; GPU et
  haut-parleurs physiques non testés.
- Source compilée : `a23add970340058799a90ad298c9cd3816fbfa29`.
- ZIP : 59298741 octets, SHA-256 `dde9dba9b747af892b4cb703ceee148ce65e2c198cc1c1c3ffe616f253773a49`.
- EXE : SHA-256 `bc33aae9dd3ac2c29bc35d08c290f7659681f1c3f96ac66d8fa418f539396048`.

# Validation 0.10.0 — paramètres par voiture

- Récupération indépendante de 191 fiches dans chaque bibliothèque : 1337
  valeurs identiques et 382 bornes d’identifiant vérifiées. Les écritures et
  empreintes sont conservées dans `stock-vehicles.json`.
- 166 contrôles du cœur Linux réussis. Accélération/freinage des 191 voitures,
  masses et puissances de base, 33 FWD / 126 RWD / 32 AWD, 16 moteurs remplacés avec régimes propres, absence de plancher
  abusif à 600 kg, sauvegardes/conversions, noms/incertitudes et indépendance FPS.
- 50 contrôles graphiques Linux réussis sur la version finale ; les captures
  de quatre fiches et de la transmission sont revues. Windows est aussi validé.
- 85 contrôles d’entrées réelles Linux : 69 garage/audio, 16 affichage/trafic.
  Le mode de transmission d’origine et les conversions manuelles sont testés.
- Les 192416 combinaisons de pièces restent vérifiées. Référence de prépa max :
  4437,94 HP / 4687,94 HP avec NOS. Le banc générique historique est inchangé.
- Les identités visuelles, les paramètres du jeu et la physique réelle sont
  distingués. Les équations Android complètes ne sont pas déclarées récupérées.

Preuves Linux : `validation/vehicles-0.10/`.

## Publication Windows vérifiée — 0.10.0

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40484200968) : 166 contrôles du cœur, 50 contrôles graphiques et 188 sons décodés.
- Les mesures d’accélération/freinage et les paramètres des 191 voitures
  concordent avec Linux à la précision des CSV exportés (tolérance 0,01).
- Archive publique redéchargée : CRC, SHA-256, source compilée et EXE vérifiés.
  Les huit aperçus publics correspondent aux captures Windows validées ; la
  fiche AWD a été revue visuellement.
- Contrôles pixels de vitesse, roues, NOS/flammes réussis sous Windows.
  Restauration des 247 ressources sur dossier vide puis réutilisation réussies.
- Rapports : `validation/windows-0.10/`. Rendu Mesa logiciel ; GPU et
  haut-parleurs physiques non testés.
- Source compilée : `36754b81fe4451ffd9c5f25cfdc4297f3918968e`.
- ZIP : 59294935 octets, SHA-256 `91692f5be3f5d710183e815ed57bac667a67866aef57fa72e56260ea9aa2ad92`.
- EXE : SHA-256 `df9b6911e39b44216422faeebe4c6e6068ae5868c47ae3acee85f31cc732f651`.

Les validations ci-dessous concernent les versions antérieures.

# Validation native 0.9.1 — correctif des échappements

- Classificateurs Android Original/Unbound récupérés séparément et identiques
  pour les 51 images ; coordonnées et branches de dessin conservées dans
  `native/evidence/merged/exhaust-rules.json`.
- 146 contrôles du cœur Linux réussis : 18336 transformations source, couches
  et racines de particules, plus les contrôles existants de physique et contenu.
- 45 contrôles graphiques Linux réussis. Quatre nouvelles planches du vrai
  moteur montrent 12 pots sur carrosserie standard, courte, longue et kit avec
  suspension modifiée. Contrôles pixels de vitesse et NOS/flammes réussis.
- Binaires Windows x64 et Linux compilés. La publication du correctif exige
  aussi les contrôles Windows via le workflow de release.
- Les pots de capot et directions des bouches restent des adaptations natives ;
  l’équivalence complète du rendu Android n’est pas revendiquée.
- Preuves Linux : `validation/exhaust-source-0.9.1/`.

## Publication Windows vérifiée — 0.9.1

- [Workflow réussi](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40463130324) : 146 contrôles du cœur, 45 contrôles graphiques, 188 sons décodés,
  physique Linux/Windows à 0,01 près et 192416 combinaisons de pièces.
- Source des 18336 transformations et couches vérifiée ; quatre planches du vrai
  rendu Windows sont dans le ZIP de validation. Aperçu des pots revu.
- ZIP public redéchargé : CRC, SHA-256, source compilée et EXE vérifiés.
  Les sept aperçus publics sont identiques aux captures Windows validées.
- Vitesse du décor, immobilité des roues et pixels NOS/flammes vérifiés sur les
  captures Windows. Restauration à froid/réutilisation : 247 ressources chacune.
- Rapports : `validation/windows-0.9.1/`. Rendu Windows logiciel Mesa ; GPU et
  haut-parleurs physiques non testés.
- Source compilée : `c2f73a2c13aede7619a6a6c590b819f42772b692`.
- ZIP : 59228865 octets, SHA-256 `9a5a6c8c2cf8ae8d48b8cd1665f8fd3eb72b16ffcd3a8d1f893810846c291f13`.
- EXE : SHA-256 `e30a5114e07d5343f90ac838a6ad2340eeef86929aeb32eb2d39dad3b08fc81d`.

Les validations ci-dessous concernent les versions antérieures.

# Validation native 0.9.0

- 143 contrôles du cœur : récupération de 4584 coordonnées, fitting de
  18718 configurations et 243334 variantes avec kits, source des pièces,
  239 ensembles visuels, migration des sièges/audio et arceau/phares.
- 45 contrôles graphiques : positions partagées pot/VFX, ancrages source,
  sièges des deux versions dans la même liste et mentions de provenance.
- 82 contrôles clavier/souris Linux (66 garage/audio, 16 affichage/trafic),
  dont sélection des variantes dans le même menu, arceau, phares et audio
  indépendant de la voiture.
- Physique, 192416 combinaisons et 188 sons conservés. La publication exige
  les contrôles Windows du cœur, fitting, rendu, physique et deux banques audio.
- Rapports locaux : `validation/attachments-0.9/`. Les adaptations de surface,
  de matériaux et les limites d’équivalence Android restent documentées.

## Publication et téléchargement vérifiés

- [Exécution Windows réussie](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40402394244) : 143 contrôles du cœur, 45 graphiques, 188 sons décodés, 18718 configurations de pot et 243334 fittings, 192416 combinaisons et physique Linux/Windows à 0,01 près.
- Captures Windows revues : provenance sous les sièges Original/Unbound dans la même liste, coordonnées récupérées et accessoires corrigés. Défilement et pixels NOS/flammes contrôlés sur les captures Windows.
- ZIP public redéchargé et vérifié : CRC, SHA-256, source compilée et exécutable. Les six aperçus publics sont identiques aux captures Windows validées.
- Restauration à froid et réutilisation : 247 ressources chacune. Rapports : `validation/windows-0.9/`.
- Rendu CI Mesa logiciel et mixage logiciel Linux ; GPU et haut-parleurs physiques restent à essayer.
- Source compilée : `eb5dde0a57318ac391ec530bf64c5288a069aa9f`.
- ZIP : 59231297 octets, SHA-256 `2c1a37ec106eef61fdde5fde2f9e87000bd6a879d4ae4548d2fbef6e70a555f4`.
- Exécutable : SHA-256 `ed44fce8b99043c1dc381cf496ad02a787d37846386820d0715224922e6dc460`.

## Historique : version 0.8.0

# Validation native 0.8.0

- 136 contrôles du cœur : 196 pièces, 521 recettes et images de jantes dans
  chaque banque, migration des sauvegardes et seize catégories esthétiques.
- 42 contrôles graphiques : jantes nommées, banque Original/Unbound, kits/livrée,
  cargaison au-dessus du toit, conduite personnalisée et corps visible après
  les changements d’affichage.
- 79 contrôles d’entrées Linux : 63 garage/équipement/audio, 16 affichage/trafic.
  Les seize catégories s’équipent par de vraies entrées, les jantes se cherchent
  par nom, les banques changent et l’ensemble survit au redémarrage.
- 188 échantillons décodés ; mixage logiciel non silencieux des deux banques,
  seize profils par banque, turbo/compresseur/NOS et événements, sans erreur.
- 192416 combinaisons de performance, 9359 ancrages et physique de référence
  conservés. Les adaptations de matériaux/accessoires restent décrites dans
  CONTENT.md ; ni fidélité complète Android ni haut-parleurs physiques démontrés.
- Rapports locaux : `validation/merged-0.8/`. La publication exige les contrôles
  Windows du cœur, physique, rendu, combinaisons et décodage des deux banques.

## Publication et téléchargement vérifiés

- [Exécution Windows réussie](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40396656078) : 136 contrôles du cœur, 42 graphiques, 188 décodages, 192416 combinaisons, 9359 ancrages et mesures physiques Linux/Windows concordantes à 0,01 près.
- Les captures Windows montrent les jantes nommées, livrées, kits et cargaison au-dessus du toit ; les comparaisons de défilement/NOS/flammes passent aussi sur ces images.
- ZIP public redéchargé : CRC, SHA-256, source compilée et exécutable vérifiés. Les quatre aperçus publics correspondent exactement aux captures Windows validées.
- Restauration à froid et réutilisation : 247 ressources chacune. Rapports : `validation/windows-0.8/`.
- Rendu CI Mesa logiciel ; mixage sur périphérique audio logiciel Linux. GPU et haut-parleurs physiques restent à essayer.
- Source compilée : `1a062312344c6644cc1aea0908bd22c9a0762b7f`.
- ZIP : 59174529 octets, SHA-256 `30beaa74beaaf7294855ecc7c930db273788ed7b58e862ebd83fece72016d290`.
- Exécutable : SHA-256 `ab08600e233c169bd30d380c84103da2cd21c5d9ce8fdea32b12a214fdccb262`.

## Historique : version 0.7.1

# Validation native 0.7.1

- 129 contrôles du cœur : conservation des 23 identifiants de vraies jantes et
  migration des 31 anciens choix de pneus/effets, sans perte de pièces.
- 39 contrôles graphiques, dont exclusion des calques du catalogue ; captures
  des quatre pages pour revoir les 23 vignettes et leur rendu sur la voiture.
- 57 contrôles clavier/souris Linux : 41 garage/boîte/frein à main, 16 affichage
  et trafic. La dernière vraie jante s’équipe ; une recherche d’un effet ne
  permet plus de l’équiper.
- Rapports locaux : `validation/rims-0.7.1/`. Publication conditionnée aux contrôles
  Windows du cœur, physique, rendu, 188384 combinaisons, 9359 ancrages et 94 sons.

## Publication vérifiée

- [Exécution Windows réussie](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40390236234) : 129 contrôles du cœur, 39 graphiques, physique Linux/Windows à 0,01 près, 188384 combinaisons, 9359 ancrages, 94 sons et comparaisons défilement/VFX.
- Les quatre pages de jantes ont été capturées sous Windows ; les 23 styles sont visibles et les calques ne sont plus proposés.
- ZIP public redéchargé : CRC, SHA-256, source et exécutable vérifiés. Restauration à froid et réutilisation : 146 ressources chacune.
- Rapports : `validation/windows-0.7.1/`. Rendu CI Mesa logiciel ; GPU et haut-parleurs physiques restent à essayer.
- Source compilée : `bab2e5b427bcbdd677a5ae4903f2e535a8a7233f`.
- ZIP : 31721429 octets, SHA-256 `8e0defc432e0c9d976a63b38463afe715fd7099c6d771c136a0b2997c44961ab`.
- Exécutable : SHA-256 `1dd0e12df8db0bbb6a68e2d33abd6b69d2e2231cc20707e18fe32610b76be454`.

## Historique : version 0.7.0

# Validation native 0.7.0

- 127 contrôles du cœur : ressources UI originales, frein à main distinct du
  frein de service, arrêt sans marche arrière, rotation arrière bloquée/libérée,
  priorité sur accélération/NOS et fumée sur le bon essieu.
- 38 contrôles graphiques : atelier et inventaire originaux, catégories et jantes,
  transmission, VFX et frein à main. Les comparaisons du défilement et des pixels
  NOS/flammes sont conservées.
- 55 contrôles de vraies entrées Linux : 39 pour garage/boîte/frein à main et
  16 pour affichage/trafic. Équipement, aperçu, remplacement de recherche,
  Ctrl+A, molette, double-clic, sauvegarde, redémarrage, fenêtre 4:3 et Full HD.
- Les rapports locaux sont dans `validation/garage-pc-0.7/`. La publication
  exige les contrôles Windows du cœur, du rendu, de la physique, des 188384
  combinaisons, des 9359 ancrages et du décodage des 94 sons.
- Les jauges montrent le modèle natif ; économie et progression d'origine restent
  à reconstruire. La calibration physique reste décrite dans PHYSICS.md.

## Publication et téléchargement vérifiés

- [Exécution Windows réussie](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40388248419) : 127 contrôles du cœur, 38 graphiques, physique Linux/Windows à 0,01 près, 188384 combinaisons, 9359 ancrages, 94 sons décodés, défilement et VFX visibles.
- ZIP public redéchargé, CRC et empreintes vérifiés ; les deux aperçus publics sont identiques aux captures Windows validées. Restauration à froid et réutilisation : 146 ressources chacune.
- Rapports : `validation/windows-0.7/`. Rendu CI Mesa logiciel ; essais sur GPU et haut-parleurs physiques restent à effectuer.
- Source compilée : `44013341088a1c9ebabc085b7c9a3a69d1fec80b`.
- ZIP : 31719254 octets, SHA-256 `64a55eee952872d669dcdfb2d9cdf9f925bb1ea55d6a42a4819651024abe5b91`.
- Exécutable : SHA-256 `df18d90507638f3ca6a0691bc35d88eec6a5065583dbf7a299d4b8372e604588`.

## Historique : validation native 0.6.0

# Validation native 0.6.0

- 119 contrôles du cœur : 9359 placements carrosserie/pot, sorties multiples,
  direction et suspension, jets attachés à haute vitesse/changement de voie ;
  huit préréglages de boîte, quatre à dix rapports, passage 9→10 automatique,
  effet du pont sans gain artificiel de HP et sauvegarde/rechargement sécurisé.
- 36 contrôles graphiques ; 45 clavier/souris Linux (29 pièces/boîte, 16 paramètres),
  dont curseurs, boutons de rapport, choix du nombre de vitesses, sauvegarde,
  annulation, réinitialisation et reprise réelle de la boîte dix rapports.
- Cinq comparaisons du défilement et contrôle des pixels bleus NOS/chauds de
  flamme dans les captures. Les paramètres d'origine à six rapports conservent
  leur référence physique. Les 188384 combinaisons de pièces sont conservées.
- Les rapports locaux sont dans `validation/exhaust-gearbox-0.6/`. La publication
  exige les contrôles Windows du cœur, des images, du défilement, de la physique
  et des 94 sons. Les ancrages et adaptations de transmission sont natifs.

Exécution Windows réussie :
[40376544654](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40376544654).
119 contrôles du cœur, 36 graphiques, 9359 placements géométriques, huit
préréglages et dix rapports maximum ; les pixels NOS/flammes sont visibles
(83 bleus, 131 chauds dans la zone contrôlée). Les captures Windows de la boîte
à dix rapports et des échappements ont été vérifiées. Physique de base,
défilement, 188384 combinaisons de pièces et décodage des 94 sons réussis.
Rapports : `validation/windows-0.6/` et le ZIP de validation joint à la release.

Archive publique retéléchargée et vérifiée : 29 754 752 octets, SHA-256
`168fdffb7914ab1297701148827433ed13d2fe684f56bb2c022f35015989bfbe`.
EXE : `ec8526fa2c5c580ce2a229329faad4064284a1c6207aacdb642dc85e796ed78f`.
Source compilée : `e26b8a3db5982f9b54744c31f1b62090183354e2`.
Les 144 ressources ont été restaurées en dossier neuf et réutilisées dans le
répertoire de travail sans modification. Les images source ajoutent les
atlas nécessaires aux échappements ; les données originales sont conservées.

## Historique : validation native 0.5.1

# Validation native 0.5.1

- 105 contrôles du cœur, dont circulation désactivée sans déplacement des NPC,
  collisions ou dépassements ; réactivation à distance et ancienne sauvegarde.
- 30 contrôles graphiques : option appliquée/enregistrée, absence de collisions
  cachées, réactivation, annulation d'un essai et nouvelle session sans trafic.
- 37 contrôles clavier/souris Linux : 21 pour les pièces et 16 pour les paramètres,
  dont désactivation du trafic sauvegardée, appliquée et reprise après redémarrage.
- Les comparaisons de défilement, 188 384 combinaisons de pièces et le banc
  physique de base restent inchangés. Rapports : `validation/traffic-0.5.1/`.
- La publication exige les contrôles Windows du cœur, de la puissance, de la
  physique, du rendu/défilement et du décodage des 94 sons.

Exécution Windows réussie :
[40370059371](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40370059371).
105 contrôles du cœur, 30 graphiques, 188 384 combinaisons de groupes de pièces,
94 sons décodés et comparaisons du banc physique et du défilement réussis.
La capture Windows sans trafic et la préférence `traffic=0` ont été vérifiées.
Rapports : `validation/windows-0.5.1/` et le ZIP de validation joint à la release.

Archive publique retéléchargée, CRC et identités source/EXE vérifiés :
28 732 455 octets, SHA-256
`d75abc7fcc2298944df824449b3cb200e5e27ae88f909a3d78e4b5f2fadd9fea`.
EXE : `5250adac5c6b28fbdb46748cda20e6ec8b563aa41d2d77d068556d70bb5241be`.
Source compilée : `c34605f076f42a3e87ca3d8da4b207af3960873f`.
Les 140 ressources sont restaurées en dossier neuf et réutilisées dans le
répertoire de travail sans modification.

## Historique : validation native 0.5.0

# Validation native 0.5.0

- 101 contrôles du cœur, dont 188 384 combinaisons de groupes de pièces et
  chacune des 194 substitutions de la préparation maximale.
- Vérification du calcul composé de puissance, rôle de l'intercooler, gain ECU,
  classement monotone, variantes cosmétiques, exclusivité turbo/compresseur,
  puissance réelle au pic et coupure du NOS au limiteur.
- 24 contrôles graphiques et 21 clavier/souris : rareté/tri, PRÉPA MAX, banc,
  puissance active en mode libre et conservation des choix au redémarrage.
- Les cinq comparaisons du défilement 0.4.1 sont conservées.
- La référence physique du véhicule sans pièces est inchangée. Les équations
  des pièces et raretés sont natives ; l'équivalence Android n'est pas établie.
- Rapports : `validation/power-0.5/`. La publication exige les contrôles Windows
  du cœur, des combinaisons, du banc physique, des images et des 94 sons.

Exécution Windows réussie :
[40368604089](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40368604089).
Les 101 contrôles du cœur, 24 graphiques, 188 384 combinaisons de groupes de
pièces, 94 sons et comparaisons de physique et de défilement réussissent.
Les rapports de puissance Linux et Windows sont identiques : 4288,88 HP sans
NOS et 4538,88 HP avec NOS. Les captures Windows du classement et du banc
ont été vérifiées. Rapports : `validation/windows-0.5/` et le ZIP de validation
joint à la release.

Le paquet public retéléchargé et vérifié mesure 28 731 040 octets ; SHA-256
`5eb9e860af6621882ad6f0715aead72833f6651f95068972ec78acc3b993f030`.
EXE : `c361ff39412246446f244eec2362c899554ce4e5416e61c03972bac8f1d81644`.
Source compilée : `414c350f0f444c4f7b5bb80b26f7397c4428b5b0`.
Les 140 ressources ont été restaurées en dossier neuf puis réutilisées dans le
répertoire de travail sans modification.

## Historique : validation native 0.4.1

# Validation native 0.4.1

- 85 contrôles du cœur : échelle route/circulation, parallaxe, rotation des
  roues, déplacements selon les FPS, fumée ancrée au sol et pause des effets.
- Les 21 contrôles graphiques et 18 contrôles clavier/souris du garage sont
  repris avec le nouveau rendu ; le code audio est conservé depuis 0.4.0.
- Captures contrôlées : arrêt, pause à vitesse non nulle, 100 et 200 km/h.
  La mesure des pixels vérifie le déplacement réel du marquage sur 0,1 seconde.
- Rapports : `validation/motion-0.4.1/`. La publication exige en plus les
  contrôles Windows du rendu, du déplacement des images, de la physique et du
  décodage des 94 sons. La référence physique 0.3 reste inchangée.

Exécution Windows réussie :
[40350423994](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40350423994).
85 contrôles du cœur, 21 graphiques, décodage des 94 sons, concordance du banc
physique et comparaison des captures réussis. Les images Windows mesurent
101 pixels à 100 km/h et 200 pixels à 200 km/h sur 0,1 seconde à 960 × 540 ;
la différence d'un pixel est due à la rastérisation. À l'arrêt et en pause à
vitesse non nulle, les images sont identiques. Rapports : `validation/windows-0.4.1/`.

Paquet public retéléchargé et vérifié : 28 718 194 octets, SHA-256
`6712b2680edd48f007f42cc9ee2960a78053adf9695843aa93bf24f8f66c095a`.
EXE : `adf61e01130051afb6e5210d7b74fef70616b7f1ab64d0ce818190b41d5cb69a`.
Source compilée : `5bf20af2cf08ea8669ff0a7d07dbe40db1e1d419`.
Les 140 ressources du paquet ont été restaurées en dossier neuf et réutilisées
sans modification dans le dossier de travail.

## Historique : validation native 0.4.0

# Validation native 0.4.0

- Linux : 75 contrôles du cœur, 21 graphiques, 19 de vraies entrées clavier/souris,
  dont équipement des 11 catégories, pagination, exclusivité et redémarrage.
- 94 sons originaux décodés ; échantillons moteur non silencieux.
- Mixage réel Raylib sur périphérique logiciel : 16 paires moteur, turbo,
  compresseur, NOS et événements ; PCM non nul, aucun échec de chargement.
- Le programme graphique initialise aussi son backend audio sans échec.
- Rapports : `validation/customization-0.4/`. Ces essais ne valident ni un
  haut-parleur Windows physique ni la correspondance originale moteur–son.
- La publication exige les contrôles Windows du cœur, du banc, du rendu et
  du décodage des 94 sons. Le rapport effectif accompagne la release.

Exécution Windows 0.4 réussie :
[40346990077](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40346990077).
75 contrôles du cœur, 21 graphiques, 94 sons décodés et huit mesures du banc
concordantes avec Linux. Rapports : `validation/windows-0.4/` et
`Validation-Windows.zip` sur la release. Captures Windows du garage,
customisation, profils audio, NOS et collisions vérifiées.

Source compilée : `163765c9441c05b52137ec8d5a9ea899e91cadd5`.
Archive publique : 28 716 585 octets ; SHA-256
`e50087133a9f49c8152f3fbac8d7312e5bf2824765875c123edb39f8e21738c7`.
EXE SHA-256 : `25dc5a12539b5f573529aea41338cfe879a97f044ca0765d686b0276078cd1ef`.

## Historique 0.3.1

# Validation de la reconstruction native 0.3.1

## Correction des roues 0.3.1

- Le placement proportionnel à la largeur de la carrosserie est supprimé. Le
  point arrière utilise l’origine du sprite ; le point avant est mesuré dans
  les ouvertures transparentes. La recherche échoue explicitement si un nouveau
  sprite est ambigu, au lieu de choisir des coordonnées approximatives.
- Pneus et jantes utilisent le même canevas de 62 × 62 et leur origine 31 × 31.
  Le pneu original est rendu à demi-échelle de la carrosserie. Le fond du passage
  de roue et les roues sont derrière les ailes, y compris les ailes couvrantes.
- Cas signalé, carrosserie 021 : arrière (62, 58), avant (160, 58) ; rayon extérieur
  du pneu 12,5 pixels dans le repère de la carrosserie.
- Les 191 carrosseries ont été sélectionnées via les vrais boutons du garage,
  capturées avec la jante 09 et revues sur 12 planches de rendu natif Linux.
  Le sprite spécial 183 ne possède pas de passages de roue ; les roues ajoutées
  artificiellement sont retirées sur ce modèle.
- 46 contrôles du cœur et 15 contrôles graphiques Linux passent. La physique du
  modèle de référence est conservée ; les mesures du banc ne changent pas.
- Métadonnées : `validation/wheel-anchors.json`. Rapports :
  `validation/wheels-0.3.1/`. Reproduction visuelle sous XTest :
  `tests/wheel_visual_audit.py`, dans un écran X isolé et un dossier neuf.
- Le test graphique Windows de la release utilise maintenant la carrosserie 021
  et la jante 09 pour produire les captures du cas signalé. La publication est
  conditionnée aux contrôles Windows du cœur, du banc et du rendu.

Exécution Windows 0.3.1 réussie :
[40319746159](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40319746159).
Les 46 contrôles du cœur, les 15 contrôles graphiques et la comparaison du banc
réussissent. La capture Windows du garage montre la carrosserie 021 avec la
jante 09. Le paquet public a été retéléchargé et vérifié : 7 950 681 octets,
SHA-256 `71d33b788a70a6b91889f7f7a7328b0ac072363f5c9c908d3f891ff63469a990`.
Source compilée : `4974757f9f9535c107c546a07dbfed12b0c04198`.
Les aperçus des 191 carrosseries sont joints à la release dans
`Verification-roues-191-carrosseries.zip` ; les originaux de capture restent dans
le répertoire d’audit du cloud.

## Historique : contrôles de la version 0.3

- 43 contrôles du cœur réussis sur Linux : simulation indépendante des FPS,
  conduite, boîte, adhérence commune aux freins, transfert de poids selon
  l’essieu moteur, persistance et banc de mesure.
- 15 contrôles du rendu Linux et 13 contrôles de vraies entrées clavier/souris
  réussis après les corrections. Le mode libre reprend après les paramètres.
- Construction Linux et Windows x64 sans avertissement du compilateur.
- Le banc intégré fonctionne sans écran ni audio, produit JSON/CSV et refuse
  de remplacer un dossier existant. Aucun profil de joueur n’est modifié.
- Référence native provisoire : 0–100 km/h en 4,507 s ; 402 m en 12,727 s ;
  freinage depuis 100 km/h en quatrième : 42,99 m et 3,108 s.
  Ces nombres ne sont pas des références Android.
- Rapports : `validation/physics-core-linux.txt`, `physics-graphics-linux.txt`,
  `physics-ui-input-linux.json` et `native-physics-baseline.json`.
- La publication 0.3 est conditionnée à l’exécution sous Windows du cœur, du
  banc de mesure et du programme graphique. Les mesures Windows doivent être
  à moins de 0,01 des mesures Linux, dans l’unité de chaque grandeur.
  Le rapport effectif accompagne la release dans `Validation-Windows.zip`.

Exécution Windows réussie : [40315185715](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40315185715).
Le paquet public a été retéléchargé et vérifié : SHA-256
`fdf3a352d6a6dacc52cc9a1c7a442d83ce44ac78b475ccfa618d64500373a643`,
7 582 601 octets. Source compilée :
`c9fe0982b364959c9567fe087303afd316ea5e8d`.
Les rapports Windows sont aussi dans `validation/windows-0.3/`.

La fidélité au jeu original reste à valider. Le calcul principal YYC n’a pas
été reconstitué par les trois passes ciblées Ghidra ; voir `PHYSICS.md` et les
preuves dans `native/evidence/unbound/physics/` du dépôt.

## Historique de validation : release 0.2

## Contrôles terminés dans le cloud Linux

- 22 vérifications du cœur : course de référence terminée, même résultat à
  30/60/120/144/165/240 FPS, mode libre au-delà de 400 mètres, freinage, voies,
  contacts avec la circulation, paramètres invalides, fichiers Unicode,
  remplacement d'un fichier existant, sauvegarde du garage et des préférences.
- Simulation libre de 70 secondes : environ 4,4 km parcourus sans événement de
  fin de course. Cette mesure concerne le modèle natif réimplémenté.
- 15 contrôles graphiques sous Xvfb/Mesa : avance du véhicule, entrée de voie,
  état sans bordure et taille du bureau, rétablissement après expiration,
  absence de sauvegarde d'un choix non confirmé, plein écran et sa résolution, retour avec bordure,
  résolution appliquée, demande VSync, limite à 30 FPS, persistance et reprise.
- Mesure de la limite à 30 FPS : au moins 0,9 seconde pour 30 images. La durée
  observée est conservée dans le rapport de chaque exécution. Le drapeau VSync
  vérifié est une demande au pilote, pas une mesure de synchronisation physique.
- 11 contrôles de vraies entrées XTest : choix d'une carrosserie et de jantes,
  accélération, voie, boîte, mode sans bordure, FPS, VSync, qualité et compteur.
  Le véhicule a parcouru plus de 35 mètres dans ce parcours d'essai.
- Construction du PE Windows x64 et contrôle de ses imports : bibliothèques
  système Windows et UCRT, sans bibliothèque Android ou moteur d'émulation.

Ces essais vérifient la reconstruction, pas l'équivalence avec la physique et
la progression du jeu GameMaker.

## Windows

Exécution réussie : [40305565837](https://github.com/Imdraks/pixel-car-decompiled/actions/runs/40305565837),
sur Windows Server 2025, avec 22 contrôles du cœur et 15 contrôles graphiques.
L'archive testée porte le SHA-256
`dfe16f0c55049cd32c26ff1489709ed6147e647a691d03ec4423f9807b42c425`.
Les rapports texte correspondants sont aussi conservés dans `validation/`.

Le pipeline de publication `publish-native-release.yml` vérifie le même paquet
sur un runner Windows avant sa publication. Le rapport de cette exécution et
ses captures sont joints séparément à la release dans `Validation-Windows.zip`.
Le rendu de ce test utilise Mesa logiciel, installé uniquement sur le runner.
Cette bibliothèque de test n'est pas incluse dans la distribution du jeu.

Un essai préalable avec une installation Wine portable incomplète n'a pas pu
initialiser son propre environnement Windows. Il ne constitue pas une validation
du programme et n'est pas présenté comme un test réussi de l'exécutable.

Le premier essai sur Windows Server 2025 a détecté une fenêtre plus petite que
les 1 280 pixels demandés sur le bureau virtuel. La correction limite les choix
fenêtrés à l'espace utilisable, bordures et DPI compris. Le plein écran demande
aussi explicitement le mode vidéo choisi au backend GLFW, et un contrôle séparé
vérifie que sa résolution est bien appliquée.

Les essais sur un PC Windows physique, plusieurs écrans, les pilotes GPU des
fabricants, le HDR et l'audio réel restent à effectuer. Aucun achat ni compte
personnel n'est utilisé. Aucun APK ou émulateur n'est lancé dans cette application.
