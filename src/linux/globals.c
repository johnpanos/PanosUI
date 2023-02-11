#include "globals.h"

struct UIPlatformGlobals UIPlatformGlobalsShared = {
    .compositor = NULL,
    .subcompositor = NULL,
    .display = NULL,
    .wl_registry = NULL,
    .wl_seat = NULL,
    .wl_shm = NULL};