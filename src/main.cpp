#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QDateTime>
#include <QDialog>
#include <QInputDialog>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QStack>
#include <QProcess>
#include <QList>
#include <QTimer>
#include <QTextEdit>
#include <QObject>
#include <QDesktopServices>
#include <QUrl>

class Message {
public:
    QString text;
    QString sender;
    QDateTime timestamp;
};

void setWindowSize(QMainWindow& window, int width, int height) {
    window.resize(width, height);
}

void setChatBoxSize(QTextEdit* chatBox, int width, int height) {
    chatBox->setFixedSize(width, height);
}

void setHistoryWindowSize(QDialog& dialog, int width, int height) { dialog.resize(width, height); }

void addMessageToHistory(QList<Message>& messageHistory, const QString& sender, const QString& text) {
    Message newMessage;
    newMessage.text = text;
    newMessage.sender = sender;
    newMessage.timestamp = QDateTime::currentDateTime();
    messageHistory.append(newMessage);
}

void displayMessage(QTextEdit* chatBox, const QString& sender, const QString& text) {
    if (sender == "Bot") {
        chatBox->append(sender + ": " + text);
    } else {
        chatBox->append(sender + ": " + text);
    }
}


bool isOperator(const QChar &op) {
    return op == '+' || op == '-' || op == '*' || op == '/';
}

double evaluateExpression(const QString &expression) {
    QStack<double> operands;
    QStack<QChar> operators;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i].isDigit() || expression[i] == '.') {
            QString number;
            while (i < expression.length() && (expression[i].isDigit() || expression[i] == '.')) {
                number.append(expression[i]);
                i++;
            }
            operands.push(number.toDouble());
            i--;
        } else if (isOperator(expression[i])) {
            while (!operators.isEmpty() && ((expression[i] == '+' || expression[i] == '-') &&
                    (operators.top() == '*' || operators.top() == '/'))) {
                double operand2 = operands.pop();
                double operand1 = operands.pop();
                QChar op = operators.pop();
                double result;
                if (op == '+') {
                    result = operand1 + operand2;
                } else if (op == '-') {
                    result = operand1 - operand2;
                } else if (op == '*') {
                    result = operand1 * operand2;
                } else {
                    result = operand1 / operand2;
                }
                operands.push(result);
            }
            operators.push(expression[i]);
        } else if (expression[i] == '(') {
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            while (operators.top() != '(') {
                double operand2 = operands.pop();
                double operand1 = operands.pop();
                QChar op = operators.pop();
                double result;
                if (op == '+') {
                    result = operand1 + operand2;
                } else if (op == '-') {
                    result = operand1 - operand2;
                } else if (op == '*') {
                    result = operand1 * operand2;
                } else {
                    result = operand1 / operand2;
                }
                operands.push(result);
            }
            operators.pop();
        }
    }

    while (!operators.isEmpty()) {
        double operand2 = operands.pop();
        double operand1 = operands.pop();
        QChar op = operators.pop();
        double result;
        if (op == '+') {
            result = operand1 + operand2;
        } else if (op == '-') {
            result = operand1 - operand2;
        } else if (op == '*') {
            result = operand1 * operand2;
        } else {
            result = operand1 / operand2;
        }
        operands.push(result);
    }

    return operands.pop();
}

void runApplication(const QString& program) {
    QProcess *process = new QProcess();
    process->start(program);
}

void getTime(QTextEdit* chatBox) {
    QDateTime currentTime = QDateTime::currentDateTime();
    chatBox->append("Bot: Текущее время: " + currentTime.toString("hh:mm:ss"));
}
void openLab(QTextEdit* chatBox, QList<Message>& messageHistory) {
    chatBox->append("Bot: Открываю страницу с документацией...");
    QDesktopServices::openUrl(QUrl("https://drive.google.com/file/d/1XPwekfV6TW1L6RAhAGhuOjeLg1av-lI-/view"));
    addMessageToHistory(messageHistory, "Bot", "Открытие страницы с лабораторной работой");
}

