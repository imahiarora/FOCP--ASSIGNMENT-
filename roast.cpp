#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <stdexcept>
#include <thread>
#include <chrono>

// ── Helpers ───────────────────────────────────────────────────────────────────

bool isBlank(const std::string& s) {
    for (size_t i = 0; i < s.size(); ++i)
        if (!isspace(static_cast<unsigned char>(s[i]))) return false;
    return true;
}

bool isLettersOnly(const std::string& s) {
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (!isalpha(static_cast<unsigned char>(c)) && !isspace(static_cast<unsigned char>(c)))
            return false;
    }
    return true;
}

std::string toLower(const std::string& s) {
    std::string result = s;
    for (size_t i = 0; i < result.size(); ++i)
        result[i] = static_cast<char>(tolower(static_cast<unsigned char>(result[i])));
    return result;
}

std::string applyName(const std::string& roast, const std::string& name) {
    const std::string placeholder = "{name}";
    std::string result = roast;
    size_t pos = 0;
    while ((pos = result.find(placeholder, pos)) != std::string::npos) {
        result.replace(pos, placeholder.length(), name);
        pos += name.length();
    }
    return result;
}

int pickNewIndex(int lastIndex, int total) {
    if (total == 1) return 0;
    int index;
    do { index = rand() % total; } while (index == lastIndex);
    return index;
}

// ── UI helpers ────────────────────────────────────────────────────────────────

const int WIDTH = 48;

// Print a full-width line of a repeated character
void printLine(char c = '=') {
    std::cout << std::string(WIDTH, c) << "\n";
}

// Print text centred within WIDTH
void printCentered(const std::string& text) {
    int padding = (WIDTH - static_cast<int>(text.size())) / 2;
    if (padding < 0) padding = 0;
    std::cout << std::string(padding, ' ') << text << "\n";
}

