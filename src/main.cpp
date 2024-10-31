#include <gtk/gtk.h>
#include <second.hpp>
#include <sstream>

static void on_button_clicked(GtkWidget *widget, gpointer user_data) {
    GtkEntry *entry = GTK_ENTRY(user_data);
    GtkTextBuffer *text_buffer = GTK_TEXT_BUFFER(g_object_get_data(G_OBJECT(widget), "text_buffer"));

  const gchar *input_text = gtk_entry_get_text(entry);
  double input_value = atof(input_text);

  if (input_text[0] == '\0') {
    gtk_text_buffer_set_text(text_buffer, "Введите значение!", -1);
    return;
  }

  RealNumber number(input_value);
  double fractionalPart = number();
  double integerPart = number[0];

  std::ostringstream result;
  result << "Целая часть: " << static_cast<int>(integerPart) << "\n";
  result << "Дробная часть: " << fractionalPart << "\n";

  gtk_text_buffer_set_text(text_buffer, result.str().c_str(), -1);
}

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *grid;
  GtkWidget *entry;
  GtkWidget *button;
  GtkWidget *text_view;
  GtkTextBuffer *text_buffer;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "RealNumber GTK+ App");
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_container_add(GTK_CONTAINER(window), box);

  grid = gtk_grid_new();
  gtk_box_pack_start(GTK_BOX(box), grid, TRUE, TRUE, 0);

  gtk_widget_set_margin_top(grid, 10);
  gtk_widget_set_margin_bottom(grid, 10);
  gtk_widget_set_margin_start(grid, 10);
  gtk_widget_set_margin_end(grid, 10);

  gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
  gtk_grid_set_column_spacing(GTK_GRID(grid), 5);

  entry = gtk_entry_new();
  gtk_entry_set_max_length(GTK_ENTRY(entry), 20);
  gtk_grid_attach(GTK_GRID(grid), entry, 0, 0, 1, 1);
  gtk_widget_set_hexpand(entry, TRUE);

  text_view = gtk_text_view_new();
  text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
  gtk_grid_attach(GTK_GRID(grid), text_view, 0, 1, 2, 1);
  gtk_widget_set_vexpand(text_view, TRUE);
  gtk_widget_set_hexpand(text_view, TRUE);

  button = gtk_button_new_with_label("✓");
  g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), entry);
  g_object_set_data(G_OBJECT(button), "text_buffer", text_buffer);
  gtk_grid_attach(GTK_GRID(grid), button, 1, 0, 1, 1);
  gtk_widget_set_size_request(button, 30, 30);
  gtk_widget_set_hexpand(button, FALSE);

  gtk_widget_set_vexpand(grid, TRUE);
  gtk_widget_set_hexpand(grid, TRUE);

  gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}
