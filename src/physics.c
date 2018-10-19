//
// Created by Thomas Lienbacher on 18.10.2018.
//

#include <stdio.h>
#include <utils.h>
#include "physics.h"
#include "defs.h"
#include "player.h"
#include "world.h"

physicsengine_t g_physicsengine;

void physics_init() {
    g_physicsengine.bodys = vector_new(16);
    g_physicsengine.steps = 3;
}

void physics_add_body(physicsbody_t *physicsbody) {
    vector_push(g_physicsengine.bodys, physicsbody);
}

char physics_colliding(physicsbody_t *a, physicsbody_t *b) {
    //top down radius check
    vec2 tmp;
    vec2 bpos2d = {b->pos[0], b->pos[2]};
    vec2 ppos2d = {a->pos[0], a->pos[2]};
    vec2_sub(tmp, ppos2d, bpos2d);

    if (vec2_len(tmp) < a->radius + b->radius) {

        //side y axis check
        if (a->pos[1] < b->pos[1] + b->height &&
            a->pos[1] + a->height > b->pos[1]) {

            //colliding with body
            return 1;
        } else return 0;
    } else return 0;
}

void physics_update() {
    for (int j = 0; j < g_physicsengine.steps; ++j) {
        float delta = g_control.delta / (float) g_physicsengine.steps;

        vector_t *colliders = vector_new(4);
        char colliding = 0;

        //bodys
        for (int i = 0; i < g_physicsengine.bodys->size; i++) {
            physicsbody_t *b = (physicsbody_t *) vector_get(g_physicsengine.bodys, i);
            if (!b) continue;

            if (physics_colliding(g_physicsengine.player, b)) {
                vector_push(colliders, b);
                colliding = 1;
            }
        }

        //response
        if (colliding) {
            for (int i = 0; i < colliders->size; ++i) {
                physicsbody_t *b = (physicsbody_t *) vector_get(colliders, i);
                if (!b) continue;

                vec2 tmp;
                vec2 bpos2d = {b->pos[0], b->pos[2]};
                vec2 ppos2d ={g_physicsengine.player->pos[0], g_physicsengine.player->pos[2]};
                vec2_sub(tmp, ppos2d, bpos2d);

                //ontop
                float dist = vec2_len(tmp);
                if (dist < b->radius) {

                    if(g_physicsengine.player->pos[1] > b->pos[1]){
                        g_physicsengine.player->pos[1] = b->pos[1] + b->height + SPACING;
                        g_player.inair = 0;
                    }
                    else {
                        g_physicsengine.player->pos[1] = b->pos[1] - g_physicsengine.player->height - SPACING;
                        g_player.inair = 1;
                    }

                    g_physicsengine.player->vel[1] = 0;

                } else { //side
                    vec3 away;
                    vec3_sub(away, g_physicsengine.player->pos, b->pos);
                    away[1] = 0;
                    vec3_norm(away, away);
                    vec3_scale(away, away, (b->radius + g_physicsengine.player->radius) - dist + SPACING);
                    vec3_add(g_physicsengine.player->pos, g_physicsengine.player->pos, away);
                    g_physicsengine.player->vel[0] = g_physicsengine.player->vel[2] = 0;
                }
            }
        } else {
            float grav = GRAVITY * delta * (g_physicsengine.player->vel[1] < 0 ? 1.4f : 1.0f);
            vec3_add(g_physicsengine.player->vel, g_physicsengine.player->vel, (vec3) {0, grav, 0});
            vec3 move;
            vec3_scale(move, g_physicsengine.player->vel, delta);
            vec3_add(g_physicsengine.player->pos, g_physicsengine.player->pos, move);
        }

        g_player.body.pos[0] = clampf(g_player.body.pos[0], -WORLD_SIZE + PLAYER_RADIUS, WORLD_SIZE - PLAYER_RADIUS);
        g_player.body.pos[2] = clampf(g_player.body.pos[2], -WORLD_SIZE + PLAYER_RADIUS, WORLD_SIZE - PLAYER_RADIUS);

        vector_free(colliders);
    }
}

void physics_quit() {
    vector_free(g_physicsengine.bodys);
}
