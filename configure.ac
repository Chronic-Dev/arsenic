#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.


AC_INIT([arsenic], [0.1], [opensource@chronic-dev.org])
AC_PREREQ([2.63])
AM_INIT_AUTOMAKE([arsenic], [0.1])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/arsenic.cpp])
#AC_CONFIG_FILES([src/Makefile])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
AC_CHECK_LIB([crypto], [CRYPTO_free], [], [AC_MSG_ERROR(libcrypto not found!)])
AC_CHECK_LIB([curl], [curl_version], [], [AC_MSG_ERROR(libcurl not found)])
AC_CHECK_LIB([partial], [PartialZipGetFile], [], [AC_MSG_ERROR(libpartial not found)])
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

AC_OUTPUT(Makefile src/Makefile)
