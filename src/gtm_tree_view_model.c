#include "gtm_tree_view_model.h"

typedef struct 
{
    guint64 process_cnt;
} GtmTreeViewModelPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (GtmTreeViewModel, gtm_tree_view_model, GTK_TYPE_LIST_STORE)

static void
gtm_tree_view_model_dispose (GObject *object)
{
    G_OBJECT_CLASS (gtm_tree_view_model_parent_class)->dispose (object);
}

static void
gtm_tree_view_model_finalize (GObject *object)
{
    G_OBJECT_CLASS (gtm_tree_view_model_parent_class)->finalize (object);
}

static void
gtm_tree_view_model_class_init (GtmTreeViewModelClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->dispose = gtm_tree_view_model_dispose;
    object_class->finalize = gtm_tree_view_model_finalize;
}

static void
gtm_tree_view_model_init (GtmTreeViewModel *self)
{
    GType types[NUM_COLUMNS];

    types[PROCESS_NAME_COLUMN] = G_TYPE_STRING;
    types[USER_NAME_COLUMN] = G_TYPE_STRING;
    types[CPU_COLUMN] = G_TYPE_STRING;
    types[MEM_COLUMN] = G_TYPE_STRING;
    types[PID_COLUMN] = G_TYPE_INT;
    types[STATE_COLUMN] = G_TYPE_STRING;
    types[VIRT_COLUMN] = G_TYPE_UINT64;
    types[RES_COLUMN] = G_TYPE_UINT64;
    types[SHR_COLUMN] = G_TYPE_UINT64;
    types[TIME_COLUMN] = G_TYPE_STRING;
    types[PRI_COLUMN] = G_TYPE_INT;
    types[NICE_COLUMN] = G_TYPE_INT;
    types[WCHAN_COLUMN] = G_TYPE_STRING;
    types[PPID_COLUMN] = G_TYPE_INT;
    types[CMD_COLUMN] = G_TYPE_STRING;
    types[PR_RTIME_COLUMN] = G_TYPE_UINT64;
    types[PR_TOTAL_COLUMN] = G_TYPE_UINT64;
    
    gtk_list_store_set_column_types (GTK_LIST_STORE (self),
                                     NUM_COLUMNS,
                                     types);
}

