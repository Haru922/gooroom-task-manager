#include "gtm_application.h"

G_DEFINE_TYPE (GtmApplication, gtm_application, GTK_TYPE_APPLICATION);

void
quit_activated (GSimpleAction *action,
                GVariant      *parameter,
                gpointer       app)
{
    g_application_quit (G_APPLICATION (app));
}

static void
gtm_application_init (GtmApplication *app) 
{
}

static GActionEntry app_entries[] =
{
    { "quit", quit_activated, NULL, NULL, NULL }
};

static void
gtm_application_startup (GApplication *app)
{
    GtkBuilder *builder;
    GMenuModel *app_menu;
    const gchar *quit_accels[2] = { "<Ctrl>Q", NULL };

    G_APPLICATION_CLASS (gtm_application_parent_class)->startup (app);

    g_action_map_add_action_entries (G_ACTION_MAP (app),
                                     app_entries, G_N_ELEMENTS (app_entries),
                                     app);
    gtk_application_set_accels_for_action (GTK_APPLICATION (app),
                                           "app.quit",
                                           quit_accels);

    builder = gtk_builder_new_from_resource ("/kr/gooroom/Gooroom-Task-Manager/gtm_menu.ui");
    app_menu = G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu"));
    gtk_application_set_app_menu (GTK_APPLICATION (app), app_menu);
    g_object_unref (builder);
}

static void
gtm_application_activate (GApplication *app)
{
    GtmWindow *win;

    win = gtm_window_new (GTM_APPLICATION (app));
    gtk_window_set_default_size (GTK_WINDOW (win), GTM_WINDOW_WIDTH, GTM_WINDOW_HEIGHT);
    gtk_window_present (GTK_WINDOW (win));
}

static void
gtm_application_class_init (GtmApplicationClass *klass)
{
    G_APPLICATION_CLASS (klass)->startup = gtm_application_startup;
    G_APPLICATION_CLASS (klass)->activate = gtm_application_activate;
}

GtmApplication *
gtm_application_new (void)
{
    return g_object_new (GTM_TYPE_APPLICATION,
                         "application-id", "kr.gooroom.Goooroom-Task-Manager",
                         "flags", G_APPLICATION_HANDLES_OPEN,
                         NULL);
}
