#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "main_frame.hpp"

CV_GUI::CV_GUI(GtkApplication *app)
{
    file = nullptr;

    // ウィンドウを作成
    GtkWidget *window = gtk_window_new();
    gtk_widget_set_size_request(window, 640, 480);
    gtk_window_set_application(GTK_WINDOW(window), app);

    GtkWidget *vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), vbox1);

    GtkWidget *select_button = gtk_button_new_with_label("select Image file");
    gtk_box_append(GTK_BOX(vbox1), select_button);

    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_size_request(hbox, 400, 400);
    gtk_box_append(GTK_BOX(vbox1), hbox);

    image = (GtkPicture *)(gtk_picture_new());

    // ウィンドウに画像をセット
    gtk_box_append(GTK_BOX(hbox), GTK_WIDGET(image));
    gtk_widget_set_vexpand(GTK_WIDGET(image), TRUE);
    gtk_widget_set_hexpand(GTK_WIDGET(image), TRUE);
    
    g_signal_connect_swapped(select_button, "clicked", G_CALLBACK(&ImageSelect), this);

    GtkWidget *vbox2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(vbox2, 100, 200);
    gtk_box_append(GTK_BOX(hbox), vbox2);

    const char *process_list[] = {"0:Gray Scale",
                                  "1:Value Scaling", 
                                  "2:Gamma Correction", 
                                  "3:S Tone Curve", 
                                  "4:High Contrast", 
                                  "5:Low Contrast", 
                                  "6:Nega Posi Inversion", 
                                  "7:Postarization", 
                                  "8:Solarization", 
                                  "9:Binarize", 
                                  "10:Change Brightness",
                                  "11:Prewitt Filter", 
                                  "12:Sobel Filter", 
                                  "13:Laplacian Filter", 
                                  "14:Mean Filter", 
                                  "15:Weighted Mean Filter", 
                                  "16:Median Filter", 
                                  "17:Gaussian Filter", 
                                  "18:Motion Blur", 
                                  NULL};
    ddown_process = (GtkDropDown *)(gtk_drop_down_new_from_strings(process_list));
    gtk_box_append(GTK_BOX(vbox2), GTK_WIDGET(ddown_process));

    lbl_argv = (GtkLabel *)(gtk_label_new("Usage:    // Gray scale"));
    g_signal_connect(ddown_process, "notify::selected-item", G_CALLBACK(&ProcessChange), this);
    gtk_box_append(GTK_BOX(vbox2), GTK_WIDGET(lbl_argv));

    txt_argv = (GtkEntry *)(gtk_entry_new());
    gtk_box_append(GTK_BOX(vbox2), GTK_WIDGET(txt_argv));

    GtkWidget *exe_button = gtk_button_new_with_label("execute");
    gtk_box_append(GTK_BOX(vbox2), exe_button);
    g_signal_connect_swapped(exe_button, "clicked", G_CALLBACK(&ProcessExecute), this);

    // add quit button
    GtkWidget *quit_button = gtk_button_new_with_label("Quit");
    gtk_box_append(GTK_BOX(vbox1), quit_button);
    g_signal_connect_swapped(quit_button, "clicked", G_CALLBACK(g_application_quit), app);
    // ウィンドウを表示
    gtk_widget_show(window);
}

CV_GUI::~CV_GUI()
{

}

void CV_GUI::ImageChange()
{
    gtk_picture_set_file(image, file);
}

void CV_GUI::ImageSelect(GtkWidget *widget, gpointer data)
{
    GtkFileDialog *dialog = gtk_file_dialog_new();
    gtk_file_dialog_open(dialog, NULL, NULL, (GAsyncReadyCallback)ImageSelected, data);
}

void CV_GUI::ImageSelected(GObject *dialog, GAsyncResult *res, gpointer data)
{
    CV_GUI *self = static_cast<CV_GUI *>(data);
    self->file = gtk_file_dialog_open_finish(GTK_FILE_DIALOG(dialog), res, NULL);
    if (self->file) {
        self->ImageChange();
    }
}

void CV_GUI::ProcessChange(GtkWidget *widget, gpointer data)
{
    CV_GUI *self = static_cast<CV_GUI *>(data);

    int process_num = gtk_drop_down_get_selected(self->ddown_process);
    
    if (process_num == 0) gtk_label_set_label(self->lbl_argv, "Usage:    // Gray scale");
    else if (process_num == 1) gtk_label_set_label(self->lbl_argv, "Usage: a(int), b(int)    // a * value * b");
    else if (process_num == 2) gtk_label_set_label(self->lbl_argv, "Usage: gamma(double)    // pow(value/255, gamma) * 255");
    else if (process_num == 3) gtk_label_set_label(self->lbl_argv, "Usage: p(double)    // 255 / (1 + exp(p * (-x + 128)))");
    else if (process_num == 4) gtk_label_set_label(self->lbl_argv, "Usage: a(double), b(double)    // 255 * (x - a) / (b - a)");
    else if (process_num == 5) gtk_label_set_label(self->lbl_argv, "Usage: a(double), b(double)    // (b - a) / 255 * x + a");
    else if (process_num == 6) gtk_label_set_label(self->lbl_argv, "Usage:     // 255 - value");
    else if (process_num == 7) gtk_label_set_label(self->lbl_argv, "Usage: ly(int)    // ");
    else if (process_num == 8) gtk_label_set_label(self->lbl_argv, "Usage: a(int)    // ");
    else if (process_num == 9) gtk_label_set_label(self->lbl_argv, "Usage: threshold(int)    // ");
    else if (process_num == 10) gtk_label_set_label(self->lbl_argv, "Usage: x    // V(YUV) + x");
    else if (process_num == 11) gtk_label_set_label(self->lbl_argv, "Usage: mode(1: Horisontal, 2: Vertical, 3: 1+2), d(int)    // edge * d");
    else if (process_num == 12) gtk_label_set_label(self->lbl_argv, "Usage: mode(1: Horisontal, 2: Vertical, 3: 1+2), d(int)    // edge * d");
    else if (process_num == 13) gtk_label_set_label(self->lbl_argv, "Usage: direction(4 or 8), d(int)    // edge * d");
    else if (process_num == 14) gtk_label_set_label(self->lbl_argv, "Usage: size(int)    // size * size filter");
    else if (process_num == 15) gtk_label_set_label(self->lbl_argv, "Usage: add(int)    // value / (9 + add)");
    else if (process_num == 16) gtk_label_set_label(self->lbl_argv, "Usage: size(int)    // size * size filter");
    else if (process_num == 17) gtk_label_set_label(self->lbl_argv, "Usage: size(int), sigma(double)    // ");
    else if (process_num == 18) gtk_label_set_label(self->lbl_argv, "Usage: size(int), direction(0 or 90)    // ");
}

