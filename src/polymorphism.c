/*
* Copyright (c) 2025-present Wojciech Kaptur ( _Sqyd_ / Sqydev )
* Github: https://github.com/Sqydev
* GPG Fingerprint: 6DC2516B0DFDA9C59661650722F7B8A777F33B56
* 
* This software is provided "as-is", without any express or implied warranty. In no event
* will the authors be held liable for any damages arising from the use of this software.
* 
* Permission is granted to anyone to use this software for any purpose, including commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
* 
* 1. Non-Misrepresentation: The origin of this software must not be misrepresented; 
*	you must not claim that you wrote the original software. An acknowledgment in 
*	product documentation is appreciated but not required.
* 
* 2. Source-Level Copyleft: Any altered versions (forks) of this software's source code, 
*	or files containing significant portions of this code, must be distributed under 
*	these same license terms. Such modified source code must be made publicly available 
*	to any recipient, even if used over a network (SaaS).
* 
* 3. Proprietary Integration: This software may be integrated into, linked with, or 
*	used as a component of proprietary and closed-source products. In such cases, 
*	the surrounding proprietary application code does not need to be disclosed, 
*	provided that the original or modified source code of THIS software remains 
*	available under the terms of Section 2.
* 
* 4. Persistent Metadata: All original credits, including those in the source code headers 
*	and binary metadata (e.g., ELF .comment section, PE StringFileInfo, or equivalent), 
*	must not be removed. You may add your own credits to forks, provided the original 
*	authorship remains clearly identified.
* 
* 5. Notice Retention: This license notice may not be removed or altered from any 
*	source or binary distribution.
*/

#include "../include/Classes.h"

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L

#include <stdlib.h>
#include <stdbool.h>

static poly_t** polyRegistry = NULL;
static size_t polyCount = 0;
static bool polyInited = false;

static poly_type_id_t customTypeCounter = 1;

void DestroyAllPolys(void) {
    for(size_t i = 0; i < polyCount; i++) {
        if(!polyRegistry[i]) { continue; }
        for(size_t j = 0; j < polyRegistry[i]->count; j++) {
            free(polyRegistry[i]->entries[j].sig);
            free(polyRegistry[i]->entries[j].type_ids);
        }
        free(polyRegistry[i]->entries);
        free(polyRegistry[i]);
    }
    free(polyRegistry);
    polyRegistry = NULL;
    polyCount = 0;
    polyInited = false;
}

poly_t* CreatePoly(void) {
    if(!polyInited) { atexit(DestroyAllPolys); polyInited = true; }

    poly_t* p = calloc(1, sizeof(poly_t));
    if(!p) { return NULL; }

    poly_t** tmp = realloc(polyRegistry, (polyCount + 1) * sizeof(poly_t*));
    if(!tmp) { free(p); return NULL; }
    polyRegistry = tmp;
    polyRegistry[polyCount++] = p;

    return p;
}

void DestroyPoly(poly_t* poly) {
    for(size_t i = 0; i < polyCount; i++) {
        if(polyRegistry[i] == poly) { polyRegistry[i] = NULL; break; }
    }
    for(size_t j = 0; j < poly->count; j++) {
        free(poly->entries[j].sig);
        free(poly->entries[j].type_ids);
    }
    free(poly->entries);
    free(poly);
}

poly_type_id_t CreatePolyType(void) {
    return customTypeCounter++;
}

void _PolyRegSig(poly_t* poly, pm_sig_item_t* sig, poly_handler_t handler) {
    size_t len = 0;
    while(sig[len].type != (poly_type_t)-1) { len++; }

    poly_entry_t entry;
    entry.sig_len = len;
    entry.handler = handler;
    entry.sig = malloc(len * sizeof(poly_type_t));
    entry.type_ids = malloc(len * sizeof(poly_type_id_t));

    for(size_t i = 0; i < len; i++) {
        entry.sig[i] = sig[i].type;
        entry.type_ids[i] = sig[i].type_id;
    }

    poly_entry_t* tmp = realloc(poly->entries, (poly->count + 1) * sizeof(poly_entry_t));
    if(!tmp) { free(entry.sig); free(entry.type_ids); return; }
    poly->entries = tmp;
    poly->entries[poly->count++] = entry;
}

void CallPoly(poly_t* poly, object_t* self, pm_item_t* items) {
    size_t argc = 0;
    while(items[argc].type != (poly_type_t)-1) { argc++; }

    for(size_t i = 0; i < poly->count; i++) {
        poly_entry_t* e = &poly->entries[i];
        if(e->sig_len != argc) { continue; }

        bool match = true;
        for(size_t k = 0; k < argc && match; k++) {
            if(e->sig[k] != items[k].type) { match = false; break; }

            if(items[k].type == POLY_TYPE_OBJ && e->type_ids[k] != 0) {
                if(((object_t*)items[k].arg.p)->root->id != e->type_ids[k]) { match = false; }
			}

            if(items[k].type == POLY_TYPE_CUSTOM && e->type_ids[k] != 0) {
                if(items[k].arg.custom.type_id != e->type_ids[k]) { match = false; }
			}
        }

        if(match) {
            poly_arg_t args[argc];
            for(size_t k = 0; k < argc; k++) { args[k] = items[k].arg; }
            e->handler(self, args, argc);
            return;
        }
    }
}

#endif