void respondToMessage(QTextEdit* chatBox, const QString& messageText, QList<Message>& messageHistory) {
    if (messageText.toLower() == "привет" ) {
        chatBox->append("Bot: Привет!");
        addMessageToHistory(messageHistory, "Bot", "Привет!");
    } else if (messageText.toLower() == "лаба") {
        openLab(chatBox, messageHistory);
    }else if (messageText.toLower() == "steam") {
        chatBox->append("Bot: запуск стима...");
        addMessageToHistory(messageHistory, "Bot", "запуск стима...");
        runApplication("C:\\Program Files (x86)\\Steam\\steam.exe");
    } else if (messageText.toLower() == "opera") {
        chatBox->append("Bot: запуск браузера...");
        addMessageToHistory(messageHistory, "Bot:", "запуск браузера...");
        runApplication("C:\\Users\\mugiv\\AppData\\Local\\Programs\\Opera GX\\launcher.exe");
    } else if (messageText.toLower() == "время") {
       getTime(chatBox);
       addMessageToHistory(messageHistory, "Bot", "Текущее время: " + QDateTime::currentDateTime().toString("hh:mm:ss"));
    } else if (messageText.contains(QRegularExpression("[0-9\\+\\-\\*\\/\\(\\)]+"))) {
        double result = evaluateExpression(messageText);
        chatBox->append("Bot: Результат: " + QString::number(result));
        addMessageToHistory(messageHistory, "Bot", "Результат: " + QString::number(result));
    } else if (messageText.toLower() == "помощь") {
        chatBox->append("Bot: Доступные команды:");
        chatBox->append("1. Привет - поприветствовать бота");
        chatBox->append("2. Steam - запустить Steam");
        chatBox->append("3. Opera - запустить браузер Opera");
        chatBox->append("4. Время - получить текущее время");
        chatBox->append("5. Математическое выражение - вычислить результат выражения");
        chatBox->append("6. Пока - закрытие программы");
        addMessageToHistory(messageHistory, "Bot", "Доступные команды:\n1. Привет \n2. Steam \n3. Opera \n4. Время \n5. Математическое выражение \n 6. Пока");
    } else if (messageText.toLower() == "пока") {
        chatBox->append("Bot: До свидания!");
        addMessageToHistory(messageHistory, "Bot", "До свидания!");
        QTimer::singleShot(1000, [](){ QApplication::exit(); });
    } else {
        chatBox->append("Bot: Извините, я не понимаю ваш запрос.");
        addMessageToHistory(messageHistory, "Bot", "Извините, я не понимаю ваш запрос.");
    }
}


void updateHistoryBox(QTextEdit* historyBox, const QList<Message>& messageHistory) {
    historyBox->clear();
    for (const Message& message : messageHistory) {
        historyBox->append(message.timestamp.toString("dd.MM.yyyy hh:mm:ss") + " - " + message.sender + ": " + message.text);
    }
}

void saveMessageHistory(const QList<Message>& messageHistory, const QString& username) {
    QFile file(username + ".txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Message& message : messageHistory) {
            out << message.timestamp.toString(Qt::ISODate) << "," << message.sender << "," << message.text << "\n";
        }
        file.close();
    }
}

QList<Message> loadMessageHistory(const QString& username) {
    QList<Message> messageHistory;
    QFile file(username + ".txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QStringList parts = in.readLine().split(",");
            if (parts.size() == 3) {
                Message message;
                message.timestamp = QDateTime::fromString(parts[0], Qt::ISODate);
                message.sender = parts[1];
                message.text = parts[2];
                messageHistory.append(message);
            }
        }
        file.close();
    }
    return messageHistory;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString username = QInputDialog::getText(nullptr, "Введите ваше имя", "Пожалуйста введите имя:");

    if(username.isEmpty()) {
        return 0;
    }

    QList<Message> messageHistory = loadMessageHistory(username);

    QObject::connect(&app, &QApplication::aboutToQuit, [&, username]() {
        saveMessageHistory(messageHistory, username);
    });

    QMainWindow window;
    window.setWindowTitle("Chat Bot");
    setWindowSize(window, 800, 600);
    window.setWindowIcon(QIcon("../src/grafic/icon/zxc.jpg"));

    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    QTextEdit *chatBox = new QTextEdit();
    chatBox->setReadOnly(true);

    QLineEdit *inputBox = new QLineEdit();

    QPushButton *sendButton = new QPushButton("Отправить сообщение");
    QPushButton *historyButton = new QPushButton("Посмотреть историю");

    QVBoxLayout *historyLayout = new QVBoxLayout();
    QTextEdit *historyBox = new QTextEdit();
    historyBox->setReadOnly(true);

    layout->addWidget(chatBox);
    layout->addWidget(inputBox);
    layout->addWidget(sendButton);
    layout->addWidget(historyButton);

    widget->setLayout(layout);

    QObject::connect(sendButton, &QPushButton::clicked, [chatBox, inputBox, &messageHistory, historyBox, username]() {
        QString messageText = inputBox->text();
        inputBox->clear();

        addMessageToHistory(messageHistory, username, messageText);
        displayMessage(chatBox, username, messageText);

        respondToMessage(chatBox, messageText, messageHistory);
    });

    QObject::connect(inputBox, &QLineEdit::returnPressed, [sendButton]() {
        sendButton->click();
    });

    QObject::connect(historyButton, &QPushButton::clicked, [historyBox, &messageHistory]() {
        QDialog historyDialog;
        setHistoryWindowSize(historyDialog, 400, 400);
        QVBoxLayout *historyDialogLayout = new QVBoxLayout();
        historyDialogLayout->addWidget(historyBox);
        historyDialog.setLayout(historyDialogLayout);

        updateHistoryBox(historyBox, messageHistory);

        historyDialog.exec();
    });

     QFile styleFile("../src/grafic/style/zxc.qss");
     styleFile.open(QFile::ReadOnly);
     QString styleSheet = QLatin1String(styleFile.readAll());
     app.setStyleSheet(styleSheet);

    window.setCentralWidget(widget);
    window.show();

    return app.exec();
}
