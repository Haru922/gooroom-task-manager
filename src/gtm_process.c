#include "gtm_process.h"

void
gtm_get_tasks_info (tasks_model *ptasks)
{
    glibtop_proclist   all_tasks;
    glibtop_proc_state pstate;
    pid_t             *pids;
    pid_t              pid;
    gint               i;

    pids = glibtop_get_proclist (&all_tasks, GLIBTOP_KERN_PROC_ALL, getuid ());

    ptasks->total_tasks = all_tasks.number;
    ptasks->running_tasks = 0;
    ptasks->sleeping_tasks = 0;
    ptasks->stopped_tasks = 0;
    ptasks->zombie_tasks = 0;

    for (i = 0; i < all_tasks.number; i++)
    {
        pid = pids[i];
        glibtop_get_proc_state (&pstate, pid);
        switch (pstate.state)
        {
            case GLIBTOP_PROCESS_RUNNING:
                ptasks->running_tasks++;
                break;
            case GLIBTOP_PROCESS_INTERRUPTIBLE: case GLIBTOP_PROCESS_UNINTERRUPTIBLE: case GLIBTOP_PROCESS_SWAPPING:
                ptasks->sleeping_tasks++;
                break;
            case GLIBTOP_PROCESS_STOPPED:
                ptasks->stopped_tasks++;
                break;
            case GLIBTOP_PROCESS_ZOMBIE:
                ptasks->zombie_tasks++;
                break;
            default:
                ptasks->sleeping_tasks++;
                break;
        }
    }
    g_free (pids);
}

void
gtm_get_running_user_name (char *user_name)
{
    glibtop_proclist    all_tasks;
    glibtop_proc_uid    puid;
    pid_t              *pids;
    pid_t               pid;
    struct passwd      *user;
    gint                i;

    pids = glibtop_get_proclist (&all_tasks, GLIBTOP_KERN_PROC_ALL, getuid ());
    for (i = 0; i < all_tasks.number; i++)
    {
        pid = pids[i];

        if (pid == getpid ())
        {
            glibtop_get_proc_uid (&puid, pid);
            user = getpwuid (puid.uid);
            g_strlcpy (user_name, user->pw_name, GTM_USER_NAME_LIMIT);
            break;
        }
    }
    g_free (pids);
}

void
gtm_get_process_cpu_info (guint64 cur_rtime,
                          guint64 cur_total,
                          guint64 pr_rtime,
                          guint64 pr_total,
                          char   *cpu)
{
    glibtop_cpu cpu_buf;
    guint64     diff;
    double      usage;

    glibtop_get_cpu (&cpu_buf);
    diff = cur_total - pr_total;
    if (diff)
    {
        usage = (cur_rtime - pr_rtime) * CPU_SCALE / diff;
    }
    else 
    {
        usage = diff * CPU_SCALE;
    }

    gtm_gdouble_to_str (usage, cpu);
    g_strlcat (cpu, " %", GTM_INFO_BUF);
}

gdouble
gtm_get_total_cpu_info (void)
{
    glibtop_cpu cpu_buf;

    glibtop_get_cpu (&cpu_buf);

    return (double) cpu_buf.user / (double) cpu_buf.total;
}

gdouble
gtm_get_total_memory_info (void)
{
    glibtop_mem mem_buf;

    glibtop_get_mem (&mem_buf);

    return (double) mem_buf.user / (double) mem_buf.total;
}

