#include "gtm_window.h"

typedef struct 
{
    GtkWidget        *root_box_scrolled_window;
    GtkWidget        *user_box_scrolled_window;
    GtkWidget        *search_entry;
    GtkWidget        *root_process_list;
    GtkWidget        *user_process_list;
    GtkWidget        *root_column1;
    GtkWidget        *root_column2;
    GtkWidget        *root_column3;
    GtkWidget        *user_column1;
    GtkWidget        *user_column2;
    GtkWidget        *user_column3;
    GtkWidget        *root_kill_button;
    GtkWidget        *root_term_button;
    GtkWidget        *root_stop_button;
    GtkWidget        *root_continue_button;
    GtkWidget        *root_details_button;
    GtkWidget        *user_kill_button;
    GtkWidget        *user_term_button;
    GtkWidget        *user_stop_button;
    GtkWidget        *user_continue_button;
    GtkWidget        *user_details_button;
    GtkWidget        *summary_box;
    GtkWidget        *tasks_summary;
    GtmTreeViewModel *root_process_list_view_model;
    GtmTreeViewModel *user_process_list_view_model;
    GtmTextViewModel *tasks_text_view_model;
    gint              root_custom_columns[GTM_TREE_VIEW_COLUMNS];
    gint              user_custom_columns[GTM_TREE_VIEW_COLUMNS];
    gulong            root_button_handlers[GTM_ACTION_BUTTONS];
    gulong            user_button_handlers[GTM_ACTION_BUTTONS];
} GtmWindowPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(GtmWindow, gtm_window, GTK_TYPE_APPLICATION_WINDOW);

void
root_first_column_changed (GtkComboBoxText *root_column,
                           gpointer         win)
{
    GtmWindowPrivate *priv;
    gchar            *selection;
    gint              column_id;

    priv = gtm_window_get_instance_private (win);

    selection = gtk_combo_box_text_get_active_text (root_column);
    column_id = gtm_get_matching_column (selection);

    if (column_id != priv->root_custom_columns[GTM_SECOND_COLUMN]
        && column_id != priv->root_custom_columns[GTM_THIRD_COLUMN])
    {
        priv->root_custom_columns[GTM_FIRST_COLUMN] = column_id;
        gtm_rebuild_root_process_list (win);
    }
    g_free (selection);
}

void
root_second_column_changed (GtkComboBoxText *root_column,
                            gpointer         win)
{
    GtmWindowPrivate *priv;
    gchar            *selection;
    gint              column_id;

    priv = gtm_window_get_instance_private (win);

    selection = gtk_combo_box_text_get_active_text (root_column);
    column_id = gtm_get_matching_column (selection);
    
    if (column_id != priv->root_custom_columns[GTM_FIRST_COLUMN]
        && column_id != priv->root_custom_columns[GTM_THIRD_COLUMN])
    {
        priv->root_custom_columns[GTM_SECOND_COLUMN] = column_id;
        gtm_rebuild_root_process_list (win);
    }
    g_free (selection);
}

void
root_third_column_changed (GtkComboBoxText *root_column,
                           gpointer         win)
{
    GtmWindowPrivate *priv;
    gchar            *selection;
    gint              column_id;

    priv = gtm_window_get_instance_private (win);

    selection = gtk_combo_box_text_get_active_text (root_column);
    column_id = gtm_get_matching_column (selection);
    
    if (column_id != priv->root_custom_columns[GTM_FIRST_COLUMN]
        && column_id != priv->root_custom_columns[GTM_SECOND_COLUMN])
    {
        priv->root_custom_columns[GTM_THIRD_COLUMN] = column_id;
        gtm_rebuild_root_process_list (win);
    }
    g_free (selection);
}

void
user_first_column_changed (GtkComboBoxText *user_column,
                           gpointer         win)
{
    GtmWindowPrivate *priv;
    gchar            *selection;
    gint              column_id;

    priv = gtm_window_get_instance_private (win);

    selection = gtk_combo_box_text_get_active_text (user_column);
    column_id = gtm_get_matching_column (selection);

    if (column_id != priv->user_custom_columns[GTM_SECOND_COLUMN]
        && column_id != priv->user_custom_columns[GTM_THIRD_COLUMN])
    {
        priv->user_custom_columns[GTM_FIRST_COLUMN] = column_id;
        gtm_rebuild_user_process_list (win);
    }
    g_free (selection);
}

