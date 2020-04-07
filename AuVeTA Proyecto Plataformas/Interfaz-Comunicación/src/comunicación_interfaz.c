/**
 * @file comunicación_interfaz.c
 * @author Jorge Isaac Fallas Mejía B62562
 * @author Esteban Rodríguez Quintana B66076
 * @author Fabio Villalobos Pacheco B78346
 * @brief Archivo de funciones para la interfaz y la comunicación
 * @version 1
 * @date 2019-07-18
 *
 *
 */
#include "h_comunicación_interfaz.h"

/**
 * @brief int CloseAppWindow: Es una función de tipo int que
 * recibe un widget y la información, que utiliza un
 * gtk_main_quit que retorna el cierre de la ventana y, por
 * ende, del programa.
 */
int CloseAppWindow(GtkWidget *widget, gpointer data)
{
        gtk_main_quit();

        return (FALSE);
}

/**
 * @brief void key_press: Es una función de tipo void que recibe
 * un widget, un evento y la información, hace uso de un ciclo
 * for que busca entre los botones, y una condición if que si la
 * pulsación de tecla es el primer carácter de un botón y la longitud
 * de la etiqueta del botón es uno, entonces permite el retorno que
 * conecta el botón presionado en el teclado con la interfaz gráfica
 * tarea asociada.
 */

void key_press(GtkWidget *widget,
               GdkEventKey *event,
               gpointer data)
{
        int npressed;

        for (npressed = 0; npressed < numbuttons; npressed++)
        {
                if (event->keyval == buttonList[npressed].szLabel[0] &&
                    buttonList[npressed].szLabel[1] == (char)0)
                {
                        gtk_widget_grab_focus(buttonList[npressed].widget);

                        gtk_button_clicked(GTK_BUTTON(buttonList[npressed].widget));
                        return;
                }
        }
}

/**
 * void button_clicked: Es una función de tipo void que recibe un widget
 * y la información, este contiene instancias de las funciones que trabajan
 * con el puerto serial, dos punteros de tipo char, el str se encarga
 * de agarrar el texto del botón y la información, además contiene
 * la ventana que contiene la interfaz, luego varias condiciones if
 * que permiten comparar el botón clickeado o presinado en el teclado
 * que conecta con el puerto serial y retorna la tarea que realiza
 * el vehículo.
 */

void button_clicked(GtkWidget *widget, gpointer data)
{
        int baudrate = 115200;
        int port;
        port = serialport_init("/dev/rfcomm0", baudrate);

        char ch = *((char *)data);
        char *str;
        GtkWidget *window;
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

        str = (char *)data;

        if (strcmp(str, "w") == 0)
        {

                char a = 'w';
                const char *ptr = &a;
                serialport_write(port, ptr);

                return;
        }
        else if (strcmp(str, "a") == 0)
        {

                char a = 'a';
                const char *ptr = &a;
                serialport_write(port, ptr);

                return;
        }
        else if (strcmp(str, "d") == 0)
        {

                char a = 'd';
                const char *ptr = &a;
                serialport_write(port, ptr);

                return;
        }
        else if (strcmp(str, "s") == 0)
        {

                char a = 's';
                const char *ptr = &a;
                serialport_write(port, ptr);

                return;
        }
        else if (strcmp(str, "1") == 0)
        {

                char a = '1';
                const char *ptr = &a;
                serialport_write(port, ptr);

                gtk_label_set(GTK_LABEL(label), "Control Mode");
                return;
        }
        else if (strcmp(str, "2") == 0)
        {

                char a = '2';
                const char *ptr = &a;
                serialport_write(port, ptr);

                gtk_label_set(GTK_LABEL(label), "Waiting mode");
                return;
        }
        else if (strcmp(str, "3") == 0)
        {

                char a = '3';
                const char *ptr = &a;
                serialport_write(port, ptr);

                gtk_label_set(GTK_LABEL(label), "Tracking mode");
                return;
        }
        else if (strcmp(str, "y") == 0)
        { //scalubur time

                char a = 'e';
                const char *ptr = &a;
                serialport_write(port, ptr);

                return;
        }
        else if (strcmp(str, "b") == 0)
        { //buzzer

                char a = 'b';
                const char *ptr = &a;
                serialport_write(port, ptr);

                return;
        }
        else if (strcmp(str, "t") == 0)
        { //trompo

                char a = 't';
                const char *ptr = &a;
                serialport_write(port, ptr);

                return;
        }


}

/**
 * @brief GtkWidget *CreateButton: Es una función tipo Gtkwidget
 * que recibe la tabla que contiene los botones, un dato
 * char que es el tamaño de los botones, además dos datos de
 * tipo int que son la posición en fila y columna de los botones,
 * luego esta hace un gtk_button_new_with_label que es el botón,
 * además del color, de la posicion en la interfaz y gtk_widget_show
 * que hace que retorne todas esas características del botón.
 */

GtkWidget *CreateButton(GtkWidget *table, char *szLabel, int row, int column)
{
        GtkWidget *button;

        button = gtk_button_new_with_label(szLabel);

        gtk_signal_connect(GTK_OBJECT(button), "clicked",
                           GTK_SIGNAL_FUNC(button_clicked), szLabel);

        GdkColor color;

        gdk_color_parse("red", &color);

        gtk_widget_modify_bg(GTK_WIDGET(button), GTK_STATE_NORMAL, &color);

        gtk_table_attach(GTK_TABLE(table), button,
                         column, column + 1,
                         row, row + 1,
                         GTK_FILL | GTK_EXPAND,
                         GTK_FILL | GTK_EXPAND,
                         10, 15);

        gtk_widget_show(button);

        return (button);
}

/**
 * @brief void CreateControlButtons: Es una función tipo void
 * que recibe la tabla que contiene los botones, luego se crea
 * un dato que hace que el ciclo for recorra la lista de los
 * botones y con ayuda de la función CreateButton se cree el
 * botón y aparezca en la interfaz.
 */

void CreateControlButtons(GtkWidget *table)
{
        int nIndex;

        for (nIndex = 0; nIndex < numbuttons; nIndex++)
        {

                buttonList[nIndex].widget =
                    CreateButton(table,
                                 buttonList[nIndex].szLabel,
                                 buttonList[nIndex].row,
                                 buttonList[nIndex].col);
        }
}

/////////////////////////////////////////////////////
/**
 *@brief Función serialport_write: Esta función recibe de parámetros el puerto
 *inicializado y el caracter que se desea enviar. Luego, el caracter se escribe
 *en el puerto inicializado para ser recibido en el arduino.
*/

int serialport_write(int fd, const char *str)

{

        int len = strlen(str);

        int n = write(fd, str, len);

        if (n != len)

                return -1;

        return n;
}
/**
 *@brief Función serialport_init: Esta función recibe de parámetros el nombre
 *del puerto que se desea inicializar y el baud rate que utiliza el módulo bluetooth.
 *Seguidamente, el puerto es abierto para poder escribir o leer datos.
*/

int serialport_init(const char *serialport, int baud)

{

        int fd;
        fd = open(serialport, O_RDWR | O_NOCTTY);
        if (fd == -1)
        {

                perror("init_serialport: Unable to open port ");

                return -1;
        }
        return fd;
}
