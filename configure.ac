#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([arsenic], [0.1], [opensource@chronic-dev.org])
AC_CONFIG_SRCDIR([src/arsenic.cpp])
#AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET

# Checks for libraries.
AC_CHECK_LIB([crypto], [CRYPTO_free], [], [AC_MSG_ERROR(libcrypto not found!)])
AC_CHECK_LIB([curl], [curl_version], [], [AC_MSG_ERROR(libcurl not found)])
AC_CHECK_LIB([partial], [PartialZipInit], [AC_MSG_ERROR(libpartial not found)])
AC_CHECK_LIB([plist], [plist_from_bin], [], [AC_MSG_ERROR(libplist not found)])
AC_CHECK_LIB([xml2], [xmlParseFile], [], [AC_MSG_ERROR(libxml2 not found)])
AC_CHECK_LIB([z], [gzread], [], [AC_MSG_ERROR(zlib not found)])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_UINT32_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strstr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

AM_INIT_AUTOMAKE([arsenic], [0.1])