void
gtm_update_process_list (GtmTreeViewModel *tree_view_model,
                         gint              mode)
{
    GtmTreeViewModelPrivate *priv;
    process_cell_model       pcells[GTM_PROC_NUM_LIMIT] = {0, };
    GtkTreeIter              iter;
    gint                     i;
    gint                     item_pid;
    gboolean                 found;
    gint                     pnum;
    guint64                  pr_rtime;
    guint64                  pr_total;

    priv = gtm_tree_view_model_get_instance_private (tree_view_model);
    pnum = gtm_get_process_cells (pcells, mode);

    for (i = 0; i < pnum; i++)
    {
        found = FALSE;
        gtk_tree_model_get_iter_first (GTK_TREE_MODEL (tree_view_model), &iter);
        
        do
        {
            gtk_tree_model_get (GTK_TREE_MODEL (tree_view_model), &iter, PID_COLUMN, &item_pid, -1);
            if (pcells[i].pid == item_pid)
            {
                found = TRUE;
                gtk_tree_model_get (GTK_TREE_MODEL (tree_view_model), &iter, PR_RTIME_COLUMN, &pr_rtime, -1);
                gtk_tree_model_get (GTK_TREE_MODEL (tree_view_model), &iter, PR_TOTAL_COLUMN, &pr_total, -1);
                gtm_get_process_cpu_info (pcells[i].rtime, pcells[i].total, pr_rtime, pr_total, pcells[i].cpu);
                gtk_list_store_set (GTK_LIST_STORE (tree_view_model), &iter,
                                    PROCESS_NAME_COLUMN, pcells[i].process_name,
                                    USER_NAME_COLUMN, pcells[i].user_name,
                                    CPU_COLUMN, pcells[i].cpu,
                                    MEM_COLUMN, pcells[i].mem,
                                    PID_COLUMN, pcells[i].pid,
                                    STATE_COLUMN, pcells[i].state, 
                                    VIRT_COLUMN, pcells[i].virt,
                                    RES_COLUMN, pcells[i].res,
                                    SHR_COLUMN, pcells[i].shr,
                                    TIME_COLUMN, pcells[i].time,
                                    PRI_COLUMN, pcells[i].pri,
                                    NICE_COLUMN, pcells[i].nice,
                                    WCHAN_COLUMN, pcells[i].wchan,
                                    PPID_COLUMN, pcells[i].ppid,
                                    CMD_COLUMN, pcells[i].cmd,
                                    PR_RTIME_COLUMN, pcells[i].rtime,
                                    PR_TOTAL_COLUMN, pcells[i].total,
                                    -1);
            }
        }
        while (!found && gtk_tree_model_iter_next (GTK_TREE_MODEL (tree_view_model), &iter));
        if (!found)
        {
            gtk_list_store_append (GTK_LIST_STORE (tree_view_model), &iter);
            gtk_list_store_set (GTK_LIST_STORE (tree_view_model), &iter,
                                PROCESS_NAME_COLUMN, pcells[i].process_name,
                                USER_NAME_COLUMN, pcells[i].user_name,
                                CPU_COLUMN, pcells[i].cpu,
                                MEM_COLUMN, pcells[i].mem,
                                PID_COLUMN, pcells[i].pid,
                                STATE_COLUMN, pcells[i].state,
                                VIRT_COLUMN, pcells[i].virt,
                                RES_COLUMN, pcells[i].res,
                                SHR_COLUMN, pcells[i].shr,
                                TIME_COLUMN, pcells[i].time,
                                PRI_COLUMN, pcells[i].pri,
                                NICE_COLUMN, pcells[i].nice,
                                WCHAN_COLUMN, pcells[i].wchan,
                                PPID_COLUMN, pcells[i].ppid,
                                CMD_COLUMN, pcells[i].cmd,
                                PR_RTIME_COLUMN, pcells[i].rtime,
                                PR_TOTAL_COLUMN, pcells[i].total,
                                -1);
            priv->process_cnt++;
        }
    }
    gtk_tree_model_get_iter_first (GTK_TREE_MODEL (tree_view_model), &iter);
    do
    {
        gtk_tree_model_get (GTK_TREE_MODEL (tree_view_model), &iter, PID_COLUMN, &item_pid, -1);
        found = FALSE;
        for (i = 0; i < pnum; i++)
        {
            if (pcells[i].pid == item_pid)
            {
                found = TRUE;
                break;
            }
        }
        if (!found)
        {
            gtk_list_store_remove (GTK_LIST_STORE (tree_view_model), &iter);
            priv->process_cnt--;
        }
    }
    while ((priv->process_cnt != pnum) && gtk_tree_model_iter_next (GTK_TREE_MODEL (tree_view_model), &iter));
}

void
gtm_set_process_model (GtmTreeViewModel *tree_view_model,
                       gint              mode)
{
    process_cell_model       pcells[GTM_PROC_NUM_LIMIT]; 
    gint                     i; 
    gint                     pnum;
    GtkTreeIter              iter;
    GtmTreeViewModelPrivate *priv;

    priv = gtm_tree_view_model_get_instance_private (tree_view_model);

    pnum = gtm_get_process_cells (pcells, mode);

    for (i = 0; i < pnum; i++)
    {
        gtk_list_store_append (GTK_LIST_STORE (tree_view_model), &iter);
        gtk_list_store_set (GTK_LIST_STORE (tree_view_model), &iter,
                            PROCESS_NAME_COLUMN, pcells[i].process_name,
                            USER_NAME_COLUMN, pcells[i].user_name,
                            CPU_COLUMN, pcells[i].cpu,
                            MEM_COLUMN, pcells[i].mem,
                            PID_COLUMN, pcells[i].pid,
                            STATE_COLUMN, pcells[i].state,
                            VIRT_COLUMN, pcells[i].virt,
                            RES_COLUMN, pcells[i].res,
                            SHR_COLUMN, pcells[i].shr,
                            TIME_COLUMN, pcells[i].time,
                            PRI_COLUMN, pcells[i].pri,
                            NICE_COLUMN, pcells[i].nice,
                            WCHAN_COLUMN, pcells[i].wchan,
                            PPID_COLUMN, pcells[i].ppid,
                            CMD_COLUMN, pcells[i].cmd,
                            PR_RTIME_COLUMN, pcells[i].rtime,
                            PR_TOTAL_COLUMN, pcells[i].total,
                            -1);
        priv->process_cnt++;
    }
}

GtmTreeViewModel*
gtm_tree_view_model_new (gint mode)
{
    GtmTreeViewModel        *self = g_object_new (GTM_TYPE_TREE_VIEW_MODEL, NULL);
    GtmTreeViewModelPrivate *priv;

    priv = gtm_tree_view_model_get_instance_private (self);
    priv->process_cnt = 0;

    gtm_set_process_model (self, mode);

    return self;
}
