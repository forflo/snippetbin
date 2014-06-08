AC_PREREQ(2.59)

dnl Standard boilderplate code
AC_INIT([bashm], [1.0], [mayer.florian@web.de])
AM_INIT_AUTOMAKE([1.9 gnu])

AC_PROG_CC

dnl Check for libs
AC_CHECK_LIB([m], [pow])

dnl Check for headers
AC_CHECK_HEADERS([stdlib.h, unistd.h, math.h, sys/ipc.h sys/types, sys/shm.h])
AC_CHECK_HEADERS([string.h, getopt.h])

dnl Check for functions
AC_FUNC_REALLOC
AC_FUNC_MALLOC
AC_CHECK_FUNCS([pow])


AC_CONFIG_FILES([Makefile])
AC_OUTPUT
