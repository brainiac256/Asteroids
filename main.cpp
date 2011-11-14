#define NDEBUG
#include <iostream>
#include <allegro5/allegro5.h>
#include "GameEngine.h"
#include "Player.h"
#include "Asteroid.h"

const float FPS = 60;
const int SCREEN_W = 640;
const int SCREEN_H = 480;

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;
   ALLEGRO_TIMER *timer = NULL;
   bool redraw = true;
   bool doexit = false;

   if(!al_init()) {
      std::cout << "failed to initialize allegro!" << std::endl;
      return -1;
   }
 
   if(!al_install_keyboard()) {
      std::cout << "failed to initialize the keyboard!" << std::endl;
      return -1;
   }
 
   timer = al_create_timer(1.0 / FPS);
   if(!timer) {
      std::cout << "failed to create timer!" << std::endl;
      return -1;
   }

   //al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
   //al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_REQUIRE);
   //al_set_new_display_flags(al_get_new_display_flags() | ALLEGRO_FULLSCREEN);
   al_set_new_display_flags(al_get_new_display_flags() | ALLEGRO_NOFRAME);
   display = al_create_display(SCREEN_W, SCREEN_H);
   if(!display) {
      std::cout << "failed to create display!" << std::endl;
      al_destroy_timer(timer);
      return -1;
   }

   if(!al_init_primitives_addon()) {
	   std::cout << "failed to init primitives addon!" << std::endl;
	   al_destroy_timer(timer);
	   al_destroy_display(display);
	   return -1;
   }
 
   al_set_target_bitmap(al_get_backbuffer(display));
 
   event_queue = al_create_event_queue();
   if(!event_queue) {
      std::cout << "failed to create event_queue!" << std::endl;
      al_destroy_display(display);
      al_destroy_timer(timer);
      return -1;
   }
 
   al_register_event_source(event_queue, al_get_display_event_source(display));
   al_register_event_source(event_queue, al_get_timer_event_source(timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   al_clear_to_color(al_map_rgb(0,0,0));
   al_flip_display();
   
   add(new Player());
   for(int i=0; i<8; ++i)
	   add(new Asteroid());
   

   al_start_timer(timer);
   while(!doexit)
   {
      ALLEGRO_EVENT ev;
      al_wait_for_event(event_queue, &ev);
 
      if(ev.type == ALLEGRO_EVENT_TIMER) {
          redraw = true; // next frame triggered
      }
      else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		  doexit = true; //received a close window event
      }
      else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
		  //process keys
		  switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               setKey(KEY_UP);
               break;
 
            case ALLEGRO_KEY_DOWN:
               setKey(KEY_DOWN);
               break;
 
            case ALLEGRO_KEY_LEFT: 
               setKey(KEY_LEFT);
               break;
 
            case ALLEGRO_KEY_RIGHT:
               setKey(KEY_RIGHT);
               break;

			case ALLEGRO_KEY_SPACE:
				setKey(KEY_SPACE);
				break;
         }
      } else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
         switch(ev.keyboard.keycode) {
            case ALLEGRO_KEY_UP:
               releaseKey(KEY_UP);
               break;
 
            case ALLEGRO_KEY_DOWN:
               releaseKey(KEY_DOWN);
               break;
 
            case ALLEGRO_KEY_LEFT: 
               releaseKey(KEY_LEFT);
               break;
 
            case ALLEGRO_KEY_RIGHT:
               releaseKey(KEY_RIGHT);
               break;
 
            case ALLEGRO_KEY_ESCAPE:
               doexit = true;
               break;

			case ALLEGRO_KEY_SPACE:
				releaseKey(KEY_SPACE);
				break;
         }
      }
 
      if(redraw && al_is_event_queue_empty(event_queue)) {
         redraw = false;
         al_clear_to_color(al_map_rgb_f(0,0,0)); //clear to black
		 drawObjects();
         al_flip_display();
		 updateEngine();
	  }
	  
   }
 
   al_destroy_timer(timer);
   al_destroy_display(display);
   al_destroy_event_queue(event_queue);
 
   return 0;
}
