#ifndef _GTM_CONSTANTS_
#define _GTM_CONSTANTS_

G_BEGIN_DECLS

#define GTM_WINDOW_TIME_INTERVAL 1000
#define GTM_WINDOW_WIDTH         1330
#define GTM_WINDOW_HEIGHT         600
#define GTM_TREE_VIEWS              2 
#define GTM_TREE_VIEW_COLUMNS       3

#define GTM_FIRST_COLUMN            0
#define GTM_SECOND_COLUMN           1
#define GTM_THIRD_COLUMN            2

#define GTM_UNSET                  -1

#define GTM_ACTION_BUTTONS          5

#define GTM_PROC_NUM_LIMIT       9999

#define GTM_PROCESS_NAME_LIMIT     50
#define GTM_USER_NAME_LIMIT        50
#define GTM_WCHAN_BUF              50
#define GTM_CMD_BUF                50
#define GTM_INFO_BUF               50

#define GTM_ROOT                    0
#define GTM_USER                    1
#define GTM_ALL                     2

#define GTM_TASKS_INFO              0
#define GTM_DETAILS_INFO            1

#define GTM_PRECISION_VAL         100

#define N_CPUS                      8
#define CPU_SCALE                 100
#define MIB           (1024*1024*1.0) 
#define KIB                (1024*1.0) 


enum _column_num
{
    PROCESS_NAME_COLUMN = 0, USER_NAME_COLUMN, CPU_COLUMN,
    MEM_COLUMN, PID_COLUMN, STATE_COLUMN, VIRT_COLUMN,
    RES_COLUMN, SHR_COLUMN, TIME_COLUMN, PRI_COLUMN,
    NICE_COLUMN, WCHAN_COLUMN, PPID_COLUMN, CMD_COLUMN,
    PR_RTIME_COLUMN, PR_TOTAL_COLUMN,
    NUM_COLUMNS
};

static char* column_names[] =
{
    "PROCESS NAME", "USER NAME", "CPU",
    "MEM", "PID", "STATE", "VIRT",
    "RES", "SHR", "TIME+", "PRI",
    "NICE", "WCHAN", "PPID", "CMD",
};

enum _signal_num
{
    KILL = 0, TERM,
    STOP, CONTINUE,
    DETAILS, NUM_ACTIONS
};

enum _tasks_num
{
    TOTAL_TASKS = 0, RUNNING_TASKS,
    SLEEPING_TASKS, STOPPED_TASKS,
    ZOMBIE_TASKS, TASKS_NUM
};

G_END_DECLS

#endif
