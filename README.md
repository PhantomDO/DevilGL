# opengl_shader

https://github.com/rorygames/OBJ-Loader/blob/master/ObjectLoader/Model.h
https://gamedev.stackexchange.com/questions/116208/modern-opengl-c-obj-loader
https://stackoverflow.com/questions/60829086/custom-opengl-obj-model-loader-indices-calculation-not-working

# Open GL

Pour la dernière partie en synthèse d'image, nous avons utilisé OpenGL. Le but étant de réaliser un jeu temps réel, nous avons dû apprendre les bases de l'utilisation de cette librairie. Les premiers pas ont été d'afficher un triangle à l'écran, lui appliquer une couleur, puis une texture. Enfin, vu qu'un jeu est constitué de triangles cachés dans des objets, nous avons utilisé le lecteurs d'OBJ déjà implémenter pour le projet de Raytracing. 

Nous avons ensuite cherché à utiliser des inputs, pour effectuer des modifications, comme bouger la caméra, changer sa rotation, etc... 

Pour améliorer la lisibilité et l'utilisation du code, j'ai décidé d'en faire un mini-moteur de jeu, en reprenant le principe des composants qu'utilise le moteur Unity et grâce à différentes aides ([component system](https://stackoverflow.com/questions/44105058/implementing-component-system-from-unity-in-c), [rtii](https://docs.microsoft.com/fr-fr/cpp/cpp/run-time-type-information?view=msvc-170)). 

Je travaillerais sur mon temps libre à créer un petit fps. 