void
user_second_column_changed (GtkComboBoxText *user_column,
                            gpointer         win)
{
    GtmWindowPrivate *priv;
    gchar            *selection;
    gint              column_id;

    priv = gtm_window_get_instance_private (win);

    selection = gtk_combo_box_text_get_active_text (user_column);
    column_id = gtm_get_matching_column (selection);

    if (column_id != priv->user_custom_columns[GTM_FIRST_COLUMN]
        && column_id != priv->user_custom_columns[GTM_THIRD_COLUMN])
    {
        priv->user_custom_columns[GTM_SECOND_COLUMN] = column_id;
        gtm_rebuild_user_process_list (win);
    }
    g_free (selection);
}

void
user_third_column_changed (GtkComboBoxText *user_column,
                           gpointer         win)
{
    GtmWindowPrivate *priv;
    gchar            *selection;
    gint              column_id;

    priv = gtm_window_get_instance_private (win);

    selection = gtk_combo_box_text_get_active_text (user_column);
    column_id = gtm_get_matching_column (selection);

    if (column_id != priv->user_custom_columns[GTM_FIRST_COLUMN]
        && column_id != priv->user_custom_columns[GTM_SECOND_COLUMN])
    {
        priv->user_custom_columns[GTM_THIRD_COLUMN] = column_id;
        gtm_rebuild_user_process_list (win);
    }
    g_free (selection);
}

void
kill_button_clicked (GtkButton *kill_button,
                     gpointer process_list)
{
    gint32            target_pid;
    GtkTreeSelection *selection;
    GtkTreeModel     *process_model;
    GtkTreeIter       iter;

    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (process_list));
    if (gtk_tree_selection_get_selected (selection, &process_model, &iter))
    {
        gtk_tree_model_get (process_model, &iter, PID_COLUMN, &target_pid, -1);
        kill (target_pid, SIGKILL);
    }
}

void
term_button_clicked (GtkButton *term_button,
                     gpointer process_list)
{
    gint32            target_pid;
    GtkTreeSelection *selection;
    GtkTreeModel     *process_model;
    GtkTreeIter       iter;

    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (process_list));
    if (gtk_tree_selection_get_selected (selection, &process_model, &iter))
    {
        gtk_tree_model_get (process_model, &iter, PID_COLUMN, &target_pid, -1);
        kill (target_pid, SIGTERM);
    }
}

void
stop_button_clicked (GtkButton *stop_button,
                     gpointer process_list)
{
    gint32            target_pid;
    GtkTreeSelection *selection;
    GtkTreeModel     *process_model;
    GtkTreeIter       iter;

    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (process_list));
    if (gtk_tree_selection_get_selected (selection, &process_model, &iter))
    {
        gtk_tree_model_get (process_model, &iter, PID_COLUMN, &target_pid, -1);
        kill (target_pid, SIGSTOP);
    }
}

void
continue_button_clicked (GtkButton *continue_button,
                         gpointer process_list)
{
    gint32            target_pid;
    GtkTreeSelection *selection;
    GtkTreeModel     *process_model;
    GtkTreeIter       iter;

    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (process_list));
    if (gtk_tree_selection_get_selected (selection, &process_model, &iter))
    {
        gtk_tree_model_get (process_model, &iter, PID_COLUMN, &target_pid, -1);
        kill (target_pid, SIGCONT);
    }
}

void
details_button_clicked (GtkButton *details_button,
                        gpointer process_list)
{
    gint32            target_pid;
    GtkTreeSelection *selection;
    GtkTreeModel     *process_model;
    GtkTreeIter       iter;
    GtkWidget        *details_dialog;
    GtkWidget        *details_content;
    GtkWidget        *details_text_view;
    GtmTextViewModel *details_text_view_model;

    selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (process_list));
    if (gtk_tree_selection_get_selected (selection, &process_model, &iter))
    {
        gtk_tree_model_get (process_model, &iter, PID_COLUMN, &target_pid, -1);
        details_dialog = gtk_dialog_new ();
        details_content = gtk_dialog_get_content_area (GTK_DIALOG (details_dialog));
        details_text_view = gtk_text_view_new ();
        gtk_text_view_set_editable (GTK_TEXT_VIEW (details_text_view), FALSE);
        gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (details_text_view), FALSE);
        details_text_view_model = gtm_text_view_model_new (GTK_TEXT_VIEW (details_text_view), GTM_DETAILS_INFO, target_pid);
        gtk_box_pack_start (GTK_BOX (details_content), details_text_view, TRUE, TRUE, 0);
        gtk_widget_show_all (GTK_WIDGET (details_dialog));
        gtk_dialog_run (GTK_DIALOG (details_dialog));
    }
    gtk_widget_destroy (details_dialog);
}

