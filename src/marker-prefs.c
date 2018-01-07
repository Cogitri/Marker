#include <gtk/gtk.h>
#include <gtksourceview/gtksource.h>

#include <dirent.h>
#include <stdlib.h>
#include <string.h>

#include "marker.h"
#include "marker-editor-window.h"
#include "marker-widget.h"
#include "marker-string.h"

#include "marker-prefs.h"

MarkerPrefs prefs;

char*
marker_prefs_get_css_theme()
{
  return g_settings_get_string(prefs.preview_settings, "css-theme");
}

void
marker_prefs_set_css_theme(const char* theme)
{
  g_settings_set_string(prefs.preview_settings, "css-theme", theme);
}

char*
marker_prefs_get_highlight_theme()
{
  return g_settings_get_string(prefs.preview_settings, "highlight-theme");
}


void
marker_prefs_set_highlight_theme(const char* theme)
{
  g_settings_set_string(prefs.preview_settings, "highlight-theme", theme);
}

gboolean
marker_prefs_get_use_katex()
{
  return g_settings_get_boolean(prefs.preview_settings, "katex-toggle");
}

void
marker_prefs_set_use_katex(gboolean state)
{
  g_settings_set_boolean(prefs.preview_settings, "katex-toggle", state);
}

gboolean
marker_prefs_get_use_highlight()
{
  return g_settings_get_boolean(prefs.preview_settings, "highlight-toggle");
}

void
marker_prefs_set_use_highlight(gboolean state)
{
  g_settings_set_boolean(prefs.preview_settings, "highlight-toggle", state);
}

char*
marker_prefs_get_syntax_theme()
{
  return g_settings_get_string(prefs.editor_settings, "syntax-theme");
}

void
marker_prefs_set_syntax_theme(const char* theme)
{
  g_settings_set_string(prefs.editor_settings, "syntax-theme", theme);
}

guint
marker_prefs_get_right_margin_position()
{
  return 0;
}

void
marker_prefs_set_right_margin_position(guint position)
{
  
}

gboolean
marker_prefs_get_replace_tabs()
{
  return  g_settings_get_boolean(prefs.editor_settings, "replace-tabs");
}

void
marker_prefs_set_replace_tabs(gboolean state)
{
   g_settings_set_boolean(prefs.editor_settings, "replace-tabs", state);
}

guint
marker_prefs_get_tab_width()
{
  return g_settings_get_uint(prefs.editor_settings, "tab-width");
}

void
marker_prefs_set_tab_width(guint width)
{
  g_settings_set_uint(prefs.editor_settings, "tab-width", width);
}

gboolean
marker_prefs_get_auto_indent()
{
  return g_settings_get_boolean(prefs.editor_settings, "auto-indent");
}

void
marker_prefs_set_auto_indent(gboolean state)
{
  return g_settings_set_boolean(prefs.editor_settings, "auto-indent", state);
}

gboolean
marker_prefs_get_show_line_numbers()
{
  return g_settings_get_boolean(prefs.editor_settings, "show-line-numbers");
}

void
marker_prefs_set_show_line_numbers(gboolean state)
{
  g_settings_set_boolean(prefs.editor_settings, "show-line-numbers", state);
}

gboolean
marker_prefs_get_highlight_current_line()
{
  return g_settings_get_boolean(prefs.editor_settings, "highlight-current-line");
}

void
marker_prefs_set_highlight_current_line(gboolean state)
{
  g_settings_set_boolean(prefs.editor_settings, "highlight-current-line", state);
}

gboolean
marker_prefs_get_wrap_text()
{
  return g_settings_get_boolean(prefs.editor_settings, "wrap-text");
}

void
marker_prefs_set_wrap_text(gboolean state)
{
  g_settings_set_boolean(prefs.editor_settings, "wrap-text", state);
}

gboolean
marker_prefs_get_show_right_margin()
{
  return g_settings_get_boolean(prefs.editor_settings, "show-right-margin");
}

