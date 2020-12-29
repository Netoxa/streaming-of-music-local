//Read the README.md

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <fmod.h>
#include <string.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800


void SDL_ExitWithError(const char *message);
int Take_Number_Music(char *musics, FILE *fic);
char ***Take_List_Music(int number_music, FILE *fic, char *music, char *images, char *titre, char *genre, char *artiste);
char ***Shuffle_music_list(char ***tab_music, int number_music, int cols);
void Add_Music();
void Add_Image();
void Add_Artist();
void Add_Title();
void Add_Genre();
void Display_Images(SDL_Rect rectangle, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture, char *array, int po_y, int po_x);
void Image_Pause_Start(int k, SDL_Rect rectangle, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture);
void Image_Next_Previous(SDL_Rect rectangle, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture);
void Image_Mute_Demute(SDL_Rect rectangle, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture, int volume_zero);
void Image_Down_Turn(SDL_Rect rectangle, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture);

void SDL_ExitWithError(const char *message){
    
    SDL_Log("ERREUR : %s\n", message);
    
    SDL_Quit();
    
    exit(EXIT_FAILURE);

}

int Take_Number_Music(char *music, FILE *fic){

    int i = 0;
    
    while(fgets(music, 255, fic) != NULL){

        i++;

    }

    return i;
}

char ***Take_List_Music(int number_music, FILE *fic, char *music, char *images, char *titre, char *genre, char *artiste){

    unsigned int i;
    unsigned int j;

    rewind(fic);

    char ***tab = malloc(sizeof(char**) * number_music);


    for(i = 0; i < number_music; i++){

        tab[i] = malloc(sizeof(char*) * 5);

    }


    for(i = 0; i < number_music; i++){
        
        for(j = 0; j < 5; j++){

            tab[i][j] = malloc(sizeof(char) * 255);

        }
    }

    for(i = 0; i < number_music; i++){
        
        j = 0;
        
        fscanf(fic, "%s %s %s %s %s", music, images, artiste, titre, genre);

        strcpy(tab[i][j], music);
        j++;
        strcpy(tab[i][j], images);
        j++;
        strcpy(tab[i][j], artiste);
        j++;
        strcpy(tab[i][j], titre);
        j++;
        strcpy(tab[i][j], genre);

    }


    return tab;

}

 char ***Shuffle_music_list(char ***tab_music, int number_music, int cols){

    unsigned int i;
    unsigned int j;
    
    int position_music_one;
    int position_music_two;
    char music_one[255];
    char image_one[255];
    char artiste_one[255];
    char titre_one[255];
    char genre_one[255];
    char music_two[255];
    char image_two[255];
    char artiste_two[255];
    char titre_two[255];
    char genre_two[255];

    for(i = 0; i < 100; i++){

        position_music_one = rand() % number_music;
        position_music_two = rand() % number_music;
        
        strcpy(music_one, tab_music[position_music_one][0]);
        strcpy(music_two, tab_music[position_music_two][0]);
        
        strcpy(tab_music[position_music_two][0], music_one);
        strcpy(tab_music[position_music_one][0], music_two);

        strcpy(music_one, tab_music[position_music_one][1]);
        strcpy(music_two, tab_music[position_music_two][1]);
        
        strcpy(tab_music[position_music_two][1], music_one);
        strcpy(tab_music[position_music_one][1], music_two); 

        strcpy(music_one, tab_music[position_music_one][2]);
        strcpy(music_two, tab_music[position_music_two][2]);
        
        strcpy(tab_music[position_music_two][2], music_one);
        strcpy(tab_music[position_music_one][2], music_two); 

        strcpy(music_one, tab_music[position_music_one][3]);
        strcpy(music_two, tab_music[position_music_two][3]);
        
        strcpy(tab_music[position_music_two][3], music_one);
        strcpy(tab_music[position_music_one][3], music_two); 

        strcpy(music_one, tab_music[position_music_one][4]);
        strcpy(music_two, tab_music[position_music_two][4]);
        
        strcpy(tab_music[position_music_two][4], music_one);
        strcpy(tab_music[position_music_one][4], music_two); 

    }

    return tab_music;

}

