AC_PREREQ([2.69])  # Wersja autotools (wymagana)
AC_INIT([matrix-multiplication], [1.0], [your-email@example.com])  # Nazwa projektu i wersja
AM_INIT_AUTOMAKE([foreign])  # Inicjalizacja Automake, 'foreign' oznacza mniej rygorystyczne sprawdzanie

AC_PROG_CC  # Sprawdzanie, czy kompilator C jest dostępny
AC_PROG_MAKE_SET  # Sprawdzanie narzędzi make

# Włączenie wsparcia dla ARM NEON, jeśli dostępne
AC_CHECK_HEADER([arm_neon.h], [AC_DEFINE([__ARM_NEON], 1, [Define if ARM NEON is available])])

# Tworzenie pliku config.h.in
AC_CONFIG_HEADERS([config.h])

# Sprawdzanie, czy mamy bibliotekę math.h
AC_CHECK_LIB([m], [sin])

# Wygenerowanie pliku Makefile.in
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
