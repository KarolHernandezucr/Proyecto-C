// Juego de Tic Tac Toe (Gato) con libreria GTK-3 e interfaz
// grafica de Glade. Grupo 8
// Estudiantes: Karol Hernandez Morera
//              Oscar Rojas Rojas
//              Steven Ruiz Urbina

// Importación de libreria GTK-3
#include <gtk/gtk.h>

// Variables globales: 0 para vacío, 1 para X, 2 para O
GtkWidget *buttons[3][3];
int currentPlayer = 0;
int gameState[3][3] = {0};

// Función para verificar el estado del juego
int checkGameState() {
    // Verificacion de filas
    for (int i = 0; i < 3; i++) {
        if (gameState[i][0] == gameState[i][1] && gameState[i][1] == gameState[i][2] && gameState[i][0] != 0)
            return gameState[i][0];
    }
    // Verificacion de columnas
    for (int i = 0; i < 3; i++) {
        if (gameState[0][i] == gameState[1][i] && gameState[1][i] == gameState[2][i] && gameState[0][i] != 0)
            return gameState[0][i];
    }
     // Verificacion de las diagonales
    if (gameState[0][0] == gameState[1][1] && gameState[1][1] == gameState[2][2] && gameState[0][0] != 0)
        return gameState[0][0];

    if (gameState[0][2] == gameState[1][1] && gameState[1][1] == gameState[2][0] && gameState[0][2] != 0)
        return gameState[0][2];
    // Verificacion de empate
    int isDraw = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameState[i][j] == 0) {
                isDraw = 0;
                break;
            }
        }
        if (!isDraw)
            break;
    }
    if (isDraw)
        return 3;

    // Si el juego continúa
    return 0;
}

// Función para los clics
void button_clicked(GtkWidget *widget, gpointer data) {
    int index = GPOINTER_TO_INT(data);
    int row = index / 3;
    int col = index % 3;
    // Verificamos si la casilla está vacía
    if (gameState[row][col] == 0) {
        // Marcar la casilla segun el jugador
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
    // Iniciamos GTK
    gtk_init(&argc, &argv);

    // Cargamos la interfaz gráfica desde el archivo Glade
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "karol.glade", NULL);
    // Obtenemos el objeto ventana y conectamos la señal para cerrar la aplicación
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "mainWindow"));
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    // Obtenemos los botones y conectamos la señal para manejar el clic
    char buttonName[20];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            sprintf(buttonName, "button%d%d", i+1, j+1); // Generamos el nombre del botón según su posición
            buttons[i][j] = GTK_WIDGET(gtk_builder_get_object(builder, buttonName));
            g_signal_connect(buttons[i][j], "clicked", G_CALLBACK(button_clicked), GINT_TO_POINTER(i * 3 + j));
        }
    }

    // Mostramos la ventana principal
    gtk_widget_show(window);

    // Iniciamos el bucle principal de GTK
    gtk_main();
    
 return 0;
}