void Add_Music(FILE *fic){


    unsigned int check = 0;
    char music_add[255];
    char path[255] = "sons/";

    printf("\n Enter the name of the music (Size between 1 and 50) : ");

    while(check == 0){
        
        fgets(music_add, 255, stdin);

        if(music_add[strlen(music_add) - 1] == '\n')
            music_add[strlen(music_add) - 1] = '\0';

        if(strlen(music_add) > 50 || strlen(music_add) < 1){

            printf("\n Wrong size\n");

        }else{

            check = 1;

        }

    }

    fseek(fic, 0, SEEK_END); 

    if(ftell(fic) == 0){

        fprintf(fic, "%s%s", path, music_add);
        
    }else{

        fprintf(fic, "\n%s%s", path, music_add);

    }
}   

void Add_Image(FILE *fic){


    unsigned int check = 0;
    char image_add[255];
    char path[255] = "images/";

    printf("\n Enter the name of the image (Size between 1 and 50) : ");

    while(check == 0){
        
        fgets(image_add, 255, stdin);

        if(image_add[strlen(image_add) - 1] == '\n')
            image_add[strlen(image_add) - 1] = '\0';

        if(strlen(image_add) > 50 || strlen(image_add) < 1){

            printf("\n Wrong size\n");

        }else{

            check = 1;

        }

    }

    fseek(fic, 0, SEEK_END); 

    fprintf(fic, " %s%s", path, image_add);
       //  fclose(fic);
}

void Add_Artist(FILE *fic){


    unsigned int check = 0;
    char artist_add[255];

    printf("\n Enter the name of the artist (Size between 1 and 50) : ");

    while(check == 0){
        
        fgets(artist_add, 255, stdin);

        if(artist_add[strlen(artist_add) - 1] == '\n')
            artist_add[strlen(artist_add) - 1] = '\0';

        if(strlen(artist_add) > 50 || strlen(artist_add) < 1){

            printf("\n Wrong size\n");

        }else{

            check = 1;

        }

    }

    fseek(fic, 0, SEEK_END); 

    fprintf(fic, " %s", artist_add);
        // fclose(fic);
}

void Add_Title(FILE *fic){


    unsigned int check = 0;
    char title_add[255];

    printf("\n Enter the name of the title (Size between 1 and 50) : ");

    while(check == 0){
        
        fgets(title_add, 255, stdin);

        if(title_add[strlen(title_add) - 1] == '\n')
            title_add[strlen(title_add) - 1] = '\0';

        if(strlen(title_add) > 50 || strlen(title_add) < 1){

            printf("\n Wrong size\n");

        }else{

            check = 1;

        }

    }

    fseek(fic, 0, SEEK_END); 

    fprintf(fic, " %s", title_add);
 //fclose(fic);
}

void Add_Genre(FILE *fic){


    unsigned int check = 0;
    char genre_add[255];

    printf("\n Enter the name of the genre (Size between 1 and 50) : ");

    while(check == 0){
        
        fgets(genre_add, 255, stdin);

        if(genre_add[strlen(genre_add) - 1] == '\n')
            genre_add[strlen(genre_add) - 1] = '\0';

        if(strlen(genre_add) > 50 || strlen(genre_add) < 1){

            printf("\n Wrong size\n");

        }else{

            check = 1;

        }

    }

    fseek(fic, 0, SEEK_END); 

    fprintf(fic, " %s", genre_add);

    //fclose(fic);

    printf("\n Music information has been recorded correctly");
}

void Add_playlist(){
 

    unsigned int check = 0;
    char *playlist_add = malloc(sizeof(char) * 255);
    char playlist_list[255];

    FILE *fic = fopen("playlists.txt", "a+");

    printf("\n List of playlist : ");
    
    while(fgets(playlist_list, 255, fic) != NULL){

        printf("\n %s", playlist_list);

    }

    while(check == 0){

        printf("\n Enter the name of the new playlist (Size between 1 and 50) : ");
        
        rewind(fic);
        
        fgets(playlist_add, 255, stdin);

        if(playlist_add[strlen(playlist_add) - 1] == '\n')

            playlist_add[strlen(playlist_add) - 1] = '\0';

            

        if(strlen(playlist_add) > 50 && strlen(playlist_add) < 1){

            printf("\n Wrong size\n");

        }

        
        while(fgets(playlist_list, 255, fic) != NULL){

            if(playlist_list[strlen(playlist_list) - 1] == '\n')
                
                playlist_list[strlen(playlist_list) - 1] = '\0';

             if(strcmp(playlist_add, playlist_list) == 0){
                 
                 printf("\n The playlist already exists\n");

                break;

             }else{

                 check = 1;

            }
        }
    }

    fseek(fic, 0, SEEK_END);

    if(ftell(fic) == 0){

    fprintf(fic, "%s", playlist_add);
        
    }else{

        fprintf(fic, "\n%s", playlist_add);

    }

    fclose(fic);

    fic = fopen(playlist_add, "w+");

    fclose(fic);

}


