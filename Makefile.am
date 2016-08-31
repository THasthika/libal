ACLOCAL_AMFLAGS = -I m4 --install

# AM_CFLAGS = -g3 --std=c99 -DNDEBUG
AM_CFLAGS = --std=c99

# bin_PROGRAMS = cp
# cp_SOURCES = src/cp.c src/cp.h src/common.c src/common.h
# cp_CFLAGS = -g3 --std=c99 -DNDEBUG

lib_LTLIBRARIES = libTHB.la

libTHB_la_SOURCES = THB/list.c THB/list.h THB/queue.c THB/queue.h THB/stack.c THB/stack.h THB/hash_table.c THB/hash_table.h THB/sort.h THB/sort_merge.c THB/sort_insertion.c THB/sort_heap.c
nobase_include_HEADERS = THB/list.h THB/queue.h THB/stack.h THB/hash_table.h THB/sort.h

TESTS = test/check_list test/check_sort test/check_queue test/check_stack test/check_hash_table

check_PROGRAMS = test/check_list test/check_sort test/check_queue test/check_stack test/check_hash_table

test_check_list_SOURCES = test/check_list.c
test_check_list_LDADD = libTHB.la

test_check_sort_SOURCES = test/check_sort.c
test_check_sort_LDADD = libTHB.la

test_check_queue_SOURCES = test/check_queue.c
test_check_queue_LDADD = libTHB.la

test_check_stack_SOURCES = test/check_stack.c
test_check_stack_LDADD = libTHB.la

test_check_hash_table_SOURCES = test/check_hash_table.c
test_check_hash_table_LDADD = libTHB.la

EXTRA_DIST = m4/NOTES
