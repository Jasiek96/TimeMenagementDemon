#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <limits>
#include <algorithm>

#include <EventManager.h>
#include <Event_task.h>
#include <Event_meeting.h>
#include <DateTime.h>

// -------------------- Pomocnicze I/O --------------------

static void clearCinLine()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static std::string askLine(const std::string &prompt)
{
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

static int askInt(const std::string &prompt, int minV, int maxV)
{
    while (true)
    {
        std::cout << prompt;
        int v;
        if (std::cin >> v)
        {
            if (v >= minV && v <= maxV)
            {
                clearCinLine();
                return v;
            }
            std::cout << "Wartość poza zakresem [" << minV << ", " << maxV << "]. Spróbuj ponownie.\n";
        }
        else
        {
            std::cout << "Niepoprawna liczba. Spróbuj ponownie.\n";
            std::cin.clear();
            clearCinLine();
        }
    }
}

static bool askBool01(const std::string &prompt)
{
    while (true)
    {
        std::cout << prompt << " (0/1): ";
        int b;
        if (std::cin >> b)
        {
            clearCinLine();
            if (b == 0)
                return false;
            if (b == 1)
                return true;
        }
        else
        {
            std::cin.clear();
            clearCinLine();
        }
        std::cout << "Wpisz 0 lub 1.\n";
    }
}

// YYYY-MM-DD HH:MM[:SS] -> DateTime(y,m,d,H,M,S)
static bool parseDateTime(const std::string &s, DateTime &out)
{
    // Prosty parser: dopuszczamy "YYYY-MM-DD HH:MM" lub "YYYY-MM-DD HH:MM:SS"
    int y, m, d, H, M, S = 0;

    // znajdź separator spacji
    auto pos = s.find(' ');
    if (pos == std::string::npos)
        return false;

    std::string date = s.substr(0, pos);
    std::string time = s.substr(pos + 1);

    char dash1, dash2, colon1, colon2;
    std::istringstream ds(date), ts(time);

    if (!(ds >> y >> dash1 >> m >> dash2 >> d) || dash1 != '-' || dash2 != '-')
        return false;

    if (!(ts >> H >> colon1 >> M))
        return false;
    if (colon1 != ':')
        return false;

    if (ts.peek() == ':')
    {
        ts.get();
        if (!(ts >> S))
            return false;
    }

    try
    {
        out = DateTime(y, m, d, H, M, S);
        return true;
    }
    catch (const std::exception &e)
    {
        std::cout << "Błąd tworzenia DateTime: " << e.what() << "\n";
        return false;
    }
}

static DateTime askDateTime()
{
    while (true)
    {
        std::string line = askLine("Data i czas (YYYY-MM-DD HH:MM[:SS]): ");
        DateTime dt(1970, 1, 1, 0, 0, 0);
        if (parseDateTime(line, dt))
            return dt;
        std::cout << "Niepoprawny format daty/czasu. Spróbuj ponownie.\n";
    }
}

static std::vector<std::string> splitCSV(const std::string &line)
{
    std::vector<std::string> items;
    std::string item;
    std::istringstream ss(line);
    while (std::getline(ss, item, ','))
    {
        auto l = item.find_first_not_of(" \t");
        auto r = item.find_last_not_of(" \t");
        if (l == std::string::npos)
        {
            items.emplace_back();
        }
        else
        {
            items.emplace_back(item.substr(l, r - l + 1));
        }
    }
    while (!items.empty() && items.back().empty())
        items.pop_back();
    return items;
}

static void actionAddTask(EventManager &manager)
{
    std::string name = askLine("Nazwa: ");
    std::string desc = askLine("Opis: ");
    DateTime dt = askDateTime();
    int prio = askInt("Priorytet (1-5): ", 1, 5);
    bool notify = askBool01("Powiadomienie");

    try
    {
        auto ptr = std::make_unique<Task>(name, desc, dt, prio, notify);
        manager.add(std::move(ptr));
        std::cout << "Dodano Task.\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "Błąd dodawania Task: " << e.what() << "\n";
    }
}

static void actionAddMeeting(EventManager &manager)
{
    std::string name = askLine("Nazwa: ");
    std::string desc = askLine("Opis: ");
    DateTime dt = askDateTime();
    std::string location = askLine("Lokalizacja: ");
    std::string attendeesLine = askLine("Uczestnicy (oddziel przecinkami): ");
    auto attendees = splitCSV(attendeesLine);
    int prio = askInt("Priorytet (1-5): ", 1, 5);
    bool notify = askBool01("Powiadomienie");

    try
    {
        auto ptr = std::make_unique<Meeting>(name, desc, dt, location, attendees, prio, notify);
        manager.add(std::move(ptr));
        std::cout << "Dodano Meeting.\n";
    }
    catch (const std::exception &e)
    {
        std::cout << "Błąd dodawania Meeting: " << e.what() << "\n";
    }
}

static void actionList(const EventManager &manager)
{
    manager.list(std::cout);
}

static void actionSortByDate(EventManager &manager)
{
    manager.sortByDate();
    std::cout << "Posortowano po dacie (rosnąco).\n";
}

static void actionSortByName(EventManager &manager)
{
    manager.sortByName();
    std::cout << "Posortowano po nazwie (A→Z).\n";
}

static void actionFindByName(EventManager &manager)
{
    std::string name = askLine("Podaj nazwę do wyszukania: ");
    auto *ev = manager.findByName(name);
    if (ev)
    {
        std::cout << "Znaleziono: ";
        ev->display();
        std::cout << "\n";
    }
    else
    {
        std::cout << "Brak wydarzenia o nazwie: " << name << "\n";
    }
}

static void actionRemoveLowPriority(EventManager &manager)
{
    int threshold = askInt("Usuń wydarzenia o priorytecie ≤ (1-5): ", 1, 5);
    auto removed = manager.removeIf([&](const Event &e)
                                    { return e.getPriority() <= threshold; });
    std::cout << "Usunięto " << removed << " wydarzeń.\n";
}

static void printMenu()
{
    std::cout << "\n=== EVENT MANAGER ===\n"
              << "1. Dodaj Task\n"
              << "2. Dodaj Meeting\n"
              << "3. Wypisz wszystkie wydarzenia\n"
              << "4. Posortuj po dacie\n"
              << "5. Posortuj po nazwie\n"
              << "6. Znajdź po nazwie\n"
              << "7. Usuń wg priorytetu (≤)\n"
              << "8. Wyjście\n\n"
              << "Wybór: ";
}

int main()
{
    EventManager manager;

    auto DT = [](int y, int m, int d, int H, int M, int S = 0)
    { return DateTime(y, m, d, H, M, S); };

    manager.add(std::make_unique<Task>(
        "Oddać projekt OOP",
        "Zaliczenie z OOP – finalny commit",
        DT(2025, 9, 12, 9, 0, 0),
        4, true));

    manager.add(std::make_unique<Meeting>(
        "Stand-up zespołu",
        "Codzienny status + blokery",
        DT(2025, 9, 11, 10, 0, 0),
        "Room 101",
        std::vector<std::string>{"Ala", "Ola", "Marek"},
        3, true));

    manager.add(std::make_unique<Task>(
        "Pomiary P-XRD",
        "Seria próbek 05–12",
        DT(2025, 10, 1, 7, 30, 0),
        3, false));

    manager.add(std::make_unique<Meeting>(
        "Spotkanie z promotorem",
        "Omówienie postępów i planów",
        DT(2025, 10, 5, 16, 45, 0),
        "Gabinet 204",
        std::vector<std::string>{"Ja", "Promotor"},
        5, true));

    manager.add(std::make_unique<Task>(
        "Rozdział dysertacji",
        "Szkic rozdziału o termometrii",
        DT(2025, 9, 20, 12, 0, 0),
        5, false));

    manager.add(std::make_unique<Meeting>(
        "Seminarium zespołu",
        "Prezentacje tygodniowe",
        DT(2025, 9, 18, 13, 15, 0),
        "A-1.23",
        std::vector<std::string>{"Zespół NMM"},
        3, false));

    manager.add(std::make_unique<Task>(
        "Raport z laboratoriów",
        "Sprawozdanie z ćwiczenia 7",
        DT(2025, 10, 12, 23, 59, 0),
        4, true));

    manager.add(std::make_unique<Meeting>(
        "Kolokwium grupowe",
        "Omówienie pytań i zakresu",
        DT(2025, 11, 2, 15, 0, 0),
        "Sala 3",
        std::vector<std::string>{"Grupa A", "Grupa B"},
        4, true));

    manager.add(std::make_unique<Task>(
        "Prezentacja na seminarium",
        "Slajdy + wstępne demo",
        DT(2025, 9, 25, 18, 0, 0),
        3, false));

    manager.add(std::make_unique<Task>(
        "Plan badań 2026",
        "Kamienie milowe + konferencje",
        DT(2026, 1, 10, 9, 30, 0),
        2, false));

    while (true)
    {
        printMenu();
        int choice;
        if (!(std::cin >> choice))
        {
            std::cin.clear();
            clearCinLine();
            std::cout << "Niepoprawny wybór.\n";
            continue;
        }
        clearCinLine();

        switch (choice)
        {
        case 1:
            actionAddTask(manager);
            break;
        case 2:
            actionAddMeeting(manager);
            break;
        case 3:
            actionList(manager);
            break;
        case 4:
            actionSortByDate(manager);
            break;
        case 5:
            actionSortByName(manager);
            break;
        case 6:
            actionFindByName(manager);
            break;
        case 7:
            actionRemoveLowPriority(manager);
            break;
        case 8:
            std::cout << "Do zobaczenia!\n";
            return 0;
        default:
            std::cout << "Nie ma takiej opcji.\n";
            break;
        }
    }
}
