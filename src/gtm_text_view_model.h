#ifndef _GTM_TEXT_VIEW_MODEL_H_
#define _GTM_TEXT_VIEW_MODEL_H_

#include <gtk/gtk.h>
#include "gtm_constants.h"
#include "gtm_models.h"
#include "gtm_process.h"
#include "gtm_common_util.h"

G_BEGIN_DECLS

#define GTM_TYPE_TEXT_VIEW_MODEL (gtm_text_view_model_get_type ())
#define GTM_TEXT_VIEW_MODEL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTM_TYPE_TEXT_VIEW_MODEL, GtmTextViewModel))
#define GTM_TEXT_VIEW_MODEL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTM_TYPE_TEXT_VIEW_MODEL, GtmTextViewModelClass))
#define GTM_IS_TEXT_VIEW_MODEL(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTM_TEXT_VIEW_MODEL))
#define GTM_IS_TEXT_VIEW_MODEL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTM_TYPE_TEXT_VIEW_MODEL))
#define GTM_TEXT_VIEW_MODEL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTM_TEXT_VIEW_MODEL, GtmTextViewModelClass))

typedef struct _GtmTextViewModel      GtmTextViewModel;
typedef struct _GtmTextViewModelClass GtmTextViewModelClass;

struct _GtmTextViewModel
{
    GtkTextBuffer parent_instance;
};

struct _GtmTextViewModelClass
{
    GtkTextBufferClass parent_class;
};

GType             gtm_text_view_model_get_type (void);
GtmTextViewModel *gtm_text_view_model_new (GtkTextView *view, gint flags, gint32 target_pid);
void              gtm_get_tasks_model_info (GtmTextViewModel *text_view_model);
void              gtm_get_details_model_info (GtmTextViewModel *text_view_model, gint32 target_pid);
void              gtm_update_tasks_text_view_model (GtmTextViewModel *text_view_model);

G_END_DECLS

#endif
