#ifndef _GTM_WINDOW_H_
#define _GTM_WINDOW_H_

#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <gtk/gtk.h>

#include "gtm_application.h"
#include "gtm_tree_view_model.h"
#include "gtm_text_view_model.h"
#include "gtm_constants.h"
#include "gtm_common_util.h"

G_BEGIN_DECLS

#define GTM_TYPE_WINDOW (gtm_window_get_type ())
#define GTM_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTM_TYPE_WINDOW, GtmWindow))
#define GTM_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTM_TYPE_WINDOW, GtmWindowClass))
#define GTM_IS_WINDOW(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTM_WINDOW))
#define GTM_IS_WINDOW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTM_TYPE_WINDOW))
#define GTM_WINDOW_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTM_WINDOW, GtmWindowClass))

typedef struct _GtmWindow      GtmWindow;
typedef struct _GtmWindowClass GtmWindowClass;

struct _GtmWindow
{
    GtkApplicationWindow parent_instance;
};

struct _GtmWindowClass
{
    GtkApplicationWindowClass parent_class;
};


GType      gtm_window_get_type (void);
GtmWindow* gtm_window_new (GtkApplication *app);
void       root_first_column_changed (GtkComboBoxText *root_column, gpointer win);
void       root_second_column_changed (GtkComboBoxText *root_column, gpointer win);
void       root_third_column_changed (GtkComboBoxText *root_column, gpointer win);
void       user_first_column_changed (GtkComboBoxText *user_column, gpointer win);
void       user_second_column_changed (GtkComboBoxText *user_column, gpointer win);
void       user_third_column_changed (GtkComboBoxText *user_column, gpointer win);
void       kill_button_clicked (GtkButton *kill_button, gpointer process_list);
void       term_button_clicked (GtkButton *term_button, gpointer process_list);
void       stop_button_clicked (GtkButton *stop_button, gpointer process_list);
void       continue_button_clicked (GtkButton *continue_button, gpointer process_list);
void       details_button_clicked (GtkButton *details_button, gpointer process_list);
void       connect_root_button_signal_handlers (GtmWindow *win);
void       disconnect_root_button_signal_handlers (GtmWindow *win);
void       connect_user_button_signal_handlers (GtmWindow *win);
void       disconnect_user_button_signal_handlers (GtmWindow *win);
void       gtm_build_root_process_list (GtmWindow *win);
void       gtm_build_user_process_list (GtmWindow *win);
void       gtm_rebuild_root_process_list (GtmWindow *win);
void       gtm_rebuild_user_process_list (GtmWindow *win);

G_END_DECLS

#endif
