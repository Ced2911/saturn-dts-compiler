/* internal use only -- mapping of "system calls" for libraries that lose
   and only provide C names, so that we end up in violation of ANSI */
#ifndef __SYSLIST_H
#define __SYSLIST_H
#ifdef MISSING_SYSCALL_NAMES
#define _close close
#define _fcntl fcntl
#define _fork fork
#define _fstat fstat
#define _getpid getpid
#define _kill kill
#define _link link
#define _lseek lseek
#define _open open
#define _read read
#define _sbrk sbrk
#define _stat stat
#define _unlink unlink
#define _wait wait
#define _write write
/* functions not yet sysfaked */
#define _raise raise
#define _execve execve
#define _opendir opendir
#define _readdir readdir
#define _closedir closedir
#endif
#endif
