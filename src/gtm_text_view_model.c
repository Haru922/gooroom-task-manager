#include "gtm_text_view_model.h"

typedef struct
{
    gint flags;
} GtmTextViewModelPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (GtmTextViewModel, gtm_text_view_model, GTK_TYPE_TEXT_BUFFER)

static void
gtm_text_view_model_dispose (GObject *object)
{
    G_OBJECT_CLASS (gtm_text_view_model_parent_class)->dispose (object);
}

static void
gtm_text_view_model_finalize (GObject *object)
{
    G_OBJECT_CLASS (gtm_text_view_model_parent_class)->finalize (object);
}

static void
gtm_text_view_model_class_init (GtmTextViewModelClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);

    object_class->dispose = gtm_text_view_model_dispose;
    object_class->finalize = gtm_text_view_model_finalize;
}

static void
gtm_text_view_model_init (GtmTextViewModel *self)
{
}

void
gtm_get_tasks_model_info (GtmTextViewModel *text_view_model)
{
    GtkTextIter iter;
    tasks_model tasks_info;
    char        tmp[GTM_INFO_BUF];
    char        user_name[GTM_USER_NAME_LIMIT];

    gtm_get_tasks_info (&tasks_info);
    gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (text_view_model), &iter, 0);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "Executed by \"", -1);
    gtm_get_running_user_name (user_name);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, user_name, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\".\nTotal Cpu Usage: ", -1);
    gtm_gdouble_to_str ((gtm_get_total_cpu_info () * 100), tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, " %,    Total Memory Usage: ", -1);
    gtm_gdouble_to_str ((gtm_get_total_memory_info () * 100), tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, " %\nTotal Tasks: ", -1);
    gtm_guint_to_str (tasks_info.total_tasks, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, ",    Running Tasks: ", -1);
    gtm_guint_to_str (tasks_info.running_tasks, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, ",    Sleeping Tasks: ", -1);
    gtm_guint_to_str (tasks_info.sleeping_tasks, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, ",    Stopped Tasks: ", -1);
    gtm_guint_to_str (tasks_info.stopped_tasks, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, ",    Zombie Tasks: ", -1);
    gtm_guint_to_str (tasks_info.zombie_tasks, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);
}

void
gtm_get_details_model_info (GtmTextViewModel *text_view_model,
                            gint32            target_pid)
{
    GtkTextIter        iter;
    process_cell_model details_info;
    char               tmp[GTM_INFO_BUF];

    gtm_get_target_pid_info (&details_info, target_pid);
    gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (text_view_model), &iter, 0);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "    PROCESS NAME: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.process_name, -1, "bold", NULL);
    
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    USER NAME: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.user_name, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    CPU: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.cpu, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    MEM: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.mem, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    PID: ", -1);
    gtm_gint_to_str (details_info.pid, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    STATE: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.state, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    VIRT: ", -1);
    gtm_guint_to_str (details_info.virt, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    RES: ", -1);
    gtm_guint_to_str (details_info.res, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    SHR: ", -1);
    gtm_guint_to_str (details_info.shr, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    TIME+: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.time, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    PRI: ", -1);
    gtm_gint_to_str (details_info.pri, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    NICE: ", -1);
    gtm_gint_to_str (details_info.nice, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    WCHAN: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.wchan, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    PPID: ", -1);
    gtm_gint_to_str (details_info.ppid, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "bold", NULL);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n    CMD: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.cmd, -1, "bold", NULL);
}

void
gtm_update_tasks_text_view_model (GtmTextViewModel *text_view_model)
{
    GtkTextIter start_iter;
    GtkTextIter end_iter;

    gtk_text_buffer_get_start_iter (GTK_TEXT_BUFFER (text_view_model), &start_iter);
    gtk_text_buffer_get_end_iter (GTK_TEXT_BUFFER (text_view_model), &end_iter);
    gtk_text_buffer_delete (GTK_TEXT_BUFFER (text_view_model), &start_iter, &end_iter);
    gtm_get_tasks_model_info (text_view_model);
}

GtmTextViewModel*
gtm_text_view_model_new (GtkTextView *view,
                         gint         flags,
                         gint32       target_pid)
{
    GtmTextViewModel *self = g_object_new (GTM_TYPE_TEXT_VIEW_MODEL, NULL);
   
    self = gtk_text_view_get_buffer (view);
    gtk_text_buffer_create_tag (self, "bold", "weight", PANGO_WEIGHT_BOLD, NULL);
    if (flags == GTM_TASKS_INFO)
    {
        gtm_get_tasks_model_info (self);
    }
    else
    {
        gtm_get_details_model_info (self, target_pid);
    }

    return self;
}
