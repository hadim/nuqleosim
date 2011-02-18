=======================
Contenu des repertoires
=======================

* data/ : données nécessaires au fonctionnement et à la compilation de
nuqleosim.

* packages/ : binaires pour executer nuqleosim sans avoir à le
  compiler

* rapport/ : rapport présentant nuqleosim

* src/ : code source de nuqleosim

* cmake/ : module cmake tiers

* doc/ : documentation développeur généré par Doxygen

* presentation/ : slide de la présentation

* tools/ : outils divers


===========
Dépendances
===========

NuQleoSim dépend des librairies / programmes suivant : 

- cmake > 2.6 (compilation)
- Qt > 4.6 (paquet de développement pour la compilation)
- QGLViewer et OpenGL (visualisation en 3D) : http://www.libqglviewer.com/
- QwT (génération de graphique) : http://qwt.sourceforge.net

Si Qwt et QGLViewer sont installés dans des paths non conventionnels,
il peut être nécessaire d'éditer le fichier CMakeLists.txt à partir de
la ligne 7, afin d'indiquer les paths.

==========================
Instruction de compilation
==========================

Le projet utilise cmake pour générer le Makefile.

(sudo apt-get install cmake sous ubuntu / debian)

Si le repertoire build/ n'existe pas, créez-le : 

$ mkdir build/
$ cd build/
$ cmake ../
$ make && make install

Note: le "make install" n'installe pas l'application en dehors du
repertoire build/. Il copie simplement les fichiers d'exemple dans le
repertoire build/bin/. 

Exécution de l'application : 

$ ./bin/nuqleosim (depuis le repertoire build/)

=========================
Documentation développeur
=========================

Une documentation développeur est dipsonible sous forme html
(doc/index.html).