void
marker_prefs_set_show_right_margin(gboolean state)
{
  g_settings_set_boolean(prefs.editor_settings, "show-right-margin", state);
}

gboolean
marker_prefs_get_gnome_appmenu()
{
  return g_settings_get_boolean(prefs.window_settings, "gnome-appmenu");
}

void
marker_prefs_set_gnome_appmenu(gboolean state)
{
  g_settings_set_boolean(prefs.window_settings, "gnome-appmenu", state);
}

MarkerEditorWindowViewMode
marker_prefs_get_default_view_mode()
{
  return g_settings_get_enum(prefs.window_settings, "view-mode");
}

void
marker_prefs_set_default_view_mode(MarkerEditorWindowViewMode view_mode)
{
  g_settings_set_enum(prefs.window_settings, "view-mode", view_mode);
}

GList*
marker_prefs_get_available_stylesheets()
{
  GList* list = NULL;
  char* list_item;
  
  DIR* dir;
  struct dirent* ent;
  char* filename;
  if ((dir = opendir(STYLES_DIR)) != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
    {
      filename = ent->d_name;
      if (marker_string_ends_with(filename, ".css"))
      {
        list_item = marker_string_alloc(filename);
        list = g_list_prepend(list, list_item);
      }
    }
  }
  closedir(dir);
  
  list_item = marker_string_alloc("none");
  list = g_list_prepend(list, list_item);
  
  return list;
}

GList*
marker_prefs_get_available_highlight_themes()
{
  GList* list = NULL;
  char* list_item;

  DIR* dir;
  struct dirent* ent;
  char* filename;

  if ((dir = opendir(HIGHLIGHT_STYLES_DIR)) != NULL)
  {
    while ((ent = readdir(dir)) != NULL)
    {
      filename = ent->d_name;

      if (marker_string_ends_with(filename, ".css"))
      {
        list_item = marker_string_filename_get_name_noext(filename);
        list = g_list_prepend(list, list_item);
      }
    }
  }
  closedir(dir);
  
  list_item = marker_string_alloc("none");
  list = g_list_prepend(list, list_item);
  
  return list;
}

GList*
marker_prefs_get_available_syntax_themes()
{
  GList* list = NULL;
  
  GtkSourceStyleSchemeManager* style_manager =
    gtk_source_style_scheme_manager_get_default();
  const gchar * const * ids =
    gtk_source_style_scheme_manager_get_scheme_ids(style_manager);
    
  for (int i = 0; ids[i] != NULL; ++i)
  {
    const gchar* id = ids[i];
    char* item = marker_string_alloc(id);
    list = g_list_prepend(list, item);
  }
  
  return list;
}

static void
show_line_numbers_toggled(GtkToggleButton* button,
                          gpointer         user_data)
{
  gboolean state = gtk_toggle_button_get_active(button);
  marker_prefs_set_show_line_numbers(state);
  
  GtkApplication* app = marker_get_app();
  GList* windows = gtk_application_get_windows(app);
  for (GList* item = windows; item != NULL; item = item->next)
  {
    if (MARKER_IS_EDITOR_WINDOW(item->data))
    {
      MarkerEditorWindow* window = item->data;
      marker_editor_window_set_show_line_numbers(window, state);
    }
  }
}

static void
highlight_current_line_toggled(GtkToggleButton* button,
                               gpointer         user_data)
{
  gboolean state = gtk_toggle_button_get_active(button);
  marker_prefs_set_highlight_current_line(state);
  
  GtkApplication* app = marker_get_app();
  GList* windows = gtk_application_get_windows(app);
  for (GList* item = windows; item != NULL; item = item->next)
  {
    if (MARKER_IS_EDITOR_WINDOW(item->data))
    {
      MarkerEditorWindow* window = item->data;
      marker_editor_window_set_highlight_current_line(window, state);
    }
  }
}

static void refresh_preview(){
  GtkApplication* app = marker_get_app();
  GList* windows = gtk_application_get_windows(app);
  for (GList* item = windows; item != NULL; item = item->next)
  {
    if (MARKER_IS_EDITOR_WINDOW(item->data))
    {
      MarkerEditorWindow* window = item->data;
      marker_editor_window_refresh_preview(window);
    }
  }
}

