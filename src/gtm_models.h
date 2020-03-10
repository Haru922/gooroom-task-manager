#ifndef _GTM_MODEL_H_
#define _GTM_MODEL_H_

#include <gtk/gtk.h>

#include "gtm_constants.h"

G_BEGIN_DECLS

typedef struct _process_cell_model
{
    gchar process_name[GTM_PROCESS_NAME_LIMIT];
    gchar user_name[GTM_PROCESS_NAME_LIMIT];
    gchar cpu[GTM_INFO_BUF];
    gchar mem[GTM_INFO_BUF];
    gint32 pid;
    gchar state[GTM_INFO_BUF];
    guint64 virt;
    guint64 res;
    guint64 shr;
    gchar time[GTM_INFO_BUF];
    gint pri;
    gint nice;
    gchar wchan[GTM_INFO_BUF];
    gint ppid;
    gchar cmd[GTM_INFO_BUF];
    guint64 rtime;
    guint64 total;
} process_cell_model;

typedef struct _tasks_model
{
    guint64 total_tasks;
    guint64 running_tasks;
    guint64 sleeping_tasks;
    guint64 stopped_tasks;
    guint64 zombie_tasks;
} tasks_model;

G_END_DECLS

#endif
