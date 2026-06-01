/*
 *     zero-over-zero ( 0/0 )
 *     incremental game using ECStaic DODgy writing.
 */

#pragma once
#include <raylib.h>
#include <stdint.h>

/**
 * ======================= GLOBALS AND TYPES
 */

#define MAX_ENTITIES 16384
#define MAX_SLABS 16
#define MAX_EVENTS 1024
#define CHUNK_WIDTH (1 << 10)
#define CHUNK_HEIGHT (1 << 10)
#define CHUNK_WIDTH_F 1024.0
#define CHUNK_HEIGHT_F 1024.0
#define MAP_HEIGHT (1 << 14)
#define MAP_WIDTH (1 << 14)
#define MAP_HEIGHT_F 16384.0
#define MAP_WIDTH_F 16384.0

typedef int16_t ZEntityId;
typedef int16_t ZEntityIdx;
typedef int16_t ZEntityMaxAmount;
// typedef int16_t ZChunkId;
typedef int16_t ZSlabId;

// Forward declaring the context struct so I can typedef the function pointer below.
typedef struct ZCore ZCore;
typedef struct ZWorldButtonSlab ZWorldButtonSlab;
typedef struct ZEvent ZEvent;

// This is a universal function pointer for behavior, so it can run via other code in the system
typedef void (*ZAction)(ZCore* core, ZEvent* event);

/*
 * ======================= MISCELLANOUS STRUCTS DEFINITIONS
 */

/* ========= ZChunk
 * The ZChunk is used inside a slab to subdivide the slab, making it rigid but fast for looping
 * A use is for viewport culling in my ZWorldButtonSlab. (not used atm)
 */

/*
typedef struct {
    ZEntityMaxAmount count; // number of entities this chunk CURRENTLY has (don't count nonexistent things.)
    ZEntityIdx start_index;
} ZChunk;
*/

/* ========= ZMeta
 * Stores a slab pointer and its index in the slab.
 * Nothing else
 * Absolutely nothing else.
 * I use it for the id_to_meta array in ZCore
 */

typedef struct {
    void* slab_ptr;
    int local_idx;
} ZMetaData;

/*
 * ======================= ZWorldButtonSlab
 *
 * - contains: a sparse set (id_to_idx) and dense set (idx_to_id)
 *             data sets (positions, sizes, etc..)
 * - The enums are to just minimize magic numbers.
 *
 * - The slab has it's own command buffer, to cache stuff that gets deleted after a frame
 */

typedef enum {
    // flags for bitmasks array
    IS_HOVERED = 1 << 0,
    IS_CLICKED = 1 << 1,
    IS_ACTIVE = 1 << 2,
    WBSLAB_ECOUNT = 128, // entity count
    WBSLAB_CCOUNT = 128, // chunk count. depends on how much chunks the buttons in my game occupies in.
} wbslab_globals;

// aos because Im lazy..
struct ZEvent {
    ZAction action;
    bool kill_me;
    bool tick_timer;
    int target_id;
    float timer;
    char data[64];
    void* heap;
};

struct ZWorldButtonSlab {
    int entity_count;
    int chunk_count;

    ZEntityId idx_to_id[WBSLAB_ECOUNT]; // Maps local slab index to global ID

    Vector2 positions[WBSLAB_ECOUNT];
    Vector2 sizes[WBSLAB_ECOUNT];
    uint16_t bitmasks[WBSLAB_ECOUNT];
    ZAction onclicks[WBSLAB_ECOUNT];
    ZAction onhovers[WBSLAB_ECOUNT];
    int level_max[WBSLAB_ECOUNT];
    int level_current[WBSLAB_ECOUNT];
};

/* ======================= ZCore
 * - A context struct to store global variables and slab pointers
 * - Also contains an used id array to store invalid arrays
 */

struct ZCore {
    ZEntityId id_used[MAX_ENTITIES];
    int used_id_count;

    ZEntityIdx id_to_idx[MAX_ENTITIES]; // Maps global ID to local slab index
    ZWorldButtonSlab* wbslab;
    ZEvent events[MAX_EVENTS];
    int event_count;
    Camera2D camera;
    Vector2 camera_position;
    Vector2 screen_size;
    float move_speed;
    float delta_time;
    // uint32_t padding[14];
};

/*
 * ========================= Miscellaneous functions
 * - Functions that don't belong to a struct / slab, e.g rendering, input / output
 *
 * * also known as the "I dont belong to anyone" circus. -peanut
 */