void
connect_root_button_signal_handlers (GtmWindow *win)
{
    GtmWindowPrivate *priv;

    priv = gtm_window_get_instance_private (win);

    priv->root_button_handlers[KILL] = g_signal_connect (priv->root_kill_button, "clicked", G_CALLBACK (kill_button_clicked), GTK_TREE_VIEW (priv->root_process_list));
    priv->root_button_handlers[TERM] = g_signal_connect (priv->root_term_button, "clicked", G_CALLBACK (term_button_clicked), GTK_TREE_VIEW (priv->root_process_list));
    priv->root_button_handlers[STOP] = g_signal_connect (priv->root_stop_button, "clicked", G_CALLBACK (stop_button_clicked), GTK_TREE_VIEW (priv->root_process_list));
    priv->root_button_handlers[CONTINUE] = g_signal_connect (priv->root_continue_button, "clicked", G_CALLBACK (continue_button_clicked), GTK_TREE_VIEW (priv->root_process_list));
    priv->root_button_handlers[DETAILS] = g_signal_connect (priv->root_details_button, "clicked", G_CALLBACK (details_button_clicked), GTK_TREE_VIEW (priv->root_process_list));
}

void
disconnect_root_button_signal_handlers (GtmWindow *win)
{
    GtmWindowPrivate *priv;

    priv = gtm_window_get_instance_private (win);

    g_signal_handler_disconnect (priv->root_kill_button, priv->root_button_handlers[KILL]);
    g_signal_handler_disconnect (priv->root_term_button, priv->root_button_handlers[TERM]);
    g_signal_handler_disconnect (priv->root_stop_button, priv->root_button_handlers[STOP]);
    g_signal_handler_disconnect (priv->root_continue_button, priv->root_button_handlers[CONTINUE]);
    g_signal_handler_disconnect (priv->root_details_button, priv->root_button_handlers[DETAILS]);
}

void
connect_user_button_signal_handlers (GtmWindow *win)
{
    GtmWindowPrivate *priv;

    priv = gtm_window_get_instance_private (win);

    priv->user_button_handlers[KILL] = g_signal_connect (priv->user_kill_button, "clicked", G_CALLBACK (kill_button_clicked), priv->user_process_list);
    priv->user_button_handlers[TERM] = g_signal_connect (priv->user_term_button, "clicked", G_CALLBACK (term_button_clicked), priv->user_process_list);
    priv->user_button_handlers[STOP] = g_signal_connect (priv->user_stop_button, "clicked", G_CALLBACK (stop_button_clicked), priv->user_process_list);
    priv->user_button_handlers[CONTINUE] = g_signal_connect (priv->user_continue_button, "clicked", G_CALLBACK (continue_button_clicked), priv->user_process_list);
    priv->user_button_handlers[DETAILS] = g_signal_connect (priv->user_details_button, "clicked", G_CALLBACK (details_button_clicked), priv->user_process_list);
}

void
disconnect_user_button_signal_handlers (GtmWindow *win)
{
    GtmWindowPrivate *priv;

    priv = gtm_window_get_instance_private (win);

    g_signal_handler_disconnect (priv->user_kill_button, priv->user_button_handlers[KILL]);
    g_signal_handler_disconnect (priv->user_term_button, priv->user_button_handlers[TERM]);
    g_signal_handler_disconnect (priv->user_stop_button, priv->user_button_handlers[STOP]);
    g_signal_handler_disconnect (priv->user_continue_button, priv->user_button_handlers[CONTINUE]);
    g_signal_handler_disconnect (priv->user_details_button, priv->user_button_handlers[DETAILS]);
}

