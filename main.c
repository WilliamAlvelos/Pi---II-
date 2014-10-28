#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "compilador_PD.h"
#define TAMANHO 200

const int LARGURA_TELA = 1704;
const int ALTURA_TELA = 700;

ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_BITMAP *w[2];
ALLEGRO_BITMAP *fundo = NULL;
ALLEGRO_BITMAP *fundo2 = NULL;
ALLEGRO_FONT *fonte = NULL;
ALLEGRO_BITMAP *erro1 = NULL;
ALLEGRO_BITMAP *carro = NULL;
ALLEGRO_BITMAP *carro_dir = NULL;
ALLEGRO_BITMAP *carro_esq = NULL;
ALLEGRO_BITMAP *carro_down = NULL;
ALLEGRO_BITMAP *carro_batida = NULL;
ALLEGRO_BITMAP *batida_esq = NULL;
ALLEGRO_BITMAP *batida_dir = NULL;
ALLEGRO_BITMAP *batida_down = NULL;



char str[TAMANHO][TAMANHO];

    int manipular_entrada(ALLEGRO_EVENT evento, int linha);
    void exibir_texto_centralizado();
    void tela2 (int x, int y, int estado_carro, bool sair);
    void tela1 (int x, int y, int estado_carro, bool sair);
    bool inicializar();
    int esta_vazia(char (*matriz)[TAMANHO]);
    int ultima_linha(char (*matriz)[TAMANHO]);
    void finalizar();
    void error_tela1(int x, int y, int estado_carro);
    void comando_teclado(int x, int y, int estado_carro, bool sair);
    void troca_tela(int x , int y, int estado_carro, bool sair);



    int avanca(int quantidade, int x, int y, int estado_carro){
        int cima;
            
        if(estado_carro == 1){

            cima = x;
                 while(x>=cima-(100*quantidade)){
                    al_draw_bitmap(fundo, 0, 0, 0);
                    al_draw_bitmap(carro, y, x, 0);
                    error_tela1(x, y, estado_carro);
                    troca_tela(x , y, estado_carro, false);
                    x--;
                    al_flip_display();
                    al_rest(0.01);
                    estado_carro=1;
                     }
            return x;

        }

        if(estado_carro == 2){

            cima = x;
                 while(x>=cima-(100*quantidade)){
                    al_draw_bitmap(fundo, 0, 0, 0);
                    al_draw_bitmap(carro_down, y, x, 0);
                    error_tela1(x, y, estado_carro);
                    troca_tela(x , y, estado_carro, false);
                    x++;
                    al_flip_display();
                    al_rest(0.01);
                    estado_carro=2;
                     }
            return x;

        }


                    if(estado_carro == 4){

                        cima = y;        
                        while(y>=cima-(100*quantidade)){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro_esq, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            y--;
                            al_flip_display();
                            al_rest(0.01);
                            estado_carro = 3;
                        }
                return y;
            }

                     if(estado_carro == 3){

                        cima = y;        
                        while(y<=cima+(100*quantidade)){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro_dir, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            y++;
                            al_flip_display();
                            al_rest(0.01);
                            estado_carro = 3;
                        }
                    return y;
            }
            return x;

     }
    

    int vira(int lado, int x, int y, int estado_carro){
        //mesma coisa ele so faz a curva conforme o lado que foi solicitado
        //queria criar um struct paara armazenar melhores os valores de x e y mais assim da para fazer tmb
            if (lado == 1){
                //int esq;
                //esq = y;

                //estado_carro = 1 cima // =2 baixo // =3 direita // =4 esqeurda
            if(estado_carro == 1){
                //while(y>=esq-100){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro_dir, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            //y--;
                            al_flip_display();
                            al_rest(0.01);
                            estado_carro = 3;
                  //}
                return estado_carro;
            }
            if(estado_carro ==2){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro_esq, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            al_flip_display();
                            estado_carro = 4;
                            return estado_carro;
            }

            if(estado_carro == 3){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro_down, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            al_flip_display();
                            estado_carro = 2;
                            return estado_carro;
            }
            if(estado_carro == 4){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            al_flip_display();
                            estado_carro = 1;
                            return estado_carro;
            }
            }
            else if(lado == 2){
                //int dir;
                 //dir = y;
                  if(estado_carro == 1){
                     //   while(y<=dir+100){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro_esq, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                       //     y++;
                            al_flip_display();
                         //   al_rest(0.01);
                            estado_carro = 4;
                        return estado_carro;
                        } 
                //return y;  
                    if(estado_carro ==2){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro_dir, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            al_flip_display();
                            estado_carro = 3;
                            return estado_carro;
                         }

                    if(estado_carro == 3){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            al_flip_display();
                            estado_carro = 1;
                            return estado_carro;
                         }
                     if(estado_carro == 4){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro_down, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            al_flip_display();
                            estado_carro = 2;
                            return estado_carro;
                         }
            }


            return y;
    }



    int retorna(int quantidade, int x, int y, int estado_carro){
        //cara aqui eu nao sei oq comentar ahaha so mandei chamar aqui quando no seu compilador ele retorna aqui to vendo formas de melhorar ainda 
        int baixo;
            baixo = x;
                    if(estado_carro == 1){
                        while(x<=baixo+(100*quantidade)){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro_down, y, x, 0);
                            estado_carro=2;
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            x++;
                            al_flip_display();
                            al_rest(0.01);
                        }

            return x;

    }

    if(estado_carro == 2){
                        while(x>=baixo-(100*quantidade)){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro, y, x, 0);
                            estado_carro=1;
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            x--;
                            al_flip_display();
                            al_rest(0.01);
                        }

            return x;

    }


     if(estado_carro == 3){

                        baixo = y;        
                        while(y>=baixo-(100*quantidade)){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro_dir, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            y--;
                            al_flip_display();
                            al_rest(0.01);
                            estado_carro = 3;
                        }
                    return y;
            }


            if(estado_carro == 4){

                        baixo = y;        
                        while(y<=baixo+(100*quantidade)){
                            al_draw_bitmap(fundo, 0, 0, 0);
                            al_draw_bitmap(carro_dir, y, x, 0);
                            error_tela1(x, y, estado_carro);
                            troca_tela(x , y, estado_carro, false);
                            y++;
                            al_flip_display();
                            al_rest(0.01);
                            estado_carro = 4;
                        }
                    return y;
            }

    return x;
}

    void error_tela1(int x, int y, int estado_carro){
        //detecçao de colisao melhorar futuramente
         if((y <= 250) ||  (y >= 350 && y <= 850 && x >= 480) || (y >= 950 && x >= 380) || (x <= 180 && y >= 750) || (y <= 650 && x <= 180 && y >= 350) || (y>=350 && y<=850 && x >=280 && x <= 380)){

                                if(estado_carro == 1){
                                    al_draw_bitmap(fundo, 0, 0, 0);
                                    al_draw_bitmap(carro_batida, y, x, 0);
                                    al_flip_display();
                                         if (al_show_native_message_box(janela, "Voce Bateu o carro! ","Pergunta:", "O jogo ira ser reniciado",NULL, ALLEGRO_MESSAGEBOX_WARN)){
                                            //tela1(630, 300, estado_carro, false);
                                            //al_destroy_display(janela);
                                            comando_teclado(x, y, 1, false);
                                            }
                                }
                                if(estado_carro == 2){
                                    al_draw_bitmap(fundo, 0, 0, 0);
                                    al_draw_bitmap(batida_down, y, x, 0);
                                    al_flip_display();
                                         if (al_show_native_message_box(janela, "Voce Bateu o carro! ","Pergunta:", "O jogo ira ser reniciado",NULL, ALLEGRO_MESSAGEBOX_WARN)){
                                            //tela1(630, 300, estado_carro, false);
                                            comando_teclado(x, y, 1, false);
                                            }
                                }

                                if(estado_carro == 3){
                                    al_draw_bitmap(fundo, 0, 0, 0);
                                    al_draw_bitmap(batida_dir, y, x, 0);
                                    al_flip_display();
                                        if (al_show_native_message_box(janela, "Voce Bateu o carro! ","Pergunta:", "O jogo ira ser reniciado",NULL, ALLEGRO_MESSAGEBOX_WARN)){
                                            //tela1(630, 300, estado_carro, false);
                                            //al_destroy_display(janela);
                                            comando_teclado(x, y, 1, false);
                                            }
                                }
                                else{
                                    al_draw_bitmap(fundo, 0, 0, 0);
                                    al_draw_bitmap(batida_esq, y, x, 0);
                                    al_flip_display();
                                        if (al_show_native_message_box(janela, "Voce Bateu o carro! ","Pergunta:", "O jogo ira ser reniciado",NULL, ALLEGRO_MESSAGEBOX_WARN)){
                                            //tela1(630, 300, estado_carro, false);
                                            //al_destroy_display(janela);
                                            comando_teclado(x, y, 1, false);
                                            }

                                }
                        }

    }



    void error_tela2(int x, int y, int estado_carro){
        // se o valor de x e y na tela 2 forem esse detecta colisao, podemos aprimorar futuramente mais o objetivo agora nao é esse
        //nessa semana nao pelo menos
         if((y<259) || (x< 250 && y > 350 && y < 550) || (x < 250 && y > 650)){

                                if(estado_carro == 1){
                                    al_draw_bitmap(fundo2, 0, 0, 0);
                                    al_draw_bitmap(carro_batida, y, x, 0);
                                    al_flip_display();
                                         if (al_show_native_message_box(janela, "Voce Bateu o carro! ","Pergunta:", "O jogo ira ser reniciado",NULL, ALLEGRO_MESSAGEBOX_WARN)){
                                            tela2(630, 300, estado_carro, false);
                                            al_destroy_display(janela);
                                            
                                            }
                                }
                                if(estado_carro == 2){
                                    al_draw_bitmap(fundo2, 0, 0, 0);
                                    al_draw_bitmap(batida_down, y, x, 0);
                                    al_flip_display();
                                         if (al_show_native_message_box(janela, "Voce Bateu o carro! ","Pergunta:", "O jogo ira ser reniciado",NULL, ALLEGRO_MESSAGEBOX_WARN)){
                                            tela2(630, 300, estado_carro, false);
                                            al_destroy_display(janela);
                                            }
                                }

                                if(estado_carro == 3){
                                    al_draw_bitmap(fundo2, 0, 0, 0);
                                    al_draw_bitmap(batida_dir, y, x, 0);
                                    al_flip_display();
                                        if (al_show_native_message_box(janela, "Voce Bateu o carro! ","Pergunta:", "O jogo ira ser reniciado",NULL, ALLEGRO_MESSAGEBOX_WARN)){
                                            tela2(630, 300, estado_carro, false);
                                            al_destroy_display(janela);
                                            }
                                }
                                else{
                                    al_draw_bitmap(fundo2, 0, 0, 0);
                                    al_draw_bitmap(batida_esq, y, x, 0);
                                    al_flip_display();
                                        if (al_show_native_message_box(janela, "Voce Bateu o carro! ","Pergunta:", "O jogo ira ser reniciado",NULL, ALLEGRO_MESSAGEBOX_WARN)){
                                            tela2(630, 300, estado_carro, false);
                                            al_destroy_display(janela);
                                            }

                                }
                        }

    }


    
