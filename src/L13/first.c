#include <gtk/gtk.h>

static void wyswietl_witaj(GtkWidget *widget, gpointer data) {
    GtkEntry * txtName = (GtkEntry*) data;

    printf("Akuku %s...\n", gtk_entry_get_text(txtName));
} 

static void activate(GtkApplication * app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *button_box;
    GtkWidget * txtName;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Okienko");
    gtk_window_set_default_size(GTK_WINDOW(window), 300,300);

    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER(window), button_box);

    button = gtk_button_new_with_label("Witaj Świecie.");
    gtk_container_add(GTK_CONTAINER(button_box), button);

    txtName = gtk_entry_new();
    gtk_container_add(GTK_CONTAINER(button_box), txtName);

    g_signal_connect(button, "clicked", G_CALLBACK(wyswietl_witaj), txtName);


    gtk_widget_show_all(window);

} 

int main(int argc, char *argv[]) {
    GtkApplication *app;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}