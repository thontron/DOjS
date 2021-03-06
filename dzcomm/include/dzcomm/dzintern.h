/*
 * DZcomm : a serial port API.
 * file : dzintern.h
 *
 * Some definitions for internal use by the library code.
 * 
 * By Neil Townsend
 *
 * See readme.txt for copyright information.
 */

#ifndef __dzintern_h__
#define __dzintern_h__

#ifdef DZCOMM_AND_ALLEGRO_OVERLAP
#include <allegro.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
   DZ_METHOD(int,         method_init,       (void));
   DZ_METHOD(comm_port *, init,              (comm_port *port, comm com));
   DZ_METHOD(int,         install_handler,   (comm_port *port));
   DZ_METHOD(void,        uninstall_handler, (comm_port *port));
   DZ_METHOD(void,        delete,            (comm_port *port));
   DZ_METHOD(void,        closedown,         (void));
   DZ_METHOD(int,         in,                (comm_port *port));
   DZ_METHOD(void,        send_break,        (comm_port *port, int msec_duration));
   DZ_METHOD(int,         out,               (comm_port *port, unsigned char *cp));
   DZ_METHOD(int,         io_buffer_query,   (comm_port *port, int io, int query));
   DZ_METHOD(void,        flush_output,      (comm_port *port));
   DZ_METHOD(void,        flush_input,       (comm_port *port));
   DZ_METHOD(int,         give_line_status,  (comm_port *port, dzcomm_line line));
   DZ_METHOD(int,         set_line_status,   (comm_port *port, dzcomm_line line, int value));
} comm_port_func_table;



DZ_ARRAY(_DZ_DRIVER_INFO, _comm_port_driver_list);
DZ_FUNC(void, lock_queue_functions, (void));

DZ_INLINE(void, dz_make_comm_err, (char *szErr),{sprintf(szDZCommErr,"Dzcomm: %s",szErr);})

/* various bits of timer stuff */
DZ_FUNC(long, _dz_handle_timer_tick, (int interval));

#define MAX_TIMERS      16

/* list of active timer handlers */
typedef struct DZ_TIMER_QUEUE
{
   DZ_METHOD(void, proc, (void));      /* timer handler functions */
   DZ_METHOD(void, param_proc, (void *param));
   void *param;                        /* param for param_proc if used */
   long speed;                         /* timer speed */
   long counter;                       /* counts down to zero=blastoff */
} DZ_TIMER_QUEUE;

DZ_ARRAY(DZ_TIMER_QUEUE, _dz_timer_queue);

DZ_VAR(int, _dz_timer_use_retrace);
DZ_VAR(volatile int, _dz_retrace_hpp_value);

/* 
 * Some flow control #defines to make the code marginally more comprehensible
 */

#define XON_RCVD   1
#define XON_SENT   1
#define XOFF_RCVD  0
#define XOFF_SENT  0
#define XON_ASCII  0x11
#define XOFF_ASCII 0x13

#define CTS_ON  0x01
#define CTS_OFF 0x00

/* For io_buffer_query */

#define DZ_IO_BUFFER_IN  0
#define DZ_IO_BUFFER_OUT 1

#define DZ_IO_BUFFER_EMPTY       0
#define DZ_IO_BUFFER_FULL        1

#ifdef DZCOMM_INTERNAL_HEADER
   #include DZCOMM_INTERNAL_HEADER
#endif

/*
 * If the following haven't yet been defined then standard definitions
 * (possibly to be nothing) can be used:
 */

#ifndef dz_enable_interrupts
   #define dz_enable_interrupts() {}
#endif

#ifndef dz_disable_interrupts
   #define dz_disable_interrupts() {}
#endif

#ifndef dz_set_interrupt_depth
   #define dz_set_interrupt_depth(x) {}
#endif
 
#ifdef __cplusplus
}
#endif

#endif /* __dzintern_h__ */