static void
enable_katex_toggled(GtkToggleButton* button,
                       gpointer         user_data)
{
  gboolean state = gtk_toggle_button_get_active(button);
  marker_prefs_set_use_katex(state);
  refresh_preview();
}

static void
wrap_text_toggled(GtkToggleButton* button,
                  gpointer         user_data)
{
  gboolean state = gtk_toggle_button_get_active(button);
  marker_prefs_set_wrap_text(state);
  
  GtkApplication* app = marker_get_app();
  GList* windows = gtk_application_get_windows(app);
  for (GList* item = windows; item != NULL; item = item->next)
  {
    if (MARKER_IS_EDITOR_WINDOW(item->data))
    {
      MarkerEditorWindow* window = item->data;
      marker_editor_window_set_wrap_text(window, state);
    }
  }
}

static void
auto_indent_toggled(GtkToggleButton* button,
                     gpointer         user_data)
{
  gboolean state = gtk_toggle_button_get_active(button);
  marker_prefs_set_auto_indent(state);

  GtkApplication* app = marker_get_app();
  GList* windows = gtk_application_get_windows(app);
  for (GList* item = windows; item != NULL; item = item->next)
  {
    if (MARKER_IS_EDITOR_WINDOW(item->data))
    {
      MarkerEditorWindow* window = item->data;
      marker_editor_window_set_auto_indent(window, state);
    }
  }
}

static void
replace_tabs_toggled(GtkToggleButton* button,
                     gpointer         user_data)
{
  gboolean state = gtk_toggle_button_get_active(button);
  marker_prefs_set_replace_tabs(state);

  GtkApplication* app = marker_get_app();
  GList* windows = gtk_application_get_windows(app);
  for (GList* item = windows; item != NULL; item = item->next)
  {
    if (MARKER_IS_EDITOR_WINDOW(item->data))
    {
      MarkerEditorWindow* window = item->data;
      marker_editor_window_set_replace_tabs(window, state);
    }
  }
}

static void
tab_width_value_changed(GtkSpinButton *spin_button,
                        gpointer       user_data)
{
  guint value = gtk_spin_button_get_value_as_int (spin_button);
  marker_prefs_set_tab_width(value);

  GtkApplication* app = marker_get_app();
  GList* windows = gtk_application_get_windows(app);
  for (GList* item = windows; item != NULL; item = item->next)
  {
    if (MARKER_IS_EDITOR_WINDOW(item->data))
    {
      MarkerEditorWindow* window = item->data;
      marker_editor_window_set_tab_width(window, value);
    }
  }
}

static void
show_right_margin_toggled(GtkToggleButton* button,
                          gpointer         user_data)
{
  gboolean state = gtk_toggle_button_get_active(button);
  marker_prefs_set_show_right_margin(state);

  GtkApplication* app = marker_get_app();
  GList* windows = gtk_application_get_windows(app);
  for (GList* item = windows; item != NULL; item = item->next)
  {
    if (MARKER_IS_EDITOR_WINDOW(item->data))
    {
      MarkerEditorWindow* window = item->data;
      marker_editor_window_set_show_right_margin(window, state);
    }
  }
}

static void
syntax_chosen(GtkComboBox* combo_box,
              gpointer     user_data)
{
  char* choice = marker_widget_combo_box_get_active_str(combo_box);
  
  if (strcmp(choice, "none") != 0)
  {
    marker_prefs_set_use_highlight(FALSE);
  }
  else
  {
    marker_prefs_set_use_highlight(TRUE);
    marker_prefs_set_syntax_theme(choice);
  }
  
  GtkApplication* app = marker_get_app();
  GList* windows = gtk_application_get_windows(app);
  for (GList* item = windows; item != NULL; item = item->next)
  {
    if (MARKER_IS_EDITOR_WINDOW(item->data))
    {
      MarkerEditorWindow* window = item->data;
      marker_editor_window_set_syntax_theme(window, choice);
    }
  }
  
  free(choice);
}