void comando_teclado (int x, int y, int estado_carro, bool sair){
    int linha = 0;
    int tela = 2;//constante para saber em qual tela ele esta
    //carrega o fundo
    al_draw_bitmap(fundo, 0, 0, 0);
    al_draw_bitmap(carro, y, x, 0);
    al_flip_display();

    while (!sair)
    {
        // mesmo codigo de evento de sempre ...
        while(!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            //espera acontecer algum evento
             linha = manipular_entrada(evento, linha);
             exibir_texto_centralizado();
             al_flip_display();

                if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ENTER)
                {
                    linha++;
                }
                if (evento.type == ALLEGRO_EVENT_KEY_DOWN && evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                {
                    //voce fez essa parte hahsahshash nem preciso comenta ne.. cometarios do nelson a baixo
                    char conjunto_string[] = "";
                    concatena_strings(str, conjunto_string, linha+1);
                    //imprime_string(conjunto_string);
                    
                    //Caso o usuário digite ESC, eh chamada a função do compilador passando APENAS a primeira linha da matriz
                    EXECUTA_COMPILADOR(conjunto_string);
                }
                //se o evento for sair
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
                  if (al_show_native_message_box(janela, "Nelson Compilador","Pergunta:", "Deseja sair do jogo?",NULL, ALLEGRO_MESSAGEBOX_YES_NO)){
                     //da a mensagem de erro se ele criar sim fecha
                     sair = true;
                     }
                    else
                    {
                            //else continua entao nao precisa fazer nada
                    }
                 }
            switch(tela){    
            case 1:
                    // caso tela 1 nao faz nada pq ela ainda nao existe seria a tela em cima da incial
            break;

            case 2:      
            if (evento.type == ALLEGRO_EVENT_KEY_UP){
                if(evento.keyboard.keycode == ALLEGRO_KEY_DOWN)
                {
                                    // caso ele esteja na tela 2 e clica para baixo ai coloca a constante de tela = 3 e imprime o fundo2
                                    al_draw_bitmap(fundo2, 0, 0, 0);
                                    al_flip_display();
                                    tela=3;
                }
                else if((evento.keyboard.keycode == ALLEGRO_KEY_UP || (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT || (evento.keyboard.keycode == ALLEGRO_KEY_LEFT)))){
                        al_show_native_message_box(janela, "ERROR 404","Pergunta:", "MAPA NAO DEFINIDO",NULL, ALLEGRO_MESSAGEBOX_WARN);

                        //se ele fazer outro comando para ainda nao definido
                }

                    break;

            case 3:
            //caso tela==3
            if (evento.type == ALLEGRO_EVENT_KEY_UP){
                    // quando a tecla for precionada e desprecionada voce entedeu ne ahhahaha
                if(evento.keyboard.keycode == ALLEGRO_KEY_UP)
                {
                                    //caso tela == 3 imprime o fundo coloca a constante igual a 2
                                    al_draw_bitmap(fundo, 0, 0, 0);
                                    al_flip_display();
                                    tela=2;
                }
                else if((evento.keyboard.keycode == ALLEGRO_KEY_DOWN || (evento.keyboard.keycode == ALLEGRO_KEY_RIGHT || (evento.keyboard.keycode == ALLEGRO_KEY_LEFT)))){
                        al_show_native_message_box(janela, "ERROR 404","Pergunta:", "MAPA NAO DEFINIDO",NULL, ALLEGRO_MESSAGEBOX_WARN);
                        //caso ele esteja na tecla 2 e de um evento que nao seja para cima imprime a native do para nao definido
                }
                    break;
                }
            }

            }
                       

        
            //joga para a funçao da tela 2 caso esteja la, ou seja o carro saia da tela sentido para baixo
            //entao eu reconheço qual rua eu estou pois duas ruas vao para a tela 2
                  
                    }
                    al_flip_display();

                }
            }

    void troca_tela (int x, int y, int estado_carro, bool sair){

                    if(x>ALTURA_TELA && y == 300){
                            x = 50;
                            y = 300;
                            al_draw_bitmap(fundo2, 0, 0, 0);
                    }
                    else if(x>ALTURA_TELA){
                            x = 50;
                            y = 710;
                            al_draw_bitmap(fundo2, 0, 0, 0);
                            tela2(x, y, estado_carro, sair);
                    }



    }



