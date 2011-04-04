/**
 * about.c - about dialog for SciteProj
 *
 *	 Copyright 2008-2011 Andreas Ronnquist
 *
 * This file is part of SciteProj.
 * 
 * SciteProj is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SciteProj is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SciteProj.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <glib.h> 
#include <gtk/gtk.h>

#include "about.h"

#include "graphics.h"


static gchar *sLicense =	(gchar*)"SciteProj is free software: you can redistribute it and/or modify\n"
											  "it under the terms of the GNU General Public License as published by\n"
											  "the Free Software Foundation, either version 3 of the License, or\n"
											  "(at your option) any later version.\n"
											  "\n"
											  "SciteProj is distributed in the hope that it will be useful,\n"
											  "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
											  "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
											  "GNU General Public License for more details.\n"
											  "\n"
											  "You should have received a copy of the GNU General Public License\n"
											  "along with SciteProj.  If not, see <http://www.gnu.org/licenses/>.\n";


gchar *homepage_string=(gchar*)"http://sciteproj.gusnan.se";

gchar *sVersion = (gchar*)"0.4.10";

static GtkWidget *window;

void create_about_dialog();

/**
 * show_about_dialog
 * Shows the about dialog, and if it isnt already made, creates it
 */
void show_about_dialog()
{
	if (!window) 
		create_about_dialog();
	else
		gtk_window_present(GTK_WINDOW(window));
}

/**
 *	creates a new dialog box, and fills it will all necessary information
 */
