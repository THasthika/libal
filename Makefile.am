ACLOCAL_AMFLAGS = -I m4 --install

AM_CFLAGS = -g3 --std=c99 -DNDEBUG

# bin_PROGRAMS = cp
# cp_SOURCES = src/cp.c src/cp.h src/common.c src/common.h
# cp_CFLAGS = -g3 --std=c99 -DNDEBUG

lib_LTLIBRARIES = libTHB.la

libTHB_la_SOURCES = THB/list.c THB/list.h THB/queue.c THB/queue.h THB/stack.c THB/stack.h THB/hash_table.c THB/hash_table.h THB/sort.h THB/merge_sort.c THB/insertion_sort.c THB/heap_sort.c
nobase_include_HEADERS = THB/list.h THB/queue.h THB/stack.h THB/hash_table.h

TESTS = check_list check_sort check_hash_table

check_PROGRAMS = check_list check_sort check_hash_table

check_list_SOURCES = tests/check_list.c
check_list_LDADD = libTHB.la

check_sort_SOURCES = tests/check_sort.c tests/util.c tests/util.h
check_sort_LDADD = libTHB.la

check_hash_table_SOURCES = tests/check_hash_table.c
check_hash_table_LDADD = libTHB.la

EXTRA_DIST = m4/NOTES
