include ../../../htx.mk

TARGET= \
	maxmem  \
             maxmem_rim  \
             hxemem64.readme  \
             mem_16m_hwpf \
             memmfg.p6 \
             memmfg \
             memmfg.p6.nodelay \
             memmfg.nodelay \
             memconfig.txt \
             default.mem.eq.4k \
             default.mem.eq.64k \
             rules.dl1_reloads_from_caches \
             rules.max_cache_hit \
             L4 \
             rules.max_cache_miss \
             rules.comm_db_pk \
             rules.web_server \
             rules.app_server \
             rules.hpc_comp_node \
             rules.MBA \
 		mem.eq.50 \
		mem.eq.90


.PHONY: all clean

all: ${TARGET}
	${MKDIR} ${REGRULES}/hxemem64/
	${CP} ${TARGET} ${REGRULES}/hxemem64/ 

clean:
	${RM} -rf ${REGRULES}/hxemem64/*
