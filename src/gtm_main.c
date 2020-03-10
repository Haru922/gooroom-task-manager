#include "gtm_application.h"

int
main (int argc,
      char *argv[])
{
    int status;
    GtmApplication *gooroom_task_manager;

    gooroom_task_manager = gtm_application_new ();
    status = g_application_run (G_APPLICATION (gooroom_task_manager), argc, argv);
    g_object_unref (gooroom_task_manager);

    return status;
}
