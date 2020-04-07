/**
 * @file main.c
 * @author Jorge Isaac Fallas Mejía B62562
 * @author Esteban Rodríguez Quintana B66076
 * @author Fabio Villalobos Pacheco B78346
 * @brief Archivo de código main para el proyecto AuVeTA
 * @version 1
 * @date 2019-07-18
 *
 *
 */

#include "h_comunicación_interfaz.h"

int main(int argc, char *argv[])
{

	numbuttons = 10;
	buttonList = malloc(sizeof(MoButton) * 11);

	int i = 0;
	buttonList[i++] = (MoButton){"w", 2, 1, NULL};
	buttonList[i++] = (MoButton){"a", 3, 0, NULL};
	buttonList[i++] = (MoButton){"d", 3, 2, NULL};
	buttonList[i++] = (MoButton){"s", 4, 1, NULL};
	buttonList[i++] = (MoButton){"1", 4, 5, NULL};
	buttonList[i++] = (MoButton){"2", 3, 7, NULL};
	buttonList[i++] = (MoButton){"3", 4, 9, NULL};
	buttonList[i++] = (MoButton){"y", 6, 6, NULL};
	buttonList[i++] = (MoButton){"t", 5, 7, NULL};
	buttonList[i++] = (MoButton){"b", 6, 8, NULL};

	GtkWidget *window;
	GtkWidget *table;

	/* --- GTK initialization --- */
	gtk_init(&argc, &argv);

	/* --- Create the AuVeTA Control window --- */
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* --- Give the window a title. --- */
	gtk_window_set_title(GTK_WINDOW(window), "AuVeTA Control");

	/* --- Set the window size. --- */
	gtk_widget_set_usize(window, 1000, 700);

	/* --- We care if a key is pressed --- */
	gtk_signal_connect(GTK_OBJECT(window), "key_press_event",
					   GTK_SIGNAL_FUNC(key_press), NULL);

	/* --- You should always remember to connect the delete event
         *     to the main window. --- */
	gtk_signal_connect(GTK_OBJECT(window), "delete_event",
					   GTK_SIGNAL_FUNC(CloseAppWindow), NULL);

	/* --- Create a 10x10 table for the items in the control. --- */
	table = gtk_table_new(10, 10, TRUE);

	/* --- Create the control buttons. --- */
	CreateControlButtons(table);

	/* --- Create the label --- */



	label = gtk_label_new (NULL);
	const char *str1 = "Control Mode";
	const char *format1 = "<span style=\"italic\">%s</span>" ;
	char *markup1;

	markup1 = g_markup_printf_escaped (format1, str1);
	gtk_label_set_markup (GTK_LABEL (label), markup1);

	gtk_misc_set_alignment(GTK_MISC(label), 0.96, .58);
	/* --- Add label to the table --- */
	gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 6, 0, 7);

	gtk_widget_show(label);

	g_free (markup1);

	/* --- Create the label --- */
	label = gtk_label_new (NULL);
	const char *str2 = "Waiting Mode";
	const char *format2 = "<span style=\"italic\">%s</span>" ;
	char *markup2;

	markup2 = g_markup_printf_escaped (format2, str2);
	gtk_label_set_markup (GTK_LABEL (label), markup2);

	gtk_misc_set_alignment(GTK_MISC(label), 0.97, .44);


	/* --- Add label to the table --- */
	gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 8, 0, 7);

	gtk_widget_show(label);

	g_free (markup2);


	/* --- Create the label --- */
	label = gtk_label_new (NULL);
	const char *str3 = "Tracking Mode";
	const char *format3 = "<span style=\"italic\">%s</span>" ;
	char *markup3;

	markup3 = g_markup_printf_escaped (format3, str3);
	gtk_label_set_markup (GTK_LABEL (label), markup3);

	gtk_misc_set_alignment(GTK_MISC(label), 0.98, .58);
	/* --- Add label to the table --- */
	gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 10, 0, 7);

	gtk_widget_show(label);

	g_free (markup3);

	/* --- Create the label --- */
	label = gtk_label_new (NULL);
	const char *str4 = "Remove Object";
	const char *format4 = "<span style=\"italic\">%s</span>" ;
	char *markup4;

	markup4 = g_markup_printf_escaped (format4, str4);
	gtk_label_set_markup (GTK_LABEL (label), markup4);

	gtk_misc_set_alignment(GTK_MISC(label), 0.97, .61);
	/* --- Add label to the table --- */
	gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 7, 0, 10);

	gtk_widget_show(label);

	g_free (markup4);

	/* --- Create the label --- */
	label = gtk_label_new (NULL);
	const char *str5 = "360°";
	const char *format5 = "<span style=\"italic\">%s</span>" ;
	char *markup5;

	markup5 = g_markup_printf_escaped (format5, str5);
	gtk_label_set_markup (GTK_LABEL (label), markup5);

	gtk_misc_set_alignment(GTK_MISC(label), 0.949, .51);
	/* --- Add label to the table --- */
	gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 8, 0, 10);

	gtk_widget_show(label);

	g_free (markup5);

	/* --- Create the label --- */
	label = gtk_label_new (NULL);
	const char *str6 = "Buzzer";
	const char *format6 = "<span style=\"italic\">%s</span>" ;
	char *markup6;

	markup6 = g_markup_printf_escaped (format6, str6);
	gtk_label_set_markup (GTK_LABEL (label), markup6);

	gtk_misc_set_alignment(GTK_MISC(label), 0.96, .61);
	/* --- Add label to the table --- */
	gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 9, 0, 10);

	gtk_widget_show(label);

	g_free (markup6);

	/* --- Create the label --- */
	label = gtk_label_new("Select 1, 2 o 3 for Operation Mode");
	gtk_misc_set_alignment(GTK_MISC(label), 2, .6);

	/* --- Add label to the table --- */
	gtk_table_attach_defaults(GTK_TABLE(table), label, 0, 6, 0, 1);
	gtk_widget_show(label);

	/* --- Make LABELS  visible --- */
	gtk_container_add(GTK_CONTAINER(window), table);
	gtk_widget_show(table);

	gtk_widget_show(window);

	/* --- Grab focus for the keystrokes --- */
	//gtk_widget_grab_focus (buttonList[0].widget);

	gtk_main();
	free(buttonList);
	return (0);
}
