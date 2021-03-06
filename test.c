#include <allegro.h>

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200
#define INTR_SPEED 60

int main(int argc, char *argv[])
{
    typedef struct
    {
        int x;
        int y;
        int speed_x;
        int speed_y;
        BITMAP *bmp;
    } SPRITE;

    SPRITE sprite;
    PALETTE palette;
    BITMAP *buffer;
    int page = 0;

    sprite.x = 0;
    sprite.y = 0;
    sprite.speed_x = 2;
    sprite.speed_y = 2;

    /* Initializing everything */
    if (allegro_init() != 0)
    {
        allegro_message("Error on initializing Allegro");
        return 1;
    }
    install_keyboard();
    set_color_depth(8);
    if (set_gfx_mode(GFX_SAFE, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0) != 0)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error on setting the VGA mode:\n%s\n",
                        allegro_error);
        return 1;
    }

    /* Load bitmap, set palette and prepare the buffer */
    sprite.bmp = load_bitmap("logok.pcx", palette);
    if (!sprite.bmp)
    {
        allegro_message("Error on loading sprite file");
        return 1;
    }
    set_palette(palette);
    buffer = create_bitmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    rectfill(buffer, 0, 0, SCREEN_W, SCREEN_H, 0);
 
    /* The action happens in this loop */
    while (!key[KEY_ESC])
    {   
        rectfill(buffer, sprite.x, sprite.y, sprite.x + sprite.bmp->w, sprite.y + sprite.bmp->h, 0); /* Clean-up the area with sprite dimensions */
        if (key[KEY_RIGHT] && sprite.x + sprite.bmp->w < SCREEN_W)
            sprite.x += sprite.speed_x;
        if (key[KEY_DOWN] && sprite.y + sprite.bmp->h < SCREEN_H)
            sprite.y += sprite.speed_y;
        if (key[KEY_LEFT] && sprite.x >= 0)
            sprite.x -= sprite.speed_x;
        if (key[KEY_UP] && sprite.y >= 0)
            sprite.y -= sprite.speed_y;
        draw_sprite(buffer, sprite.bmp, sprite.x, sprite.y);
        vsync(); /* Wait for VSync and then blit buffer to the screen */
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W - 1, SCREEN_H - 1);
    }

    /* Clean-up and exit */
    destroy_bitmap(sprite.bmp);
    destroy_bitmap(buffer);
    remove_timer();
    allegro_exit();
    return 0;
}

END_OF_MAIN()
