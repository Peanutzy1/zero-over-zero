#include <stdlib.h>
#include <assert.h>
#include "zero.h"

void z_event_add_too_simple(ZCore* core, ZAction action) {
    assert(core->event_count < MAX_EVENTS);
    assert(action != nullptr);
    ZEvent* event = &core->events[core->event_count];
    event->action = action;
    event->kill_me = true;
    core->event_count++;
}

void z_event_add_too_complicated(ZCore* core, ZEvent event) {
    assert(core->event_count < MAX_EVENTS);
    assert(event.action != nullptr);
    core->events[core->event_count++] = event;
}

void z_event_delete(ZCore* core, int event_idx) {
    if (event_idx >= core->event_count - 1) return;
    ZEvent* events = core->events;
    events[event_idx] = events[core->event_count - 1];
    core->event_count--;
}

void z_event_loop(ZCore* core) {
    ZEvent* events = core->events;
    int event_count = core->event_count;
    for (int i = 0; i < event_count; i++) {
        if (events[i].tick_timer) {
            events[i].timer -= core->delta_time;
        }
        events[i].action(core, &events[i]);
    }

    for (int i = core->event_count; i >=0; i--) {
        ZEvent* event = &core->events[i];
        if (!event->kill_me) continue; 
        free(event->heap);
        event->heap = nullptr; 
        z_event_delete(core, i);
    }
}