//nao de muito valor a ler a funacao tela 2 pois eu nao estou chamando ela no codigo so o caso do carro trocar de tela ela esta ai para aprefeicoar futuramente    
void tela2 (int x, int y, int estado_carro, bool sair){


    al_draw_bitmap(fundo2, 0, 0, 0);
    al_draw_bitmap(carro_down, y, x, 0);
    al_flip_display();
    //roda ate o sair ser true
    while (!sair)
    {   
        while(!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            //espera acontecer algum evento
            //se for evento de ALLEGRO_EVENT_KEY_UP significa que o evento vai ser quando a tecla ser precionada e depois quando ela sair entende

            if (evento.type == ALLEGRO_EVENT_KEY_UP)
            {   
                //casos de troca evento
                switch(evento.keyboard.keycode)
                {
                case ALLEGRO_KEY_UP:
                    break;
                    // se a tecla for para cima ela é reconhecida como 1
                case ALLEGRO_KEY_DOWN:
                    al_show_native_message_box(janela, "ERROR 404","Pergunta:", "MAPA NAO DEFINIDO",NULL, ALLEGRO_MESSAGEBOX_WARN);
                    break;
                case ALLEGRO_KEY_LEFT:
                    al_show_native_message_box(janela, "ERROR 404","Pergunta:", "MAPA NAO DEFINIDO",NULL, ALLEGRO_MESSAGEBOX_WARN);
                    break;
                case ALLEGRO_KEY_RIGHT:
                    al_show_native_message_box(janela, "ERROR 404","Pergunta:", "MAPA NAO DEFINIDO",NULL, ALLEGRO_MESSAGEBOX_WARN);
                    break;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                sair = true;
            }
        }
        //nao de valor para os trechos de codigo comentados
        /*if (tecla)
        {
            al_draw_bitmap(fundo2, 0, 0, 0);

            switch (tecla)
            {
            case 1:
                    cima = x;

                        while(x>=cima-100){
                            al_draw_bitmap(fundo2, 0, 0, 0);
                            al_draw_bitmap(carro, y, x, 0);
                            x--;
                            al_flip_display();
                            al_rest(0.01);
                        }

                        estado_carro=1;
                break;
            case 2:
                baixo = x;
                        // se o estado do carro for para a direita este if faz ele uma animaçao para ele ficar para baixo
                while(x<=baixo+100){
                            al_draw_bitmap(fundo2, 0, 0, 0);
                            al_draw_bitmap(carro_down, y, x, 0);
                            x++;
                            al_flip_display();
                            al_rest(0.01);
                        }

                        estado_carro = 2;

                break;
            case 3:
                esq = y;

                while(y>=esq-100){
                            al_draw_bitmap(fundo2, 0, 0, 0);
                            al_draw_bitmap(carro_esq, y, x, 0);
                            y--;
                            al_flip_display();
                            al_rest(0.01);
                        }

                         estado_carro = 3;
                break;
            case 4:

                
                        dir = y;
                        while(y<=dir+100){
                            al_draw_bitmap(fundo2, 0, 0, 0);
                            al_draw_bitmap(carro_dir, y, x, 0);
                            y++;
                            al_flip_display();
                            al_rest(0.01);
                        }
                         estado_carro = 4;

                break;
            }

            tecla = 0;*/

             if(x < 0 && y < 400){
                            x = 630;
                            y = 300;
                            //tela1(x, y, estado_carro, sair);
                    }
            else if(x < 0 && y > 400){
                            x = 630;
                            y = 910;
                            //tela1(x, y, estado_carro, sair);
                    }
        }


        al_flip_display();
    }




int main(void)
{
    bool sair = false;
    int x = 630;//vertical OU INICIAL DE 650
    int y = 300;//horisontal
    int linha = 0;
    strcpy(str[linha], "");
    int i = 0;

    al_draw_bitmap(w[1], 0 , 0 , 0);
    al_flip_display();
    al_rest(5.0);
    i++;
    al_flip_display();
    if (!inicializar())
    {
        return -1;
    }

        //chama a funcao comando tecla que serve para o usuario trocar as telas sem mecher o carro para ele visualizar melhor o cenario 
        comando_teclado(x, y, 1, sair);
    //destroi as janelas
    al_destroy_display(janela);
    al_destroy_event_queue(fila_eventos);

    return 0;
}

bool inicializar()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return false;
    }
    //inicia as fontes
    al_init_font_addon();
    al_init_ttf_addon();
    //carrega as fontes
    fonte = al_load_font("AGENCYR.TTF", 42, 0);

    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return false;
    }

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return false;
    }

    //cria a janela
    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return false;
    }
    //coloca o titulo da tela como nelson compilador obs belo nome 
    al_set_window_title(janela, "Nelson Compilador");

    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(janela);
        return false;
    }
    //carrega as imagens
    fundo2 = al_load_bitmap("fase2.png");
    fundo = al_load_bitmap("fase1.png");
    carro = al_load_bitmap("carro.png");
    carro_dir = al_load_bitmap("carro_dir.png");
    carro_esq = al_load_bitmap("carro_esq.png");
    carro_batida = al_load_bitmap("batida.png");
    batida_esq = al_load_bitmap("batida_esq.png");
    batida_dir = al_load_bitmap("batida_dir.png");
    batida_down = al_load_bitmap("batida_down.png");
    carro_down = al_load_bitmap("carro_dow.png");
    w[1] = al_load_bitmap("Cenario.png");

    if (!fundo)
    {   
        fprintf(stderr, "Falha ao carregar imagem de fundo.\n");
        al_destroy_display(janela);
        al_destroy_event_queue(fila_eventos);
        return false;
    }
    //registra os eventos
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));

    return true;
}

