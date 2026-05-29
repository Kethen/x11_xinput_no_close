#include <stdlib.h>
#include <stdbool.h>

#include <dlfcn.h>

#include "libdetour/src/libdetour.h"

#include "log.h"

DETOUR_DECL_TYPE(void , XCloseDevice_orig, void *, unsigned long);
detour_ctx_t XCloseDevice_detour_ctx;

void XCloseDevice_hooked(void *display, unsigned long device_id){
	LOG("%s: closing of display %p device %lu rejected\n", __func__, display, device_id);
}

__attribute__((constructor))
int init(){
	init_log();

	void *lib_handle = dlopen("libXi.so", RTLD_NOW);
	if (lib_handle == NULL){
		LOG("%s: failed loading libXi.so\n", __func__);
		exit(1);
	}

	void *func = dlsym(lib_handle, "XCloseDevice");
	if (func == NULL){
		LOG("%s: failed fetching XCloseDevice from libXi.so", __func__);
		exit(1);
	}

	detour_init(&XCloseDevice_detour_ctx, func, XCloseDevice_hooked);
	bool enable_status = detour_enable(&XCloseDevice_detour_ctx);
	if (!enable_status){
		LOG("%s: failed enabling XCloseDevice detour\n", __func__);
		exit(1);
	}

	LOG("%s: ready\n", __func__);
	return 0;
}
