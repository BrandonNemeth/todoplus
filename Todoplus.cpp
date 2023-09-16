#include <iostream>
#include <string>

using namespace std;

// Definición de la estructura de una tarea
struct Task {
    string description;
    int priority;
    string deadline;
    bool completed;
    Task* next;

    // Constructor para inicializar una tarea
    Task(const string& desc, int prio, const string& date)
        : description(desc), priority(prio), deadline(date), completed(false), next(nullptr) {}
};

// Clase para administrar la lista de tareas
class TodoList {
private:
    Task* head; // Puntero al primer elemento de la lista

public:
    TodoList() : head(nullptr) {}

    // Método para agregar una nueva tarea a la lista
    void addTask(const string& desc, int prio, const string& date) {
        Task* newTask = new Task(desc, prio, date);
        if (!head) {
            // Si la lista está vacía, el nuevo elemento será el primero
            head = newTask;
            head->next = head; // Lista circular
        } else {
            // Enlazamos el nuevo elemento al final de la lista
            Task* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newTask;
            newTask->next = head; // Lista circular
        }
        cout << "Tarea agregada con éxito." << endl;
    }

    // Método para marcar una tarea como completada
    void markTaskCompleted(const string& desc) {
        Task* current = head;
        do {
            if (current->description == desc) {
                current->completed = true;
                cout << "Tarea marcada como completada." << endl;
                return;
            }
            current = current->next;
        } while (current != head);
        cout << "Tarea no encontrada." << endl;
    }

    // Método para eliminar una tarea de la lista
    void removeTask(const string& desc) {
        Task* current = head;
        Task* prev = nullptr;
        do {
            if (current->description == desc) {
                if (prev) {
                    prev->next = current->next;
                    if (current == head) {
                        head = current->next;
                    }
                    delete current;
                    cout << "Tarea eliminada con éxito." << endl;
                } else {
                    // Si la tarea a eliminar es la primera de la lista
                    Task* last = head;
                    while (last->next != head) {
                        last = last->next;
                    }
                    last->next = head->next;
                    head = head->next;
                    delete current;
                    cout << "Tarea eliminada con éxito." << endl;
                }
                return;
            }
            prev = current;
            current = current->next;
        } while (current != head);
        cout << "Tarea no encontrada." << endl;
    }

    // Método para mostrar la lista de tareas
    void displayTasks() {
        if (!head) {
            cout << "La lista de tareas está vacía." << endl;
            return;
        }
        Task* current = head;
        cout << "Lista de tareas:" << endl;
        do {
            cout << "Descripción: " << current->description << endl;
            cout << "Prioridad: " << current->priority << endl;
            cout << "Fecha límite: " << current->deadline << endl;
            cout << "Completada: " << (current->completed ? "Sí" : "No") << endl;
            cout << "---------------------" << endl;
            current = current->next;
        } while (current != head);
    }

    // Destructor para liberar la memoria al finalizar
    ~TodoList() {
        while (head) {
            Task* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    TodoList todoList;
    int choice;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Agregar tarea" << endl;
        cout << "2. Marcar tarea como completada" << endl;
        cout << "3. Eliminar tarea" << endl;
        cout << "4. Mostrar lista de tareas" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string desc, date;
                int prio;
                cout << "Descripcion de la tarea: ";
                cin.ignore(); // Limpiar el buffer del teclado
                getline(cin, desc);
                cout << "Prioridad de la tarea (1-10): ";
                cin >> prio;
                cout << "Fecha limite de la tarea: ";
                cin.ignore();
                getline(cin, date);
                todoList.addTask(desc, prio, date);
                break;
            }
            case 2: {
                string desc;
                cout << "Ingrese la descripcion de la tarea completada: ";
                cin.ignore();
                getline(cin, desc);
                todoList.markTaskCompleted(desc);
                break;
            }
            case 3: {
                string desc;
                cout << "Ingrese la descripcion de la tarea a eliminar: ";
                cin.ignore();
                getline(cin, desc);
                todoList.removeTask(desc);
                break;
            }
            case 4:
                todoList.displayTasks();
                break;
            case 5:
                cout << "Saliendo de la aplicacion." << endl;
                break;
            default:
                cout << "Opcion no valida. Por favor, seleccione una opcion valida." << endl;
        }
    } while (choice != 5);

    return 0;
}