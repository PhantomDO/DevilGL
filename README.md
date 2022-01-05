# opengl_shader

https://github.com/rorygames/OBJ-Loader/blob/master/ObjectLoader/Model.h
https://gamedev.stackexchange.com/questions/116208/modern-opengl-c-obj-loader
https://stackoverflow.com/questions/60829086/custom-opengl-obj-model-loader-indices-calculation-not-working

# Synthèse d'image

Dans ce cours de synthèse d'image, nous avons effectué au départ des rappels mathématique utiles dans un environnement 3D. Nous avons du créer un créateur de PPM pour pouvoir extraire une image de pixels. 

Ensuite nous avons dû créer une petite librairie de mathématiques vectorielle (V4D, V3D, V2D, Dot, Cross, etc…) ce qui nous a permis de simplifier la création de couleur par pixel (V4D pour la couleur). En parallèles, pour tester la librairie, nous avons implémenté le problème du parachutiste.

Une fois cette mise à niveau/introduction au base du calcul en 3D terminé, nous avons implémenté un raytracer. Le but étant de créer une scène où la lumière et les ombres soient physiquement réalistes. Le calcul est très gourmand, c'est pour cet exercice que nous avons utilisé le créateur de PPM et ainsi afficher notre image finale.

Comme la simulation du raytracing est physique, nous avons tester sur différent type de matériaux afin de voir les différences produites (réflexion et réfraction).

Enfin, pour réellement tester le projet, nous avons implémenté un parser de fichier OBJ afin d'avoir accès aux normals et uvs de l'objets en question.
Ce qui nous a permis de valider le projet sur d'autres objets que la sphère.

Pour améliorer le calcul nous avons mis en place une structure accélératrice qui regroupaient les bounds de l'objet et les divisaient en sous-boites internes, ce qui permit raytracer d'aller chercher en profondeur les triangles affichables ou non.


# Simulation physique

Nous avons étudié la cinématique inverse via l'implémentation de l'algorithme [FABRIK](http://andreasaristidou.com/publications/papers/FABRIK.pdf). Nous avons mis en pratique l'algorithme dans Unity, afin d'avoir un visuel et de quoi pouvoir manipuler les bones dans un editeur. L'algorithme est une version simplifié et rapide de la cinématique inverse, il fonctionne en deux phase : 

- Forward : part du point le plus en profondeur et remonte jusqu'au root
- Backward : part du root jusqu'au point le plus en profondeur

On utilise ces deux phases pour modifier les positions de chaque bones avec des contraintes sur les jointures.

Toujours en simulation physique, nous avons implémenter une pseudo simulation de particules ([fluide viscoelastique](http://www.ligum.umontreal.ca/Clavet-2005-PVFS/pvfs.pdf)), de mon côté étant donné que l'algorithme n'était pas très rapide j'ai décidé d'utiliser les compute shader pour accélerer les calculs de mouvement des particules, je n'ai pas eu le temps d'implémenter la structures accélératrice utiliser en synthèse d'image sur GPU cependant ([lien](https://wickedengine.net/2018/05/21/scalabe-gpu-fluid-simulation/)).


