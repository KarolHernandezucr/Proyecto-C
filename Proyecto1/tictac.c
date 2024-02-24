
#include <gtk/gtk.h>


// Variables globales
GtkWidget *buttons[3][3];
int currentPlayer = 0;
int gameState[3][3] = {0}; // 0 para vacío, 1 para X, 2 para O

// Función para verificar el estado del juego
int checkGameState() {
    // Aquí implementa la lógica para verificar el estado del juego
    // Retorna 0 si el juego continúa, 1 si gana X, 2 si gana O, y 3 si hay empate
}

// Función para manejar el clic en un botón
void button_clicked(GtkWidget *widget, gpointer data) {
    // Obtenemos las coordenadas del botón clickeado
    int row = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "row"));
    int col = GPOINTER_TO_INT(g_object_get_data(G_OBJECT(widget), "col"));

    // Verificamos si la casilla está vacía
    if (gameState[row][col] == 0) {
        // Marcamos la casilla según el jugador actual
        if (currentPlayer == 0) {
            gtk_button_set_label(GTK_BUTTON(widget), "X");
            gameState[row][col] = 1;
        } else {
            gtk_button_set_label(GTK_BUTTON(widget), "O");
            gameState[row][col] = 2;
        }
        // Cambiamos de jugador
        currentPlayer = !currentPlayer;

        // Verificamos el estado del juego
        int result = checkGameState();
        if (result != 0) {
            // Mostramos el mensaje de resultado
            GtkWidget *dialog;
            if (result == 1)
                dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "¡Gana X!");
            else if (result == 2)
                dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "¡Gana O!");
            else
                dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "¡Empate!");

            gtk_dialog_run(GTK_DIALOG(dialog));
            gtk_widget_destroy(dialog);
        }
    }
}

int main(int argc, char *argv[]) {
    // Inicializamos GTK
    gtk_init(&argc, &argv);

    // Cargamos la interfaz gráfica desde el archivo Glade
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "interfaz.glade", NULL);

    // Obtenemos el objeto ventana y conectamos la señal para cerrar la aplicación
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window1"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Obtenemos los botones y conectamos la señal para manejar el clic
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            char buttonName[20];
            sprintf(buttonName, "button_%d_%d", i, j);
            buttons[i][j] = GTK_WIDGET(gtk_builder_get_object(builder, buttonName));
            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(button_clicked), NULL);
            g_object_set_data(G_OBJECT(buttons[i][j]), "row", GINT_TO_POINTER(i));
            g_object_set_data(G_OBJECT(buttons[i][j]), "col", GINT_TO_POINTER(j));
        }
    }

    // Mostramos la ventana principal
    gtk_widget_show(window);

    // Iniciamos el bucle principal de GTK
    gtk_main();

    return 0;
}