void Display_Images(SDL_Rect rectangle, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture, char *array, int po_y, int po_x){

    image = IMG_Load(array);

        if(image == NULL){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Impossible to load the picture");
        }        

        texture = SDL_CreateTextureFromSurface(renderer, image);
        
        SDL_FreeSurface(image);

        if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Impossible to load the texture");
        }

        rectangle.x = po_x;
        rectangle.y = po_y;

        if(SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0){
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_ExitWithError("Impossible to display the texture");
        }

    SDL_RenderPresent(renderer);

}

void Image_Pause_Start(int k, SDL_Rect rectangle, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture){

    char etat_musique[2][16] = {"images/paus.jpg","images/play.jpg"};

    Display_Images(rectangle, window, renderer, image, texture, etat_musique[k], 600, 475);

}

void Image_Next_Previous(SDL_Rect rectangle, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture){

    char previous_next[2][20] = {"images/previous.jpg","images/next.jpg"};
    unsigned int i;
    unsigned int position = 280;

    for(i = 0; i < 2; i++){

        Display_Images(rectangle, window, renderer, image, texture, previous_next[i], 600, position);

        position = 670;

    }
}

void Image_Mute_Demute(SDL_Rect rectangle, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture, int volume_zero){

    char mute_demute[2][20] = {"images/mute.jpg","images/demute.jpg"};

    Display_Images(rectangle, window, renderer, image, texture, mute_demute[volume_zero], 600, 560);

}

void Image_Down_Turn(SDL_Rect rectangle, SDL_Window *window, SDL_Renderer *renderer, SDL_Surface *image, SDL_Texture *texture){

    char previous_next[2][30] = {"images/sound_down.jpg","images/turn_up.jpg"};
    unsigned int i;
    unsigned int position = 100;

    for(i = 0; i < 2; i++){

        Display_Images(rectangle, window, renderer, image, texture, previous_next[i], 600, position);

        position = 180;

    }
}

char *Choice_Music(){

    unsigned int check = 0;
    char *music_delete = malloc(sizeof(char) * 255);

    printf("\n Enter the name of the music (Size between 1 and 50) : ");

    while(check == 0){
        
        fgets(music_delete, 255, stdin);

        if(music_delete[strlen(music_delete) - 1] == '\n')
            music_delete[strlen(music_delete) - 1] = '\0';

        if(strlen(music_delete) > 50 || strlen(music_delete) < 1){

            printf("\n Wrong size\n");

        }else{

            check = 1;

        }

    }
    return music_delete;


}

int Verify_music(char ***tab_music, char *choice_delete_music, int number_music){

    unsigned int i;
    char music[255];

    for(i = 0; i < number_music; i++){

        strncpy(music, tab_music[i][0] + 5, 255);

        if(strcmp(music, choice_delete_music) == 0){

            return 1;
   

        }
    }

    return 0;

}

void Delete_music(char *choice_playlist, char *choice_delete_music, FILE *fic, int number_music, char *music, char *images, char *artiste, char *titre, char *genre){

    unsigned int i;
    unsigned int j;
    char music_[255];

    rewind(fic);

    number_music--;

    char ***tab = malloc(sizeof(char**) * number_music);


    for(i = 0; i < number_music; i++){

        tab[i] = malloc(sizeof(char*) * 5);

    }


    for(i = 0; i < number_music; i++){
        
        for(j = 0; j < 5; j++){

            tab[i][j] = malloc(sizeof(char) * 255);

        }
    }

    for(i = 0; i < number_music; i++){
        
        j = 0;
        
        fscanf(fic, "%s %s %s %s %s", music, images, artiste, titre, genre);

        strncpy(music_, music + 5, 255);

        if(strcmp(music_, choice_delete_music) != 0){

            strcpy(tab[i][j], music);
            j++;
            strcpy(tab[i][j], images);
            j++;
            strcpy(tab[i][j], artiste);
            j++;
            strcpy(tab[i][j], titre);
            j++;
            strcpy(tab[i][j], genre);

        }else{

            i--;

        }
    }

    fclose(fic);

    fic = fopen(choice_playlist, "w+");

    for(i = 0; i < number_music; i++){

        fprintf(fic, "%s %s %s %s %s", tab[i][0], tab[i][1], tab[i][2], tab[i][3], tab[i][4]);

        fputc('\n', fic);

    }

    printf("\n The deletion of a music has been made");

    fclose(fic);

}