// Dramatic pause + animated dots
void dramaticPause() {
    std::cout << "\n  Preparing your roast";
    std::cout.flush();
    for (int i = 0; i < 3; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
        std::cout << " .";
        std::cout.flush();
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\n";
}

// ── Main ──────────────────────────────────────────────────────────────────────

int main() {
    try {
        srand(static_cast<unsigned int>(time(0)));

        // ── Roast categories ─────────────────────────────────────────────────
        std::map<std::string, std::vector<std::string> > categories;

        std::vector<std::string> coding;
        coding.push_back("{name}, your code is so bad even the compiler files complaints with HR.");
        coding.push_back("I've seen better logic in a 'Hello World' program, {name}.");
        coding.push_back("{name}, your Git history looks like a crime scene with no detective.");
        coding.push_back("They say code never lies, {name} — yours just screams for help.");
        coding.push_back("{name}, you don't fix bugs, you just give them better hiding spots.");
        coding.push_back("Your variable names, {name}, make abstract art look self-explanatory.");
        coding.push_back("{name}, Stack Overflow flagged your questions as a public health hazard.");
        coding.push_back("I've seen spaghetti with better structure than your codebase, {name}.");
        coding.push_back("{name}, the only thing your code ships on time is confusion.");
        coding.push_back("Your pull requests, {name}, are the reason reviewers drink.");
        categories["coding"] = coding;

        std::vector<std::string> laziness;
        laziness.push_back("{name}, you didn't get out of bed today — and honestly, neither did your ambition.");
        laziness.push_back("Scientists studied {name}'s daily routine and officially classified it as hibernation.");
        laziness.push_back("{name}, your idea of a workout is reaching for the TV remote.");
        laziness.push_back("I asked {name} for help moving. They sent their thoughts and prayers.");
        laziness.push_back("{name}, your to-do list has been 'pending' since 2019.");
        laziness.push_back("The only thing {name} runs is out of excuses.");
        laziness.push_back("{name}, you treat deadlines like suggestions and effort like a myth.");
        laziness.push_back("NASA once asked {name} to study inertia. They declined — too much effort.");
        laziness.push_back("{name}, your spirit animal is a loading bar stuck at 2%.");
        laziness.push_back("If procrastination were an Olympic sport, {name} would get around to winning eventually.");
        categories["laziness"] = laziness;

        std::vector<std::string> general;
        general.push_back("Hey {name}, I'd roast you, but my mom said I'm not allowed to burn trash.");
        general.push_back("{name}, you're the reason they put instructions on shampoo bottles.");
        general.push_back("I'd explain it to you, {name}, but I left my crayons at home.");
        general.push_back("{name}, if brains were gasoline, you wouldn't have enough to power a go-kart around a Cheerio.");
        general.push_back("You know, {name}, some people are like clouds — when they disappear, it's a beautiful day.");
        general.push_back("Calling you an idiot would be an insult to idiots, {name}.");
        general.push_back("Don't worry, {name} — even garbage gets picked up eventually.");
        general.push_back("You're not stupid, {name} — you just have bad luck thinking.");
        general.push_back("I envy people who've never met you, {name}.");
        general.push_back("{name}, you bring everyone so much joy — the moment you leave the room.");
        categories["general"] = general;

        if (categories.empty())
            throw std::runtime_error("Category map is empty — nothing to serve!");

        // ── Welcome banner ───────────────────────────────────────────────────
        std::cout << "\n";
        printLine('=');
        printCentered("*  THE ROAST MACHINE 3000  *");
        printLine('=');
        printCentered("Where dignity goes to die.");
        printLine('-');
        std::cout << "\n";

        // ── Name input ───────────────────────────────────────────────────────
        std::string name;
        while (true) {
            std::cout << "  Enter your name (if you dare): ";
            if (!std::getline(std::cin, name))
                throw std::runtime_error("Unexpected end of input while reading name.");

            if (isBlank(name)) {
                std::cout << "  Error: Name cannot be empty. Please try again.\n";
                continue;
            }
            if (!isLettersOnly(name)) {
                std::cout << "  Error: Name must contain letters only.\n";
                continue;
            }
            break;
        }

        // ── Category input ───────────────────────────────────────────────────
        std::string category;
        while (true) {
            std::cout << "  Choose a category (coding / laziness / general): ";
            if (!std::getline(std::cin, category))
                throw std::runtime_error("Unexpected end of input while reading category.");

            category = toLower(category);
            if (isBlank(category) || categories.find(category) == categories.end()) {
                std::cout << "  Error: Invalid category. Choose coding, laziness, or general.\n";
                continue;
            }
            break;
        }

        // ── Roast loop ───────────────────────────────────────────────────────
        std::vector<std::string>& pool = categories[category];
        int lastIndex  = -1;
        int roastCount =  0;

        while (true) {
            // Dramatic pause with animated dots
            dramaticPause();

            int index  = pickNewIndex(lastIndex, static_cast<int>(pool.size()));
            lastIndex  = index;
            ++roastCount;

            std::string roast = applyName(pool[index], name);

            std::cout << "\n";
            printLine('=');
            printCentered("[ " + category + " ] ROAST #" + std::to_string(roastCount));
            printLine('=');
            std::cout << "\n  " << roast << "\n\n";
            printLine('-');
            printCentered("^ No feelings were spared. ^");
            printLine('-');

            // ── Replay prompt ─────────────────────────────────────────────
            while (true) {
                std::cout << "\n  Want another roast? (y/n): ";

                std::string choice;
                if (!std::getline(std::cin, choice))
                    throw std::runtime_error("Unexpected end of input while reading choice.");

                if (choice == "y" || choice == "Y") {
                    break;
                } else if (choice == "n" || choice == "N") {

                    // ── Goodbye banner ────────────────────────────────────
                    std::cout << "\n";
                    printLine('=');
                    printCentered("SESSION COMPLETE");
                    printLine('=');
                    printCentered("Victim : " + name);
                    printCentered("Category: " + category);
                    printCentered("Roasts delivered: " + std::to_string(roastCount));
                    printLine('-');
                    printCentered("Goodbye, " + name + "!");
                    printCentered("May your WiFi be strong & your ego recover.");
                    printLine('=');
                    std::cout << "\n";
                    return 0;

                } else {
                    std::cout << "  Error: Invalid choice. Enter y or n only.\n";
                }
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "\n[Unexpected Error] " << e.what() << "\n";
        std::cerr << "The Roast Machine has crashed. How fitting.\n";
        return 1;
    }

    return 0;
}