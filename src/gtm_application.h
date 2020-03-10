#ifndef _GTM_APPLICATION_H_
#define _GTM_APPLICATION_H_

#include <gtk/gtk.h>

#include "gtm_constants.h"
#include "gtm_window.h"

G_BEGIN_DECLS

#define GTM_TYPE_APPLICATION (gtm_application_get_type ())
#define GTM_APPLICATION(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GTM_TYPE_APPLICATION, GtmApplication))
#define GTM_APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GTM_TYPE_APPLICATION, GtmApplicationClass))
#define GTM_IS_APPLICATION(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GTM_APPLICATION))
#define GTM_IS_APPLICATION_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GTM_TYPE_APPLICATION))
#define GTM_APPLICATION_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GTM_APPLICATION, GtmApplicationClass))

typedef struct _GtmApplication      GtmApplication;
typedef struct _GtmApplicationClass GtmApplicationClass;

struct _GtmApplication
{
    GtkApplication parent_instance;
};

struct _GtmApplicationClass
{
    GtkApplicationClass parent_class;
};

GType           gtm_application_get_type (void);
GtmApplication* gtm_application_new (void);

G_END_DECLS

#endif
