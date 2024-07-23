/**
 * @file
 * @brief Main file
 */

#include "brick_game.h"

using namespace s21;

int main() {
    GameType gameType = getGameType();
    ViewType viewType = getViewType();

    GameFactory factory;

    IModel *model = factory.createModel(gameType);

    Controller controller(model);

    IView *view = factory.createView(viewType, controller);

    view->startEventLoop();

    delete view;

   return 0;
}

// int main(int argc, char *argv[]) {
//     QApplication app(argc, argv);

//     Model model(nullptr);

//     ViewModel viewModel(&model);
//     View view(&viewModel);

//     QMainWindow window;
//     window.setCentralWidget(&view);
//     window.show();
//     view.show();

//     return app.exec();
// }

// int main(int argc, char *argv[])
// {
//     QApplication app(argc, argv);

//     Model model;
//     View view(&model);
//     view.show();

//     return app.exec();
// }