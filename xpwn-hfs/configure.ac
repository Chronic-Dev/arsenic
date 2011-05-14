AC_INIT([xpwn-hfs], [1.0], [opensource@chronic-dev.org])
AC_PREREQ([2.60])
AM_INIT_AUTOMAKE([xpwn-hfs], [0.1])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([z], [gzread], [], [AC_MSG_ERROR(zlib not found)])
AC_CHECK_LIB([ssl], [SSL_library_init], [], [AC_MSG_ERROR(ssl not found)])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

# Checks for programs.
AC_PROG_CXX