int
gtm_get_process_cells (process_cell_model *pcells,
                       gint                mode)
{
    glibtop_proclist    all_tasks;
    glibtop_proc_kernel pkernel;
    glibtop_proc_state  pstate;
    glibtop_proc_time   ptime;
    glibtop_proc_uid    puid;
    glibtop_proc_mem    pmem;
    glibtop_cpu         cpu_buf;
    glibtop_mem         mem_buf;
    struct passwd      *user;
    gchar             **command;
    gchar             **pname;
    pid_t              *pids;
    pid_t               pid;
    guint64             mem_diff;
    gint                pcount;
    gint                i;

    pids = glibtop_get_proclist (&all_tasks, GLIBTOP_KERN_PROC_ALL, getuid ());

    glibtop_get_cpu (&cpu_buf);
    glibtop_get_mem (&mem_buf);

    pcount = 0;
    for (i = 0; i < all_tasks.number; i++)
    {
        pid = pids[i];
        glibtop_get_proc_uid (&puid, pid);
        if (mode == GTM_ROOT)
        {
            if (puid.uid != GTM_ROOT)
            {
                continue;
            }
        }
        else if (mode == GTM_USER)
        {
            if (puid.uid == GTM_ROOT)
            {
                continue;
            }
        }
        glibtop_get_proc_mem (&pmem, pid);
        glibtop_get_proc_time (&ptime, pid);
        glibtop_get_proc_state (&pstate, pid);
        glibtop_get_proc_kernel (&pkernel, pid);
        user = getpwuid (puid.uid);
        g_strlcpy (pcells[pcount].user_name, user->pw_name, GTM_USER_NAME_LIMIT);
        gtm_get_process_cpu_info (0, 0, 0, 0, pcells[pcount].cpu);
        pcells[pcount].rtime = ptime.rtime;
        pcells[pcount].total = cpu_buf.total;

        mem_diff = pmem.resident - pmem.share;
        if (mem_diff < MIB)
        {
            gtm_gdouble_to_str (((mem_diff) / KIB), pcells[pcount].mem);
            g_strlcat (pcells[pcount].mem, " KiB", GTM_INFO_BUF);
        }
        else
        {
            gtm_gdouble_to_str (((mem_diff) / MIB), pcells[pcount].mem);
            g_strlcat (pcells[pcount].mem, " MiB", GTM_INFO_BUF);
        }

        pcells[pcount].pid = puid.pid;
        pcells[pcount].ppid = puid.ppid;
        switch (pstate.state)
        {
            case GLIBTOP_PROCESS_RUNNING:
                g_strlcpy (pcells[pcount].state, "RUNNING", GTM_INFO_BUF);
                break;
            case GLIBTOP_PROCESS_INTERRUPTIBLE: case GLIBTOP_PROCESS_UNINTERRUPTIBLE: case GLIBTOP_PROCESS_SWAPPING:
                g_strlcpy (pcells[pcount].state, "SLEEPING", GTM_INFO_BUF);
                break;
            case GLIBTOP_PROCESS_STOPPED:
                g_strlcpy (pcells[pcount].state, "STOPPED", GTM_INFO_BUF);
                break;
            case GLIBTOP_PROCESS_ZOMBIE:
                g_strlcpy (pcells[pcount].state, "ZOMBIE", GTM_INFO_BUF);
                break;
            default:
                g_strlcpy (pcells[pcount].state, "SLEEPING", GTM_INFO_BUF);
                break;
        }
        pcells[pcount].virt = pmem.vsize;
        pcells[pcount].res = pmem.resident;
        pcells[pcount].shr = pmem.share;
        gtm_gtime_to_str (((guint64) time (NULL) - ptime.start_time), pcells[pcount].time);
        pcells[pcount].pri = puid.priority;
        pcells[pcount].nice = puid.nice;
        g_strlcpy (pcells[pcount].wchan, pkernel.wchan, GTM_WCHAN_BUF);
        g_strlcpy (pcells[pcount].cmd, pstate.cmd, GTM_CMD_BUF);
        if (pstate.cmd != NULL)
        {
            command = g_strsplit (pstate.cmd, " ", 1);
            if (command[0] != NULL)
            {
                pname = g_strsplit (command[0], "/", -1);
                g_strlcpy (pcells[pcount].process_name, pname[0], GTM_PROCESS_NAME_LIMIT);
            }
        }
        pcount++;
    }
    g_strfreev (command);
    g_strfreev (pname);
    g_free (pids);

    return pcount;
}

void
gtm_get_target_pid_info (process_cell_model *pcell,
                         gint32              target_pid)
{
    process_cell_model pcells[GTM_PROC_NUM_LIMIT];
    gint               pnum;
    gint               i;

    pnum = gtm_get_process_cells (pcells, GTM_ALL);
    for (i = 0; i < pnum; i++)
    {
        if (pcells[i].pid == target_pid)
        {
            g_strlcpy (pcell->process_name, pcells[i].process_name, GTM_PROCESS_NAME_LIMIT);
            g_strlcpy (pcell->user_name, pcells[i].user_name, GTM_USER_NAME_LIMIT);
            g_strlcpy (pcell->cpu, pcells[i].cpu, GTM_INFO_BUF);
            g_strlcpy (pcell->mem, pcells[i].mem, GTM_INFO_BUF);
            pcell->pid = pcells[i].pid;
            g_strlcpy (pcell->state, pcells[i].state, GTM_INFO_BUF);
            pcell->virt = pcells[i].virt;
            pcell->res = pcells[i].res;
            pcell->shr = pcells[i].shr;
            g_strlcpy (pcell->time, pcells[i].time, GTM_INFO_BUF);
            pcell->pri = pcells[i].pri;
            pcell->nice = pcells[i].nice;
            g_strlcpy (pcell->wchan, pcells[i].wchan, GTM_WCHAN_BUF);
            pcell->ppid = pcells[i].ppid;
            g_strlcpy (pcell->cmd, pcells[i].cmd, GTM_CMD_BUF);
        }
    }
}
