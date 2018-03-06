/*
 * A sample prefetcher which does sequential one-block lookahead.
 * This means that the prefetcher fetches the next block _after_ the one that
 * was just accessed. It also ignores requests to blocks already in the cache.
 */

#include "interface.hh"
#include <stdlib.h>

const size_t K = 1; // Sequential prefetch factor

void prefetch_forward(Addr address, size_t blocks) {
	for (size_t i = 1; i < blocks + 1; ++i) {
		issue_prefetch(address + i * BLOCK_SIZE);
	}
}

void prefetch_init(void)
{
	/* Called before any calls to prefetch_access. */
	/* This is the place to initialize data structures. */
	DPRINTF(HWPrefetch, "Initialized sequential-on-access prefetcher\n");
}

void prefetch_access(AccessStat stat)
{
	// Prefetch on miss
	Addr pf_addr = stat.mem_addr + BLOCK_SIZE;
	if (stat.miss && !in_cache(pf_addr)) {
		prefetch_forward(stat.mem_addr, K);
	}
}

void prefetch_complete(Addr addr) {
	/*
	* Called when a block requested by the prefetcher has been loaded.
	*/
	DPRINTF(HWPrefetch, "Complete: %d\n", addr);
}