void
gtm_build_root_process_list (GtmWindow *win)
{
    GtmWindowPrivate  *priv;
    GtkCellRenderer   *renderer;
    GtkTreeViewColumn *process_list_columns[NUM_COLUMNS];
    gint               column_id;

    priv = gtm_window_get_instance_private (win);
    priv->root_process_list = gtk_tree_view_new ();

    for (column_id = PROCESS_NAME_COLUMN; column_id < NUM_COLUMNS; column_id++)
    {
        renderer = gtk_cell_renderer_text_new ();
        process_list_columns[column_id] = gtk_tree_view_column_new_with_attributes (column_names[column_id],
                                                                                    renderer,
                                                                                    "text",
                                                                                    column_id,
                                                                                    NULL);
        gtk_tree_view_column_set_sort_column_id (process_list_columns[column_id], column_id);
    }
    gtk_tree_view_append_column (GTK_TREE_VIEW (priv->root_process_list), process_list_columns[PROCESS_NAME_COLUMN]);
    gtk_tree_view_append_column (GTK_TREE_VIEW (priv->root_process_list), process_list_columns[USER_NAME_COLUMN]);
    gtk_tree_view_append_column (GTK_TREE_VIEW (priv->root_process_list), process_list_columns[priv->root_custom_columns[GTM_FIRST_COLUMN]]);
    gtk_tree_view_append_column (GTK_TREE_VIEW (priv->root_process_list), process_list_columns[priv->root_custom_columns[GTM_SECOND_COLUMN]]);
    gtk_tree_view_append_column (GTK_TREE_VIEW (priv->root_process_list), process_list_columns[priv->root_custom_columns[GTM_THIRD_COLUMN]]);
    gtk_tree_view_set_activate_on_single_click (GTK_TREE_VIEW (priv->root_process_list), TRUE);
    gtk_tree_view_set_search_entry (GTK_TREE_VIEW (priv->root_process_list), GTK_ENTRY (priv->search_entry));
}

void
gtm_build_user_process_list (GtmWindow *win)
{
    GtmWindowPrivate  *priv;
    GtkCellRenderer   *renderer;
    GtkTreeViewColumn *process_list_columns[NUM_COLUMNS];
    gint               column_id;

    priv = gtm_window_get_instance_private (win);
    priv->user_process_list = gtk_tree_view_new ();

    for (column_id = PROCESS_NAME_COLUMN; column_id < NUM_COLUMNS; column_id++)
    {
        renderer = gtk_cell_renderer_text_new ();
        process_list_columns[column_id] = gtk_tree_view_column_new_with_attributes (column_names[column_id],
                                                                                    renderer,
                                                                                    "text",
                                                                                    column_id,
                                                                                    NULL);
        gtk_tree_view_column_set_sort_column_id (process_list_columns[column_id], column_id);
    }
    gtk_tree_view_append_column (GTK_TREE_VIEW (priv->user_process_list), process_list_columns[PROCESS_NAME_COLUMN]);
    gtk_tree_view_append_column (GTK_TREE_VIEW (priv->user_process_list), process_list_columns[USER_NAME_COLUMN]);
    gtk_tree_view_append_column (GTK_TREE_VIEW (priv->user_process_list), process_list_columns[priv->user_custom_columns[GTM_FIRST_COLUMN]]);
    gtk_tree_view_append_column (GTK_TREE_VIEW (priv->user_process_list), process_list_columns[priv->user_custom_columns[GTM_SECOND_COLUMN]]);
    gtk_tree_view_append_column (GTK_TREE_VIEW (priv->user_process_list), process_list_columns[priv->user_custom_columns[GTM_THIRD_COLUMN]]);
    gtk_tree_view_set_activate_on_single_click (GTK_TREE_VIEW (priv->user_process_list), TRUE);
    gtk_tree_view_set_search_entry (GTK_TREE_VIEW (priv->user_process_list), GTK_ENTRY (priv->search_entry));
}

void
gtm_rebuild_root_process_list (GtmWindow *win)
{
    GtmWindowPrivate *priv;
    
    priv = gtm_window_get_instance_private (win);

    disconnect_root_button_signal_handlers (win);
    gtk_widget_destroy (priv->root_process_list);
    gtm_build_root_process_list (win);
    gtk_tree_view_set_model (GTK_TREE_VIEW (priv->root_process_list), GTK_TREE_MODEL (priv->root_process_list_view_model));
    connect_root_button_signal_handlers (win);
    gtk_container_add (GTK_CONTAINER (priv->root_box_scrolled_window), priv->root_process_list);

    gtk_widget_show_all (GTK_WIDGET (win));
}

