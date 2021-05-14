set (
    FIBER_SOURCES 
    fiber_context.c
    fiber_manager.c
    fiber_mutex.c
    fiber_semaphore.c
    fiber_spinlock.c
    fiber_cond.c
    fiber.c
    fiber_barrier.c
    fiber_io.c
    fiber_rwlock.c
    fiber_scheduler_wsd.c
    hazard_pointer.c
    work_stealing_deque.c
    work_queue.c
)

if (FIBER_EV)
    list (APPEND FIBER_SOURCES "fiber_event_ev.c")    
else()
    list (APPEND FIBER_SOURCES "fiber_event_native.c")
endif(FIBER_EV)

add_library (fiber SHARED ${FIBER_SOURCES})
add_library (fiber_static STATIC ${FIBER_SOURCES})
set_target_properties(fiber_static  PROPERTIES
    OUTPUT_NAME fiber
    COMPILE_FLAGS "-fPIC"
)

#set_target_properties(coro PROPERTIES COMPILE_DEFINITIONS "CORO_ASM=1")