void finalizar()
{
    al_destroy_bitmap(fundo);
    al_destroy_font(fonte);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
}

int manipular_entrada(ALLEGRO_EVENT evento, int linha){
    if (evento.type == ALLEGRO_EVENT_KEY_CHAR)
    {
        if (evento.keyboard.keycode != ALLEGRO_KEY_BACKSPACE && evento.keyboard.keycode != ALLEGRO_KEY_ENTER && evento.keyboard.keycode != ALLEGRO_KEY_ESCAPE)
        {
            if(strlen(str[linha]) >= 18)
                linha++;

            char temp[] = {evento.keyboard.unichar, '\0'};
            strcat(str[linha], temp);
        }
 
        if (evento.keyboard.keycode == ALLEGRO_KEY_BACKSPACE)
        {
            if(strlen(str[linha]) != 0)
                str[linha][strlen(str[linha]) - 1] = '\0';
            else
                if(linha>0)
                    linha--;
        }
    }

    return linha;
}

void exibir_texto_centralizado()
{
    int i, y=10;

    if (!esta_vazia(str))
    {
        for(i=0; i<=(ultima_linha(str)); i++){
            al_draw_text(fonte, al_map_rgb(0,255,0), 1300 , y , 0, str[i]);
            y+=40;
            al_flip_display();
        }
    }

    /*if (strlen(str) > 25)
       {   
           al_draw_text(fonte, al_map_rgb(0,255,0), 10 , 50 , 0, str);
    }*/
}