void CV_GUI::ProcessExecute(GtkWidget *widget, gpointer data)
{
    CV_GUI *self = static_cast<CV_GUI *>(data);

    if (self->file == nullptr) return;

    const char *line = gtk_editable_get_text(GTK_EDITABLE(txt_argv));

    std::string str(line);
    std::regex re(" *, *"); // if re doesn't match, use "\\s*,\\s*"
    std::vector<std::string> argv;

    std::sregex_token_iterator it(str.begin(), str.end(), re, -1);
    std::sregex_token_iterator end;

    while (it != end) {
        argv.push_back(*it++);
    }

    GdkPixbuf *tmp = self->pixbuf;
    pixbuf = gdk_pixbuf_new_from_file(g_file_get_path(self->file), NULL);

    int width = gdk_pixbuf_get_width(pixbuf);
    int height = gdk_pixbuf_get_height(pixbuf);
    int channel = gdk_pixbuf_get_n_channels(pixbuf);

    IMG *img = new IMG;
    img->channel = channel;
    img->width = width;
    img->height = height;
    img->pixel = width * height;
    img->value = gdk_pixbuf_get_pixels(pixbuf);

    IMG_RGB *img_rgb = new IMG_RGB;
    AllocImgRGB(img_rgb, width, height);
    IMG2RGB(img_rgb, img);

    int process_num = gtk_drop_down_get_selected(self->ddown_process);
    if (process_num == 0) GrayScale(img_rgb);
    else if (process_num == 1) {
        if (argv.size() >= 2) ValueScaling(img_rgb, stoi(argv[0]), stoi(argv[1]));
    }
    else if (process_num == 2) {
        if (argv.size() >= 1) GammaCorrection(img_rgb, stod(argv[0]));
    }
    else if (process_num == 3) {
        if (argv.size() >= 1) SToneCurve(img_rgb, stod(argv[0]));
    }
    else if (process_num == 4) {
        if (argv.size() >= 2) HighContrast(img_rgb, stod(argv[0]), stod(argv[1]));
    }
    else if (process_num == 5) {
        if (argv.size() >= 2) LowContrast(img_rgb, stod(argv[0]), stod(argv[1]));
    }
    else if (process_num == 6) {
        NegaPosiInversion(img_rgb);
    }
    else if (process_num == 7) {
        if (argv.size() >= 1) Postarization(img_rgb, stoi(argv[0]));
    }
    else if (process_num == 8) {
        if (argv.size() >= 1) Solarization(img_rgb, stoi(argv[0]));
    }
    else if (process_num == 9) {
        if (argv.size() >= 1) Binarize(img_rgb, stoi(argv[0]));
    }
    else if (process_num == 10) {
        if (argv.size() >= 1) ChangeBrightness(img_rgb, stoi(argv[0]));
    }
    else if (process_num == 11) {
        if (argv.size() >= 2) PrewittFilter(img_rgb, stoi(argv[0]), stoi(argv[1]));
    }
    else if (process_num == 12) {
        if (argv.size() >= 2) SobelFilter(img_rgb, stoi(argv[0]), stoi(argv[1]));
    }
    else if (process_num == 13) {
        if (argv.size() >= 2) LaplacianFilter(img_rgb, stoi(argv[0]), stoi(argv[1]));
    }
    else if (process_num == 14) {
        if (argv.size() >= 1) MeanFilter(img_rgb, stoi(argv[0]));
    }
    else if (process_num == 15) {
        if (argv.size() >= 1) WeightedMeanFilter(img_rgb, stoi(argv[0]));
    }
    else if (process_num == 16) {
        if (argv.size() >= 1) MedianFilter(img_rgb, stoi(argv[0]));
    }
    else if (process_num == 17) {
        if (argv.size() >= 2) GaussianFilter(img_rgb, stoi(argv[0]), stod(argv[1]));
    }
    else if (process_num == 18) {
        if (argv.size() >= 2) MotionBlur(img_rgb, stoi(argv[0]), stoi(argv[1]));
    }

    RGB2IMG(img, img_rgb);

    Free(img_rgb);
    delete img;
    gtk_picture_set_pixbuf(GTK_PICTURE(self->image), pixbuf);
}
