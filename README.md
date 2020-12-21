Impossible d'acceder au formulaire d'ajout de musique quand au moins une musique a été joué ou en cours
Doit quitter le programme à la fin de l'ajout d'une musique
Ne pas mettre d'espace dans les noms dans le formulaire
Tous les champs doivent être rempli
Faire attention aux noms de l'image et de la musique, si les noms des musiques sont mauvais le programme plante
Tailles des images entre 300x300 et 400x400 (jpg, png et bmp)
Pour compiler : gcc main.c -o prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lfmodex -lSDL2_image -lSDL2_ttf