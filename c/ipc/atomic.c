//#include <rte_atomic.h>
//#include <asm-generic/atomic.h>
#include "rte_atomic.h"
#include <pthread.h>

static rte_atomic32_t v;

int main()
{
    rte_atomic32_init(&v);
    //atomic_t v = ATOMIC_INIT(1);
    int ret;
	if (rte_atomic32_dec_and_test(&v));
		//rte_atomic64_inc(&count);
//    ret = atomic_dec_and_test(&v);
//    atomic_inc(&v);
    return 0;
}
