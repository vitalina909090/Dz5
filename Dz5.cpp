#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

class Reservoir {
private:
    string name;
    double width;
    double length;
    double maximumDepth;
    string type;

public:
    Reservoir() : name(" - "), width(0), length(0), maximumDepth(0), type(" - ") {}

    explicit Reservoir(const string& name, double width, double length, double maximumDepth, const string& type)
    : name(name), width(width), length(length), maximumDepth(maximumDepth), type(type) {}

    Reservoir(const Reservoir& other)
    : name(other.name), width(other.width), length(other.length), maximumDepth(other.maximumDepth), type(other.type) {}

    double approximateVolume() const {
        return width * length * maximumDepth;
    }

    double surfaceArea() const {
        return width * length;
    }

    bool typeChecking(const Reservoir& other) const {
        return this->type == other.type;
    }

    bool surfaceAreaComparison(const Reservoir& other) const {
        if (typeChecking(other)) {
            return this->surfaceArea() > other.surfaceArea();
        }
        return false;
    }

    string getName() const { return name; }
    double getWidth() const { return width; }
    double getLength() const { return length; }
    double getMaximumDepth() const { return maximumDepth; }
    string getType() const { return type; }

    void setName(const string& name) { this->name = name; }
    void setWidth(double width) { this->width = width; }
    void setLength(double length) { this->length = length; }
    void setMaximumDepth(double maximumDepth) { this->maximumDepth = maximumDepth; }
    void setType(const string& type) { this->type = type; }

    void information() const {
        cout << "Назва: " << name << "\nТип: " << type <<"\nШирина: " << width << " м" <<"\nДовжина: " << length << " м" << "\nМаксимальна глибина: " << maximumDepth << " м" << "\nПлоща водної поверхні: " << surfaceArea() << " м^2" <<"\nОбсяг водойми: " << approximateVolume() << " м^3" << endl;
    }

    void write(ofstream& file) const {
        file << name << " " << type << " " << width << " " << length << " " << maximumDepth << endl;
    }
};

void addition(Reservoir*& reservoirs, int& size) {
    string name, type;
    double width, length, maximumDepth;

    cout << "Введіть назву водойми: ";
    cin >> name;
    cout << "Введіть тип водойми: ";
    cin >> type;
    cout << "Введіть ширину: ";
    cin >> width;
    cout << "Введіть довжину: ";
    cin >> length;
    cout << "Введіть максимальну глибину: ";
    cin >> maximumDepth;

    Reservoir* newReservoirs = new Reservoir[size + 1];

    for (int i = 0; i < size; i++) {
        newReservoirs[i] = reservoirs[i];
    }

    newReservoirs[size] = Reservoir(name, width, length, maximumDepth, type);

    delete[] reservoirs;

    reservoirs = newReservoirs;
    size++;
}


void deletion(Reservoir*& reservoirs, int& size, int index) {
    if (index >= 0 && index < size) {
        Reservoir* newReservoirs = new Reservoir[size - 1];

        for (int i = 0, j = 0; i < size; i++) {
            if (i != index) {
                newReservoirs[j] = reservoirs[i];
                j++;
            }
        }

        delete[] reservoirs;

        reservoirs = newReservoirs;
        size--;

        cout << "Водойму успішно видалено" << endl;
    }
    else {
        cout << "Невірний індекс" << endl;
    }
}

void save(Reservoir* reservoirs, int size, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; i++) { 
            reservoirs[i].write(file);
        }
        file.close();
        cout << "Дані успішно записано в файл" << endl;
    }
    else {
        cout << "Не вдалося відкрити файл для запису" << endl;
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int size = 0;
    Reservoir* reservoirs = nullptr;
    int choice;

    do {
        cout << "\nМеню:\n"
            << "1. Додати водойму\n"
            << "2. Видалити водойму\n"
            << "3. Вивести інформацію про всі водойми\n"
            << "4. Зберегти інформацію у текстовий файл\n"
            << "5. Порівняти площу водної поверхні\n"
            << "0. Вийти\n"
            << "Ваш вибір: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addition(reservoirs, size);
            break;
        case 2: {
            int index;
            cout << "Введіть індекс водойми для видалення: ";
            cin >> index;
            deletion(reservoirs, size, index - 1);
            break;
        }
        case 3:
            for (int i = 0; i < size; i++) {
                cout << "\nВодойма №" << i + 1 << ":\n";
                reservoirs[i].information();
            }
            break;
        case 4:
            save(reservoirs, size, "reservoirs.txt");
            break;
        case 5: {
            int index1, index2;
            cout << "Введіть індекс першої водойми для порівняння: ";
            cin >> index1;
            cout << "Введіть індекс другої водойми для порівняння: ";
            cin >> index2;

            if (index1 >= 1 && index1 <= size && index2 >= 1 && index2 <= size) {
                if (!reservoirs[index1 - 1].typeChecking(reservoirs[index2 - 1])) {
                    cout << "Типи водойм різні. Порівняння неможливе\n";
                }
                else {
                    double area1 = reservoirs[index1 - 1].surfaceArea();
                    double area2 = reservoirs[index2 - 1].surfaceArea();

                    cout << "Площа водойми №" << index1 << " = " << area1 << " м^2\n";
                    cout << "Площа водойми №" << index2 << " = " << area2 << " м^2\n";

                    if (area1 > area2) {
                        cout << "Водойма №" << index1 << " більша, ніж водойма №" << index2 << "\n";
                    }
                    else if (area1 < area2) {
                        cout << "Водойма №" << index2 << " більша, ніж водойма №" << index1 << "\n";
                    }
                    else {
                        cout << "Водойми однакові за площею\n";
                    }
                }
            }
            else {
                cout << "Невірні індекси\n";
            }
            break;
        }
        case 0:
            cout << "Вихід з програми\n";
            break;
        default:
            cout << "Невірний вибір\n";
            break;
        }
    } while (choice != 0);

    delete[] reservoirs;

    return 0;
}