#pragma once
//libteken: terminal emulation library.
//This library converts an UTF-8 stream of bytes to terminal drawing commands.
#include "sys/types.h"
#include "Macros.h"

#ifdef TEKEN_UTF8
typedef uint32_t teken_char_t;
#else 
typedef unsigned char teken_char_t;
#endif
typedef unsigned short teken_unit_t;
typedef unsigned char teken_format_t;
#define	TF_BOLD		0x01
#define	TF_UNDERLINE	0x02
#define	TF_BLINK	0x04
#define	TF_REVERSE	0x08
typedef unsigned char teken_color_t;
#define	TC_BLACK	0
#define	TC_RED		1
#define	TC_GREEN	2
#define	TC_BROWN	3
#define	TC_BLUE		4
#define	TC_MAGENTA	5
#define	TC_CYAN		6
#define	TC_WHITE	7
#define	TC_NCOLORS	8

typedef struct {
	teken_unit_t	tp_row;
	teken_unit_t	tp_col;
} teken_pos_t;
typedef struct {
	teken_pos_t	tr_begin;
	teken_pos_t	tr_end;
} teken_rect_t;
typedef struct {
	teken_format_t	ta_format;
	teken_color_t	ta_fgcolor;
	teken_color_t	ta_bgcolor;
} teken_attr_t;
typedef struct {
	teken_unit_t	ts_begin;
	teken_unit_t	ts_end;
} teken_span_t;

typedef struct __teken teken_t;

typedef void teken_state_t(teken_t *, teken_char_t);

/*
* Drawing routines supplied by the user.
*/

typedef void tf_bell_t(void *);
typedef void tf_cursor_t(void *, const teken_pos_t *);
typedef void tf_putchar_t(void *, const teken_pos_t *, teken_char_t,
	const teken_attr_t *);
typedef void tf_fill_t(void *, const teken_rect_t *, teken_char_t,
	const teken_attr_t *);
typedef void tf_copy_t(void *, const teken_rect_t *, const teken_pos_t *);
typedef void tf_param_t(void *, int, unsigned int);
#define	TP_SHOWCURSOR	0
#define	TP_CURSORKEYS	1
#define	TP_KEYPADAPP	2
#define	TP_AUTOREPEAT	3
#define	TP_SWITCHVT	4
#define	TP_132COLS	5
#define	TP_SETBELLPD	6
#define	TP_SETBELLPD_PITCH(pd)		((pd) >> 16)
#define	TP_SETBELLPD_DURATION(pd)	((pd) & 0xffff)
typedef void tf_respond_t(void *, const void *, size_t);

typedef struct {
	tf_bell_t	*tf_bell;
	tf_cursor_t	*tf_cursor;
	tf_putchar_t	*tf_putchar;
	tf_fill_t	*tf_fill;
	tf_copy_t	*tf_copy;
	tf_param_t	*tf_param;
	tf_respond_t	*tf_respond;
} teken_funcs_t;

#if defined(TEKEN_XTERM) && defined(TEKEN_UTF8)
typedef teken_char_t teken_scs_t(teken_char_t);
#endif /* TEKEN_XTERM && TEKEN_UTF8 */

/*
* Terminal state.
*/

struct __teken {
	const teken_funcs_t *t_funcs;
	void		*t_softc;

	teken_state_t	*t_nextstate;
	unsigned int	 t_stateflags;

#define T_NUMSIZE	8
	unsigned int	 t_nums[T_NUMSIZE];
	unsigned int	 t_curnum;

	teken_pos_t	 t_cursor;
	teken_attr_t	 t_curattr;
	teken_pos_t	 t_saved_cursor;
	teken_attr_t	 t_saved_curattr;

	teken_attr_t	 t_defattr;
	teken_pos_t	 t_winsize;

	/* For DECSTBM. */
	teken_span_t	 t_scrollreg;
	/* For DECOM. */
	teken_span_t	 t_originreg;

#define	T_NUMCOL	160
	unsigned int	 t_tabstops[T_NUMCOL / (sizeof(unsigned int)* 8)];

#ifdef TEKEN_UTF8
	unsigned int	 t_utf8_left;
	teken_char_t	 t_utf8_partial;
#endif /* TEKEN_UTF8 */

#if defined(TEKEN_XTERM) && defined(TEKEN_UTF8)
	unsigned int	 t_curscs;
	teken_scs_t	*t_saved_curscs;
	teken_scs_t	*t_scs[2];
#endif /* TEKEN_XTERM && TEKEN_UTF8 */
};

/* Initialize teken structure. */
extern C void teken_init(teken_t *, const teken_funcs_t *, void *);

/* Deliver character input. */
extern C void teken_input(teken_t *, const void *, size_t);

/* Get/set teken attributes. */
extern C const teken_attr_t *teken_get_curattr(teken_t *);
extern C const teken_attr_t *teken_get_defattr(teken_t *);
extern C void teken_set_cursor(teken_t *, const teken_pos_t *);
extern C void teken_set_curattr(teken_t *, const teken_attr_t *);
extern C void teken_set_defattr(teken_t *, const teken_attr_t *);
extern C void teken_set_winsize(teken_t *, const teken_pos_t *);

