Documentation
============

AgileRTOS can probably be a RTOS but mostly it is just a RAM saving malloc and pthread implementation for microcontroller without memory management unit.

 🔗 [Documentation](http://agilertos.com)

 🔗 [Repository](https://github.com/ykat-UG-haftungsbeschrankt/agilertos)

Examples
------------

### malloc() / free() ###

[Implementation details](http://agilertos.com/zrtos__malloc_8h.html)

```C
#include <avr/io.h>

/**
 * If malloc and new is only used on boot without releasing the memory, code and
 * ram usage can be further reduced by '#define ZRTOS_MALLOC__CFG_DISABLE_FREE'.
 */
//#define ZRTOS_MALLOC__CFG_DISABLE_FREE
#include "zrtos_malloc.h"

// global heap for malloc()/free()
ZRTOS_MALLOC__GLOBAL_HEAP(heap,ZRTOS_MALLOC__GET_REQUIRED_SIZE(char,160));

int main(void){
	ZRTOS_MALLOC__GLOBAL_HEAP_INIT(heap);

	// separate heap usable with zrtos_malloc__malloc()/zrtos_malloc__free()
	ZRTOS_MALLOC__INIT(heap2,ZRTOS_MALLOC__GET_REQUIRED_SIZE(char,160));

	// separate heap usable with zrtos_malloc__malloc()/zrtos_malloc__free()
	ZRTOS_MALLOC__INIT(heap3,ZRTOS_MALLOC__GET_REQUIRED_SIZE(char,160));

	size_t length = 10,l;
	void *ptr[10];

	for(l=0;l<=length;l++){
		ptr[l] = malloc(16);
	}
	for(l=0;l<=length;l++){
		free(ptr[l]);
	}
	for(l=0;l<=length;l++){
		ptr[l] = malloc(16);
	}
	for(l=0;l<=length;l++){
		free(ptr[l]);
	}

	for(l=0;l<=length;l++){
		ptr[l] = zrtos_malloc__malloc(heap2,16);
	}
	for(l=0;l<=length;l++){
		zrtos_malloc__free(ptr[l]);
	}
	for(l=0;l<=length;l++){
		ptr[l] = zrtos_malloc__malloc(heap3,16);
	}
	for(l=0;l<=length;l++){
		zrtos_malloc__free(ptr[l]);
	}

	return 0;
}
```

### pthread ###
```C
```

### Supported Chips and Boards ###

  * None