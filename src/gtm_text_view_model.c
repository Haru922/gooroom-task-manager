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

    gtm_get_tasks_info (&tasks_info);
    gtk_text_buffer_get_iter_at_offset (GTK_TEXT_BUFFER (text_view_model), &iter, 0);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "Total Tasks: ", -1);
    gtm_guint_to_str (tasks_info.total_tasks, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\t", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tRunning Tasks: ", -1);
    gtm_guint_to_str (tasks_info.running_tasks, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\t", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tSleeping Tasks: ", -1);
    gtm_guint_to_str (tasks_info.sleeping_tasks, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\t", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tStopped Tasks: ", -1);
    gtm_guint_to_str (tasks_info.stopped_tasks, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\t", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tZombie Tasks: ", -1);
    gtm_guint_to_str (tasks_info.zombie_tasks, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
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
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tPROCESS NAME: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.process_name, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);
    
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tUSER NAME: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.user_name, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tCPU: ", -1);
    //gtm_gdouble_to_str (details_info.cpu, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.cpu, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tMEM: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.mem, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tPID: ", -1);
    gtm_gint_to_str (details_info.pid, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tSTATE: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.state, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tVIRT: ", -1);
    gtm_guint_to_str (details_info.virt, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tRES: ", -1);
    gtm_guint_to_str (details_info.res, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tSHR: ", -1);
    gtm_guint_to_str (details_info.shr, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tTIME+: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.time, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tPRI: ", -1);
    gtm_gint_to_str (details_info.pri, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tNICE: ", -1);
    gtm_gint_to_str (details_info.nice, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tWCHAN: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.wchan, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tPPID: ", -1);
    gtm_gint_to_str (details_info.ppid, tmp);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, tmp, -1, "left_mg", "bold", NULL);
    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\n", -1);

    gtk_text_buffer_insert (GTK_TEXT_BUFFER (text_view_model), &iter, "\tCMD: ", -1);
    gtk_text_buffer_insert_with_tags_by_name (GTK_TEXT_BUFFER (text_view_model), &iter, details_info.cmd, -1, "left_mg", "bold", NULL);
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
    gtk_text_buffer_create_tag (self, "left_mg", "left_margin", 80, NULL);
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