char *List_playlist(FILE *fic){

    char *playlist = malloc(sizeof(char) * 255);
    char *choice_playlist = malloc(sizeof(char) * 255);
    int i = 0;
    
    printf("\n List of playlist : ");
    
    while(fgets(playlist, 255, fic) != NULL){

        printf("\n %s", playlist);

    }

    while(i == 0){

        rewind(fic);

        printf("\n Enter the name of the playlist : ");
        
        fgets(choice_playlist, 255, stdin);

        if(choice_playlist[strlen(choice_playlist) - 1] == '\n')

            choice_playlist[strlen(choice_playlist) - 1] = '\0';

        while(fgets(playlist, 255, fic) != NULL){
            
            if(playlist[strlen(playlist) - 1] == '\n')
                
                playlist[strlen(playlist) - 1] = '\0';

            if(strcmp(playlist, choice_playlist) == 0)
            
                i = 1;
    
        }
    }

    fclose(fic);

    printf("\n The selection of the playlist has been made");

    return choice_playlist;

}


int main(int argc, char *argv[])
{
    SDL_bool program_launched = SDL_TRUE;
    SDL_Event event;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface *image = NULL;
    SDL_Texture *texture = NULL;
    SDL_Rect rectangle;
    SDL_Surface *texte = NULL;
    SDL_Color couleur = {25, 31, 29};
    
    TTF_Font *police = NULL;

    FMOD_BOOL etat = 0;
    FMOD_BOOL etat_musique = 0;
    FMOD_CHANNELGROUP *canal;
    FMOD_CHANNEL *channel;
    FMOD_SYSTEM *system;
    FMOD_SOUND *musique;
    FMOD_RESULT resultat;

    unsigned int lecture_check;
    unsigned int change_something;
    int number_music = 0;
    unsigned int number_playlist = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int check;
    unsigned int volume_zero = 1;
    float volume = 0.5; 
    char music[255];
    char images[255];
    char artiste[255];
    char titre[255];
    char genre[255];
    char ***tab_music;
    char *choice_delete_music = NULL;
    char *choice_playlist = NULL;
    FILE *fic;

    /* Launch SDL */
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        SDL_ExitWithError("Initialization SDL");

    /* Creation window + render */
    if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Impossible to create the window and renderer");


    /* Creation and initialization of a system object */
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    if(TTF_Init() == -1)
        SDL_ExitWithError("Impossible to create ttf");

    police = TTF_OpenFont("polices/ArialNova-Light.ttf", 30);

    

    printf("\n\n Play the music list : p");
    printf("\n Restart the music list : m");
    printf("\n Pause / Replay : space ");
    printf("\n Replay the music a the begin : r");
    printf("\n Shuffle the music list : j");
    printf("\n Add a music : o");
    printf("\n Delete a music : x");
    printf("\n Choice a playlist : c");
    printf("\n Create a playlist : w");
    printf("\n Delete a playlist : z");
    printf("\n");
    /*------------------------------------------------------------*/

    SDL_SetRenderDrawColor(renderer, 85, 158, 142, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    

    while(program_launched){ // As long as the window is displayed

        FMOD_Channel_IsPlaying(channel, &etat_musique); // Check if a music is playing

        if((lecture_check == 1 && !etat_musique && i < number_music) || change_something == 1 && lecture_check == 1){

            resultat = FMOD_System_CreateSound(system, tab_music[i][0] , FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);

            // Check if it has been opened and it's not the last music
            if (resultat != FMOD_OK){

                SDL_ExitWithError("Impossible to read the music");

            }

            SDL_RenderClear(renderer);

            Display_Images(rectangle, window, renderer, image, texture, tab_music[i][1], 150, 300);

            FMOD_System_GetMasterChannelGroup(system, &canal);
            
            FMOD_ChannelGroup_GetPaused(canal, &etat);

            if (etat){

                Image_Pause_Start(1, rectangle, window, renderer, image, texture);

            }else{

                Image_Pause_Start(0, rectangle, window, renderer, image, texture);

            }

            Image_Next_Previous(rectangle, window, renderer, image, texture);

            Image_Mute_Demute(rectangle, window, renderer, image, texture, volume_zero);

            Image_Down_Turn(rectangle, window, renderer, image, texture);
                
            texte = TTF_RenderText_Blended(police, tab_music[i][2], couleur);

            if(texte == NULL){
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_ExitWithError("Impossible to load the text");
            }

            texture = SDL_CreateTextureFromSurface(renderer, texte);
            SDL_FreeSurface(texte);

            if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0){
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_ExitWithError("Impossible to load the texture");
            }

            rectangle.x = (WINDOW_WIDTH - rectangle.w) / 2;
            rectangle.y = 690;

            if(SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0){
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_ExitWithError("Impossible to display the texture");
            }

            SDL_RenderPresent(renderer);

            texte = TTF_RenderText_Blended(police,  tab_music[i][3], couleur);

            if(texte == NULL){
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_ExitWithError("Impossible to load the text");
            }

            texture = SDL_CreateTextureFromSurface(renderer, texte);
            SDL_FreeSurface(texte);

            if(SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0){
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_ExitWithError("Impossible to load the texture");
            }

            rectangle.x = (WINDOW_WIDTH - rectangle.w) / 2;
            rectangle.y = 730;

            if(SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0){
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_ExitWithError("Impossible to display the texture");
            }

            SDL_RenderPresent(renderer);

            change_something = 0;

            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, &channel);

            i++;

        }

        while(SDL_PollEvent(&event)){ // The events that do not block the program

            switch(event.type){ // List of events
                	
                case SDL_KEYUP:
                    
                    switch(event.key.keysym.sym){

                        case SDLK_SPACE:

                            FMOD_System_GetMasterChannelGroup(system, &canal);
                            FMOD_ChannelGroup_GetPaused(canal, &etat);

                            if (etat){
                                // If the song is in pause

                                Image_Pause_Start(0, rectangle, window, renderer, image, texture);
                            
                                FMOD_ChannelGroup_SetPaused(canal, 0); // We remove the pause
                            
                            }else{
                                // Otherwise, it is in play

                                Image_Pause_Start(1, rectangle, window, renderer, image, texture);
                            
                                FMOD_ChannelGroup_SetPaused(canal, 1); // We activate the pause

                            }

                            continue;

                        case SDLK_p:

                            if(choice_playlist == NULL)

                                printf("\n No playlist selection");

                            if(number_music == 0 && choice_playlist != NULL)

                                printf("\n The playlist is empty");

                            if(i == number_music && number_music > 1 && choice_playlist != NULL)

                                printf("\n List of musics is finished");

                            else

                                lecture_check = 1;

                            continue;

                        case SDLK_r:

                            if(i <= number_music){ // Music must be playing

                                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, &channel);

                            }

                            continue;


                        case SDLK_m:

                            i = 0; // Return the list to the beginning
                            change_something = 1;
            
                            continue;

                        case SDLK_j:

                            tab_music = Shuffle_music_list(tab_music, number_music, 5);

                            i = 0;
                        
                            change_something = 1;

                            continue;

                        case SDLK_o:

                        if(choice_playlist == NULL)
                            printf("\n No playlist selection");

                            else{
                        
                         fic = fopen(choice_playlist, "a+");

                            Add_Music(fic);
                            Add_Image(fic);
                            Add_Artist(fic);
                            Add_Title(fic);
                            Add_Genre(fic);

                            fclose(fic);
                                                  
                            fic = fopen(choice_playlist, "r");

                            number_music = Take_Number_Music(music, fic);
    
                            tab_music = Take_List_Music(number_music, fic, music, images, artiste, titre, genre);
                            
                            fclose(fic);
                        }
                            continue;

                        case SDLK_x:

                            if(choice_playlist == NULL){
                            printf("\n No playlist selection");

                        }else{
                        
                    fic = fopen(choice_playlist, "r");
                      
                    number_music = Take_Number_Music(music, fic);
            
     
                            tab_music = Take_List_Music(number_music, fic, music, images, artiste, titre, genre);
                           
                            choice_delete_music = Choice_Music();

                            check = Verify_music(tab_music, choice_delete_music, number_music);

                            if(check == 1)
                            
 
                                Delete_music(choice_playlist, choice_delete_music, fic, number_music, music, images, artiste, titre, genre);
                            
                            else
                            
                                printf("\n Music does not exist");
                            
                           
                            fic = fopen(choice_playlist, "r");

                            number_music = Take_Number_Music(music, fic);
    
                            tab_music = Take_List_Music(number_music, fic, music, images, artiste, titre, genre);
                        }
                   

                            continue;

                        case SDLK_c:

                        fic = fopen("playlists.txt", "r");

                        choice_playlist =  List_playlist(fic);
                        
                    fic = fopen(choice_playlist, "r");
                    number_music = Take_Number_Music(music, fic);
    
                        tab_music = Take_List_Music(number_music, fic, music, images, artiste, titre, genre);

                        fclose(fic);

                        lecture_check = 0;

                        continue;

                        default:
                        
                            continue;

                            case SDLK_w:

                        Add_playlist();

                        continue;


                        }
                    
                        


                case SDL_MOUSEBUTTONUP:

                    if (event.button.button == SDL_BUTTON_LEFT){    
                
                        if(event.button.x >= 475 && event.button.x <= 525 && event.button.y <= 651 && event.button.y >= 601){

                            FMOD_System_GetMasterChannelGroup(system, &canal);
                            FMOD_ChannelGroup_GetPaused(canal, &etat);

                            if (etat){
                                // If the song is in pause

                                Image_Pause_Start(0, rectangle, window, renderer, image, texture);
        
                                FMOD_ChannelGroup_SetPaused(canal, 0); // We remove the pause
                            
                            }else{
                                // Otherwise, it is in play

                                Image_Pause_Start(1, rectangle, window, renderer, image, texture);
                        
                                FMOD_ChannelGroup_SetPaused(canal, 1); // We activate the pause

                        }

                    }

                    if(event.button.x >= 280 && event.button.x <= 330 && event.button.y <= 651 && event.button.y >= 601 && number_music != 0){ 
                    // previous music
                        if(i == 1){

                            i--; // If it's the first music that plays
                            change_something = 1;

                        }

                        if(i > 1){

                            i = i - 2; // If it's another music that plays
                            change_something = 1;

                        }

                    }

                    if(event.button.x >= 670 && event.button.x <= 720 && event.button.y <= 651 && event.button.y >= 601 && i < number_music){ 
                    //next music
                        change_something = 1;

                    }

                    if(event.button.x >= 560 && event.button.x <= 610 && event.button.y <= 651 && event.button.y >= 601){ 
                    //mute / demute music
                        if(volume_zero == 1){

                             FMOD_Channel_SetVolume(channel, 0);

                             volume_zero = 0;

                        }else{

                             FMOD_Channel_SetVolume(channel, volume);

                             printf("\n The volume is %.0lf", volume * 10);

                             volume_zero = 1;

                        }

                        Image_Mute_Demute(rectangle, window, renderer, image, texture, volume_zero);

                    }

                    if(event.button.y <= 651 && event.button.y >= 601 && event.button.x >= 100 && event.button.x <= 150){
                    // Down the music
                        Image_Down_Turn(rectangle, window, renderer, image, texture);

                        if(volume > 0.1){
                            
                            volume = volume - 0.1;

                            FMOD_Channel_SetVolume(channel, volume);

                            printf("\n The volume is %.0lf", volume * 10);

                        }
                    }

                    if(event.button.y <= 651 && event.button.y >= 601 && event.button.x >= 180 && event.button.x <= 230){
                    // Up the music
                        Image_Down_Turn(rectangle, window, renderer, image, texture);

                        if(volume < 1){
                            
                            volume = volume + 0.1;

                            FMOD_Channel_SetVolume(channel, volume);

                            printf("\n The volume is %.0lf", volume * 10);

                        }
                    }
                }

                continue;
                
                case SDL_QUIT: // If click on the button to close the window

                    program_launched = SDL_FALSE; // Close the window

                    break;

                default:
                    break;
            }
        }
    }

    /*------------------------------------------------------------*/

    for (i = 0; i < number_music; i++) {
        
        for (j = 0; j < 5; j++) {
        
            free(tab_music[i][j]);

        }

        free(tab_music[i]);
    }

    free(tab_music);
    FMOD_Sound_Release(musique);
    FMOD_System_Close(system);
    FMOD_System_Release(system);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;

}