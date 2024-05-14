#include <stdio.h>
#include <dlfcn.h>

int malloc_counter = 0;

// ================================== PUBLIC ==================================

void check_leaks() {
    if (malloc_counter != 0)
        fprintf(stderr, "LEAKS: there are %d leaks\n", malloc_counter);
}

// ================================= INTERNAL =================================

static void *(*real_malloc)(unsigned long) = 0;
static void (*real_free)(void *) = 0;

static void malloc_init(void) {
    real_malloc = (void *(*)(unsigned long))dlsym(RTLD_NEXT, "malloc");
    if (real_malloc == 0)
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
}

static void free_init(void) {
    real_free = (void (*)(void *))dlsym(RTLD_NEXT, "free");
    if (real_free == 0)
        fprintf(stderr, "Error in `dlsym`: %s\n", dlerror());
}

void *malloc(unsigned long size) {
    if (real_malloc == 0)
        malloc_init();

    void *p = 0;
    p = real_malloc(size);
    malloc_counter++;
    return p;
}

void free(void *p) {
    if (real_free == 0)
        free_init();

    real_free(p);
    malloc_counter--;
}