#ifndef _GTM_PROCESS_H_
#define _GTM_PROCESS_H_

#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <pwd.h>

#include <gtk/gtk.h>
#include <glibtop/proclist.h>
#include <glibtop/procstate.h>
#include <glibtop/procuid.h>
#include <glibtop/procmem.h>
#include <glibtop/proctime.h>
#include <glibtop/prockernel.h>
#include <glibtop/cpu.h>
#include <glibtop/mem.h>

#include "gtm_constants.h"
#include "gtm_models.h"
#include "gtm_common_util.h"

G_BEGIN_DECLS

void gtm_get_tasks_info (tasks_model *ptasks);
void gtm_get_target_pid_info (process_cell_model *pcell, gint32 target_pid);
void gtm_get_cpu_info (guint64 cur_rtime, guint64 cur_total, guint64 pr_rtime, guint64 pr_total, char *cpu);
int  gtm_get_process_cells (process_cell_model *pcells, gint mode);

G_END_DECLS

#endif
