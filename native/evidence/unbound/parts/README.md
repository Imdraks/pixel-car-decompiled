# Catalogue et sons Unbound : preuves statiques

Source : lib/x86/libyoyo.so, SHA-256
`fb3726e175e7d1c643e0ddac1ec1a365901c4d52a16ded97e89fd672f6a9e9cc`.
Le script recover_part_catalog.py suit les pointeurs GOT et constantes SSE de
`gml_Script_db_shop_items` sans exécuter le binaire. 1195 appels d'insertion
sont couverts après 0x3abbd3. Le schéma source est
`type|string,name|string,float|real,hp|real,weight|real,value|real,subimage|real,equiped|real`.
195 lignes correspondent aux catégories demandées, dont turbo None : 194 pièces
équipables, avec adresses source et valeurs brutes dans catalog.json.
Les compresseurs sont classés depuis les noms SC/WIPPLE/BLOWER du type turbo.
Aucune valeur nécessaire aux lignes retenues ne reste non résolue.

sounds.json documente les 94 échantillons, leurs octets et SHA-256. L'export
UndertaleModTool lit EmbeddedAudio et les fichiers externes, sans réencodage.
recover_engine_audio.py suit les deux tables de dispatch moteur de car Step :
16 paires charge/décélération avec chemins d'instruction dans engine-audio.json.
**La relation entre les objets moteur du catalogue et ces profils n'est pas
récupérée.** L'association AUTO du port est une approximation explicite ; les
profils manuels permettent de choisir les sons indépendamment.
Les formules d'équipement, poids, pression, adhérence, audio et VFX du port
restent des adaptations natives ; ces preuves ne démontrent pas leur fidélité.
