/*Programa: move.
el objetivo de este programa es lograr que el usuario mueva un circulo por la pantalla usando las flechas del teclado
se compila con "gcc move.cpp -o move.exe -lallegro -lallegro_font -lallegro_primitives"*/
#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <stdio.h>
#define XMAXPANT 1200
#define YMAXPANT 700
#define radio 40
int matriz[8][8];
int r,c;
ALLEGRO_COLOR contorno=al_map_rgb(114,47,126);
void cuadricula()
{   
    //Cuadricula dibujada mediante figuras primitivas
    al_draw_line(200,0,200,140,contorno,3); //linea1
    al_draw_line(0,280,400,280,contorno,3); //linea2
    al_draw_line(400,140,400,420,contorno,3); //linea3
    al_draw_line(400,140,600,140,contorno,3); //linea4
    al_draw_line(400,420,600,420,contorno,3); //linea5
    al_draw_line(600,280,600,540,contorno,3); //linea6
    al_draw_line(600,540,800,540,contorno,3); //linea7
    al_draw_line(800,140,800,420,contorno,3); //linea8
    al_draw_line(800,280,1200,280,contorno,3); //linea9
    al_draw_line(800,420,1000,420,contorno,3); //linea10
    al_draw_line(1000,420,1000,560,contorno,3); //linea11
    al_draw_line(200,560,400,560,contorno,3); //linea12
    al_draw_line(400,560,400,700,contorno,3); //linea13
    al_draw_line(0,280,0,560,contorno,3); //linea14
    al_flip_display;
}
void camColor(int x, int y)
{
    al_draw_filled_circle(x,y,radio,al_map_rgb(175,99,61));
}
int main(void)
{
    ALLEGRO_DISPLAY *disp; //display
    ALLEGRO_COLOR colorFondo;
    ALLEGRO_EVENT_QUEUE *eventos;
    ALLEGRO_EVENT evento;


    int fin=0;
    int x=100, y=70; //variables para mover a la figura por el plano y matriz
    char redibujar=1;
    if(!al_init())
    {
        printf("No se pudo iniciar allegro");
        fin=1;
    }
    if(!al_init_primitives_addon())
    {
        printf("No se pudo iniciar la biblioteca primitives");
        fin=1;
    }
    if(!al_install_keyboard())
    {
        printf("No se instal%c teclado", 162);
        fin=1;
    }
    if(fin==0)
    {
        disp=al_create_display (XMAXPANT,YMAXPANT);
        al_set_window_title (disp, "9thLife");
        colorFondo=al_map_rgb(235,155,199);
        al_clear_to_color(colorFondo);
        al_flip_display();
        eventos=al_create_event_queue();
        al_register_event_source(eventos, al_get_display_event_source(disp));
        al_register_event_source(eventos, al_get_keyboard_event_source());

        while(fin==0)
        {
            //Dibujar
            al_clear_to_color(colorFondo);//vuelve a dibujar el fondo
            //Circulo cambia de color y se baja una vida
            al_draw_filled_circle(x,y,radio,al_map_rgb(221,160,129));
            al_draw_circle(x,y,radio,al_map_rgb(175,99,61),4);
            al_flip_display();                                   

            cuadricula();
            al_flip_display();

            al_wait_for_event(eventos,&evento);
            switch(evento.type)
            {
                //evento de la ventana
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    printf("Cerrado :(");
                    fin=1;
                    break;
                case ALLEGRO_EVENT_KEY_CHAR:
                        if (x+radio<XMAXPANT && x-radio>0)
                        {
                            if (y+radio<YMAXPANT && y-radio>0)
                            {
                                if(evento.keyboard.keycode==82 || evento.keyboard.keycode==1)//flecha izquierda
                                x-=10;
                                if(evento.keyboard.keycode==83 || evento.keyboard.keycode==4)//flecha derecha
                                    x+=10;
                                if(evento.keyboard.keycode==84 || evento.keyboard.keycode==23)//flecha arriba
                                    y-=10;
                                if(evento.keyboard.keycode==85 || evento.keyboard.keycode==19)//flecha abajo
                                    y+=10;

                                if (x+radio==200 && y<=140)
                                {
                                    al_clear_to_color(colorFondo);
                                    al_draw_filled_circle(x,y,radio,al_map_rgb(252,242,222));//color del circulo
                                    al_draw_circle(x,y,radio,al_map_rgb(199,167,121),4);//color del borde del circulo, grosor de 2
                                    x-=10;
                                    
                                }
                            }
                            else
                            {
                                y+=y;
                            }
                        }
                        else
                        {
                            x+=x;
                        }
                    break;
            }
        }
    }
    al_destroy_event_queue(eventos);//destruye apuntador
    al_flip_display();
    return 0;
}
