/**
 * @file
 * @brief Brick game library header
 */

#ifndef BRICK_GAME_H
#define BRICK_GAME_H

#ifdef __cplusplus

#include "components/GameFactory/GameFactory.h"

// #include <QtCore>
// #include <QtGui>
// #include <QtWidgets>
// #include <iostream>

extern "C" {
#endif

#ifdef __cplusplus
}
#endif

// Observer interface
// class Observer
// {
// public:
//     virtual void update(const QString &message) = 0;
// };

// // Observable class
// class Observable
// {
// public:
//     void addObserver(Observer *observer)
//     {
//         observers.push_back(observer);
//     }

//     void notifyObservers(const QString &message)
//     {
//         for (Observer *observer : observers)
//         {
//             observer->update(message);
//         }
//     }

// private:
//     std::vector<Observer*> observers;
// };

// // Model class
// class Model : public Observable
// {
// public:
//     void changeData(const QString &data)
//     {
//         // Change the data
//         notifyObservers(data);
//     }
// };

// // View class
// class View : public QWidget, public Observer
// {
//     Q_OBJECT

// public:
//     View(Model *model, QWidget *parent = nullptr) : QWidget(parent), model(model)
//     {
//         QVBoxLayout *layout = new QVBoxLayout(this);

//         QLabel *label = new QLabel("Текст:");
//         layout->addWidget(label);

//         textEdit = new QLineEdit;
//         layout->addWidget(textEdit);

//         updateButton = new QPushButton("Обновить");
//         layout->addWidget(updateButton);

//         connect(updateButton, &QPushButton::clicked, this, &View::onUpdateClicked);

//         model->addObserver(this);
//     }

//     void update(const QString &message) override
//     {
//         textEdit->setText(message);
//     }

// public slots:
//     void onUpdateClicked()
//     {   
//         update("Новые данные");
//         model->changeData("Новые данные");
//     }

// private:
//     Model *model;
//     QLineEdit *textEdit;
//     QPushButton *updateButton;
// };

// class Model : public QObject {
//     Q_OBJECT

// public:
//     Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

//     Model(QWidget *parent): QObject(parent) {}

//     QString name() const {
//         return m_name;
//     }

//     void setName(const QString &name) {
//         std::cout << "Model name changed" << std::endl;
//         if (m_name != name) {
//             m_name = std::move(name);
//             emit nameChanged();
//         }
//     }

// signals:
//     void nameChanged();

// private:
//     QString m_name;
// };

// //ViewModel (ViewModel)
// class ViewModel : public QObject {
//     Q_OBJECT
// public:
//     ViewModel(Model *model, QObject *parent = nullptr) : QObject(parent), m_model(model) {
//         connect(m_model, &Model::nameChanged, this, &ViewModel::updateName);
//     }

// public slots:
//     void updateName() {
//         //std::cout << "ViewModel name changed" << std::endl;
//         emit nameChanged(m_model->name());
//     }

//     QString name() const {
//         return m_model->name();
//     }

//     void setName(const QString &name) {
//         m_model->setName(name);
//     }

// signals:
//     void nameChanged(const QString &name);

// private:
//     Model *m_model;
// };

// // Представление (View)
// class View : public QWidget {
//     Q_OBJECT
// public:
//     View(ViewModel *viewModel, QWidget *parent = nullptr) : QWidget(parent), m_viewModel(viewModel) {
//         QVBoxLayout *layout = new QVBoxLayout(this);
//         m_nameLabel = new QLabel("Name:");
//         layout->addWidget(m_nameLabel);
//         m_nameLineEdit = new QLineEdit;
//         layout->addWidget(m_nameLineEdit);
//         m_greetButton = new QPushButton("Greet");
//         layout->addWidget(m_greetButton);

//         connect(m_nameLineEdit, &QLineEdit::textChanged, this, &View::updateName);
//         connect(m_greetButton, &QPushButton::clicked, this, &View::greet);
//         connect(m_viewModel, &ViewModel::nameChanged, this, &View::updateNameLabel);
//     }

// public slots:
//     void updateName() {
//         QString name = m_nameLineEdit->text();
//         m_viewModel->setName(name);
//     }

//     void greet() {
//         QString name = m_viewModel->name();
//         QMessageBox::information(this, "Greeting", QString("Hello, %1!").arg(name));
//     }

//     void updateNameLabel(const QString &name) {
//         m_nameLabel->setText(QString("Name: %1").arg(name));
//     }

// private:
//     ViewModel *m_viewModel;

//     QLabel *m_nameLabel;
//     QLineEdit *m_nameLineEdit;
//     QPushButton *m_greetButton;
// };

#endif