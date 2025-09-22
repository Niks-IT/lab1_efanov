#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <iomanip>

using namespace std;

struct Pipeline {
    string name;
    double length_km;
    int diameter_mm;
    bool under_repair;
};

struct CompressorStation {
    string name;
    int workshop_count;
    int active_workshops;
    int station_class;
};

// Функции валидации ввода
int getIntegerInput(const string& prompt) {
    int value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка! Введите целое число: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

double getDoubleInput(const string& prompt) {
    double value;
    cout << prompt;
    while (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка! Введите число: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

int getPositiveInteger(const string& prompt) {
    int value;
    while (true) {
        value = getIntegerInput(prompt);
        if (value > 0) return value;
        cout << "Ошибка! Значение должно быть положительным. Попробуйте снова: ";
    }
}

double getPositiveDouble(const string& prompt) {
    double value;
    while (true) {
        value = getDoubleInput(prompt);
        if (value > 0) return value;
        cout << "Ошибка! Значение должно быть положительным. Попробуйте снова: ";
    }
}

bool getConfirmation(const string& prompt) {
    string input;
    while (true) {
        cout << prompt << " (y/n): ";
        getline(cin, input);
        if (input == "y" || input == "Y") return true;
        if (input == "n" || input == "N") return false;
        cout << "Ошибка! Введите 'y' или 'n': ";
    }
}

// Основные функции программы
void displayMainMenu() {
    cout << "\n=== Система управления трубопроводом ===" << endl;
    cout << "1. Добавить трубопровод" << endl;
    cout << "2. Добавить компрессорную станцию" << endl;
    cout << "3. Просмотр всех объектов" << endl;
    cout << "4. Редактировать трубопровод" << endl;
    cout << "5. Редактировать компрессорную станцию" << endl;
    cout << "6. Сохранить данные" << endl;
    cout << "7. Загрузить данные" << endl;
    cout << "0. Завершение работы" << endl;
    cout << "Выберите действие: ";
}

void createPipeline(Pipeline& pipe) {
    cout << "\n=== Создание трубопровода ===" << endl;
    cout << "Введите название трубопровода: ";
    getline(cin, pipe.name);
    pipe.length_km = getPositiveDouble("Введите длину трубопровода (км): ");
    pipe.diameter_mm = getPositiveInteger("Введите диаметр трубопровода (мм): ");
    pipe.under_repair = false;
    cout << "Трубопровод успешно создан!" << endl;
}

void createStation(CompressorStation& station) {
    cout << "\n=== Создание компрессорной станции ===" << endl;
    cout << "Введите название станции: ";
    getline(cin, station.name);
    station.workshop_count = getPositiveInteger("Введите общее количество цехов: ");

    while (true) {
        station.active_workshops = getIntegerInput("Введите количество активных цехов: ");
        if (station.active_workshops >= 0 && station.active_workshops <= station.workshop_count) break;
        cout << "Ошибка! Количество активных цехов должно быть от 0 до "
            << station.workshop_count << ". Попробуйте снова." << endl;
    }

    station.station_class = getPositiveInteger("Введите класс станции: ");
    cout << "Компрессорная станция успешно создана!" << endl;
}

void displayObjects(const Pipeline& pipe, const CompressorStation& station) {
    cout << "\n=== Обзор объектов ===" << endl;

    cout << "--- Трубопровод ---" << endl;
    if (pipe.name.empty()) {
        cout << "Трубопровод не создан" << endl;
    }
    else {
        cout << "Название: " << pipe.name << endl;
        cout << "Длина: " << pipe.length_km << " км" << endl;
        cout << "Диаметр: " << pipe.diameter_mm << " мм" << endl;
        cout << "Состояние: " << (pipe.under_repair ? "В ремонте" : "Работает") << endl;
    }

    cout << "\n--- Компрессорная станция ---" << endl;
    if (station.name.empty()) {
        cout << "Станция не создана" << endl;
    }
    else {
        cout << "Название: " << station.name << endl;
        cout << "Всего цехов: " << station.workshop_count << endl;
        cout << "Активных цехов: " << station.active_workshops << endl;
        cout << "Класс станции: " << station.station_class << endl;
        cout << "Процент активных цехов: " << fixed << setprecision(1)
            << (station.workshop_count > 0 ? (100.0 * station.active_workshops / station.workshop_count) : 0)
            << "%" << endl;
    }
}

void modifyPipeline(Pipeline& pipe) {
    if (pipe.name.empty()) {
        cout << "Ошибка! Сначала создайте трубопровод." << endl;
        return;
    }

    cout << "\n=== Редактирование трубопровода ===" << endl;
    cout << "Текущие параметры:" << endl;
    cout << "Название: " << pipe.name << endl;
    cout << "Длина: " << pipe.length_km << " км" << endl;
    cout << "Диаметр: " << pipe.diameter_mm << " мм" << endl;
    cout << "Состояние: " << (pipe.under_repair ? "В ремонте" : "Работает") << endl;

    cout << "\nВарианты действий:" << endl;
    cout << "1. Изменить статус ремонта" << endl;
    cout << "2. Обновить все параметры" << endl;
    cout << "0. Отменить действие" << endl;

    int option = getIntegerInput("Выберите действие: ");
    switch (option) {
    case 1:
        pipe.under_repair = !pipe.under_repair;
        cout << "Статус изменен: " << (pipe.under_repair ? "В ремонте" : "Работает") << endl;
        break;
    case 2:
        cout << "Введите новое название: ";
        getline(cin, pipe.name);
        pipe.length_km = getPositiveDouble("Введите новую длину (км): ");
        pipe.diameter_mm = getPositiveInteger("Введите новый диаметр (мм): ");
        cout << "Параметры трубопровода обновлены!" << endl;
        break;
    case 0:
        cout << "Редактирование отменено." << endl;
        break;
    default:
        cout << "Неверный выбор. Действие отменено." << endl;
    }
}

void modifyStation(CompressorStation& station) {
    if (station.name.empty()) {
        cout << "Ошибка! Сначала создайте станцию." << endl;
        return;
    }

    cout << "\n=== Редактирование станции ===" << endl;
    cout << "Текущие параметры:" << endl;
    cout << "Название: " << station.name << endl;
    cout << "Всего цехов: " << station.workshop_count << endl;
    cout << "Активных цехов: " << station.active_workshops << endl;
    cout << "Класс станции: " << station.station_class << endl;

    cout << "\nВарианты действий:" << endl;
    cout << "1. Активировать цех" << endl;
    cout << "2. Деактивировать цех" << endl;
    cout << "3. Обновить все параметры" << endl;
    cout << "0. Отменить действие" << endl;

    int option = getIntegerInput("Выберите действие: ");
    switch (option) {
    case 1:
        if (station.active_workshops < station.workshop_count) {
            station.active_workshops++;
            cout << "Цех активирован. Активных цехов: " << station.active_workshops << endl;
        }
        else {
            cout << "Ошибка! Все цехи уже активны." << endl;
        }
        break;
    case 2:
        if (station.active_workshops > 0) {
            station.active_workshops--;
            cout << "Цех деактивирован. Активных цехов: " << station.active_workshops << endl;
        }
        else {
            cout << "Ошибка! Нет активных цехов для деактивации." << endl;
        }
        break;
    case 3:
        cout << "Введите новое название: ";
        getline(cin, station.name);
        station.workshop_count = getPositiveInteger("Введите общее количество цехов: ");

        while (true) {
            station.active_workshops = getIntegerInput("Введите количество активных цехов: ");
            if (station.active_workshops >= 0 && station.active_workshops <= station.workshop_count) break;
            cout << "Ошибка! Количество активных цехов должно быть от 0 до "
                << station.workshop_count << ". Попробуйте снова." << endl;
        }

        station.station_class = getPositiveInteger("Введите класс станции: ");
        cout << "Параметры станции обновлены!" << endl;
        break;
    case 0:
        cout << "Редактирование отменено." << endl;
        break;
    default:
        cout << "Неверный выбор. Действие отменено." << endl;
    }
}

void saveData(const Pipeline& pipe, const CompressorStation& station) {
    ofstream dataFile("pipeline_data.txt");
    if (!dataFile.is_open()) {
        cout << "Ошибка создания файла!" << endl;
        return;
    }

    dataFile << "PIPELINE" << endl;
    dataFile << pipe.name << endl;
    dataFile << pipe.length_km << endl;
    dataFile << pipe.diameter_mm << endl;
    dataFile << pipe.under_repair << endl;

    dataFile << "STATION" << endl;
    dataFile << station.name << endl;
    dataFile << station.workshop_count << endl;
    dataFile << station.active_workshops << endl;
    dataFile << station.station_class << endl;

    dataFile.close();
    cout << "Данные сохранены в файл 'pipeline_data.txt'" << endl;
}

void loadData(Pipeline& pipe, CompressorStation& station) {
    ifstream dataFile("pipeline_data.txt");
    if (!dataFile.is_open()) {
        cout << "Ошибка! Файл не найден." << endl;
        return;
    }

    string line;
    string section;

    try {
        getline(dataFile, section);
        if (section != "PIPELINE") throw runtime_error("Неверный формат файла");

        getline(dataFile, pipe.name);
        getline(dataFile, line);
        pipe.length_km = stod(line);
        getline(dataFile, line);
        pipe.diameter_mm = stoi(line);
        getline(dataFile, line);
        pipe.under_repair = (line == "1");

        getline(dataFile, section);
        if (section != "STATION") throw runtime_error("Неверный формат файла");

        getline(dataFile, station.name);
        getline(dataFile, line);
        station.workshop_count = stoi(line);
        getline(dataFile, line);
        station.active_workshops = stoi(line);
        getline(dataFile, line);
        station.station_class = stoi(line);

        dataFile.close();
        cout << "Данные загружены из файла 'pipeline_data.txt'" << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка загрузки: " << e.what() << endl;
        dataFile.close();
        pipe = Pipeline();
        station = CompressorStation();
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    Pipeline pipeline;
    CompressorStation station;
    int choice;

    while (true) {
        displayMainMenu();
        choice = getIntegerInput("");

        switch (choice) {
        case 1:
            createPipeline(pipeline);
            break;
        case 2:
            createStation(station);
            break;
        case 3:
            displayObjects(pipeline, station);
            break;
        case 4:
            modifyPipeline(pipeline);
            break;
        case 5:
            modifyStation(station);
            break;
        case 6:
            saveData(pipeline, station);
            break;
        case 7:
            loadData(pipeline, station);
            break;
        case 0:
            cout << "Завершение работы программы..." << endl;
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }

    return 0;
}