void create_about_dialog()
{
	GtkWidget *vbox;
	GtkWidget *textview_info;
	GtkWidget *logo_image;
	GtkWidget *linkbutton;
	GtkWidget *ok_button;
	GtkWidget *notebook;
	GtkWidget *notebook_label1;
	GtkWidget *notebook_label2;
	GtkTextBuffer *textbuffer_info;
	GtkTextBuffer *textbuffer_license;
	GtkWidget *textview_license;
	GtkTextIter iter;
	
	gchar *copyrightstring;
	
	GtkWidget *label;
	
	
	// Make the dialog
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_container_set_border_width(GTK_CONTAINER(window), 8);
	
	gtk_widget_set_size_request(window,500,400);
	
	// Make a container
	vbox=gtk_vbox_new(FALSE,5);
	
	gtk_container_add(GTK_CONTAINER(window),vbox);
	
	logo_image=gtk_image_new_from_pixbuf(program_icon_pixbuf);
	
	gtk_box_pack_start(GTK_BOX(vbox), logo_image, FALSE, FALSE, 0);
	
	label=gtk_label_new(NULL);
	gtk_label_set_selectable(GTK_LABEL(label),FALSE);
	gtk_label_set_markup(GTK_LABEL(label),"<big><b>SciteProj</b></big>");
		
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	
	// Show version of SciteProj
	
	gchar *version_string;
	
#ifdef _DEBUG
	version_string=g_strdup_printf("version %s DEBUG",sVersion);
#else
	version_string=g_strdup_printf("version %s",sVersion);
#endif
	
	label=gtk_label_new(version_string);
	gtk_label_set_selectable(GTK_LABEL(label),FALSE);
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	
	// Show SciteProj copyrights
	copyrightstring=g_strdup_printf("Copyright (C) 2008-2011 Andreas Rönnquist <gusnan@gusnan.se>");
	
	label=gtk_label_new(copyrightstring);
	gtk_label_set_selectable(GTK_LABEL(label),FALSE);
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	
	// show GTK versions
	gchar *gtk_string=g_strdup_printf("GTK+ %d.%d.%d / GLib %d.%d.%d",
		   //"Operating System: unknown",
		   gtk_major_version, gtk_minor_version, gtk_micro_version,
		   glib_major_version, glib_minor_version, glib_micro_version);
			
	label=gtk_label_new(gtk_string);
	
	gtk_label_set_selectable(GTK_LABEL(label),FALSE);
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	
	// Show a link to the SciteProj homepage
	linkbutton=gtk_link_button_new_with_label(homepage_string,"http://www.gusnan.se/sciteproj");
	
	
	GtkWidget *hbox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

	linkbutton=gtk_link_button_new_with_label(homepage_string,"http://www.gusnan.se/sciteproj");
	gtk_box_pack_start(GTK_BOX(hbox), linkbutton, TRUE, FALSE, 0);
	
	// New notebook - we want tabs for different sets of text
	
	notebook=gtk_notebook_new();
	
	notebook_label1=gtk_label_new("Information");
	notebook_label2=gtk_label_new("License");
	
	// create a scrolled_window and a textview for the license
	textbuffer_license=gtk_text_buffer_new(NULL);
	gtk_text_buffer_get_start_iter(textbuffer_license,&iter);
	
	gtk_text_buffer_insert(textbuffer_license,&iter,sLicense,-1);
	
	textview_license=gtk_text_view_new_with_buffer(textbuffer_license);
	
	
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview_license),TRUE);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textview_license),FALSE);
	
	GtkWidget *scrolled_window_license;
	
	scrolled_window_license=gtk_scrolled_window_new(NULL,NULL);

	// Never show horisontal scrollbar, always show vertical
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window_license),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

	gtk_container_add(GTK_CONTAINER(scrolled_window_license),textview_license);
	
	

	// New textbuffer - and we get the beginning of the textbuffer
	textbuffer_info=gtk_text_buffer_new(NULL);
	gtk_text_buffer_get_start_iter(textbuffer_info,&iter);

	gchar *about_text2=g_strdup_printf(""
											"SciteProj is based on ScitePM by\n"
											"Roy Wood<roy.wood@gmail.com> and\n"
											"Martin Andrews<ScitePM@PLATFORMedia.com>\n\n"
											"Many thanks to\n"
											"Mattias Wecksten <wecksten@gmail.com>\n"
											"Frank Wunderlich\n\n"
											"For more information about SciteProj, see the README file that\n"
											"is provided with the package."
											);
	
	gtk_text_buffer_insert(textbuffer_info,&iter,about_text2,-1);
	
	gtk_text_buffer_get_end_iter(textbuffer_info,&iter);
	
	// Setup the textview and windows
	textview_info=gtk_text_view_new_with_buffer(textbuffer_info);
	
	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(textview_info),TRUE);
	gtk_text_view_set_editable(GTK_TEXT_VIEW(textview_info),FALSE);
	
	GtkWidget *scrolled_window_info;
	
	scrolled_window_info=gtk_scrolled_window_new(NULL,NULL);

	// Never show horisontal scrollbar, always show vertical
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window_info),GTK_POLICY_NEVER,GTK_POLICY_ALWAYS);

	gtk_container_add(GTK_CONTAINER(scrolled_window_info),textview_info);
		
	//gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);
	
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),scrolled_window_info,notebook_label1);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook),scrolled_window_license,notebook_label2);
	
	gtk_box_pack_start(GTK_BOX(vbox), notebook,TRUE,TRUE,0);
	
	gtk_text_buffer_place_cursor(textbuffer_info,&iter);
	gtk_text_buffer_select_range (textbuffer_info,&iter,&iter);

	hbox=gtk_hbox_new(FALSE,0);
	
	// Create an ok button
	ok_button=gtk_button_new_from_stock(GTK_STOCK_OK);
	
	gtk_box_pack_end(GTK_BOX(hbox),ok_button,FALSE,FALSE,0);
	
	gtk_box_pack_start(GTK_BOX(vbox),hbox,FALSE,FALSE,0);
	
	gtk_widget_grab_focus(ok_button);
		
	gtk_text_buffer_get_start_iter(textbuffer_info, &iter);
	gtk_text_buffer_place_cursor(textbuffer_info, &iter);
	
	g_signal_connect_closure
		(G_OBJECT(ok_button), "clicked",
		 g_cclosure_new_swap(G_CALLBACK(gtk_widget_hide_on_delete),
				     window, NULL), FALSE);
					  
	
	gtk_widget_show_all(window);

}

/**
 * Show version
 */
void show_version()
{
	g_print("SciteProj version %s\n", sVersion);
}