static void
css_chosen(GtkComboBox* combo_box,
           gpointer     user_data)
{
  char* choice = marker_widget_combo_box_get_active_str(combo_box);

  char* path;
  if (strcmp(choice, "none") != 0)
  {
    path = marker_string_prepend(choice, STYLES_DIR, NULL, 0);
    marker_prefs_set_css_theme(path);
    free(path);
  }
  else
  {
    marker_prefs_set_css_theme(choice);
  }
  free(choice);
  
  refresh_preview();
}

static void
highlight_css_chosen(GtkComboBox* combo_box,
                     gpointer     user_data)
{
  char* choice = marker_widget_combo_box_get_active_str(combo_box);
  marker_prefs_set_highlight_theme(choice);

  free(choice);

  refresh_preview();
}

static void
default_view_mode_chosen(GtkComboBox* combo_box,
                         gpointer     user_data)
{
  MarkerEditorWindowViewMode mode = gtk_combo_box_get_active(combo_box);
  marker_prefs_set_default_view_mode(mode);
}

static void
use_gnome_appmenu_toggled(GtkToggleButton* button,
                          gpointer         user_data)
{
  gboolean state = gtk_toggle_button_get_active(button);
  marker_prefs_set_gnome_appmenu(state);
}

void
marker_prefs_show_window()
{
  GtkBuilder* builder =
    gtk_builder_new_from_resource(
      "/com/github/fabiocolacio/marker/ui/prefs-window.ui");
 
  GList *list = NULL;
  GtkComboBox* combo_box;
  GtkToggleButton* check_button;
  GtkSpinButton* spin_button;
  
  combo_box = GTK_COMBO_BOX(gtk_builder_get_object(builder, "syntax_chooser"));
  list = marker_prefs_get_available_syntax_themes();
  marker_widget_populate_combo_box_with_strings(combo_box, list);
  char* syntax = marker_prefs_get_syntax_theme();
  marker_widget_combo_box_set_active_str(combo_box,syntax, g_list_length(list));
  g_free(syntax);
  g_list_free_full(list, free);
  list = NULL;
  
  combo_box = GTK_COMBO_BOX(gtk_builder_get_object(builder, "css_chooser"));
  list = marker_prefs_get_available_stylesheets();
  marker_widget_populate_combo_box_with_strings(combo_box, list);
  char* css = marker_prefs_get_css_theme();
  char* css_filename = marker_string_filename_get_name(css);
  marker_widget_combo_box_set_active_str(combo_box, css_filename, g_list_length(list));
  free(css_filename);
  g_free(css);
  g_list_free_full(list, free);
  list = NULL;

  combo_box = GTK_COMBO_BOX(gtk_builder_get_object(builder, "highlight_css_chooser"));
  list = marker_prefs_get_available_highlight_themes();
  marker_widget_populate_combo_box_with_strings(combo_box, list);
  char* theme = marker_prefs_get_highlight_theme();
  marker_widget_combo_box_set_active_str(combo_box, theme, g_list_length(list));
  g_free(theme);
  g_list_free_full(list, free);
  list = NULL;
  
  combo_box = GTK_COMBO_BOX(gtk_builder_get_object(builder, "view_mode_chooser"));
  GtkCellRenderer* cell_renderer = gtk_cell_renderer_text_new();
  gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(combo_box), cell_renderer, TRUE);
  gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(combo_box),
                                 cell_renderer,
                                 "text", 0,
                                 NULL);
  gtk_combo_box_set_active(combo_box, marker_prefs_get_default_view_mode());
  
  check_button =
    GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "katex_check_button"));
  gtk_toggle_button_set_active(check_button, marker_prefs_get_use_katex());
  
  check_button =
    GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "show_line_numbers_check_button"));
  gtk_toggle_button_set_active(check_button, marker_prefs_get_show_line_numbers());
  
  check_button =
    GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "show_right_margin_check_button"));
  gtk_toggle_button_set_active(check_button, marker_prefs_get_show_right_margin());
  
  check_button =
    GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "wrap_text_check_button"));
  gtk_toggle_button_set_active(check_button, marker_prefs_get_wrap_text());
  
  check_button =
    GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "highlight_current_line_check_button"));
  gtk_toggle_button_set_active(check_button, marker_prefs_get_highlight_current_line());

  check_button =
    GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "auto_indent_check_button"));
  gtk_toggle_button_set_active(check_button, marker_prefs_get_auto_indent());

  check_button =
    GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "replace_tabs_check_button"));
  gtk_toggle_button_set_active(check_button, marker_prefs_get_replace_tabs());

  check_button =
    GTK_TOGGLE_BUTTON(gtk_builder_get_object(builder, "use_appmenu_check_button"));
  gtk_toggle_button_set_active(check_button, marker_prefs_get_gnome_appmenu());

  spin_button =
    GTK_SPIN_BUTTON(gtk_builder_get_object(builder, "tab_width_spin_button"));
  gtk_spin_button_set_range(spin_button, 1, 12);
  gtk_spin_button_set_increments(spin_button, 1, 0);
  gtk_spin_button_set_value(spin_button, marker_prefs_get_tab_width());
  
  GtkWindow* window = GTK_WINDOW(gtk_builder_get_object(builder, "prefs_win"));
  gtk_window_set_position(window, GTK_WIN_POS_CENTER);
  gtk_widget_show_all(GTK_WIDGET(window));
  
  gtk_builder_add_callback_symbol(builder,
                                  "syntax_chosen",
                                  G_CALLBACK(syntax_chosen));
  gtk_builder_add_callback_symbol(builder,
                                  "css_chosen",
                                  G_CALLBACK(css_chosen));
  gtk_builder_add_callback_symbol(builder,
                                  "highlight_css_chosen",
                                  G_CALLBACK(highlight_css_chosen));
  gtk_builder_add_callback_symbol(builder,
                                  "default_view_mode_chosen",
                                  G_CALLBACK(default_view_mode_chosen));
  gtk_builder_add_callback_symbol(builder,
                                  "show_line_numbers_toggled", 
                                  G_CALLBACK(show_line_numbers_toggled));
  gtk_builder_add_callback_symbol(builder,
                                  "highlight_current_line_toggled", 
                                  G_CALLBACK(highlight_current_line_toggled));
  gtk_builder_add_callback_symbol(builder,
                                  "replace_tabs_toggled",
                                  G_CALLBACK(replace_tabs_toggled));
  gtk_builder_add_callback_symbol(builder,
                                  "auto_indent_toggled",
                                  G_CALLBACK(auto_indent_toggled));
  gtk_builder_add_callback_symbol(builder,
                                  "tab_width_value_changed",
                                  G_CALLBACK(tab_width_value_changed));
  gtk_builder_add_callback_symbol(builder,
                                  "enable_katex_toggled",
                                  G_CALLBACK(enable_katex_toggled));
  gtk_builder_add_callback_symbol(builder,
                                  "wrap_text_toggled", 
                                  G_CALLBACK(wrap_text_toggled));
  gtk_builder_add_callback_symbol(builder,
                                  "show_right_margin_toggled", 
                                  G_CALLBACK(show_right_margin_toggled));
  gtk_builder_add_callback_symbol(builder,
                                  "use_gnome_appmenu_toggled",
                                  G_CALLBACK(use_gnome_appmenu_toggled));
  gtk_builder_connect_signals(builder, NULL);
  
  g_object_unref(builder);
}

void
marker_prefs_load()
{
  prefs.editor_settings =
    g_settings_new("com.github.fabiocolacio.marker.preferences.editor");
  prefs.preview_settings =
    g_settings_new("com.github.fabiocolacio.marker.preferences.preview");
  prefs.window_settings = 
    g_settings_new("com.github.fabiocolacio.marker.preferences.window");
}

