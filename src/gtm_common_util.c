#include "gtm_common_util.h"

int
gtm_get_matching_column (gchar *selection)
{
    int column_id;
    for (column_id = 0; column_id < NUM_COLUMNS; column_id++)
    {
        if (!(g_strcmp0 (column_names[column_id], selection)))
        {
            break;
        }
    }
    return column_id;
}

void
gtm_gint_to_str (gint32 num,
                 char *str)
{
    int i = 0;
    int j = 0;
    char tmp[GTM_PROC_NUM_LIMIT] = { 0, };
    int rem;

    if (num == 0)
    {
        tmp[i++] = '0'; 
    } 
    else
    {
        if (num < 0)
        {
            str[j++] = '-';
            num = num * (-1);
        }
        while (num > 0)
        {
            rem = num % 10;
            tmp[i++] = rem + '0';
            num /= 10;
        }
    }

    i -= 1;

    while (i >= 0)
    {
        str[j++] = tmp[i--];
    }
    str[j] = '\0';
}

void
gtm_guint_to_str (guint64 num,
                  char *str)
{
    int i = 0;
    int j = 0;
    char tmp[GTM_PROC_NUM_LIMIT] = { 0, };
    int rem;

    if (num == 0)
    {
        tmp[i++] = '0';
    }
    else
    {
        while (num > 0)
        {
            rem = num % 10;
            tmp[i++] = rem + '0';
            num /= 10;
        }
    }

    i -= 1;

    while (i >= 0)
    {
        str[j++] = tmp[i--];
    }
    str[j] = '\0';
}

void
gtm_gdouble_to_str (double num,
                    char *str)
{
    char tmp[GTM_INFO_BUF];
    int inum;
    int fnum;

    inum = num;
    num -= inum;
    fnum = num * GTM_PRECISION_VAL;
    gtm_gint_to_str (inum, tmp);
    g_strlcpy (str, tmp, GTM_INFO_BUF);
    g_strlcat (str, ".", GTM_INFO_BUF);
    gtm_gint_to_str (fnum, tmp);
    g_strlcat (str, tmp, GTM_INFO_BUF);
}

void
gtm_gtime_to_str (guint64 time,
                  char *str)
{
    char hour[10] = { '\0', };
    char min[3] = { '\0', };
    char second[3] = { '\0', };

    gtm_guint_to_str ((time / 3600), hour);
    time %= 3600;
    gtm_guint_to_str ((time / 60), min);
    time %= 60;
    gtm_guint_to_str ((time), second);

    g_strlcpy (str, "+ ", GTM_INFO_BUF);
    g_strlcat (str, hour, GTM_INFO_BUF);
    g_strlcat (str, "h ", GTM_INFO_BUF);
    g_strlcat (str, min, GTM_INFO_BUF);
    g_strlcat (str, "m ", GTM_INFO_BUF);
    g_strlcat (str, second, GTM_INFO_BUF);
    g_strlcat (str, "s", GTM_INFO_BUF);
}