void
gtm_rebuild_user_process_list (GtmWindow *win)
{
    GtmWindowPrivate *priv;

    priv = gtm_window_get_instance_private (win);

    disconnect_user_button_signal_handlers (win);
    gtk_widget_destroy (priv->user_process_list);
    gtm_build_user_process_list (win);
    gtk_tree_view_set_model (GTK_TREE_VIEW (priv->user_process_list), GTK_TREE_MODEL (priv->user_process_list_view_model));
    connect_user_button_signal_handlers (win);
    gtk_container_add (GTK_CONTAINER (priv->user_box_scrolled_window), priv->user_process_list);

    gtk_widget_show_all (GTK_WIDGET (win));
}

void
renew_all (GtmWindow *win)
{
    GtmWindowPrivate *priv;
    GtkTreeSelection *selection[2];
    GtkTreeModel     *process_model[2];
    GtkTreePath      *selected_path[2] = { NULL, NULL };
    GtkTreeIter       iter[2];

    priv = gtm_window_get_instance_private (win);
    
    selection[GTM_ROOT] = gtk_tree_view_get_selection (GTK_TREE_VIEW (priv->root_process_list));
    if (gtk_tree_selection_get_selected (selection[GTM_ROOT], &process_model[GTM_ROOT], &iter[GTM_ROOT]))
    {
        selected_path[GTM_ROOT] = gtk_tree_model_get_path (process_model[GTM_ROOT], &iter[GTM_ROOT]);
    }
    gtm_update_process_list (priv->root_process_list_view_model, GTM_ROOT);
    if (selected_path[GTM_ROOT] != NULL)
    {
        gtk_tree_selection_select_path (selection[GTM_ROOT], selected_path[GTM_ROOT]);
        gtk_tree_path_free (selected_path[GTM_ROOT]);
    }

    selection[GTM_USER] = gtk_tree_view_get_selection (GTK_TREE_VIEW (priv->user_process_list));
    if (gtk_tree_selection_get_selected (selection[GTM_USER], &process_model[GTM_USER], &iter[GTM_USER]))
    {
        selected_path[GTM_USER] = gtk_tree_model_get_path (process_model[GTM_USER], &iter[GTM_USER]);
    }
    gtm_update_process_list (priv->user_process_list_view_model, GTM_USER);
    if (selected_path[GTM_USER] != NULL)
    {
        gtk_tree_selection_select_path (selection[GTM_USER], selected_path[GTM_USER]);
        gtk_tree_path_free (selected_path[GTM_USER]);
    }

    gtm_update_tasks_text_view_model (priv->tasks_text_view_model);
    gtk_widget_show_all (GTK_WIDGET (win));
}

static void
gtm_window_constructed (GtmWindow *win)
{
    g_timeout_add (GTM_WINDOW_TIME_INTERVAL, G_SOURCE_FUNC (renew_all), win);
    G_OBJECT_CLASS (gtm_window_parent_class)->constructed (win);
}

