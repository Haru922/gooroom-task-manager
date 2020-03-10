#ifndef _GTM_TREE_VIEW_MODEL_H_
#define _GTM_TREE_VIEW_MODEL_H_

#include <gtk/gtk.h>
#include "gtm_constants.h"
#include "gtm_models.h"
#include "gtm_process.h"

G_BEGIN_DECLS

#define GTM_TYPE_TREE_VIEW_MODEL (gtm_tree_view_model_get_type ())
#define GTM_TREE_VIEW_MODEL(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTM_TYPE_TREE_VIEW_MODEL, GtmTreeViewModel))
#define GTM_TREE_VIEW_MODEL_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTM_TYPE_TREE_VIEW_MODEL, GtmTreeViewModelClass))
#define GTM_IS_TREE_VIEW_MODEL(obj) (G_TYPE_CHECK_INSTNACE_TYPE ((obj), GTM_TREE_VIEW_MODEL))
#define GTM_IS_TREE_VIEW_MODEL_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTM_TYPE_TREE_VIEW_MODEL))
#define GTM_TREE_VIEW_MODEL_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTM_TREE_VIEW_MODEL, GtmTreeViewModelClass))

typedef struct _GtmTreeViewModel      GtmTreeViewModel;
typedef struct _GtmTreeViewModelClass GtmTreeViewModelClass;

struct _GtmTreeViewModel
{
    GtkListStore parent_instance;
};

struct _GtmTreeViewModelClass
{
    GtkListStoreClass parent_class;
};

GType             gtm_tree_view_model_get_type (void);
GtmTreeViewModel *gtm_tree_view_model_new (gint mode);
void              gtm_set_process_model (GtmTreeViewModel *tree_view_model, gint mode);
void              gtm_update_process_list (GtmTreeViewModel *tree_view_model, gint mode);

G_END_DECLS

#endif
