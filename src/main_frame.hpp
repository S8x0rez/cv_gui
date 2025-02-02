#ifndef MAIN_FRAME_HPP
#define MAIN_FRAME_HPP

#include <gtk/gtk.h>

#include "../../CV/src/my_cv.hpp"
#include "../../CV/src/data.hpp"

class CV_GUI {
public:
    CV_GUI(GtkApplication *);
    ~CV_GUI();

private:
    GtkPicture *image;
    GdkPixbuf *pixbuf;
    GFile *file;

    GtkDropDown *ddown_process;
    GtkLabel *lbl_argv;
    GtkEntry *txt_argv;

// slots:
    void ImageSelect(GtkWidget *, gpointer);
    static void ImageSelected(GObject *, GAsyncResult *, gpointer);
    void ImageChange();

    void ProcessChange(GtkWidget *, gpointer);

    void ProcessExecute(GtkWidget *, gpointer);
};

#endif // MAIN_FRAME_HPP
