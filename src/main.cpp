#include "main_frame.hpp"

static void activate(GtkApplication *app, gpointer user_data)
{
    CV_GUI *window = new CV_GUI(app);
}

int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    // GTKアプリケーションの初期化
    app = gtk_application_new(NULL, G_APPLICATION_FLAGS_NONE);

    // アプリケーションが起動したときのコールバックに関数を設定
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // アプリケーションを実行
    return g_application_run(G_APPLICATION(app), argc, argv);
}
