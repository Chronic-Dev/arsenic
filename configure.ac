AC_INIT([arsenic], [2.0], [opensource@chronic-dev.org])
AC_PREREQ([2.60])
AM_INIT_AUTOMAKE([arsenic], [0.1])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL

# Checks for libraries.
AC_CHECK_LIB([crypto], [CRYPTO_free], [], [AC_MSG_ERROR(libcrypto not found!)])
AC_CHECK_LIB([curl], [curl_version], [], [AC_MSG_ERROR(libcurl not found)])
AC_CHECK_LIB([partial], [PartialZipGetFile], [], [AC_MSG_ERROR(libpartial not found)], -lz)
AC_CHECK_LIB([plist], [plist_from_bin], [], [AC_MSG_ERROR(libplist not found)])
AC_CHECK_LIB([xml2], [xmlParseFile], [], [AC_MSG_ERROR(libxml2 not found)])
AC_CHECK_LIB([z], [gzread], [], [AC_MSG_ERROR(zlib not found)])
AC_CHECK_LIB([ssl], [SSL_library_init], [], [AC_MSG_ERROR(ssl not found)])
AC_CHECK_LIB([log4cxx], [main], [], [AC_MSG_ERROR(log4cxx not found)])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

# Checks for programs.
AC_PROG_CXX
