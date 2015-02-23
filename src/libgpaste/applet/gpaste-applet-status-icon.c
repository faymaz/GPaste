/*
 *      This file is part of GPaste.
 *
 *      Copyright 2014 Marc-Antoine Perennou <Marc-Antoine@Perennou.com>
 *
 *      GPaste is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      GPaste is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with GPaste.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gpaste-applet-status-icon-private.h"

typedef struct
{
    GtkStatusIcon *icon;

    gulong         press_id;
} GPasteAppletStatusIconPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (GPasteAppletStatusIcon, g_paste_applet_status_icon, G_PASTE_TYPE_APPLET_ICON)

static gboolean
g_paste_applet_status_icon_popup (GtkStatusIcon  *icon G_GNUC_UNUSED,
                                  GdkEventButton *event G_GNUC_UNUSED,
                                  gpointer        user_data G_GNUC_UNUSED)
{
    g_paste_applet_icon_activate ();

    return GDK_EVENT_PROPAGATE;
}

static void
g_paste_applet_status_icon_dispose (GObject *object)
{
    GPasteAppletStatusIconPrivate *priv = g_paste_applet_status_icon_get_instance_private ((GPasteAppletStatusIcon *) object);

    if (priv->icon)
    {
        g_signal_handler_disconnect (priv->icon, priv->press_id);
        g_clear_object (&priv->icon);
    }

    G_OBJECT_CLASS (g_paste_applet_status_icon_parent_class)->dispose (object);
}

static void
g_paste_applet_status_icon_class_init (GPasteAppletStatusIconClass *klass)
{
    G_OBJECT_CLASS (klass)->dispose = g_paste_applet_status_icon_dispose;
}

static void
g_paste_applet_status_icon_init (GPasteAppletStatusIcon *self)
{
    GPasteAppletStatusIconPrivate *priv = g_paste_applet_status_icon_get_instance_private (self);

    G_GNUC_BEGIN_IGNORE_DEPRECATIONS
    priv->icon = gtk_status_icon_new_from_icon_name ("edit-paste");
    gtk_status_icon_set_tooltip_text (priv->icon, "GPaste");
    gtk_status_icon_set_visible (priv->icon, TRUE);
    G_GNUC_END_IGNORE_DEPRECATIONS

    priv->press_id = g_signal_connect (priv->icon,
                                       "button-press-event",
                                       G_CALLBACK (g_paste_applet_status_icon_popup),
                                       self);
}

/**
 * g_paste_applet_status_icon_new:
 * @client: a #GPasteClient
 *
 * Create a new instance of #GPasteAppletStatusIcon
 *
 * Returns: a newly allocated #GPasteAppletStatusIcon
 *          free it with g_object_unref
 */
G_PASTE_VISIBLE GPasteAppletIcon *
g_paste_applet_status_icon_new (GPasteClient *client)
{
    g_return_val_if_fail (G_PASTE_IS_CLIENT (client), NULL);

    return g_paste_applet_icon_new (G_PASTE_TYPE_APPLET_STATUS_ICON, client);
}
