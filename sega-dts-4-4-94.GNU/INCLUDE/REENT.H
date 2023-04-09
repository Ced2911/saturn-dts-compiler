/* This header file provides the reentrancy.  */

/* WARNING: All identifiers here must begin with an underscore.  This file is
   included by stdio.h and others and we therefore must only use identifiers
   in the namespace allotted to us.  */

#ifndef _REENT_H_
#ifdef __cplusplus
extern "C" {
#endif
#define _REENT_H_

#include <sys/reent.h>

/* Reentrant versions of system calls.  */

struct stat;
#include <sys/types.h>
#define __need_size_t
#include <stddef.h>

extern int _close_r _PARAMS ((struct _reent *, int));
extern int _fork_r _PARAMS ((struct _reent *));
extern int _wait_r _PARAMS ((struct _reent *, int *));
extern int _fstat_r _PARAMS ((struct _reent *, int, struct stat *));
extern int _link_r _PARAMS ((struct _reent *, const char *, const char *));
extern int _unlink_r _PARAMS ((struct _reent *, const char *));
extern off_t _lseek_r _PARAMS ((struct _reent *, int, off_t, int));
extern int _open_r _PARAMS ((struct _reent *, const char *, int, int));
extern void *_sbrk_r _PARAMS ((struct _reent *, size_t));
extern int _stat_r _PARAMS ((struct _reent *, const char *, struct stat *));
/* FIXME: Return value should be ssize_t.  */
extern long _read_r _PARAMS ((struct _reent *, int, void *, size_t));
extern long _write_r _PARAMS ((struct _reent *, int, const void *, size_t));

#ifdef __cplusplus
}
#endif
#endif /* _REENT_H_ */