static void
gtm_window_init (GtmWindow *win)
{
    GtmWindowPrivate *priv;
    gint              default_custom_columns[GTM_TREE_VIEW_COLUMNS] = { CPU_COLUMN, MEM_COLUMN, PID_COLUMN };
    gint              column_iter;

    gtk_widget_init_template (GTK_WIDGET (win));

    priv = gtm_window_get_instance_private (win);
    for (column_iter = GTM_FIRST_COLUMN; column_iter < GTM_TREE_VIEW_COLUMNS; column_iter++)
    {
        priv->root_custom_columns[column_iter] = default_custom_columns[column_iter];
        priv->user_custom_columns[column_iter] = default_custom_columns[column_iter];
    }

    gtm_build_user_process_list (win);
    gtm_build_root_process_list (win);
    priv->root_process_list_view_model = gtm_tree_view_model_new (GTM_ROOT);
    priv->user_process_list_view_model = gtm_tree_view_model_new (GTM_USER);
    gtk_tree_view_set_model (GTK_TREE_VIEW (priv->root_process_list), GTK_TREE_MODEL (priv->root_process_list_view_model));
    gtk_tree_view_set_model (GTK_TREE_VIEW (priv->user_process_list), GTK_TREE_MODEL (priv->user_process_list_view_model));
    priv->tasks_summary = gtk_text_view_new ();
    gtk_text_view_set_editable (GTK_TEXT_VIEW (priv->tasks_summary), FALSE);
    gtk_text_view_set_cursor_visible (GTK_TEXT_VIEW (priv->tasks_summary), FALSE);
    priv->tasks_text_view_model = gtm_text_view_model_new (GTK_TEXT_VIEW (priv->tasks_summary), GTM_TASKS_INFO, -1);
    gtk_text_view_set_justification (GTK_TEXT_VIEW (priv->tasks_summary), GTK_JUSTIFY_CENTER);

    gtk_container_add (GTK_CONTAINER (priv->root_box_scrolled_window), priv->root_process_list);
    gtk_container_add (GTK_CONTAINER (priv->user_box_scrolled_window), priv->user_process_list);
    gtk_box_pack_end (GTK_BOX (priv->summary_box), priv->tasks_summary, TRUE, TRUE, 1);

    connect_root_button_signal_handlers (win);
    connect_user_button_signal_handlers (win);

    gtk_combo_box_set_active (GTK_COMBO_BOX (priv->root_column1), 0);
    gtk_combo_box_set_active (GTK_COMBO_BOX (priv->root_column2), 1);
    gtk_combo_box_set_active (GTK_COMBO_BOX (priv->root_column3), 2);
    gtk_combo_box_set_active (GTK_COMBO_BOX (priv->user_column1), 0);
    gtk_combo_box_set_active (GTK_COMBO_BOX (priv->user_column2), 1);
    gtk_combo_box_set_active (GTK_COMBO_BOX (priv->user_column3), 2);

    g_signal_connect (priv->root_column1, "changed", G_CALLBACK (root_first_column_changed), win);
    g_signal_connect (priv->root_column2, "changed", G_CALLBACK (root_second_column_changed), win);
    g_signal_connect (priv->root_column3, "changed", G_CALLBACK (root_third_column_changed), win);
    g_signal_connect (priv->user_column1, "changed", G_CALLBACK (user_first_column_changed), win);
    g_signal_connect (priv->user_column2, "changed", G_CALLBACK (user_second_column_changed), win);
    g_signal_connect (priv->user_column3, "changed", G_CALLBACK (user_third_column_changed), win);

    gtk_window_set_default_size (GTK_WINDOW (win), GTM_WINDOW_WIDTH, GTM_WINDOW_HEIGHT);
    gtk_widget_show_all (GTK_WIDGET (win));
}

static void
gtm_window_dispose (GObject *object)
{
    G_OBJECT_CLASS (gtm_window_parent_class)->dispose (object);
}

static void
gtm_window_finalize (GObject *object)
{
    G_OBJECT_CLASS (gtm_window_parent_class)->finalize (object);
}


static void
gtm_window_class_init (GtmWindowClass *klass)
{
    GObjectClass *object_class = G_OBJECT_CLASS (klass);
    
    object_class->constructed = gtm_window_constructed;
    object_class->dispose = gtm_window_dispose;
    object_class->finalize = gtm_window_finalize;

    gtk_widget_class_set_template_from_resource (GTK_WIDGET_CLASS (klass),
                                                 "/kr/gooroom/Gooroom-Task-Manager/gtm_window.ui");

    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, root_box_scrolled_window);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, user_box_scrolled_window);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, search_entry);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, summary_box);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, root_column1);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, root_column2);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, root_column3);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, user_column1);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, user_column2);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, user_column3);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, root_kill_button);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, root_term_button);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, root_stop_button);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, root_continue_button);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, root_details_button);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, user_kill_button);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, user_term_button);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, user_stop_button);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, user_continue_button);
    gtk_widget_class_bind_template_child_private (GTK_WIDGET_CLASS (klass), GtmWindow, user_details_button);
}

GtmWindow *
gtm_window_new (GtkApplication *app)
{
    return g_object_new (GTM_TYPE_WINDOW, "application", app, NULL);
}
