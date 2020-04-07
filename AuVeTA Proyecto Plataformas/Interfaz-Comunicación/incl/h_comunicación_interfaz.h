/**
 * @file h_comunicación_interfaz.h
 * @author Jorge Isaac Fallas Mejía B62562
 * @author Esteban Rodríguez Quintana B66076
 * @author Fabio Villalobos Pacheco B78346
 * @brief Archivo de encabezado para la interfaz y la comunicación
 * @version 1
 * @date 2019-07-18
 *
 *
 */
#ifndef A
#define A

#include <stdio.h> /* Standard input/output definitions */
#include <stdlib.h>
#include <stdint.h>  /* Standard types */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <sys/ioctl.h>
#include <getopt.h>
#include <gtk/gtk.h>

#define BUF_SIZE 88
static float num1 = 0;
static char lastChar = (char)0;
static char prevCmd = (char)0;
/**
 * @brief Estructura de datos para realizar un seguimiento de los botones de la interfaz.
 */

typedef struct {

        char *szLabel;
        int row;
        int col;
        GtkWidget *widget;

} MoButton;

/**
 * @brief Lista MoButton: Crea una lista que contendrá los botones que aparecerán en la interfaz gráfica.
 */

MoButton * buttonList;

/**
 * @brief int numbuttons: Es la variable de tipo entero que contiene el número de botones que estarán en
 * la lista MoButton.
 */

int numbuttons;

/**
 * @brief Widget label: Este es el panel en el que se "imprime" la función de los botones.
 *
 */

GtkWidget *label;

/*Funciones comunicación serial*/
/**
 *@brief Función serialport_init: Inicializa el puerto serial.
 *@param serialport: El nombre del puerto al que se conecta el módulo bluetooth.
 *@param baud: El baud rate que utiliza el módulo bluetooth.
 *@return int: Si el puerto pudo ser inicializado.
*/
int serialport_init(const char *serialport, int baud);
/**
 *@brief Función serialport_write: Escribe en el puerto serial.
 *@param fd: La función serialport_init.
 *@param str: El caracter que se envía en el puerto.
 *@return int: El dato enviado por el puerto.
*/
int serialport_write(int fd, const char *str);


/* Funciones GTK */
/**
 * @brief Función CloseAppWindow: Cierra la ventana creada de la interfaz.
 * @param widget: La "caja" que contiene el texto del botón.
 * @param data: El puntero del texto contenido en el "widget".
 * @return FALSE: Retorna el cierre de la ventana del programa y finalización de operación.
 */
gint CloseAppWindow (GtkWidget *widget, gpointer data);

/**
 * @brief Función key_press: Se encarga de la lectura del botón presionado en el teclado.
 * @param widget: La "caja" que contiene el texto del botón.
 * @param event: El evento que lee el botón presionado.
 * @param data: El puntero del texto contenido en el "widget".
 * @return Retorna la tarea del botón presionado.
 */
void key_press(GtkWidget *widget, GdkEventKey *event, gpointer data);

/**
 * @brief Función button_clicked: Se encarga de leer que el botón en la interfaz se haya clickeado.
 * @param widget: La "caja" que contiene el texto del botón.
 * @param data: El puntero del texto contenido en el "widget".
 * @return Retorna la tarea del botón clickeado.
 */
void button_clicked (GtkWidget *widget, gpointer data);

/**
 * @brief Función CreateButton: Se encarga de crear las características de cada botón.
 * @param table: La tabla que contiene los botones.
 * @param szLabel: El tamaño del texto que contiene el botón.
 * @param row: La fila donde se ubicará el botón.
 * @param column: La columna donde se ubicará el botón.
 * @return button: Retorna el botón creado.
 */
GtkWidget *CreateButton (GtkWidget *table, char *szLabel, int row, int column);

/**
 * @brief Función CreateControlButtons: Se encarga de poner en la interfaz los botones que se crearon.
 * @param table: La tabla que contiene los botones.
 * @return Retorna los botones en la interfaz.
 */
void CreateControlButtons (GtkWidget *table);
#endif
