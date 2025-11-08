AC_INIT([cYclients], [1.0])
AM_INIT_AUTOMAKE([foreign])

AC_PROG_CC
LT_INIT

AC_ARG_ENABLE([tests], 
               [AS_HELP_STRING([--enable-tests], [Build
               tests @<:@no@:>@])],
               [enable_tests=yes],
               [enable_tests=no])

AM_CONDITIONAL([BUILD_TEST], [test "$enable_tests" = "yes"])

AC_CHECK_FILE([partner_token.h],[],
               [AC_MSG_ERROR([To get partner token - register in https://yclients.com/appstore/developers. create file partner_token.h with content: #define SETUP_PARTNER_TOKEN(partner_token) partner_token = "your_token"])],[])

AC_CHECK_HEADER([curl/curl.h],[],[AC_MSG_ERROR([Pleaseinstall libcurl])],[])

AC_CANONICAL_HOST
case "${host_os}" in
    cygwin*|mingw*)
        build_windows=yes;;
    darwin*)
        build_mac=yes;;
    *)
        build_linux=yes;;
esac

AM_CONDITIONAL([WINDOWS], [test "$build_windows" = "yes"])
AM_CONDITIONAL([WIN32], [test "$build_windows" = "yes" -a "$build_i386" == "yes"])
AM_CONDITIONAL([WIN64], [test "$build_windows" = "yes" -a "$build_x86_64" == "yes"])

case "${host_cpu}" in
    i?86*)
        build_i386=yes;;
    x86_64*)
        build_x86_64=yes;;
    arm64*|aarch64*)
        build_arm64=yes;;
    armv7*)
        build_arm=yes;;
    *)
		;;
esac
AM_CONDITIONAL([WIN32], [test "$build_windows" = "yes" -a "$build_i386" == "yes"])

AC_CONFIG_FILES([
Makefile
])
AC_OUTPUT
