Ne pas mettre d'espace dans les noms dans le formulaire
Tous les champs doivent être rempli (le programme se met en pause mais pas la chanson si une est en cours)
Faire attention aux noms de l'image et de la musique, si les noms des musiques sont mauvais le programme plante
Tailles des images doit être 400x400 (jpg, png et bmp) : https://www.iloveimg.com/fr/redimensionner-image
Pour compiler : gcc main.c -o prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lfmodex -lSDL2_image -lSDL2_ttf