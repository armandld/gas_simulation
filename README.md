Projet de Programmation Orientée Objet 2024: Simulation de gaz parfait

Nous avons terminé le projet et avons effectué quelques extensions.
Nous avons une version graphique du projet sur Qt 5.15.2.
Par personne, nous avons passé en moyenne 6h sur le projet chaque semaine.

Bienvenue dans le README de notre projet de fin de semestre. Ce projet a été réalisé dans le cadre du cours de Programmation Orientée Objet à L’EPFL
Introduction et Objectif
L'objectif de ce projet était de simuler des gaz parfaits dans une enceinte fermée, et éventuellement d’y ajouter d’autres fonctionnalités. Ce README contient toutes les ressources nécessaires pour comprendre et exécuter le projet. Nous ferons tout notre possible pour vous guider dans l’exécution de notre projet, merci pour le temps accordé à notre travail, nous espérons qu’il vous plaira!
Prérequis
Pour faire fonctionner notre projet, il vous faudra un compilateur C++, C++ 11 idéalement, tandis qu'une application Qt Creator fonctionnelle, nous avons travaillé et utilisé la version 5.15.2 tout au long de notre projet, elle est la version la plus adaptée.
Il vous faut aussi avoir installé le dossier de notre projet en intégralité (ce que nous imaginons que vous avez déjà fait puisque vous lisez ce message).
Fonctionnalités principales
Dans ce code vous trouverez comment simuler un mélange de gaz parfaits dans une enceinte fermée de deux façons différentes, une version texte et une version graphique, la version graphique étant complétée par quelques extensions.
Compilation et Exécution du Projet
Pour compiler les différents exécutables en version texte, il faut vous rendre sur votre terminal puis accéder au dossier du projet. Pour ce faire, soit vous ouvrez un terminal directement depuis le dossier en faisant un clic droit si votre machine le permet, soit vous vous rendez sur l’application Terminal puis écrivez cd Chemin/Pour/Accéder/Au/Dossier en mettant le chemin du dossier entre les barres obliques.
Une fois ceci écrit, appuyez sur le bouton entrée puis écrivez :
make NomFichierACompiler
Et faites Entrée.
Vous avez compilé le fichier voulu, dès lors, pour l’exécuter, faites ./NomFichierACompiler
Et faites Entrée. Vous avez exécuté le fichier avec succès!
Pour compiler les versions finales, en version texte ou en version graphique, il faut vous rendre sur votre terminal dans le dossier du projet comme pour avant, puis une fois ceci fait :
- en version texte,  rendez vous dans le dossier text avec la commande cd text, puis tapez qmake et entrez, puis tapez make et entrez, voila, la version texte finale est compilée. Enfin, pour l’exécuter, il faut écrire dans le terminal ./version_finale_text.
-en version graphique, rendez vous dans le dossier Qt_GL avec la commande cd Qt_GL, puis tapez qmake et entrez, puis tapez make et entrez, la version graphique finale est compilée. Enfin, presque comme pour la version texte, pour l’exécuter, il faut écrire dans le terminal ./version_finale_gl
A noter: si vous utilisez l’application Qt Creator, il est possible directement depuis l’application d’exécuter les deux versions finales simplement en ouvrant le fichier exerciceP14.pro dans le dossier, puis depuis l’application,  choisisez quelle version vous souhaitez  exécuter en cliquant en bas à gauche de la fenêtre sur l’ordinateur et choisir texte ou graphique et puis d’appuyer en bas à gauche sur le bouton play vert(run) ou d’effectuer la commande CTRL+R.
Il vous est possible d’ouvrir les fichiers tests sur votre compilateur et de changer les valeurs, les types des variables etc pour bien voir le fonctionnement du projet. Pour ajouter des particules au système dans le main(), il faut appeler la méthode ajouteParticule() pour une particule classique et ajouteParticule_tracable() pour une particule traçable. Il faut simplement en paramètre spécifier le type de particule voulu (un Néon par exemple).
Utilisation Optimale et Extensions
Lors de l’utilisation de l’interface graphique, il est possible et recommandé d’interagir avec le système pour mieux visualiser ce qu’il se passe. Nous avons donc installé plusieurs extensions pour ce faire, et nous vous présentons ici l’ensemble des touches utiles pour interagir avec le système :
Flèche de gauche : permet de faire une rotation de la caméra vers la gauche
Flèche de droite : permet de faire une rotation de la caméra vers la droite
Flèche du haut : permet de faire une rotation de la caméra vers le haut
Flèche du bas : permet de faire une rotation de la caméra vers le bas
Touche W ou PageUp: permet d’avancer
Touche A : permet d’aller vers la gauche
Touche S ou PageDown: permet de reculer
Touche D : permet d’aller vers la droite
Touche R : permet d’aller vers le haut
Touche F : permet d’aller vers le bas
Touche Q : permet d’incliner la caméra vers la gauche
Touche E : permet d’incliner la caméra vers la droite
Touche Espace : permet de mettre en pause la simulation
Touche C : permet de changer la couleur des particules. Il y a deux types d’affichages :
	-un où la couleur des particules change selon leur type (affichage de base), avec l’argon en violet,  le néon en vert et l'hélium en bleu
	-in où la couleur des particules change selon leur vitesse, faisant un dégradé allant du jaune pour les particules les plus lentes au rouge pour les particules les plus rapides
Touche T : permet d’afficher/cacher la trace des particules traçables (voir le fichier conception, nous n’avons qu’une partie des particules qui sont traçables). La trace est affichée en blanc, pour des raisons d’esthétisme et de bonne visualisation
Touche X: permet d’accrocher la caméra à la première particule du système, et appuyer sur X une deuxième fois permet de s’en défaire
Touches 1 à 9: Ces touches offrent la possibilité de changer le pas de temps de la simulation, et donc de faire afficher les particules à une vitesse plus ou moins élevée. Nous vous proposons de faire glisser vos doigts sur la barre des chiffres ce qui fait à peu près l’effet d’un curseur qui change la vitesse de la simulation. La touche 4 correspond à la vitesse originale du système, celle qu’il y aurait si on mettait le pas de temps de base, la touche 1 correspond à un système évoluant 10 fois moins vite et la touche 9 correspond à un système évoluant 50 fois plus vite.
Versions antérieures du code
Pour l’exercice P11 qui est la première version de la partie graphique, nous avons laissé le code tel qu’il était à ce moment-là, nous n’avions pas encore forcément réarrangé tout le code, ou bien l’affichage n’était pas forcément le même. Pour l’exécuter, il faut faire le même travail que pour la version finale expliquée ci-dessus mais avec un différent chemin ou bien avec un différent .pro : exerciceP11.pro
Contact: Si vous avez une quelconque question et/ou auriez besoin d’une réponse, n’hésitez pas à nous contacter par mail à l'adresse mail armandledouarec@gmail.com
