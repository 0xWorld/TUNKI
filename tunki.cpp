#include "raylib.h"
#include "stdlib.h"
#include "time.h"
int main(void)
{
    
    // Variables Generales
    //--------------------------------------------------------------------------------------
    const int screenWidth = 480;
    const int screenHeight = 800;
    bool quitGame = false;
    bool pause = false;
    int framesCounter = 0;
    int time  = 1;
    typedef enum {LOGO,TITLE,GAMING,ENDING} GameScreen;
    GameScreen gameScreen = LOGO;
    int state = 0;
    float alpha = 0.0;
    bool animation = false;
    int PlayerScore = 0;
    int nivel = 1;
    int totalScore = 0;
    int ptjMaxToNextLvl = 10;
    const float updateTime{1.0/12.0};
    float runningTime{};
    InitWindow(screenWidth, screenHeight, "T U N K I");
    SetTargetFPS(60);

    //------------------------------------Musica-----------------------------------------------
    InitAudioDevice();
    Music music = LoadMusicStream("musica/danza_mirlos.mp3");
    PlayMusicStream(music);
    bool pauseMusic= false;

    //----------------------------------Carga Texturas------------------------------------------
    //Background
    Texture2D background_Logo =  LoadTexture("textures/intro.png");
    Texture2D background_Title = LoadTexture("textures/title-background-1.png");
    Texture2D background_Title2 = LoadTexture("textures/title-background-2.png");
    Texture2D background_Gaming = LoadTexture("textures/background-Gaming.png");

    //Jugador
    Texture2D EnemigoTexture = LoadTexture("textures/ave-1.png");
    Texture2D EnemigoTexture2 = LoadTexture("textures/ave-2.png");
    Texture2D EnemigoTexture3 = LoadTexture("textures/ave-3.png");    

    //Enemigo
    Texture2D PlayerTexture = LoadTexture("textures/nido.png");

    //Botones
    Texture2D button_Play = LoadTexture("textures/btn-play.png");
    Texture2D button_Exit = LoadTexture("textures/btn-exit.png");
    Texture2D button_Retry = LoadTexture("textures/btn-play.png");

    //Mora
    Texture2D mora = LoadTexture("textures/mora.png");

    //Roca
    Texture2D roca = LoadTexture("textures/roca.png");

    //---------------------------------Mouse Variables----------------------------------    
    Vector2 mousePosition = {0,0};

    //-------------------------------------Jugador--------------------------------------
    Vector2 PlayerPosition = {screenWidth/2-30,screenHeight*0.8};
   
    //-------------------------------------Botones---------------------------------------
    bool buttonDer_over = false;
    bool buttonIzq_over = false;
    Vector2 buttonLeft = {(screenWidth/4)-75, (screenHeight*0.75)-46};
    Vector2 buttonRight = {(screenWidth*0.75)-75, (screenHeight*0.75)-46};

    //-------------------------------------Enemigos--------------------------------------
    Vector2 enemigoPosicion1 = {screenWidth/2-30,-500};
    Vector2 enemigoPosicion2 = {screenWidth/2-30,-650};
    Vector2 enemigoPosicion3 = {screenWidth/2-30,-800};
    Vector2 enemigoPosicion4 = {screenWidth/2-30,-950};
    Vector2 enemigoPosicion5 = {screenWidth/2-30,-1100};
    Vector2 enemigoPosicion6 = {screenWidth/2-30,-1250};                
    int enemigoSpeed = 7;   

    //--------------------------------------Variables Mora-----------------------------------------
    Rectangle moraRec;
    moraRec.width = mora.width/5;
    moraRec.height = mora.height;
    moraRec.x = 0;
    moraRec.y = 0;
    Vector2 moraPos;
    moraPos.x = 10;
    moraPos.y = 10;
    int frameMora{};
    int moraSpeed = 7;
    bool activeMora = false;
    int LvlToshowMora = 2;

    //-------------------------------------Roca----------------------------------------------------
    bool activeRoca = false;
    int LvlToshowRoca = 3;
    int rocaSpeed = 10;
    Vector2 rocaPosicion = {0,0};
    //-------------------------------------------------------------------------------------------

    while (!WindowShouldClose() && !quitGame){

        BeginDrawing();
        UpdateMusicStream(music);

        framesCounter++;
        mousePosition.x = GetMouseX();
        mousePosition.y = GetMouseY();
        const float dT{GetFrameTime()};

        switch (gameScreen){
            case LOGO:
                    if(state == 0){
                        if(alpha < 1.0){
                            alpha += 0.05;
                        }else{
                            state = 1;
                        }
                    }else if(state == 1){
                        alpha =  1.0;
                        if( time%3 == 0){ //3 sec
                            state = 2;
                        }
                    }else if(state == 2){
                        if(alpha > 0.0){
                            alpha -= 0.05;
                        }else{
                            gameScreen = TITLE; //cambia a titulo
                            state = 0; //setea el estado en 0 para usarlo en otra pantalla
                        }
                    }            
                break;
            case TITLE:                    
                    if(state == 0){
                        if(alpha < 1.0){
                            alpha += 0.05;
                        }else{
                            state = 1;
                        }
                    }else if(state == 1){
                        alpha =  1.0;
                        if((framesCounter%5)==0) animation = !animation;
                        if(mousePosition.x >= buttonRight.x && mousePosition.x <= (buttonRight.x+151) && mousePosition.y >= buttonRight.y && mousePosition.y <= (buttonRight.y+92)){
                            buttonDer_over = true;
                            //click
                            if(IsMouseButtonPressed(0)) quitGame = true;
                        }else{
                            buttonDer_over = false;                        
                        }

                        if(mousePosition.x >= buttonLeft.x && mousePosition.x <= (buttonLeft.x+151) && mousePosition.y >= buttonLeft.y && mousePosition.y <= (buttonLeft.y+92)){
                            buttonIzq_over = true;
                            //click
                            if(IsMouseButtonPressed(0)) PlayMusicStream(music),state = 2; //a jugar!
                        }else{
                            buttonIzq_over = false;
                        }
                    }else if(state == 2){
                        if(alpha > 0.0){
                            alpha -= 0.05;
                        }else{
                            gameScreen = GAMING;
                            state = 0;
                        }
                    }              
                break;
            case GAMING:
                    if(state == 0){
                        if(alpha < 1.0) alpha +=0.05;
                        else state = 1;
                    }else if(state == 1){
                        alpha = 1.0;
                        //Posicion del enemigo
                        enemigoPosicion1.y = -500;
                        enemigoPosicion2.y = -650;
                        enemigoPosicion3.y = -800;
                        enemigoPosicion4.y = -950;
                        enemigoPosicion5.y = -1100;
                        enemigoPosicion6.y = -1250;
                        PlayerPosition.x = screenWidth/2-30;
                        PlayerPosition.y = screenHeight*0.8;
                        
                        //Deteccion de ENTER
                        if(IsKeyPressed(KEY_ENTER)) state = 2;
                    }else if(state == 2){
                        if(!pause){
                            if((framesCounter % 5) == 0) animation = !animation;
                            //Posicion Jugador
                            if(GetMouseX()>=402){
                                PlayerPosition.x = 402;
                            }else{
                                PlayerPosition.x = GetMouseX();
                            }
                            
                            //movimiento mora
                            if(nivel >= LvlToshowMora){
                                activeMora = true;
                                runningTime += dT;
                                if(runningTime >= updateTime){
                                    runningTime = 0.0;
                                    //Actualizacion de la animacion del frame
                                    moraRec.x = frameMora * moraRec.width;
                                    frameMora++;

                                    if(frameMora > 4){
                                        frameMora = 0;
                                    }
                                }
                                moraPos.y +=moraSpeed;
                            }

                            //Movimiento Roca
                            if(nivel >= LvlToshowRoca){
                                rocaPosicion.y +=rocaSpeed;
                                activeRoca = true;
                            }


                            //movimiento jugador y enemigos
                            PlayerPosition.y = screenHeight*0.8;
                            enemigoPosicion1.y += enemigoSpeed;
                            enemigoPosicion2.y += enemigoSpeed;
                            enemigoPosicion3.y += enemigoSpeed;
                            enemigoPosicion4.y += enemigoSpeed;
                            enemigoPosicion5.y += enemigoSpeed;
                            enemigoPosicion6.y += enemigoSpeed;

                            if((moraPos.y+30 >= PlayerPosition.y && moraPos.y <= PlayerPosition.y+50) && (moraPos.x+95 >= PlayerPosition.x && moraPos.x <= PlayerPosition.x+95)){
                                PlayerScore += 10;
                                totalScore += 10;
                                moraPos.x = GetRandomValue(0,340)+60;
                                moraPos.y = -100;
                                if(PlayerScore >= ptjMaxToNextLvl){
                                    nivel++;
                                    enemigoSpeed +=0.3;
                                    PlayerScore = 0;
                                }
                            }else{
                                 if(moraPos.y > 750){
                                    moraPos.x = GetRandomValue(0,340)+60;
                                    moraPos.y = -100;
                                }
                            }

                            if((rocaPosicion.y+30 >= PlayerPosition.y && rocaPosicion.y <= PlayerPosition.y+50) && (rocaPosicion.x+95 >= PlayerPosition.x && rocaPosicion.x <= PlayerPosition.x+95)){
                                PlayerScore -= 10;
                                totalScore -= 10;
                                rocaPosicion.x = GetRandomValue(0,340)+60;
                                rocaPosicion.y = -100;
                                if(PlayerScore >= ptjMaxToNextLvl){
                                    nivel++;
                                    enemigoSpeed +=0.3;
                                    PlayerScore = 0;
                                }
                            }else{
                                 if(rocaPosicion.y > 750){
                                    rocaPosicion.x = GetRandomValue(0,340)+60;
                                    rocaPosicion.y = -100;
                                }
                            }


                            if((enemigoPosicion1.y+40 >= PlayerPosition.y && enemigoPosicion1.y <= PlayerPosition.y+50) && (enemigoPosicion1.x+95 >= PlayerPosition.x && enemigoPosicion1.x <= PlayerPosition.x+95)){
                                PlayerScore++;
                                totalScore++;
                                enemigoPosicion1.x = GetRandomValue(0,320)+80;
                                enemigoPosicion1.y = (screenWidth/2-30) - 500;
                                if(PlayerScore >= ptjMaxToNextLvl){
                                    nivel++;
                                    enemigoSpeed +=0.3;
                                    PlayerScore = 0;
                                }
                            }else if((enemigoPosicion2.y+40 >= PlayerPosition.y && enemigoPosicion2.y <= PlayerPosition.y+50) && (enemigoPosicion2.x+95 >= PlayerPosition.x && enemigoPosicion2.x <= PlayerPosition.x+95)){
                                PlayerScore++;  
                                totalScore++;                              
                                enemigoPosicion2.x = GetRandomValue(0,320)+80;
                                enemigoPosicion2.y = (screenWidth/2-30) - 500;
                                if(PlayerScore >= ptjMaxToNextLvl){
                                    nivel++;
                                    enemigoSpeed +=0.3;
                                    PlayerScore = 0;
                                }
                            }else if((enemigoPosicion3.y+40 >= PlayerPosition.y && enemigoPosicion3.y <= PlayerPosition.y+50) && (enemigoPosicion3.x+95 >= PlayerPosition.x && enemigoPosicion3.x <= PlayerPosition.x+95)){
                                PlayerScore++;                                
                                totalScore++;
                                enemigoPosicion3.x = GetRandomValue(0,320)+80;
                                enemigoPosicion3.y = (screenWidth/2-30) - 500;
                                if(PlayerScore >= ptjMaxToNextLvl){
                                    nivel++;
                                    enemigoSpeed +=0.3;
                                    PlayerScore = 0;
                                }
                            }else if((enemigoPosicion4.y+40 >= PlayerPosition.y && enemigoPosicion4.y <= PlayerPosition.y+50) && (enemigoPosicion4.x+95 >= PlayerPosition.x && enemigoPosicion4.x <= PlayerPosition.x+95)){
                                PlayerScore++;
                                totalScore++;
                                enemigoPosicion4.x = GetRandomValue(0,320)+80;
                                enemigoPosicion4.y = (screenWidth/2-30) - 500;
                                if(PlayerScore >= ptjMaxToNextLvl){
                                    nivel++;
                                    enemigoSpeed +=0.3;
                                    PlayerScore = 0;
                                }
                            }else if((enemigoPosicion5.y+40 >= PlayerPosition.y && enemigoPosicion5.y <= PlayerPosition.y+50) && (enemigoPosicion5.x+95 >= PlayerPosition.x && enemigoPosicion5.x <= PlayerPosition.x+95)){
                                PlayerScore++;
                                totalScore++;
                                enemigoPosicion5.x = GetRandomValue(0,320)+80;
                                enemigoPosicion5.y = (screenWidth/2-30) - 500;                                
                                if(PlayerScore >= ptjMaxToNextLvl){
                                    nivel++;
                                    enemigoSpeed +=0.3;
                                    PlayerScore = 0;
                                }
                            }else if((enemigoPosicion6.y+40 >= PlayerPosition.y && enemigoPosicion6.y <= PlayerPosition.y+50) && (enemigoPosicion6.x+95 >= PlayerPosition.x && enemigoPosicion6.x <= PlayerPosition.x+95)){
                                PlayerScore++;      
                                totalScore++;
                                enemigoPosicion6.x = GetRandomValue(0,320)+80;
                                enemigoPosicion6.y = (screenWidth/2-30) - 500;
                                if(PlayerScore >= ptjMaxToNextLvl){
                                    nivel++;
                                    enemigoSpeed +=0.3;
                                    PlayerScore = 0;                                    
                                }
                            }else{
                                if(enemigoPosicion1.y > 650){
                                    pause = true;
                                    gameScreen = ENDING;
                                    state = 1;
                                }
                                if(enemigoPosicion2.y > 650){
                                    pause = true;
                                    gameScreen = ENDING;
                                    state = 2;
                                }
                                if(enemigoPosicion3.y > 650){
                                    pause = true;
                                    gameScreen = ENDING;
                                    state = 3;
                                }
                                if(enemigoPosicion4.y > 650){
                                    pause = true;
                                    gameScreen = ENDING;
                                    state = 4;
                                }
                                if(enemigoPosicion5.y > 650 ){
                                    pause = true;
                                    gameScreen = ENDING;
                                    state = 5;
                                }
                                if(enemigoPosicion6.y > 650){
                                    pause = true;
                                    gameScreen = ENDING;
                                    state = 6;
                                }
                            }
                        }
                    }
                break;
            case ENDING:
                    PauseMusicStream(music);
                    if(mousePosition.x >= buttonRight.x && mousePosition.x <= (buttonRight.x+151) && mousePosition.y >= buttonRight.y && mousePosition.y <= (buttonRight.y+92)){
                        buttonDer_over = true;
                        //click
                        if(IsMouseButtonPressed(0)){
                            PlayMusicStream(music);
                            gameScreen = TITLE;
                            pause = false;                            
                            enemigoPosicion1.y = -500;
                            enemigoPosicion2.y = -650;
                            enemigoPosicion3.y = -800;
                            enemigoPosicion4.y = -950;
                            enemigoPosicion5.y = -1100;
                            enemigoPosicion6.y = -1250;                            
                            
                            PlayerPosition.x = screenWidth/2-30;
                            PlayerPosition.y = screenHeight*0.8;

                            enemigoSpeed = 7;
                            state = 0;                            
                            PlayerScore = 0;
                            totalScore = 0;
                            nivel = 1;
                            activeRoca = false;
                            activeMora = false;
                        }
                    }else{
                        buttonDer_over = false;                        
                    }

                    if(mousePosition.x >= buttonLeft.x && mousePosition.x <= (buttonLeft.x+151) && mousePosition.y >= buttonLeft.y && mousePosition.y <= (buttonLeft.y+92)){
                        buttonIzq_over = true;                        
                        if(IsMouseButtonPressed(0)){
                            //reset valores para el reinicio del juego
                            PlayMusicStream(music);
                            pause = false;                            
                            enemigoPosicion1.y = -500;
                            enemigoPosicion2.y = -650;
                            enemigoPosicion3.y = -800;
                            enemigoPosicion4.y = -950;
                            enemigoPosicion5.y = -1100;
                            enemigoPosicion6.y = -1250;                            
                            
                            PlayerPosition.x = screenWidth/2-30;
                            PlayerPosition.y = screenHeight*0.8;

                            enemigoSpeed = 7;
                            gameScreen = GAMING;
                            state = 0;                            
                            PlayerScore = 0;
                            totalScore = 0;
                            nivel = 1;                            
                            activeRoca = false;
                            activeMora = false;
                        }
                    }else buttonIzq_over = false;
                break;
            default:
                break;
        }


        ClearBackground(BLACK);
        
        switch (gameScreen){
            case LOGO:
                switch (state){
                    case 0:
                        DrawTexture(background_Logo,0,0,Fade(BLACK,alpha));
                        break;                        
                    case 1:
                        DrawTexture(background_Logo,0,0,WHITE);
                        break;
                    case 2:
                        DrawTexture(background_Logo,0,0,Fade(BLACK,alpha));
                        break;                             
                }
                break;
            case TITLE:
                    switch (state){
                    case 0:
                        DrawTexture(background_Title,0,0,Fade(BLACK,alpha));
                        break;
                    case 1:
                        if(animation)
                            DrawTexture(background_Title,0,0,WHITE);
                        else
                            DrawTexture(background_Title2,0,0,WHITE);

                        if(!buttonIzq_over) 
                            DrawTexture(button_Play,buttonLeft.x,buttonLeft.y,WHITE);//draw button normal
                        else 
                            DrawTexture(button_Play,buttonLeft.x,buttonLeft.y,RED);//draw button with red

                        if(!buttonDer_over) 
                            DrawTexture(button_Exit,buttonRight.x,buttonRight.y,WHITE);//draw button normal
                        else 
                            DrawTexture(button_Exit,buttonRight.x,buttonRight.y,RED);//draw button with red                            

                        DrawText("Creado por: Dylan Ramirez A.",screenWidth/2 - (MeasureText("Creado por: Dylan Ramirez A.",20))/2,buttonLeft.y-150,20,RAYWHITE);

                        break;
                    case 2:
                            DrawTexture(background_Title,0,0,Fade(BLACK,alpha));//transccion cuando hace click 
                        break;
                    }                
                break;
            case GAMING:                    
                    if(state==0){
                        DrawTexture(background_Gaming,0,0,Fade(BLACK,alpha));
                    }else if(state == 1){
                        DrawTexture(background_Gaming,0,0,WHITE);
                        DrawTexture(PlayerTexture,PlayerPosition.x,PlayerPosition.y,WHITE);
                        DrawText("PRESIONA 'ENTER' PARA INICIAR",screenWidth/2 - (MeasureText("PRESIONA 'ENTER' PARA INICIAR",20))/2,screenHeight*0.6,20,BLACK);                        
                    }else if(state == 2){                        
                        DrawTexture(background_Gaming,0,0,WHITE);
                        if(activeMora){
                            DrawTextureRec(mora,moraRec,moraPos,WHITE);
                        }
                        
                        if(activeRoca){
                            DrawTexture(roca,rocaPosicion.x,rocaPosicion.y,WHITE);    
                        }

                        DrawTexture(PlayerTexture,PlayerPosition.x,PlayerPosition.y,WHITE);
                        if(animation){
                            DrawTexture(EnemigoTexture,enemigoPosicion1.x,enemigoPosicion1.y,WHITE);
                            DrawTexture(EnemigoTexture2,enemigoPosicion2.x,enemigoPosicion2.y,WHITE);
                            DrawTexture(EnemigoTexture,enemigoPosicion3.x,enemigoPosicion3.y,WHITE);
                            DrawTexture(EnemigoTexture2,enemigoPosicion4.x,enemigoPosicion4.y,WHITE);
                            DrawTexture(EnemigoTexture,enemigoPosicion5.x,enemigoPosicion5.y,WHITE);
                            DrawTexture(EnemigoTexture2,enemigoPosicion6.x,enemigoPosicion6.y,WHITE);
                        }else{
                            DrawTexture(EnemigoTexture2,enemigoPosicion1.x,enemigoPosicion1.y,WHITE);
                            DrawTexture(EnemigoTexture,enemigoPosicion2.x,enemigoPosicion2.y,WHITE);
                            DrawTexture(EnemigoTexture2,enemigoPosicion3.x,enemigoPosicion3.y,WHITE);
                            DrawTexture(EnemigoTexture,enemigoPosicion4.x,enemigoPosicion4.y,WHITE);
                            DrawTexture(EnemigoTexture2,enemigoPosicion5.x,enemigoPosicion5.y,WHITE);
                            DrawTexture(EnemigoTexture,enemigoPosicion6.x,enemigoPosicion6.y,WHITE);
                        }
                        //score count text
                        DrawText(FormatText("NIVEL: %03i",nivel),screenWidth/2-(MeasureText("NIVEL: 0",20))/2,screenHeight*0.1,20,BLACK);
                        DrawText(FormatText("SCORE: %03i",totalScore),screenWidth/2-(MeasureText("SCORE: 000",20))/2,screenHeight*0.2,20,BLACK);
                    }
                break;
            case ENDING:                        
                        DrawTexture(background_Gaming,0,0,WHITE);
                        DrawTexture(PlayerTexture,PlayerPosition.x,PlayerPosition.y,WHITE);
                        switch (state){
                            case 1:{
                                DrawTexture(EnemigoTexture3,enemigoPosicion1.x,enemigoPosicion1.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion2.x,enemigoPosicion2.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion3.x,enemigoPosicion3.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion4.x,enemigoPosicion4.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion5.x,enemigoPosicion5.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion6.x,enemigoPosicion6.y,WHITE);
                            }break;
                            case 2:{
                                DrawTexture(EnemigoTexture,enemigoPosicion1.x,enemigoPosicion1.y,WHITE);
                                DrawTexture(EnemigoTexture3,enemigoPosicion2.x,enemigoPosicion2.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion3.x,enemigoPosicion3.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion4.x,enemigoPosicion4.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion5.x,enemigoPosicion5.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion6.x,enemigoPosicion6.y,WHITE);
                            }break;
                            case 3:{
                                DrawTexture(EnemigoTexture,enemigoPosicion1.x,enemigoPosicion1.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion2.x,enemigoPosicion2.y,WHITE);
                                DrawTexture(EnemigoTexture3,enemigoPosicion3.x,enemigoPosicion3.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion4.x,enemigoPosicion4.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion5.x,enemigoPosicion5.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion6.x,enemigoPosicion6.y,WHITE);
                            }break;
                            case 4:{
                                DrawTexture(EnemigoTexture,enemigoPosicion1.x,enemigoPosicion1.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion2.x,enemigoPosicion2.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion3.x,enemigoPosicion3.y,WHITE);
                                DrawTexture(EnemigoTexture3,enemigoPosicion4.x,enemigoPosicion4.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion5.x,enemigoPosicion5.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion6.x,enemigoPosicion6.y,WHITE);
                            }break;
                            case 5:{
                                DrawTexture(EnemigoTexture,enemigoPosicion1.x,enemigoPosicion1.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion2.x,enemigoPosicion2.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion3.x,enemigoPosicion3.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion4.x,enemigoPosicion4.y,WHITE);
                                DrawTexture(EnemigoTexture3,enemigoPosicion5.x,enemigoPosicion5.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion6.x,enemigoPosicion6.y,WHITE);
                            }break;
                            case 6:{
                                DrawTexture(EnemigoTexture,enemigoPosicion1.x,enemigoPosicion1.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion2.x,enemigoPosicion2.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion3.x,enemigoPosicion3.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion4.x,enemigoPosicion4.y,WHITE);
                                DrawTexture(EnemigoTexture,enemigoPosicion5.x,enemigoPosicion5.y,WHITE);
                                DrawTexture(EnemigoTexture3,enemigoPosicion6.x,enemigoPosicion6.y,WHITE);
                            }break;
                        }
                        if(buttonIzq_over) DrawTexture(button_Retry,buttonLeft.x,buttonLeft.y,RED);
                        else DrawTexture(button_Retry,buttonLeft.x,buttonLeft.y,WHITE);
                        if(buttonDer_over) DrawTexture(button_Exit,buttonRight.x,buttonRight.y,RED);
                        else DrawTexture(button_Exit,buttonRight.x,buttonRight.y,WHITE);
                        
                        DrawText(FormatText("NIVEL: %03i",nivel),screenWidth/2 - (MeasureText("NIVEL: 000",30))/2,screenHeight*0.1,30,BLUE);
                        DrawText(FormatText("SCORE TOTAL: %03i",totalScore),screenWidth/2 - (MeasureText("SCORE TOTAL: 000",30))/2,screenHeight*0.2,30,BLUE);
                break;
            default:
                break;
        }

        if(framesCounter==60*time){
            time++;
        }
        EndDrawing();
    }

    UnloadTexture(background_Logo);
    UnloadTexture(background_Title);
    UnloadTexture(background_Title2);
    UnloadTexture(background_Gaming);
    UnloadTexture(EnemigoTexture);
    UnloadTexture(EnemigoTexture2);
    UnloadTexture(EnemigoTexture3);
    UnloadTexture(PlayerTexture);
    UnloadTexture(button_Play);
    UnloadTexture(button_Exit);
    UnloadTexture(button_Retry);
    UnloadTexture(mora);
    UnloadTexture(roca);
    UnloadMusicStream(music);
    CloseAudioDevice(); 
    CloseWindow();
}