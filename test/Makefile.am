AM_CFLAGS = -g3 -I../src -std=c11
AM_LDFLAGS = -static -g3 -L../src

check_PROGRAMS = check_list\
		 check_sort\
		 check_queue\
		 check_stack\
		 check_hash_table\
		 check_bst\
		 check_rbt

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

check_bst_SOURCES = check_bst.c
check_bst_LDADD = -lTHB

check_rbt_SOURCES = check_rbt.c
check_rbt_LDADD = -lTHB
