AM_CFLAGS = -g3 --std=c99
AM_LDFLAGS = -g3

check_PROGRAMS = check_list\
		 check_sort\
		 check_queue\
		 check_stack\
		 check_hash_table

TESTS = $(check_PROGRAMS)

check_list_SOURCES = check_list.c
check_list_LDADD = -lTHB

check_sort_SOURCES = check_sort.c
check_sort_LDADD = -lTHB

check_queue_SOURCES = check_queue.c
check_queue_LDADD = -lTHB

check_stack_SOURCES = check_stack.c
check_stack_LDADD = -lTHB

check_hash_table_SOURCES = check_hash_table.c
check_hash_table_LDADD = -lTHB
