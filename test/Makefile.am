AM_CFLAGS = -g3 -I../src -std=c99
AM_LDFLAGS = -static -g3 -L../src

check_PROGRAMS = check_list\
		 check_sort\
		 check_queue\
		 check_stack\
		 check_hash_table\
		 check_bst

TESTS = $(check_PROGRAMS)

check_list_SOURCES = check_list.c
check_list_LDADD = -lal

check_sort_SOURCES = check_sort.c
check_sort_LDADD = -lal

check_queue_SOURCES = check_queue.c
check_queue_LDADD = -lal

check_stack_SOURCES = check_stack.c
check_stack_LDADD = -lal

check_hash_table_SOURCES = check_hash_table.c
check_hash_table_LDADD = -lal

check_bst_SOURCES = check_bst.c
check_bst_LDADD = -lal