// Default ZAction, which it's pointer is put in all behavior to prevent calling nonexistent actions
void z_debug(ZCore* core, ZEvent* me);

// input / output, controls the screen size
void z_io_init(ZCore* core);

void z_io_loop(ZCore* core);

// movement and zoom
void z_system_init(ZCore* core);

void z_movement(ZCore* core);

void z_zoom(ZCore* core);

// rendering

void z_draw_ui(ZCore* core);

void z_render_loop(ZCore* core);

// All the entity definitions and setup goes here.
void z_setup(ZCore* core);

// hitcheck handler
void z_system_hitcheck(ZCore* core);

/**
 * ========================= ZCore-related functions
 * - These are functions that are usually related to ZCore's setup or managing entities in ZCore
 * * also known as "the royal ZCore family". -peanut
 */

// Allocate and set up the used_id_count variable.
ZCore* z_core_init(void);

// Check if entity matches, check if they are out of bounds, then put them into the id_used array
void z_entity_add(ZCore* core, ZEntityId id);

/**
 * ========================= ZWorldButtonSlab-related functions
 * - These functions handle the:
 *   - Setup
 *   - Entity Addition
 *   - Rendering
 *   - Hitcheck
 *   - Culling
 *   - Processing clicks
 * * also known as the "loud as fuck world button slab family". -peanut
 */

// ============== SETUP FUNCTIONS

void wbslab_init(ZCore* core); // allocates wbslab and set up id->idx idx->id

// Requires a valid ZEntityId, along with all properties, and set it onto the slab.
void wbslab_add(
    ZCore* core,
    ZEntityId id,
    Vector2 position,
    Vector2 size,
    int max_level,
    ZAction onclick,
    ZAction onHover
);

// ============== LOOP FUNCTIONS

void wbslab_render(ZWorldButtonSlab* wbslab); // draws locally all the buttons



// ========================= ZEVENT HANDLERS
/*
 * A collection of functions that handles ZEvent, the main way of doing behaviors for entities.
 *
 * it's name is "days of insomania for this (not really)" - peanut
 */

void z_event_add_too_simple(ZCore* core, ZAction action);

void z_event_add_too_complicated(ZCore* core, ZEvent event);

void z_event_delete(ZCore* core, int event_idx);

void z_event_loop(ZCore* core);

/** DEPRECATED ZONE (sad) */
/**
 * =========================== CULLING FUNCTIONS (it's a group of functions)
 * - guys bear with me for a sec (lol)
 * - the culling process works when culling is called, and no it doesnt run per frame.
 * - wbslab_culler_labeler():
 *   - takes in the position of each entity in positions[] and calculate hash and put it in the idx_to_chunk_location[]
 *
 * - wbslab_insertion_sort_cull_everything_becuz_whynot():
 *   - insertion sorts the slab by idx_to_chunk_location[] with wbslab_culler_swapper()
 * - wbslab_now_i_accumulate_so_theres_starting_idxs_and_location():
 *   - creates chunks based on the new idx_to_chunk_location[]
 *     - imagine the newly idx_to_chunk_location[] like this: [1, 1, 1, 2, 2, 2, 2, 3, 5, 11]
 *     - the chunks[] output will be [{0, 3}, {3, 4}, {7, 1}, {8, 1}, {9, 1}, {11, 1}]
 *
 * - wbslab_update_visible_set() loops once per frame to update the new visible chunks in the command buffer.
 * - For anyone reading this, please don't spiral
 */
/*
// makes a map from button entity index to the button's location
void wbslab_culler_labeler(ZWorldButtonSlab* wbslab);

void wbslab_culler_swapper(
    ZWorldButtonSlab* wbslab,
    ZEntityIdx idx1,
    ZEntityIdx idx2); // a single swap of 2 entity indices.

void wbslab_insertion_sort_cull_everything_becuz_whynot(
    ZWorldButtonSlab* wbslab); // insertion sort, utilising the above function.

void wbslab_now_i_accumulate_so_theres_starting_idxs_and_location(
    ZWorldButtonSlab* wbslab); // accumulate and put into neat chunks

void wbslab_culler(
    ZWorldButtonSlab* wbslab); // packages all the functions above to set my (statically defined) buttons for culling.

void wbslab_update_visible_set(ZCore* core); // THIS ONE RUNS EVERY FRAME TO POLL THE CURRENT VIEWPORT GUYS
*/
