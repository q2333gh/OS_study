AC_PREREQ([2.69])
AC_INIT([become_daemon], [1.0], [lloyd@lloydrochester.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h stdlib.h syslog.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_FORK
AC_CHECK_FUNCS([dup2])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
