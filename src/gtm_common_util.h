#ifndef __GTM_COMMON_UTIL_H_
#define __GTM_COMMON_UTIL_H_

#include <gtk/gtk.h>
#include <math.h>

#include "gtm_constants.h"
#include "gtm_models.h"

G_BEGIN_DECLS

int  gtm_get_matching_column (gchar *selection);
void gtm_gint_to_str (gint32 num, char *str);
void gtm_guint_to_str (guint64 num, char *str);
void gtm_gtime_to_str (guint64 time, char *str);

G_END_DECLS

#endif
