/*Programa: Dinamica de The 9th Life
el objetivo de este programa es lograr que el usuario mueva un circulo por la pantalla usando las flechas del teclado
se compila con "gcc move.cpp -o move.exe -lallegro -lallegro_font -lallegro_primitives"*/
#include <allegro5\allegro5.h>
#include <allegro5\allegro_primitives.h>
#include <stdio.h>


#define largo 1200
#define ancho 700
#define radius 30


void jump(ALLEGRO_COLOR fondo, int xx, int yy, int r)
{
    al_clear_to_color(fondo);//vuelve a dibujar el fondo


    al_draw_filled_circle(xx,yy,30,al_map_rgb(51,255,134));
    al_draw_circle(xx,yy,r,al_map_rgb(255,255,255),2);
    al_flip_display();
    return;
}
void dibujaCirculo(ALLEGRO_COLOR fondo, int xx, int yy, int r)
{
    al_clear_to_color(fondo);//vuelve a dibujar el fondo
    //dibuja mapa
    al_draw_filled_rectangle(largo/2-radius,ancho/2+radius,900,510,al_map_rgb(255,255,255));
    //circulo
   
       
    al_draw_filled_circle(xx,yy,30,al_map_rgb(51,255,134));//color del circulo
    al_draw_circle(xx,yy,r,al_map_rgb(255,255,255),2);//color del borde del circulo, grosor de 2
    al_flip_display();
   
    return;
}


int main(void)
{
    ALLEGRO_DISPLAY *disp; //display
    ALLEGRO_COLOR colorFondo;
    ALLEGRO_EVENT_QUEUE *eventos;
    ALLEGRO_EVENT evento;


    int fin=0;
    int x=largo/2, y=ancho/2, radio=30; //variables para mover a la figura por el plano
   
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
        disp=al_create_display (largo, ancho);
        al_set_window_title (disp, "Move");
        colorFondo=al_map_rgb(0,0,0);
        al_clear_to_color(colorFondo);
        eventos=al_create_event_queue();
        al_register_event_source(eventos, al_get_display_event_source(disp));
        //icono=al_load_bitmap("C:\\Users\\52554\\programas\\The9thLife\\logo1.png");
        //al_set_display_icon(disp, icono);
        al_register_event_source(eventos, al_get_keyboard_event_source());


        while(fin==0)
        {
            //Dibujar
            dibujaCirculo(colorFondo,x,y,radio);


            al_wait_for_event(eventos,&evento);
            switch(evento.type)
            {
                //evento de la ventana
                case ALLEGRO_EVENT_DISPLAY_CLOSE:
                    printf("Cerrado :(");
                    fin=1;
                    break;
                case ALLEGRO_EVENT_KEY_CHAR:
                if (x<largo && x>0)
                {
                    if (y<=ancho && y>0)
                    {
                        if(evento.keyboard.keycode==82) //flecha izquierda
                        x-=10;
                        if(evento.keyboard.keycode==83)//flecha derecha
                            x+=10;
                        if(evento.keyboard.keycode==84)//flecha arriba
                            for(int i=0; i<5; i++)
                                y--;
                            for(int i=0; i<5; i++)
                                y++;
                    }
                    /*else
                    {
                        x=largo/2;
                        y=ancho/2;
                    }*/
                }
                /*else
                {
                    x=largo/2;
                    y=ancho/2;
                } */
                    break;
            }
        }
    }
    al_destroy_event_queue(eventos);//destruye apuntador
    al_flip_display();
    return 0;
}
